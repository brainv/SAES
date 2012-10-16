/**
 * @file ChooseSelectionWidget.cxx
 * @brief Body class choose selection widget
 * @date 12/04/2012
 * @author Yadickson Soto
 */

#include "ChooseSelectionWidget.hxx"
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;

ChooseSelectionWidget::ChooseSelectionWidget()
: StepWidget()
{
	this->choices.clear();
	this->mainFrame = NULL;
	this->alignFrame = NULL;
	this->chooseDialogWidget = NULL;
	this->showBack = false;
}

ChooseSelectionWidget::ChooseSelectionWidget(std::string title, std::vector <ChooseDialogButtonInfo*> & choices, ConfirmationDialogWidget * confirmation, bool showBack)
: StepWidget()
{
	this->mainFrame = NULL;
	this->alignFrame = NULL;
	this->chooseDialogWidget = NULL;
	this->showBack = showBack;
	setChooseButtons(title, choices, confirmation);
}

ChooseSelectionWidget::ChooseSelectionWidget(ChooseDialogInfo * info, ConfirmationDialogWidget * confirmation, bool showBack)
: StepWidget()
{
	this->choices.clear();
	this->mainFrame = NULL;
	this->alignFrame = NULL;
	this->chooseDialogWidget = NULL;
	this->showBack = showBack;
	setChooseInfo(info, confirmation);
}

ChooseSelectionWidget::~ChooseSelectionWidget()
{
	dispose();
}

void ChooseSelectionWidget::dispose()
{
	remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (alignFrame)
	{
		delete alignFrame;
		alignFrame = NULL;
	}
	if (chooseDialogWidget)
	{
		delete chooseDialogWidget;
		chooseDialogWidget = NULL;
	}

	std::vector <ChooseDialogButtonInfo*>::iterator it;

	for (it = choices.begin();
			it != choices.end();
			it++)
	{
		ChooseDialogButtonInfo * obj = (*it);
		delete obj;
		obj = NULL;
	}
}

void ChooseSelectionWidget::setChooseButtons(std::string title, std::vector <ChooseDialogButtonInfo*> & choices, ConfirmationDialogWidget * confirmation)
{
	this->choices = choices;
	ChooseDialogInfo * infoDiag = new ChooseDialogInfo(title, "", "", "", choices, false);
	setChooseInfo(infoDiag, confirmation);
}

void ChooseSelectionWidget::setChooseInfo(ChooseDialogInfo * info, ConfirmationDialogWidget * confirmation)
{
	remove();

	if (!mainFrame)
	{
		mainFrame = new Gtk::EventBox();
		mainFrame->set_border_width(60);
	}
	if (!alignFrame)
	{
		alignFrame = new Gtk::Alignment();
		alignFrame->set((float)0,(float)0,(float)1,(float)0.9);
	}
	if (chooseDialogWidget)
	{
		delete chooseDialogWidget;
		chooseDialogWidget = NULL;
	}

	if (confirmation)
	{
		chooseDialogWidget = new ChooseDialogWidget(info, confirmation);
	}
	else
	{
		chooseDialogWidget = new ChooseDialogWidget(info, showBack);
	}

	chooseDialogWidget->on_accept_intermediate_signal().connect(sigc::mem_fun(*this,&ChooseSelectionWidget::onPreSelected));
	chooseDialogWidget->on_cancel_intermediate_signal().connect(sigc::mem_fun(*this,&ChooseSelectionWidget::onPreSelectedBack));
	chooseDialogWidget->on_choose_signal().connect(sigc::mem_fun(*this,&ChooseSelectionWidget::onSelected));

	mainFrame->remove();
	mainFrame->add(*chooseDialogWidget);

	alignFrame->remove();
	alignFrame->add(*mainFrame);
	alignFrame->show();

	setWidget(alignFrame);
}

void ChooseSelectionWidget::setLabelConfig(LabelConfiguration headerConf, LabelConfiguration footerConf)
{
	if (chooseDialogWidget)
	{
		chooseDialogWidget->SetLabelConfiguration(headerConf, footerConf);
	}
}

void ChooseSelectionWidget::setLabelConfirmationConfig(LabelConfiguration headerConf, LabelConfiguration footerConf)
{
	if (chooseDialogWidget)
	{
		chooseDialogWidget->SetLabelConfirmationConfiguration(headerConf, footerConf);
	}
}

void ChooseSelectionWidget::setShowBack(bool showBack)
{
	this->showBack = showBack;
}

void ChooseSelectionWidget::onPreSelected(ChooseDialogButtonInfo* choose)
{

}

void ChooseSelectionWidget::onPreSelectedBack()
{

}

void ChooseSelectionWidget::setInternalSizeWidget(int width, int height)
{
	int formheight ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getHeight());
	int formwidth ((*SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getWidth());

	int horizontalPadding = (formwidth - width) / 2;
	int verticalPadding = (formheight - height) / 2;

	if (alignFrame)
	{
		alignFrame->set_padding(verticalPadding, verticalPadding, horizontalPadding, horizontalPadding);
		alignFrame->set(0.0,0.0,1,1);
	}

	if (mainFrame)
	{
		mainFrame->set_border_width(0);
	}
}
