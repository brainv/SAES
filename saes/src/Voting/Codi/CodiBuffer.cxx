/**
 * @file CodiBuffer.cxx
 * @brief Body class codi buffer utility
 * @date 28/02/2012
 * @author Yadickson Soto
 */

#include "CodiBuffer.hxx"
#include <cstdio>
#include <sstream>
#include <algorithm>

#define GROUP "\"" ///< field group

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::System;

static const unsigned char arrayEndInit [] =
{
	  0x0A /*LF*/
}; ///< find array end init

static const unsigned char arrayEndResult [] =
{
	  0x0D /*CR*/
	, 0x0A /*LF*/
}; ///< find array end result

static const unsigned char arrayAdd [] =
{
		0x0D /*CR*/
}; ///< array add

static const unsigned char newElement [] =
{
	  0x2C /* , */
	, 0x22 /* " */
	, 0x22 /* " */
}; ///< new element

static const unsigned char arrayRegG [] =
{
	  0x22 /* " */
	, 0x47 /* G */
	, 0x22 /* " */
}; ///< register S

static const unsigned char arrayRegS [] =
{
	  0x22 /* " */
	, 0x53 /* S */
	, 0x22 /* " */
}; ///< register S

static const unsigned char arrayRegL [] =
{
	  0x22 /* " */
	, 0x4C /* L */
	, 0x22 /* " */
}; ///< register L

static const unsigned char arrayRegC [] =
{
	  0x22 /* " */
	, 0x43 /* C */
	, 0x22 /* " */
}; ///< register C

static const unsigned char arrayRegH [] =
{
	  0x22 /* " */
	, 0x48 /* H */
	, 0x22 /* " */
}; ///< register H

static const unsigned char arrayRegT [] =
{
	  0x22 /* " */
	, 0x54 /* T */
	, 0x22 /* " */
}; ///< register T

static unsigned long sizeEndInit = sizeof (arrayEndInit) / sizeof(const unsigned char); ///< size end register init
static unsigned long sizeEndResult = sizeof (arrayEndResult) / sizeof(const unsigned char); ///< size end register result
static unsigned long sizeAdd = sizeof (arrayAdd) / sizeof(const unsigned char); ///< size array add
static unsigned long sizeNewElement = sizeof (newElement) / sizeof(const unsigned char); ///< size new register
static unsigned long sizeG = sizeof (arrayRegG) / sizeof(const unsigned char); ///< size register G
static unsigned long sizeS = sizeof (arrayRegS) / sizeof(const unsigned char); ///< size register S
static unsigned long sizeL = sizeof (arrayRegL) / sizeof(const unsigned char); ///< size register L
static unsigned long sizeC = sizeof (arrayRegC) / sizeof(const unsigned char); ///< size register C
static unsigned long sizeH = sizeof (arrayRegH) / sizeof(const unsigned char); ///< size register H
static unsigned long sizeT = sizeof (arrayRegT) / sizeof(const unsigned char); ///< size register T

/**
 * @brief method sort register L by tally position
 * @param b1 buffer one
 * @param b2 buffer two
 * @return true is b1 < b2
 * @date 28/02/2012
 * @author Yadickson Soto
 */
static bool sortL (SafeBuffer b1, SafeBuffer b2)
{
	unsigned long tally1 = CodiBuffer::getLongValue(b1, 5);
	unsigned long tally2 = CodiBuffer::getLongValue(b2, 5);
	return (tally1 < tally2);
}

/**
 * @brief method sort register C by list
 * @param b1 buffer one
 * @param b2 buffer two
 * @return true is b1 < b2
 * @date 28/02/2012
 * @author Yadickson Soto
 */
static bool sortCList (SafeBuffer b1, SafeBuffer b2)
{
	unsigned long listTally1 = CodiBuffer::getLongValue(b1, 5);
	unsigned long listTally2 = CodiBuffer::getLongValue(b2, 5);

	return (listTally1 < listTally2);
}

/**
 * @brief method sort register C by type (E or S)
 * @param b1 buffer one
 * @param b2 buffer two
 * @return true is b1 < b2
 * @date 28/02/2012
 * @author Yadickson Soto
 */
static bool sortCType (SafeBuffer b1, SafeBuffer b2)
{
	std::string type1 = CodiBuffer::getStringValue(b1, 6);
	std::string type2 = CodiBuffer::getStringValue(b2, 6);

	return (type1.compare(type2) < 0);
}

/**
 * @brief method sort register C by tally position
 * @param b1 buffer one
 * @param b2 buffer two
 * @return true is b1 < b2
 * @date 28/02/2012
 * @author Yadickson Soto
 */
static bool sortCTally (SafeBuffer b1, SafeBuffer b2)
{
	unsigned long tally1 = CodiBuffer::getLongValue(b1, 7);
	unsigned long tally2 = CodiBuffer::getLongValue(b2, 7);

	return (tally1 < tally2);
}

CodiBuffer::CodiBuffer()
{

}

CodiBuffer::~CodiBuffer()
{

}

void CodiBuffer::insertValue(SafeBuffer & buffer, unsigned long pos, std::string value)
{
	unsigned long begin = 0, end = 0;

    if (getPositionRegister(buffer, pos, begin, end))
    {
    	buffer.removeData(begin, end - begin);
    	buffer.insertData (begin, value);
    }
}

void CodiBuffer::insertValue(SafeBuffer & buffer, unsigned long pos, unsigned long value)
{
	char str[32];
	sprintf (str, "%ld", value);
	insertValue(buffer, pos, str);
}

void CodiBuffer::createRegister(Smartmatic::System::SafeBuffer & buffer, CodiBuffer::RegisterType type)
{
	buffer.Clear();

	switch(type)
	{
		case REGISTER_G:
			buffer.AddData(arrayRegG, sizeG);
			break;
		case REGISTER_S:
			buffer.AddData(arrayRegS, sizeS);
			break;
		case REGISTER_L:
			buffer.AddData(arrayRegL, sizeL);
			break;
		case REGISTER_C:
			buffer.AddData(arrayRegC, sizeC);
			break;
		case REGISTER_H:
			buffer.AddData(arrayRegH, sizeH);
			break;
		case REGISTER_T:
			buffer.AddData(arrayRegT, sizeT);
			break;
		default:
			break;
	}
}

void CodiBuffer::fixRegister(SafeBuffer & buffer, unsigned long size)
{
    unsigned long index = 0, endLine = 0;
    unsigned long begin, end;
    unsigned long total = size;

    while (!getPositionRegister(buffer, size, begin, end))
    {
		size--;
    }

    if (!buffer.findData (index, arrayEndResult, sizeEndResult, endLine))
    {
    	endLine = buffer.GetSize();
    }

    for (unsigned long i = size; i < total; i++)
    {
       	buffer.insertData (endLine, newElement, sizeNewElement);
    }
}

void CodiBuffer::addEndRegister(SafeBuffer & buffer)
{
	buffer.AddData(arrayEndResult, sizeEndResult);
}

bool CodiBuffer::getPositionRegister(SafeBuffer & buffer, unsigned long pos, unsigned long & begin, unsigned long & end)
{
	std::string group = GROUP;

	unsigned long index = 0, posResult = 0;

	while (buffer.findData (index, group, posResult) && pos >= 1)
	{
		pos--;
		begin = posResult + 1;
		index = begin;
		buffer.findData (index, group, posResult);
		end = posResult;
		index = end + 1;
	}

	if (pos != 0)
	{
		begin = 0;
		end = 0;
	}

    return pos == 0;
}

void CodiBuffer::getRegisters(SafeBuffer & buffer,
		std::vector <SafeBuffer> & regG,
		std::vector <SafeBuffer> & regS,
		std::vector <SafeBuffer> & regL,
		std::vector <SafeBuffer> & regC)
{
    unsigned long index = 0, posResult = 0;
    bool insertCR = !buffer.findData (0, arrayAdd, sizeAdd, posResult);  // if not found CR

    while (buffer.findData (index, arrayEndInit, sizeEndInit, posResult))
    {
    	SafeBuffer b((unsigned char *)(buffer.GetData() + index), posResult - index + sizeEndInit);
   		index = posResult + sizeEndInit;

   		if (insertCR)   // insert CR
   		{
   			b.insertData(b.GetSize() - sizeEndInit, arrayAdd, sizeAdd);
   		}

   		addToList(b, regG, regS, regL, regC);
    }

    //add last register if LF not found
    if (index < buffer.GetSize())
	{
    	SafeBuffer b((unsigned char *)(buffer.GetData() + index), buffer.GetSize() - index);
		addEndRegister(b);
   		addToList(b, regG, regS, regL, regC);
	}

    std::stable_sort (regL.begin(), regL.end(), sortL);
    std::stable_sort (regC.begin(), regC.end(), sortCTally);
    std::stable_sort (regC.begin(), regC.end(), sortCType);
    std::stable_sort (regC.begin(), regC.end(), sortCList);
}

void CodiBuffer::addToList(SafeBuffer & buffer,
		std::vector <SafeBuffer> & regG,
		std::vector <SafeBuffer> & regS,
		std::vector <SafeBuffer> & regL,
		std::vector <SafeBuffer> & regC)
{
	CodiBuffer::RegisterType type = getRegisterType(buffer);

	switch(type)
	{
		case REGISTER_G:
			regG.push_back(buffer);
			break;
		case REGISTER_S:
			regS.push_back(buffer);
			break;
		case REGISTER_L:
			regL.push_back(buffer);
			break;
		case REGISTER_C:
			regC.push_back(buffer);
			break;
		default:
			break;
	}
}

std::string CodiBuffer::getStringValue(Smartmatic::System::SafeBuffer & buffer, unsigned long pos)
{
	unsigned long begin, end;
	std::string value;

	if ( getPositionRegister(buffer, pos, begin, end) )
	{
		value.assign((const char *)(buffer.GetData() + begin), end-begin);
		value.resize(end-begin);
	}

	return value;
}

unsigned long CodiBuffer::getLongValue(Smartmatic::System::SafeBuffer & buffer, unsigned long pos)
{
	unsigned long value = 0;
	std::string str = getStringValue(buffer, pos);

	std::istringstream iss(str);
	iss >> std::dec >> value;

	return value;
}

CodiBuffer::RegisterType CodiBuffer::getRegisterType(Smartmatic::System::SafeBuffer & buffer)
{
	CodiBuffer::RegisterType type = NONE;
	unsigned long posResult = 0;

	if (buffer.findData (0, arrayRegG, sizeG, posResult) && posResult == 0)
	{
		type = REGISTER_G;
	}
	else if (buffer.findData (0, arrayRegS, sizeS, posResult) && posResult == 0)
	{
		type = REGISTER_S;
	}
	else if (buffer.findData (0, arrayRegL, sizeL, posResult) && posResult == 0)
	{
		type = REGISTER_L;
	}
	else if (buffer.findData (0, arrayRegC, sizeC, posResult) && posResult == 0)
	{
		type = REGISTER_C;
	}
	else if (buffer.findData (0, arrayRegH, sizeH, posResult) && posResult == 0)
	{
		type = REGISTER_H;
	}
	else if (buffer.findData (0, arrayRegT, sizeT, posResult) && posResult == 0)
	{
		type = REGISTER_T;
	}

	return type;
}
