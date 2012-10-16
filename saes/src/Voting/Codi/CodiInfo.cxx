/**
 * @file CodiInfo.cxx
 * @brief Body class codi info utility
 * @date 28/02/2012
 * @author Yadickson Soto
 */

#include "CodiInfo.hxx"
#include <System/Utils/StringUtils.hxx>

#define CUSTOM_CODE_SIZE 9 ///< custom code size

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::System::Utils;

CodiInfo::CodiInfo()
{

}

CodiInfo::~CodiInfo()
{

}

std::string CodiInfo::getElectionType(std::string customCode)
{
	std::string electionType;

	if (customCode.size() == CUSTOM_CODE_SIZE)
	{
		electionType = customCode.substr(0, 2);
	}

	return electionType;
}

std::string CodiInfo::getInputNisCode(std::string customCode)
{
	std::string niscode;

	if (customCode.size() == CUSTOM_CODE_SIZE)
	{
		niscode = customCode.substr(2, 5);
	}

	return niscode;
}

std::string CodiInfo::getOutputNisCode(
		std::string customCode,
		std::string customniscode)
{
	std::string niscode = customniscode;

	if (niscode.empty() && customCode.size() == CUSTOM_CODE_SIZE)
	{
		niscode = customCode.substr(2, 5);
	}

	return niscode;
}

std::string CodiInfo::getLanguage(std::string customCode)
{
	std::string language;

	if (customCode.size() == CUSTOM_CODE_SIZE)
	{
		language = customCode.substr(7, 2);
	}

	return language;
}
