/**
 * @file IStatWidget.cxx
 * @brief Body class state widget
 * @date 08/05/2012
 * @author Yadickson Soto
 */

#include "IStatWidget.hxx"
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Utils;

IStatWidget::IStatWidget(std::string name, std::string code)
: Gtk::EventBox()
{
	this->name = name;
	this->code = code;
}

IStatWidget::~IStatWidget()
{

}

std::string IStatWidget::getName()
{
	return name;
}

std::string IStatWidget::getCode()
{
	return code;
}

void IStatWidget::setAlign(double alig)
{

}

void IStatWidget::setSize(Gtk::Widget * widget, int width, int height)
{
	widget->set_size_request(width, height);
}
