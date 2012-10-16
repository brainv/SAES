/**
 * @file NumericStatWidget.cxx
 * @brief Body class numeric state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#include "NumericStatWidget.hxx"
#include <gdk/gdkkeysyms.h>
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Utils;

NumericStatWidget::NumericStatWidget(std::string name, std::string code, std::string regex, bool mandatory, int maxCount)
: CustomStatWidget(name, code, regex, mandatory, maxCount, "0123456789")
{
	statEntry->signal_key_press_event().connect(sigc::mem_fun(*this,&NumericStatWidget::on_key_pressed),false);
	setValue("");
}

NumericStatWidget::~NumericStatWidget()
{
	remove();

	if (statEntry)
	{
		delete statEntry;
		statEntry = NULL;
	}
}

void NumericStatWidget::setValue(std::string value)
{
	if (!value.empty())
	{
		statEntry->set_text(StringUtils::intToString(StringUtils::stringToInt(value)));
	}
}

bool NumericStatWidget::on_key_pressed(GdkEventKey* event)
{
	bool returnValue = false;

	switch(event->keyval)
	{
		case GDK_Up:
			increment();
			returnValue = true;
			break;
		case GDK_Down:
			decrement();
			returnValue = true;
			break;
		default:
			break;
	}

	return returnValue;
}

void NumericStatWidget::increment()
{
	std::string statCount = StringUtils::intToString(StringUtils::stringToInt(getValue()) + 1);
	setValue(statCount);
}

void NumericStatWidget::decrement()
{
	std::string statCount = StringUtils::intToString(StringUtils::stringToInt(getValue()) - 1);

	if(StringUtils::stringToInt(statCount) < 0)
	{
		statCount = "0";
	}

	setValue(statCount);
}
