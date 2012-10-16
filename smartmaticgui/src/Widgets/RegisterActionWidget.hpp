/**
 * @file RegisterActionWidget.pxx
 * @brief Body class register action widget
 * @data 24/05/2012
 * @author Yadickson Soto
 */

#include "RegisterActionWidget.hxx"

namespace Smartmatic
{
namespace GUI
{
namespace Widgets
{

template <class TRegister>
RegisterActionWidget<TRegister>::RegisterActionWidget()
{

}

template <class TRegister>
RegisterActionWidget<TRegister>::~RegisterActionWidget()
{
	remove();

	if (registerWidget)
	{
		delete registerWidget;
		registerWidget = NULL;
	}
}

template <class TRegister>
void RegisterActionWidget<TRegister>::addWidget(TRegister widget, std::string title)
{
	widget->getSignalClicked().connect(sigc::mem_fun(*this, &RegisterActionWidget<TRegister>::editInfo));
	registerWidget->addWidget(widget, title);
}

template <class TRegister>
void RegisterActionWidget<TRegister>::setCurrentPage(int currentPage)
{
	registerWidget->setCurrentPage(currentPage);
}

template <class TRegister>
void RegisterActionWidget<TRegister>::editInfo(TRegister widget)
{
	signalClicked.emit(widget);
}

template <class TRegister>
sigc::signal<void, TRegister> RegisterActionWidget<TRegister>::getSignalClicked()
{
	return signalClicked;
}

}
}
}
