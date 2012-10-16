/**
 * @file CustomStatWidget.cxx
 * @brief Body class custom state widget
 * @date 01/06/2012
 * @author Yadickson Soto
 */

#include "CustomStatWidget.hxx"

using namespace Smartmatic::GUI::Widgets;

CustomStatWidget::CustomStatWidget(std::string name, std::string code, std::string regex, bool mandatory, int maxCount, std::string mask)
: IStatWidget(name, code)
{
	statEntry = new SmartmaticEntry();
	statEntry->set_size_request(-1, -1);
	statEntry->SetType(SmartmaticEntry::Mask);
	statEntry->setMax(maxCount);
	statEntry->setMask(mask);
	statEntry->setRegex(regex);
	statEntry->setMandatory(mandatory);

	Gdk::Color customGray;
	customGray.set_grey(51200);

	statEntry->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	add(*statEntry);
}

CustomStatWidget::~CustomStatWidget()
{
	remove();

	if (statEntry)
	{
		delete statEntry;
		statEntry = NULL;
	}
}

std::string CustomStatWidget::getValue()
{
	return statEntry->get_text();
}

void CustomStatWidget::setValue(std::string value)
{
	statEntry->set_text(value);
}

void CustomStatWidget::setEnable(bool enable)
{
	statEntry->set_sensitive(enable);
}

void CustomStatWidget::setSize(int width, int height)
{
	IStatWidget::setSize(statEntry, width, height);
}

void CustomStatWidget::setAlign(double align)
{
	statEntry->set_alignment(align);
}

bool CustomStatWidget::validate()
{
	return statEntry->validate();
}
