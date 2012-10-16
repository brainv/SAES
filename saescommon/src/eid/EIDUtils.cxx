/*
 * EIDUtils.cxx
 *
 *  Created on: 20/07/2011
 *      Author: soto
 */

#include "EIDUtils.hxx"

using namespace Smartmatic::SAES::EID;

EIDUtils::EIDUtils()
{

}

EIDUtils::~EIDUtils()
{

}

//*****************************************************************************
// UTF8 to Ansi
//*****************************************************************************
std::string EIDUtils::utf8ToAnsi(const char* pUtf8)
{
int i=0;
char ansi[128];
char* pAnsi = ansi;

	while (pUtf8[i])
	{
		if ((pUtf8[i] & 0x80) == 0)
		{ // ASCII : 0000 0000-0000 007F 0xxxxxxx
			*pAnsi = pUtf8[i];
			++i;
		}
		else if ((pUtf8[i] & 0xE0) == 0xC0)
		{ // 0000 0080-0000 07FF 110xxxxx 10xxxxxx
			*pAnsi = (pUtf8[i] & 0x1F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 1] & 0x3F);
			i += 2;
		}
		else if ((pUtf8[i] & 0xF0) == 0xE0)
		{ // 0000 0800-0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx
			*pAnsi = (pUtf8[i] & 0x0F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 1] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 2] & 0x3F);
			i += 3;
		}
		else if ((pUtf8[i] & 0xF8) == 0xF0)
		{ // 0001 0000-001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			*pAnsi = (pUtf8[i] & 0x07);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 1] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 2] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 3] & 0x3F);
			i += 4;
		}
		else if ((pUtf8[i] & 0xFC) == 0xF8)
		{ // 0020 0000-03FF FFFF 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			*pAnsi = (pUtf8[i] & 0x03);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 1] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 2] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 3] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 4] & 0x3F);
			i += 5;
		}
		else if ((pUtf8[i] & 0xFE) == 0xFC)
		{ // 0400 0000-7FFF FFFF 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			*pAnsi = (pUtf8[i] & 0x01);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 1] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 2] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 3] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 4] & 0x3F);
			*pAnsi <<= 6;
			*pAnsi += (pUtf8[i + 5] & 0x3F);
			i += 6;
		}
		else
		{
			*pAnsi = '?';
		}
		pAnsi++;
	}
	*pAnsi = 0;
	std::string strAnsi(ansi);
	return strAnsi;
}
