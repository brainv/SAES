/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <eid/EIDManager.hxx>
#include "sign-election-resource-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <System/IO/File.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <Operation/Card/CardController.hxx>
#include <System/Exception/XmlException.hxx>
#include <Widgets/smartmatic-button.h>
#include <Log/SMTTLogManager.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation::Card;

Smartmatic::Log::ISMTTLog* SignElectionResourceWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget",GETTEXT_PACKAGE);

SignElectionResourceWidget::SignElectionResourceWidget()
{
	showQuestion = false;
	showConfirm = true;
	signFile = true;
	vbox = NULL;
	confirmBox = NULL;
	idCard = NULL;
	confirmBoxSign = NULL;

	continueOnFail = SAESGUIConfigurationManager::Current()->GetCloseElectionFunctionalityConfiguration().getContinueCloseOnSignFail();


	string fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/persist-package.gif");

	if(!File::canOpenFile(fileImage))
		fileImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");

	loadImage = manage(new Gtk::Image());
	loadImage->set(Gdk::PixbufAnimation::create_from_file(fileImage));

	label = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.SignElectionResource")));
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	label->modify_font(fontTitle);

	fontTitle.set_size(16*Pango::SCALE);

	vbox = new Gtk::VBox();
	vbox->pack_start(*loadImage);
	vbox->pack_start(*label);

	idCard = new IDCardWidget(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.IDMessage"));
	idCard->signal_accept_clicked().connect(sigc::mem_fun(*this, &SignElectionResourceWidget::on_IDWidgetAccept_clicked));

	SmartmaticButton* confirmButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.Confirm")));
	confirmButton->signal_clicked().connect(sigc::mem_fun(*this, &SignElectionResourceWidget::on_confirmButton_clicked));
	confirmButton->set_size_request(150, 60);
	confirmButton->SetButtonType(SmartmaticButton::Ok);
	confirmButton->WidgetsPosition(5,6,0);

	SmartmaticButton* cancelButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.Back")));
	cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &SignElectionResourceWidget::on_cancelButton_clicked));
	cancelButton->set_size_request(150, 60);
	cancelButton->SetButtonType(SmartmaticButton::Cancel);
	cancelButton->WidgetsPosition(5,6,0);

	HButtonBox* btnBox = manage(new HButtonBox());
	btnBox->set_spacing(80);
	btnBox->set_layout(BUTTONBOX_CENTER);
	btnBox->pack_start(*cancelButton);
	btnBox->pack_start(*confirmButton);

	Label* labelConfirm = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.ConfirmQuestion")));
	labelConfirm->set_size_request(300, 250);
	labelConfirm->modify_font(fontTitle);

	confirmBox = new VBox();
	confirmBox->pack_start(*labelConfirm, false, false);
	confirmBox->pack_start(*btnBox, false, false);

	SmartmaticButton* signButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.SignButton")));
	signButton->signal_clicked().connect(sigc::mem_fun(*this, &SignElectionResourceWidget::on_signButton_clicked));
	signButton->set_size_request(150, 60);

	SmartmaticButton* nosignButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.NoSignButton")));
	nosignButton->signal_clicked().connect(sigc::mem_fun(*this, &SignElectionResourceWidget::on_nosignButton_clicked));
	nosignButton->set_size_request(150, 60);

	HButtonBox* btnSignBox = manage(new HButtonBox());
	btnSignBox->set_spacing(80);
	btnSignBox->set_layout(BUTTONBOX_CENTER);
	btnSignBox->pack_start(*signButton);
	btnSignBox->pack_start(*nosignButton);

	Label* labelSign = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.SignPackageQuestion")));
	labelSign->set_size_request(300, 250);
	labelSign->modify_font(fontTitle);

	confirmBoxSign = new VBox();
	confirmBoxSign->pack_start(*labelSign, false, false);
	confirmBoxSign->pack_start(*btnSignBox, false, false);


	if(showQuestion)
		setWidget(confirmBoxSign);
	else
		setWidget(idCard);
}

void SignElectionResourceWidget::on_signButton_clicked()
{
	ShowIDCard();
}

void SignElectionResourceWidget::on_nosignButton_clicked()
{
	label->set_text(_("Smartmatic.SAES.GUI.Widgets.SignElectionResourceWidget.NoSignElectionResource"));
	ShowSignElectionFrame();
	signFile = false;
}

void SignElectionResourceWidget::on_confirmButton_clicked()
{
	ShowSignElectionFrame();
}

void SignElectionResourceWidget::on_cancelButton_clicked()
{
	ShowIDCard();
}

void SignElectionResourceWidget::on_IDWidgetAccept_clicked()
{
	if(showConfirm)
	{
		setWidget(confirmBox);
	}
	else
		ShowSignElectionFrame();
}

void SignElectionResourceWidget::ShowIDCard()
{
	setWidget(idCard);
}

void SignElectionResourceWidget::ShowSignElectionFrame()
{
	setWidget(vbox);

	m_disable_close_signal.emit();
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &SignElectionResourceWidget::ThreadStart), false);
	//Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SignElectionResourceWidget::on_done),5000);
}

SignElectionResourceWidget::~SignElectionResourceWidget()
{
	if(vbox)
		delete vbox;
	if(confirmBox)
		delete confirmBox;
	if(idCard)
		delete idCard;
	if(confirmBoxSign)
		delete confirmBoxSign;
}

void SignElectionResourceWidget::ShowConfirmFrame()
{
	setWidget(confirmBox);
}

void SignElectionResourceWidget::CheckIDCard()
{
	//idCard  signal_cardRemoved_detected();

	if(idCard->getCitizenInfo().getFirstName() == "")
	{
		ShowIDCard();
	}
	else
	{
		ShowConfirmFrame();
	}
}

void SignElectionResourceWidget::initialize()
{
	idCard->initialize();
	//Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SignElectionResourceWidget::CheckIDCard),5000);
}

void SignElectionResourceWidget::dispose()
{
	idCard->dispose();
}

void SignElectionResourceWidget::ThreadStart()
{
	CardController::getInstance()->dispose();

	bool errorHappen = false;
	try
	{
		MachineOperationManager::getInstance()->signElectionResults(signFile);
	}
	catch(CryptoException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget CryptoException");
		errorHappen = true;
	}
	catch(SignedException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget SignedException");
		errorHappen = true;
	}
	catch(XmlException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget XmlException");
		errorHappen = true;
	}
	catch(SignByCardIDException & ex)
	{
		logger->Debug("PersistTransmissionPackageWidget SignByCardIDException");
		errorHappen = true;
	}
	catch(...)
	{
		logger->Debug("PersistTransmissionPackageWidget Unknow Exception");
		errorHappen = true;
	}

	if(!errorHappen)
	{
		sleep(3);
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SignElectionResourceWidget::on_done), 500);
	}
	else
	{
		if(continueOnFail)
		{
			sleep(3);
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SignElectionResourceWidget::on_done), 500);
		}
		else
			Glib::signal_timeout().connect_once(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &SignElectionResourceWidget::UpdateLabel),
				_("Smartmatic.SAES.GUI.Widgets.PersistTransmissionPackageWidget.ErrorMessage")), 500);
	}
}

void SignElectionResourceWidget::on_done()
{
	idCard->dispose();
	m_done_signal.emit();
}

void SignElectionResourceWidget::UpdateLabel(Glib::ustring text)
{
	setWidget(vbox);
	loadImage->hide();
	label->set_text(text);
	m_stop_signal.emit();
}

