/**
 * @ValidateWidget.cxx
 * @brief Class validate widget
 * @date 04/06/2012
 * @author Yadickson Soto
 */

#include "ValidateWidget.hxx"
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;

ValidateWidget::ValidateWidget()
{

}

ValidateWidget::~ValidateWidget()
{

}

void ValidateWidget::setProperties(IDProperties idProperties, SmartmaticEntry * entry)
{
	if (idProperties.getType().present())
	{
		switch (idProperties.getType().get())
		{
			case ElementType::CONFIGURATION_NUMERIC:
				entry->SetType(SmartmaticEntry::AllWithoutAlphabetic);
				break;
			case ElementType::CONFIGURATION_ALPHA:
				entry->SetType(SmartmaticEntry::AllWithoutNumber);
				break;
			case ElementType::CONFIGURATION_ALPHA_NUMERIC:
				entry->SetType(SmartmaticEntry::AlphaNumeric);
				break;
			case ElementType::CONFIGURATION_CUSTOM:
				entry->SetType(SmartmaticEntry::Mask);
				entry->setMask(idProperties.getMask().present() ? idProperties.getMask().get() : "");
				entry->setRegex(idProperties.getRegex().present() ? idProperties.getRegex().get() : "");
				break;
		}
	}

	if (idProperties.getMax().present())
	{
		entry->setMax(idProperties.getMax().get());
	}

	entry->setMandatory(idProperties.getMandatory());
	entry->setText("");
	entry->setBGNormal();
}

void ValidateWidget::setProperties(IDProperties idProperties, SmartmaticTextView * textView)
{
	if (idProperties.getMax().present())
	{
		textView->setMax(idProperties.getMax().get());
	}

	textView->setMandatory(idProperties.getMandatory());
	textView->setRegex(idProperties.getRegex().present() ? idProperties.getRegex().get() : "");
	textView->setText("");
	textView->setBGNormal();
}

bool ValidateWidget::validate(IDProperties idProperties, SmartmaticEntry * entry)
{
	bool result = entry->validate();

	if (!result)
	{
		entry->grab_focus();
	}

	return result;
}

bool ValidateWidget::validate(IDProperties idProperties, SmartmaticTextView * textView)
{
	bool result = textView->validate();

	if (!result)
	{
		textView->grab_focus();
	}

	return result;
}

bool ValidateWidget::validate(IDProperties & idProperties, std::string & text)
{
	bool result = true;
	std::string data = StringUtils::trim(text);

	if (idProperties.getMandatory() && data.empty())
	{
		result = false;
	}

	return result;
}
