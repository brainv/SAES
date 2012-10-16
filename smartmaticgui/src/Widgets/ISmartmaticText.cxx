/**
 * @file ISmartmaticText.cxx
 * @brief Body class smartmatic text
 * @date 03/06/2012
 * @author Yadickson Soto
 */

#include "ISmartmaticText.hxx"
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Utils;

ISmartmaticText::ISmartmaticText()
{
	this->max = -1;
	this->mask = "";
	this->regex = "";
	this->mandatory = false;
}

ISmartmaticText::~ISmartmaticText()
{

}

void ISmartmaticText::setMax(int max)
{
	this->max = max;
}

void ISmartmaticText::setMask(std::string mask)
{
	this->mask = mask;
}

void ISmartmaticText::setRegex(std::string regex)
{
	this->regex = regex;
}

void ISmartmaticText::setMandatory(bool mandatory)
{
	this->mandatory = mandatory;
}

bool ISmartmaticText::validate()
{
	bool result = false;
	std::string text = StringUtils::trim(getText());

	if (mandatory && text.empty())
	{
		setBGError();
	}
	else if (!(text.empty() || StringUtils::regex(regex, text)))
	{
		setBGError();
	}
	else
	{
		setBGNormal();
		result = true;
	}

	return result;
}
