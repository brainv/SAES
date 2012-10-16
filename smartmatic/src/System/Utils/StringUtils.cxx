/**
 * @file StringUtils.cxx
 * @brief Body class string utils
 */

#include "StringUtils.hxx"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

using namespace Smartmatic::System::Utils;
using namespace Smartmatic::System::Utils;

StringUtils::StringUtils()
{

}

std::string StringUtils::remove(std::string input, std::string find)
{
    return replace(input, find, "");
}

std::string StringUtils::removeAll(std::string input, std::string find)
{
    return replaceAll(input, find, "");
}

std::string StringUtils::replace(std::string input, std::string find,
        std::string dest)
{
	if (!find.empty())
	{
		std::string::size_type pos;
		pos = input.find(find);

		if (pos != std::string::npos)
		{
			input.replace(pos, find.length(), dest);
		}
	}

    return input;
}

std::string StringUtils::replaceAll(std::string input, std::string find,
        std::string dest)
{
	if (!find.empty())
	{
		std::string::size_type pos;

		for (pos = input.find(find); pos != std::string::npos; pos = input.find(find))
		{
			input.replace(pos, find.length(), dest);
		}
	}

    return input;
}

std::list<std::string> StringUtils::split(const std::string & input, const std::string & find)
{
    std::list<std::string> result;

    if (find.empty())
    {
        result.push_back(input);
        return result;
    }

    std::string::const_iterator substart = input.begin(), subend;

    while (true)
    {
        subend = search(substart, input.end(), find.begin(), find.end());
        std::string temp(substart, subend);
        if (!temp.empty())
        {
            result.push_back(temp);
        }
        if (subend == input.end())
        {
            break;
        }
        substart = subend + find.size();
    }

    return result;
}

void StringUtils::split(const std::string & input, const std::string & find, std::vector <std::string> & vector)
{
	vector.clear();
	std::list<std::string> result = split(input, find);
	vector.insert(vector.end(), result.begin(), result.end());
}

std::string StringUtils::arrayHexToString(
		const std::vector <unsigned char> & input,
		std::string prefix,
		std::string separator)
{
	std::stringstream ss;
	int group = 2;

	for( size_t index = 0; index < input.size(); ++index )
	{
		ss << prefix;
		ss << std::hex << std::setw(group) << std::setfill('0') << (unsigned int)input[index];
		ss << separator;
	}

	return ss.str();
}

void StringUtils::stringToArrayHex(
		std::string input,
		std::vector <unsigned char> & output,
		std::string prefix,
		std::string separator)
{
	input = replaceAll(input, prefix, "");
	input = replaceAll(input, separator, "");

	int group = 2;
	int number;
	std::string str;
	std::string format;

	std::stringstream ss;
	ss << "%0" << group << "x";
	format = ss.str();

	for (unsigned int i = 0; i < input.length(); i+=group)
	{
		str = input.substr(i, group);

		if (sscanf(str.c_str(), format.c_str(), &number) > 0)
		{
			output.push_back(number);
		}
	}
}

std::string StringUtils::bufferHexToString(
	const Smartmatic::System::SafeBuffer & input,
	std::string prefix,
	std::string separator)
{
	std::vector <unsigned char> data;
	data.insert(data.end(), input.GetData(), input.GetData() + input.GetSize());
	return arrayHexToString(data, prefix, separator);
}

void StringUtils::stringToBufferHex(
	std::string input,
	Smartmatic::System::SafeBuffer & output,
	std::string prefix,
	std::string separator)
{
	std::vector <unsigned char> dataOut;
	stringToArrayHex(input, dataOut, prefix, separator);

	if (dataOut.size() > 0)
	{
		output.AddData((const unsigned char *)&dataOut[0], dataOut.size());
	}
}

bool StringUtils::isFound(std::string text, char character)
{
	bool f = false;

	if (!text.empty())
	{
		std::string::size_type pos;
		pos = text.find(character);
		f = pos != std::string::npos;
	}

	return f;
}

bool StringUtils::regex(std::string reg, std::string text)
{
	bool f = false;
    regex_t regex;
    int reti;

    reti = regcomp(&regex, reg.c_str(), REG_EXTENDED|REG_NOSUB);

    if( reti )
    {
    	return f;
    }

    reti = regexec(&regex, text.c_str(), 0, NULL, 0);

    f = !reti;

    regfree(&regex);

	return f;
}

std::string StringUtils::trim(std::string str)
{
	std::string::size_type pos = str.find_last_not_of(' ');

	if(pos != std::string::npos)
	{
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');

		if(pos != std::string::npos)
		{
			str.erase(0, pos);
		}
	}
	else
	{
		str.erase(str.begin(), str.end());
	}

	return str;
}

int StringUtils::stringToInt(std::string str)
{
	int value = 0;

	std::istringstream iss(str);
	iss >> std::dec >> value;

	return value;
}

long StringUtils::stringToLong(std::string str)
{
	long value = 0;

	std::istringstream iss(str);
	iss >> std::dec >> value;

	return value;
}

std::string StringUtils::intToString(int value)
{
	std::stringstream iss;
	iss << value;
	return iss.str();
}
