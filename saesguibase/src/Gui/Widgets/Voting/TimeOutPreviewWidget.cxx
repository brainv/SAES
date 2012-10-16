/**
 * @file TimeOutPreviewWidget.cxx
 * @brief Header class timeout preview
 * @date 13/04/2012
 * @author Yadickson Soto
 */

#include "TimeOutPreviewWidget.hxx"
#include <Operation/FormatLabel.hxx>
#include <Widgets/smartmatic-label.h>

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

using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Operation;

TimeOutPreviewWidget::TimeOutPreviewWidget()
: StepWidget()
{
	message = new Gtk::Label(FormatLabel::format(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.LabelPreviewCloseQuestion")));
	Pango::FontDescription fontSuperNull = message->get_style()->get_font();
	fontSuperNull.set_size(17*Pango::SCALE);
	fontSuperNull.set_weight(Pango::WEIGHT_BOLD);
	message->modify_font(fontSuperNull);
	SmartmaticLabel::SetAutoWrap(*message,600, 500);

	closeButton = new SmartmaticButton();
	closeButton->SetButtonType(SmartmaticButton::Ok);
	closeButton->WidgetsPosition(0,5,0);
	closeButton->set_size_request(200, 70);

	keepButton = new SmartmaticButton();
	keepButton->SetButtonType(SmartmaticButton::Cancel);
	keepButton->WidgetsPosition(0,5,0);
	keepButton->set_size_request(200, 70);

	hbuttonBox = new Gtk::HButtonBox();
	hbuttonBox->pack_start(*keepButton);
	hbuttonBox->pack_start(*closeButton);
	hbuttonBox->set_layout(Gtk::BUTTONBOX_CENTER);
	hbuttonBox->set_spacing(50);

	mainFrame = new Gtk::VBox();
	mainFrame->pack_start(*message,false,false);
	mainFrame->pack_start(*hbuttonBox,false,false);

	setWidget(mainFrame);
}

TimeOutPreviewWidget::~TimeOutPreviewWidget()
{
	remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (message)
	{
		delete message;
		message = NULL;
	}
	if (closeButton)
	{
		delete closeButton;
		closeButton = NULL;
	}
	if (keepButton)
	{
		delete keepButton;
		keepButton = NULL;
	}
	if (hbuttonBox)
	{
		delete hbuttonBox;
		hbuttonBox = NULL;
	}
}

Glib::SignalProxy0< void > TimeOutPreviewWidget::getCloseClicked()
{
	return closeButton->signal_clicked();
}

Glib::SignalProxy0< void > TimeOutPreviewWidget::getKeepClicked()
{
	return keepButton->signal_clicked();
}
