/**
 * @file StringStatWidget.cxx
 * @brief Body class string state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#include "StringStatWidget.hxx"

using namespace Smartmatic::GUI::Widgets;

StringStatWidget::StringStatWidget(std::string name, std::string code, bool mandatory, int maxCount, int width, int height)
: IStatWidget(name, code)
{
	textView = new SmartmaticTextView();
	textView->set_size_request(width, height);
	textView->set_border_width(1);
	textView->setMax(maxCount);
	textView->setMandatory(mandatory);

	add(*textView);
}

StringStatWidget::~StringStatWidget()
{
	remove();

	if (textView)
	{
		delete textView;
		textView = NULL;
	}
}

std::string StringStatWidget::getValue()
{
	return textView->getText();
}

void StringStatWidget::setValue(std::string value)
{
	textView->setText(value);
}

void StringStatWidget::setEnable(bool enable)
{
	textView->set_sensitive(enable);
}

void StringStatWidget::setSize(int width, int height)
{
	IStatWidget::setSize(textView, width, height);
}

bool StringStatWidget::validate()
{
	return textView->validate();
}
