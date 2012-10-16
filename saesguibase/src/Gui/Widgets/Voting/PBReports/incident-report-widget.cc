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

#include "incident-report-widget.h"
#include <Voting/PBReports/incident-report-schema.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Runtime/Environment/saes-directories.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* IncidentReportWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportWidget",GETTEXT_PACKAGE);

IncidentReportWidget::IncidentReportWidget()
{
	set_shadow_type(Gtk::SHADOW_NONE);

	showDeleteConfirmation = false;
	isModified = false;
	deleteWidget = NULL;
	externalBox = NULL;
	treeview = NULL;
	dialog = NULL;

	incidentReportWrapper = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getIncidentReport();

	//the resources has "Functionality.IncidentReportFunctionality" to avoid conflicts in po
	string sAddNewReport = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.AddNewReport");
	string sSaveReport = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.SaveReport");
	string sModifyReport = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.ModifyReport");
	string sCompleteReport = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.CompleteReport");
	string sDeleteReport = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.DeleteReport");
	string sVisualizeReport = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.VisualizeReport");
	string sBack = _("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.Back");

	ButtonBoxConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetIncidentReportFunctionalityConfiguration().getButtonConfiguration();
	
	showDeleteConfirmation = SAESGUIConfigurationManager::Current()->GetIncidentReportFunctionalityConfiguration().getShowDeleteConfirmation();

	int buttonWidth = config.getButtonWidth();
	int buttonHeight = config.getButtonHeight();
	int buttonSpacing = config.getSpacing();
	
	addReportButton = new SmartmaticButton(sAddNewReport);
	addReportButton->set_size_request(buttonWidth, buttonHeight);
	addReportButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_addReportButton_clicked));

	saveReportButton = new SmartmaticButton(sSaveReport);
	saveReportButton->show_all_children();
	saveReportButton->set_no_show_all();
	saveReportButton->set_size_request(buttonWidth, buttonHeight);
	saveReportButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_saveReportButton_clicked));
	
	modifyReportButton = new SmartmaticButton(sModifyReport);
	modifyReportButton->set_size_request(buttonWidth, buttonHeight);
	modifyReportButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_modifyReportButton_clicked));

	completeReportButton = new SmartmaticButton(sCompleteReport);
	completeReportButton->show_all_children();
	completeReportButton->set_no_show_all();
	completeReportButton->set_size_request(buttonWidth, buttonHeight);
	completeReportButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_completeReportButton_clicked));

	backButton = new SmartmaticButton(sBack);
	backButton->show_all_children();
	backButton->set_no_show_all();
	backButton->set_size_request(buttonWidth, buttonHeight);
	backButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_backButton_clicked));
	
	deleteReportButton = new SmartmaticButton(sDeleteReport);
	deleteReportButton->set_size_request(buttonWidth, buttonHeight);
	deleteReportButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_deleteReportButton_clicked));
	
	visualizeReportButton = new SmartmaticButton(sVisualizeReport);
	visualizeReportButton->set_size_request(buttonWidth, buttonHeight);
	visualizeReportButton->signal_clicked().connect(sigc::mem_fun(this, &IncidentReportWidget::on_visualizeReportButton_clicked));
	
	addReportButton->set_no_show_all();
	saveReportButton->set_no_show_all();
	modifyReportButton->set_no_show_all();
	completeReportButton->set_no_show_all();
	deleteReportButton->set_no_show_all();
	visualizeReportButton->set_no_show_all();
	backButton->set_no_show_all();

	buttonBox = new VButtonBox(BUTTONBOX_START, buttonSpacing);
	buttonBox->pack_start(*addReportButton);
	buttonBox->pack_start(*saveReportButton);
	buttonBox->pack_start(*modifyReportButton);
	buttonBox->pack_start(*completeReportButton);
	buttonBox->pack_start(*deleteReportButton);
	buttonBox->pack_start(*backButton);
	buttonBox->pack_start(*visualizeReportButton);

	buttonAlignment = new Alignment();
	buttonAlignment->set_padding(buttonSpacing,0,10,0);
	buttonAlignment->add(*buttonBox);

	dialog = new IncidentReportDialogWidget();
	dialogAlign = new Alignment();

	bool newLayout = SAESGUIConfigurationManager::Current()->GetIncidentReportFunctionalityConfiguration().getShowID();

	if(!newLayout)
	{
		dialogAlign->set_padding(10,10,15,50);
	}
	else
	{
		dialogAlign->set(0.1, 0, 0, 0);
	}
	
	dialogAlign->add(*dialog);
	dialogAlign->show_all_children();
	dialogAlign->set_no_show_all();

	treeview = new IncidentReportTreeView();
	treeview->set_no_show_all();
	treeview->show();

	treeScroll = new ScrolledWindow();
	treeScroll->set_policy(POLICY_AUTOMATIC,POLICY_AUTOMATIC);
	treeScroll->add(*treeview);
	treeScroll->set_no_show_all();
	treeScroll->show();

	treeAlign = new Alignment();
	treeAlign->set_padding(10,10,0,10);
	treeAlign->add(*treeScroll);
	treeAlign->set_no_show_all();
	treeAlign->show();

	messageLabel = new Label();
	messageLabel->set_no_show_all();
	messageLabel->show();

	Pango::FontDescription font = messageLabel->get_style()->get_font();
	font.set_size(16*Pango::SCALE);
	messageLabel->modify_font(font);
	
	//TODO configuration of label
	
	externalBox = new HBox(false, 10);
	externalBox->pack_start(*buttonAlignment, false, false);
	externalBox->pack_start(*dialogAlign);
	externalBox->pack_start(*treeAlign);
	externalBox->pack_start(*messageLabel);
	externalBox->show();

	deleteWidget = new ConfirmationDeleteWidget();
	deleteWidget->on_answer_emit().connect(sigc::mem_fun(*this, &IncidentReportWidget::on_deleteAnswer_send));
	deleteWidget->set_no_show_all();
	deleteWidget->show();

	SetButtonsVisual(false);
	ShowTree();

	add(*externalBox);
	show_all_children();
}

IncidentReportWidget::~IncidentReportWidget()
{
	remove();

	if (addReportButton)
	{
		delete addReportButton;
		addReportButton = NULL;
	}
	if (saveReportButton)
	{
		delete saveReportButton;
		saveReportButton = NULL;
	}
	if (modifyReportButton)
	{
		delete modifyReportButton;
		modifyReportButton = NULL;
	}
	if (completeReportButton)
	{
		delete completeReportButton;
		completeReportButton = NULL;
	}
	if (backButton)
	{
		delete backButton;
		backButton = NULL;
	}
	if (deleteReportButton)
	{
		delete deleteReportButton;
		deleteReportButton = NULL;
	}
	if (visualizeReportButton)
	{
		delete visualizeReportButton;
		visualizeReportButton = NULL;
	}
	if (buttonBox)
	{
		delete buttonBox;
		buttonBox = NULL;
	}
	if (buttonAlignment)
	{
		delete buttonAlignment;
		buttonAlignment = NULL;
	}
	if (dialog)
	{
		delete dialog;
		dialog = NULL;
	}
	if (dialogAlign)
	{
		delete dialogAlign;
		dialogAlign = NULL;
	}
	if (treeview)
	{
		delete treeview;
		treeview = NULL;
	}
	if (treeScroll)
	{
		delete treeScroll;
		treeScroll = NULL;
	}
	if (treeAlign)
	{
		delete treeAlign;
		treeAlign = NULL;
	}
	if (messageLabel)
	{
		delete messageLabel;
		messageLabel = NULL;
	}
	if (externalBox)
	{
		delete externalBox;
		externalBox = NULL;
	}
	if (deleteWidget)
	{
		delete deleteWidget;
		deleteWidget = NULL;
	}
}

void IncidentReportWidget::dispose()
{
	if(dialog)
	{
		dialog->dispose();
	}
}

void IncidentReportWidget::on_deleteAnswer_send(bool deleteReport)
{
	if(deleteReport)
	{
		DeleteReport();
	}

	remove();
	add(*externalBox);
	show_all_children();
}

void IncidentReportWidget::ShowDialog()
{
	dialogAlign->show();
	treeAlign->hide();
	messageLabel->hide();
}

void IncidentReportWidget::ShowTree()
{
	dialogAlign->hide();
	treeAlign->show();
	messageLabel->hide();
}

void IncidentReportWidget::ShowMessage(Glib::ustring message)
{
	dialogAlign->hide();
	treeAlign->hide();
	messageLabel->show();

	ShowBack();

	messageLabel->set_text(message);
}

bool IncidentReportWidget::ReportSelected()
{
	return (treeview ? treeview->IsRowSelected() : false);
}

void IncidentReportWidget::PersistReports()
{
	try
	{
		incidentReportWrapper->Persist();
	}
	catch(...)
	{

	}
}

void IncidentReportWidget::LoadReports()
{
	if (dialog)
	{
		dialog->InitializeBEID ();
	}
	if (treeview)
	{
		treeview->CleanAllRows();
		Reports reports = incidentReportWrapper->getReports();
		treeview->SetReports(reports);
	}
}

void IncidentReportWidget::SetButtonsVisual(bool visual)
{
	if(visual)
	{
		addReportButton->hide();
		saveReportButton->show();
		modifyReportButton->hide();
		completeReportButton->show();
		deleteReportButton->hide();
		visualizeReportButton->hide();
		backButton->show();
	}
	else
	{
		addReportButton->show();
		saveReportButton->hide();
		modifyReportButton->show();
		completeReportButton->hide();
		deleteReportButton->show();
		visualizeReportButton->show();
		backButton->hide();
	}
}

void IncidentReportWidget::ShowBack()
{
	addReportButton->hide();
	saveReportButton->hide();
	modifyReportButton->hide();
	completeReportButton->hide();
	deleteReportButton->hide();
	visualizeReportButton->hide();
	backButton->show();
}

void IncidentReportWidget::on_addReportButton_clicked()
{
	isModified = false;
	dialog->Clean();
	ShowDialog();
	SetButtonsVisual(true);
	backTo = BACKTOTREE;
}

void IncidentReportWidget::on_backButton_clicked()
{
	switch(backTo)
	{
		case BACKTOTREE:
			ShowTree();
			SetButtonsVisual(false);
			break;
		case BACKTODIALOG:
			ShowDialog();
			SetButtonsVisual(true);
			break;
	}

	dialog->SetVisualizeMode(false);

	backTo = BACKTOTREE;
}

void IncidentReportWidget::on_saveReportButton_clicked()
{
	if(dialog->CanBeSaved())
	{
		Report report;

		if(isModified)
		{
			dialog->GetParams(report);
			incidentReportWrapper->ModifyReport(report);
			treeview->ModifyRow(report);
			logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportWidget.ModifiedReport"));
		}
		else
		{
			dialog->GetParams(report);
			incidentReportWrapper->AddReport(report);
			treeview->AddRow(report);
			logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportWidget.AddedReport"));
		}

		PersistReports();
		ShowTree();
		SetButtonsVisual(false);
	}
	else
	{
		if(dialog->getErrorInHours())
		{
			ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.WrongHours"));
		}
		else
		{
			ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.IncompleteData"));
		}
		backTo = BACKTODIALOG;
	}
}

void IncidentReportWidget::on_deleteReportButton_clicked()
{
	string code = treeview->GetCustomCodeSelected();

	if(code != "")
	{
		if(showDeleteConfirmation)
		{
			remove();
			add(*deleteWidget);
			show_all_children();
		}
		else
		{
			DeleteReport();
		}
	}
}

void IncidentReportWidget::DeleteReport()
{
	string code = treeview->GetCustomCodeSelected();

	if(code != "")
	{
		incidentReportWrapper->RemoveReport(code);
		treeview->DeleteRowSelected();
		PersistReports();
	}

	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportWidget.DeletedReport"));
}

void IncidentReportWidget::on_modifyReportButton_clicked()
{
	isModified = true;
	Report report;

	string code = treeview->GetCustomCodeSelected();

	if(code != "")
	{
		if(treeview->GetRow(code, report))
		{
			dialog->Clean();
			dialog->SetParams(report);

			if(report.getIsComplete())
			{
				ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.CompleteReport"));
			}
			else
			{
				ShowDialog();
				SetButtonsVisual(true);
			}
			
			backTo = BACKTOTREE;
		}
	}
}

void IncidentReportWidget::on_completeReportButton_clicked()
{
	if(dialog->CanBeSaved())
	{
		//Report report;

		//dialog->GetParams(report);
		
		if(dialog->CanBeCompleted())
		{
			dialog->CompleteReport(true);
			on_saveReportButton_clicked();	
			logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.IncidentReportWidget.CompletedReport"));
		}
		else
		{
			if(dialog->getErrorInHours())
			{
				ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.WrongHours"));
			}
			else
			{
				ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.IncompleteDataSaved"));
			}

			backTo = BACKTODIALOG;
		}
	}
	else
	{
		if(dialog->getErrorInHours())
		{
			ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.WrongHours"));
		}
		else
		{
			ShowMessage(_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.IncompleteData"));
		}
		backTo = BACKTODIALOG;
	}
}

void IncidentReportWidget::on_visualizeReportButton_clicked()
{
	Report report;

	string code = treeview->GetCustomCodeSelected();

	if(code != "")
	{
		if(treeview->GetRow(code, report))
		{
			dialog->Clean();
			dialog->SetParams(report);
			dialog->SetVisualizeMode();

			ShowDialog();
			ShowBack();
			backTo = BACKTOTREE;
		}
	}
}


/*
void IncidentReportFunctionality::on_btn_clicked()
{
	string printValue;

	TimeFunctionality::GetDateTime(printValue);

}



void IncidentReportFunctionality::on_saveReportButton_clicked()
{
	incidentReportWidget->SaveReport();
	SetButtonsSensitive(true, true, true, true, true, false);
	HideButtons(true, false, true, true, true, false);
}


void IncidentReportFunctionality::on_completeReportButton_clicked()
{
	incidentReportWidget->CompleteReport(true);
	on_saveReportButton_clicked();
}


void IncidentReportFunctionality::on_visualizeReportButton_clicked()
{

}

*/
