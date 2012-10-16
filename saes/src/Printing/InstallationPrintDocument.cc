/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "InstallationPrintDocument.h"
#include "Voting/operation-status.h"
#include "Resources/election-string-resources-manager.h"
#include "Printing/TranslatorTextConfiguration.h"
#include "Environment/Configurations/resource-path-provider.h"
#include <System/Compression/compression-class.h>
#include <System/XML/Serialization/DomWriter.h>
#include <System/SafeBuffer.h>
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

using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::XML::Serialization;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System;
using namespace Smartmatic::Environment;
using namespace std;
using namespace Smartmatic::Log;

ISMTTLog* InstallationPrintDocument::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.InstallationPrintDocument",GETTEXT_PACKAGE);

InstallationPrintDocument::InstallationPrintDocument (Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, 
		bool installationReport, bool createBarcodeOnConstructor)
: BasePrintDocument()
{
	isPasswordRetry = false;
	_electoralConfiguration =  electoralConfiguration;
	this->installationReport = installationReport;

	this->configurationInstallation = (*SAESConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getConfigurationInstallation();

    if(SAESConfigurationManager::Current()->showBarCodeInstallationReport() && createBarcodeOnConstructor)
    {
        pixbufBarCode = Smartmatic::SAES::Printing::InstallationPrintDocument::GetQRCodeVotingMachineStatus();
    }
}

//getTextInstallationTitleLevel1
//getTextInstallationTitleLevel2
//getTextInstallationTitleLevel3
//getTextInstallationInfo

void InstallationPrintDocument::setIsPasswordRetry(bool isPasswordRetryA)
{
	isPasswordRetry = isPasswordRetryA;
}

void InstallationPrintDocument::PrintDoc()
{

	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;
	DocumentTextOptions textInstallationTitleLevel1 = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationInstallation.getTextInstallationTitleLevel1());
	DocumentTextOptions textInstallationTitleLevel2 = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationInstallation.getTextInstallationTitleLevel2());
	DocumentTextOptions textInstallationTitleLevel3 = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationInstallation.getTextInstallationTitleLevel3());
	DocumentTextOptions textInstallationInfo = TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(configurationInstallation.getTextInstallationInfo());

	AddHeader(textInstallationTitleLevel1, textInstallationTitleLevel2, textInstallationTitleLevel3,textInstallationInfo );

	if(_electoralConfiguration != NULL)
	{
		AddRegions(textInstallationTitleLevel1, textInstallationTitleLevel2, textInstallationTitleLevel3,textInstallationInfo );
	}


	if(isPasswordRetry == false)
	{
		AddDeviceStatus(textInstallationTitleLevel1, textInstallationTitleLevel2, textInstallationTitleLevel3,textInstallationInfo );
	}


	if(installationReport)
	{

		AddKeys(textInstallationTitleLevel1, textInstallationTitleLevel2, textInstallationTitleLevel3,textInstallationInfo );

	}

	if(this->configurationInstallation.getShowBarCode() && isPasswordRetry == false)
	{
		if(this->configurationInstallation.getQRcodePosition() == QRcodePosition::CONFIGURATION_BOTTOM_ALL)
		{
			this->DrawImage(pixbufBarCode,Smartmatic::SAES::Printing::Center);
			this->Indent(5);
		}
	}

	logger->Audit(N_("Smartmatic.SAES.Printing.InstallationPrintDocument.PrintInstallReport"));
}

void InstallationPrintDocument::AddHeader(
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{

	Voting_device device;
	Voting_booth votingBooth;

	if(_electoralConfiguration != NULL)
	{
		device = _electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
		votingBooth = (device.getVoting_booths().getVoting_booth())[0];
	}

	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	Glib::RefPtr<Gdk::Pixbuf> pixBuff  = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/installation-report-logo.bmp"));
	this->DrawImage(pixBuff, Left, InLineWithText, Border_Right, 10, 20, 10, 10);

	if(this->configurationInstallation.getShowBarCode() && isPasswordRetry == false)
	{
		if(this->configurationInstallation.getQRcodePosition() != QRcodePosition::CONFIGURATION_BOTTOM_ALL)
		{
			this->DrawImage(pixbufBarCode,Smartmatic::SAES::Printing::Center);
			this->Indent(5);
		}
	}

	NewTextBlock(textInstallationTitleLevel1);
	this->DrawString(" ",false);
	this->Indent(4);
	if(installationReport)
		this->DrawString(_("Smartmatic.SAES.Printing.InstallationPrintDocument.InstallationReportTitle"),false);
	else
		this->DrawString(_("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticReportTitle"),false);
	this->UnIndent(4);

	this->DrawString(" ",false);
	if(_electoralConfiguration != NULL)
	{
		// ELECTION NAME
		Smartmatic::SAES::Voting::Election::Election election = _electoralConfiguration->getElection()->getElection();
		Glib::ustring strElectionName = ElectionStringResourcesManager::Current()->getResource(election.getName_key());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		this->DrawString(strElectionName,false);
		this->UnIndent(6);
		// Voting booths
		Glib::ustring strVotingBooth = ElectionStringResourcesManager::Current()->getResource(votingBooth.getCustom_code());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		Glib::ustring strTitle = _("Smartmatic.SAES.Printing.InstallationPrintDocument.VotingBoothTitle");

		this->DrawString((Glib::ustring::compose(strTitle,strVotingBooth)),false);
		this->UnIndent(6);

		Glib::ustring votingCenterValue = ElectionStringResourcesManager::Current()->getResource(votingBooth.getPolling_place_name ());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		Glib::ustring strVotingCenter = _("Smartmatic.SAES.Printing.InstallationPrintDocument.VotingCenter");
		Glib::ustring composedVotingCenter = (Glib::ustring::compose(strVotingCenter,votingCenterValue));
		this->DrawString(composedVotingCenter,false);
		this->UnIndent(6);

		Glib::ustring votingCenterAddress = ElectionStringResourcesManager::Current()->getResource(votingBooth.getPolling_place_address ());
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		Glib::ustring strVotingCenterAddress = _("Smartmatic.SAES.Printing.InstallationPrintDocument.VotingCenterAddress");
		Glib::ustring composedVotingCenterAddress = (Glib::ustring::compose(strVotingCenterAddress,votingCenterAddress));
		this->DrawString(composedVotingCenterAddress,false);
		this->UnIndent(6);
	}
	else
	{
		std::string line = _("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine1");
		this->NewTextBlock(textInstallationTitleLevel2);
		this->Indent(6);
		if(line.size() > 0 &&  line != N_("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine1"))
		{
			this->DrawString(line,false);
		}

		line = _("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine2");
		if(line.size() > 0 &&  line != N_("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine2"))
		{
			this->DrawString(line,false);
		}

		line = _("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine3");
		if(line.size() > 0 &&  line != N_("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine3"))
		{
			this->DrawString(line,false);
		}
		line = _("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine4");
		if(line.size() > 0 &&  line != N_("Smartmatic.SAES.Printing.InstallationPrintDocument.DiagnosticAppReportDescLine4"))
		{
			this->DrawString(line,false);
		}
		this->UnIndent(6);
	}

	this->AddBreak ();

	NewTextBlock(textInstallationTitleLevel1);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);
}


void InstallationPrintDocument::AddRegions(
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{
	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	Voting_device device = _electoralConfiguration->getVotingDevice()->getFirstVotingDevice();
	Voting_booth votingBooth = (device.getVoting_booths().getVoting_booth())[0];


	NewTextBlock(textInstallationTitleLevel2);
	this->Indent(2);
	Glib::ustring strRegion = _("Smartmatic.SAES.Printing.InstallationPrintDocument.RegionTitle");
	this->DrawString(strRegion,true);
	this->DrawString(" ",true);
	this->UnIndent(2);

	this->NewTextColunmsBlock(listDocumentTextOptions);
	this->Indent(4);

	vector<Glib::ustring> vRegions = GetRegionsStrings(votingBooth);

	list<Glib::ustring> composedRegions;
	if(vRegions.size() == 8)
	{
		Glib::ustring messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region1");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region2");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region3");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region4");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region5");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region6");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region7");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}

		messageToCompose = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Region8");
		if(messageToCompose != " ")
		{
			composedRegions.push_back (Glib::ustring::compose(messageToCompose,vRegions[0],vRegions[1],vRegions[2],
					vRegions[3],vRegions[4],vRegions[5],vRegions[6],vRegions[7]));
		}
	}

	this->DrawStrings(composedRegions);
	this->UnIndent(4);
	NewTextBlock(textInstallationTitleLevel1);
	this->DrawString(" ",true);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);

}


void InstallationPrintDocument::AddDeviceStatus(
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{
	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	NewTextBlock(textInstallationTitleLevel2);
	this->Indent(2);
	Glib::ustring strDeviceStatus = _("Smartmatic.SAES.Printing.InstallationPrintDocument.DevicesStatus");
	this->DrawString(strDeviceStatus,true);
	this->DrawString(" ",true);
	this->UnIndent(2);



	this->NewTextColunmsBlock(listDocumentTextOptions);
	this->Indent(4);
	std::vector<std::string> DeviceStatusVector = OperationStatus::Current()->getDeviceStatusList();
	std::list<Glib::ustring> DeviceStatusList;
	int sizeDeviceStatus = DeviceStatusVector.size();

	for(int i=0;i < sizeDeviceStatus;i++)
	{
		Glib::ustring strDeciveStatus = DeviceStatusVector[i];
		int pos = strDeciveStatus.find("-");

		Glib::ustring status = ConvertToReadable(strDeciveStatus.substr (pos+1));
		Glib::ustring title = ConvertToReadable(strDeciveStatus.substr (0,pos));

		if(strDeciveStatus.substr (pos+1) != "NotDiagnosed")
		{
			this->DrawString(title,false);
			this->DrawString(status,false);
		}
	}
	this->UnIndent(4);

	NewTextBlock(textInstallationTitleLevel1);
	this->DrawString(" ",true);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);
}


void InstallationPrintDocument::AddKeys(
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel1,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel2,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationTitleLevel3,
		Smartmatic::SAES::Printing::DocumentTextOptions& textInstallationInfo)
{
	std::list<DocumentTextOptions> listDocumentTextOptions;
	std::list<Glib::ustring> str;

	Voting_device device = _electoralConfiguration->getVotingDevice()->getFirstVotingDevice();

	listDocumentTextOptions.push_back (textInstallationTitleLevel3);
	listDocumentTextOptions.push_back (textInstallationInfo);

	NewTextBlock(textInstallationTitleLevel2);
	this->Indent(2);
	Glib::ustring strKeys = _("Smartmatic.SAES.Printing.InstallationPrintDocument.ActivationKeys");
	this->DrawString(strKeys,true);
	this->DrawString(" ",true);
	this->UnIndent(2);

	Operation_mode operationMode = device.getOperation_modes().getOperation_mode()[0];


	this->NewTextColunmsBlock(listDocumentTextOptions);
	this->Indent(4);


	Glib::ustring strPasswordLine1 = Glib::ustring::compose(_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine1"), operationMode.getUnblocking_key (),
			operationMode.getRoles ().getRole ()[0].getKey ());
	Glib::ustring strPasswordLine2 = Glib::ustring::compose(_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine2"), operationMode.getUnblocking_key (),
			operationMode.getRoles ().getRole ()[0].getKey ());
	Glib::ustring strPasswordLine3 = Glib::ustring::compose(_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine3"), operationMode.getUnblocking_key (),
			operationMode.getRoles ().getRole ()[0].getKey ());
	Glib::ustring strPasswordLine4 = Glib::ustring::compose(_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine4"), operationMode.getUnblocking_key (),
			operationMode.getRoles ().getRole ()[0].getKey ());

	Glib::ustring strPasswordLine1Title = _("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine1Title");
	Glib::ustring strPasswordLine2Title = _("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine2Title");
	Glib::ustring strPasswordLine3Title = _("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine3Title");
	Glib::ustring strPasswordLine4Title = _("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine4Title");

	if(strPasswordLine1 != "" && strPasswordLine1
			!= N_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine1"))
	{
		this->DrawString(strPasswordLine1Title,false);
		this->DrawString(strPasswordLine1,false);
	}

	if(strPasswordLine2 != "" && strPasswordLine2
			!= N_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine2"))
	{
		this->DrawString(strPasswordLine2Title,false);
		this->DrawString(strPasswordLine2,false);
	}

	if(strPasswordLine3 != "" && strPasswordLine3
			!= N_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine3"))
	{
		this->DrawString(strPasswordLine3Title,false);
		this->DrawString(strPasswordLine3,false);
	}

	if(strPasswordLine4 != "" && strPasswordLine4
			!= N_("Smartmatic.SAES.Printing.InstallationPrintDocument.PasswordLine4"))
	{
		this->DrawString(strPasswordLine4Title,false);
		this->DrawString(strPasswordLine4,false);
	}

	this->UnIndent(4);

	NewTextBlock(textInstallationTitleLevel1);
	this->DrawString(" ",true);
	this->DrawLine (550.0, Center);
	this->DrawString(" ",true);

}


void InstallationPrintDocument::BeginPrint()
{

}

void InstallationPrintDocument::EndPrint()
{

}

vector<Glib::ustring> InstallationPrintDocument::GetRegionsStrings(const Voting_booth & votingBooth)
{
    std::list <Region_category> & listCategoryRegion (_electoralConfiguration->getRegionCategoryList());
    std::list <Region_category>::reverse_iterator it;
	std::list <Region_category> regionCategorytoShow;

	// get the last regionCategories
	const int maxRegions = 4;
	int aux =0;

	for ( it = listCategoryRegion.rbegin() ; it != listCategoryRegion.rend(); ++it )
	{
		regionCategorytoShow.push_back(*it);
		aux++;
		if(aux == maxRegions)
			break;
	}

	vector<Glib::ustring> vectorRegions;

	// get strings to show
	for(it = regionCategorytoShow.rbegin(); it != regionCategorytoShow.rend(); ++it)
	{
		vectorRegions.push_back(ElectionStringResourcesManager::Current()->getResource((*it).getName_key()));
		vectorRegions.push_back(ElectionStringResourcesManager::Current()->getResource((*it).getRegion().getName_key()));
	}

	int size = regionCategorytoShow.size();
	if(size < maxRegions)
	{
		for(int i=0;i<(maxRegions-size);i++)
		{
			vectorRegions.push_back("");
			vectorRegions.push_back("");
		}
	}

	return vectorRegions;
}

Glib::ustring InstallationPrintDocument::ConvertToReadable(const Glib::ustring & deviceName)
{
	Glib::ustring toReturn = deviceName;

	if(deviceName.compare("Ballot") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Ballot");
	}
	if(deviceName.compare("AlarmBox") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.AlarmBox");
	}
	else if(deviceName.compare("Barcode") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Barcode");
	}
	else if(deviceName.compare("Printer") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Printer");
	}
	else if(deviceName.compare("SmartCard") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Smartcard");
	}
	else if(deviceName.compare("Flash") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Flash");
	}
	else if(deviceName.compare("TouchScreenCalibration") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.TouchScreenCalibration");
	}
	else if(deviceName.compare("ScreenContrast") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.ScreenContrast");
	}
	else if(deviceName.compare("NotDiagnosed") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.NotDiagnosed");
	}
	else if(deviceName.compare("Error") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Error");
	}
	else if(deviceName.compare("Ok") == 0)
	{
		toReturn = _("Smartmatic.SAES.Printing.InstallationPrintDocument.Ok");
	}
	return toReturn;
}

Glib::RefPtr<Gdk::Pixbuf> InstallationPrintDocument::GetQRCodeVotingMachineStatus()
{
    Smartmatic::SAES::Configuration::QRCodeConfig config =
            SAESConfigurationManager::Current()->getQRCodeInstallConfig();

    int pixelSize = config.getSizeQRCode();
    int version = config.getVersionQRCode() ;
    int margin = config.getMarginQRCode();
    QRecLevel correctionLevel = SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());

	Smartmatic::SAES::Voting::VMStatusTypes::NamespaceInfomap map;
	map[""].name = NAMESPACE_VOTING_STATUS;
	map[""].schema = "";
	Smartmatic::SAES::Voting::VMStatusTypes::dom::auto_ptr< ::xercesc::DOMDocument > domptr =
			serializeVotingMachineStatus (
					Smartmatic::SAES::Voting::OperationStatus::Current()->getVotingMachineStatusWrapper()->getVotingMachineStatus(),
					map, Smartmatic::SAES::Voting::VMStatusTypes::Flags::dont_pretty_print);

	//Save signed vote to memory
	stringstream ss;
	DomWriter xmlWriter(ss);

	xmlWriter.Write(domptr.get());

	//compress vote
	std::string toDeflate(ss.str());

	SafeBuffer dataIn ((unsigned char *)toDeflate.c_str(), toDeflate.length());
	SafeBuffer dataDeflate;
	Smartmatic::System::Compression::CompressionClass::Deflate(dataIn, dataDeflate);
	SafeBuffer dataOut;
	Smartmatic::SAES::Security::Encryption::getInstance()->cryptoBufferToBuffer(dataDeflate, dataOut, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);

	gint width(0);
	gint height(0);

	Glib::RefPtr<Gdk::Drawable> drwptr;

	try
	{
		Glib::RefPtr<Gdk::Bitmap> bitmap(QREncoding::GenerateSymbol((guchar*)dataOut.GetData(),dataOut.GetSize(),pixelSize,margin,correctionLevel,version));
		bitmap->get_size(width,height);
		drwptr = bitmap;
	}
	catch(QREncodingException & ex)
	{
		std::stringstream ss;
		ss << "FATAL - " << __func__ << " " << ex.what();
		logger->Debug(ss.str());
	}


	Glib::RefPtr<Gdk::Pixbuf> pixBuf =  Gdk::Pixbuf::create(drwptr,0,0,width,height);

	return pixBuf;
}

void InstallationPrintDocument::setPixbufBarCode(Glib::RefPtr<Gdk::Pixbuf> pixbufBarCode)
{
    this->pixbufBarCode = pixbufBarCode;
}
