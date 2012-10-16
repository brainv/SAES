/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saescommon
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <glib.h>
#include <glibmm.h>
#include "s-a-e-s-common-conf-manager.h"
#include <System/IO/Path.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/ZenityWrapper.hxx>

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
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

#define LOGGER_PROJECT "Smartmatic.Configuration.SAESCommonConfigurationManager" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* SAESCommonConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* SAESCommonConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

SAESCommonConfigurationManager::SAESCommonConfigurationManager()
{
	Initialize();
}

auto_ptr<SaesCommonConfiguration>* SAESCommonConfigurationManager::getConfiguration()
{
	return configuration;
}

void SAESCommonConfigurationManager::Initialize()
{
	try
	{
		string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SAESCommon"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new  auto_ptr<SaesCommonConfiguration>(parseSaesCommonConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
		}
		else
		{
			LoadDefault();
			Initialize();
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESCOMMON Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESCOMMON Error", "Error");
		exit (0);
	}
}

void SAESCommonConfigurationManager::LoadDefault()
{
	SaesCommonConfiguration *configSAESCommon = new SaesCommonConfiguration();
	ConfigurationElectionFilesPath *configElectionFiles = new ConfigurationElectionFilesPath();
	ConfigurationPrinter *configPrinter = new ConfigurationPrinter();
	OSConfigurationFiles osConfig;
	LogConfigurationReader logConfigReader;
	BEIDConfiguration beidConfiguration;
	SmartCardConfiguration smartCardConfiguration;
	PCSCDConfiguration pcscdConfiguration;

	SecurityFileConfiguration installationFiles;
	SecurityFileConfiguration externalFiles;
    SecurityFileConfiguration resourcesFiles;
	SecurityFileConfiguration internalFiles;
    SecurityFileConfiguration utilFiles;
    SecurityFileConfiguration exchangeFiles;
    SecurityFileConfiguration printedVoteData;

	try
	{
        stringstream ss;
			
		Smartmatic::ConfigurationTypes::String defaultString("defaultConfiguration");

		configElectionFiles->setCodiFilesFolder("firstboot/INSTALLATION_FOLDER/codi_files");
		configElectionFiles->setSAESFolder("SAES");
        configElectionFiles->setResourcesFolder("StringResources");
		configElectionFiles->setImagesFolder("Images");
        configElectionFiles->setVotesFolder("Votes");
        configElectionFiles->setDocsFolder("Docs");
        configElectionFiles->setCodiFolder("Codi");
        configElectionFiles->setLogsFolderName("Logs");
        configElectionFiles->setTransmissionPackageFileName("transmission-package.xml");
        configElectionFiles->setTransmissionPackageHashFileName("transmission-package.hash");
        configElectionFiles->setTransmissionPackageKeyFileName("transmission-package.key");
        configElectionFiles->setTransmissionPackageCrtFileName("totKey.crt");
        configElectionFiles->setPVFormFileName("pv-report-data.xml");
		configElectionFiles->setElectionFileName("election.xml");		
        configElectionFiles->setElectionStatusFileName("election-status.xml");
        configElectionFiles->setCardListStatusFileName("card-list-status.xml");
		configElectionFiles->setElectionResourcesFileName("election-resources.xml");
        configElectionFiles->setVotingMachineStatusFileName("voting-device-status.xml");
        configElectionFiles->setVotingDeviceFileName("voting-devices.xml");
		configElectionFiles->setPollworkersFileName("pollworkers.xml");
		configElectionFiles->setStatisticsFileName("statistics.xml");
		configElectionFiles->setActivatedCardStatisticsFileName("activated-card-statistics.xml");
		configElectionFiles->setIncidentReportFileName("technical-troubles.xml");
        configElectionFiles->setClosingNotesFileName("closing-notes.xml");
        configElectionFiles->setXMLImageFileName("xml-image.xml");
		configElectionFiles->setAssistedActivationFileName("assisted-activations.xml");
		configElectionFiles->setVotingDisabledFileName("voting-disabled-information.xml");
		configElectionFiles->setPoliceNotesFileName("police-notes.xml");
		configElectionFiles->setLanguageFileName("default-languages.xml");
		configElectionFiles->setVotingCentersFileName("voting-centers.xml");
		configElectionFiles->setSecretKeyFile("secret-key");
		configElectionFiles->setUPKeyFile("up-key");
        configElectionFiles->setMachineKeysFile("machineKeys.p12");
        configElectionFiles->setX7SSignedKeyCertifiedFileName("signed-key.pem");
        configElectionFiles->setX7SSignedCertifiedFileName("signed-cert.pem");
        configElectionFiles->setX7SCryptoCertifiedFileName("certToEncrypt.crt");

        configElectionFiles->setCACertificateFileName("root-ca.crt");
		configElectionFiles->setItermediateCACertificatesFileName("intermediate-cas.crt");
		configElectionFiles->setItermediateCACertificatesFromPKCS12FileName("");
		configElectionFiles->setTrustedCertificatesFileName("trusted-c.crt");
		configElectionFiles->setTrustedCertificatesFromPKCS12FileName("");
		
		configElectionFiles->setIDCardMembersFileName("id-card-members-data.xml");

		configElectionFiles->setTransmissionPackageSignatureFileName("transmission-package.sig");
        configElectionFiles->setPVFormSignatureFileName("pv-report.sig");
		configElectionFiles->setPVTemplateFileName("PVTemplate.xslt");
		configElectionFiles->setGeneratedPVReportFileName("pv-report.pdf");
		configElectionFiles->setPVTemplateFolderName("PVTemplate");
		configElectionFiles->setElectionResultSignatureFileName("election-returns.sig");
		configElectionFiles->setVoteStatisticsFileName("vote-statistics.xml");
		configElectionFiles->setSignatureResourceFileName("Signature.xml");
		configElectionFiles->setLogErrorFileName("error-log-file.log");
		configElectionFiles->setLogAuditFileName("audit-log-file.log");

		configPrinter->setTimeToPrintTicket(500000);
		configPrinter->setSkipPrint(false);
		configPrinter->setUsePresentPaperOnline(false);
		configPrinter->setDefaultPrinterFontFamily("FreeSans");
		configPrinter->setEndPaddingDirectPrint(3);
		configPrinter->setCharsetDirectPrint(0);
		configPrinter->setCharPaddingDirectPrint(" ");
		configPrinter->setCharIndentationDirectPrint(" ");
		configPrinter->setCutType(Smartmatic::SAES::Common::Configuration::CutType::CONFIGURATION_PARTIALCUT);
		configPrinter->setPrinterBackendType(Smartmatic::SAES::Common::Configuration::PrinterBackendType::CONFIGURATION_GTKPRINTING);
		configPrinter->setDirectPrintDeleteFiles(true);
		configPrinter->setGeneratePVReportInAllLanguages(true);
		configPrinter->setCommandPrintingMode(Smartmatic::SAES::Common::Configuration::CommandPrintingModeType::CONFIGURATION_EMBEDDED_TEXT_CMD);
		configPrinter->setStatusMonitorTimeOut (1500);
		configPrinter->setStatusMonitorCancel (false);
		configPrinter->setDirectQrUseOptimization (false);
		configPrinter->setDirectQrCommandHeader ("<GS>s<10><128>");
		configPrinter->setDirectQrCommandFooter ("<GS>s<4><18>");
		configPrinter->setScreenPreviewWidth(450);
		configPrinter->setScreenPreviewResolutionFactor(72);

		osConfig.setIdHardwareFileFullPath("/live/image/osconf/machine.id");
        osConfig.setMasterDeviceFileFullPath("/tmp/MASTERDEVICE");
        osConfig.setEventDeviceFileFullPath("/tmp/EVENTDEVICE");
        osConfig.setLineDeviceSeparator(" ");
        osConfig.setRemoveEventDeviceFile(false);
        osConfig.setSerialLocationFileFullPath("/tmp/SerialLocation");
        osConfig.setLineSerialLocationSeparator("=");
        osConfig.setScriptRunSmartCard("smtt-smartcard");
        osConfig.setScriptRunPrintBlank("smtt-printblank");
        osConfig.setScriptRunDSortVote("smtt-dsort");
        osConfig.setSyncFileSignalUSER1("/tmp/SyncUSER1");
        osConfig.setSyncFileSignalUSER2("/tmp/SyncUSER2");

        logConfigReader.setLogAuditReader(CryptoType::CONFIGURATION_GLOBAL);
        logConfigReader.setLogErrorReader(CryptoType::CONFIGURATION_GLOBAL);

        beidConfiguration.setUseCallbackEvent(false);

        SmartCardConfiguration::NivelTestSequence nivelTest;
        nivelTest.push_back(NivelTestConfig::CONFIGURATION_SIMPLE_SELECT_APPLET);
        nivelTest.push_back(NivelTestConfig::CONFIGURATION_SIMPLE_WRITE_READ);
        smartCardConfiguration.setNivelTest(nivelTest);

		unsigned long long code = 2148532233LL;
		SmartCardConfiguration::FatalErrorCodesSequence fatalErrorCodes;
        fatalErrorCodes.push_back(code);
        smartCardConfiguration.setFatalErrorCodes(fatalErrorCodes);

        smartCardConfiguration.setAppletAID("F00000006203010C0101");
        smartCardConfiguration.setPlatformMode(PlatformMode::CONFIGURATION_GP_211);
        smartCardConfiguration.setGlobalPIN(GlobalPIN::CONFIGURATION_FIXED);
        smartCardConfiguration.setDataPIN(DataPIN::CONFIGURATION_VERIFICATION_KEY);
        smartCardConfiguration.setSecureChannelEnabled(false);
        smartCardConfiguration.setSecurityKeySetVersion(0);
        smartCardConfiguration.setSecurityKeyIndex(0);
        smartCardConfiguration.setSecurityChannelProtocol(SecurityChannelProtocol::CONFIGURATION_SCP02);
        smartCardConfiguration.setSecurityChannelProtocolImpl(SecurityChannelProtocolImpl::CONFIGURATION_SCP02_IMPL_I15);
        smartCardConfiguration.setSecurityLevel(SecurityLevel::CONFIGURATION_C_DEC_C_MAC);
        smartCardConfiguration.setSecurityKeyDerivation(SecurityKeyDerivation::CONFIGURATION_NONE);
        smartCardConfiguration.setUseConnectedSmartcardReader(false);
        smartCardConfiguration.setConnectedReaderRenewContext(false);
        smartCardConfiguration.setConnectedSmartcardPCSCCheckCard(false);
        smartCardConfiguration.setConnectedSmartcardConnectToCheckPresence(false);
        smartCardConfiguration.setSuspendResumeEachVote(false);
        smartCardConfiguration.setSuspendResumeOnErrorCondition(true);
        smartCardConfiguration.setDelayAfterSuspend(3);
        smartCardConfiguration.setDelayAfterOn(2);
        smartCardConfiguration.setShowMessagePowerCycle(true);
        smartCardConfiguration.setTimeOutMessagePowerCycle(5);
		smartCardConfiguration.setPowerCycleTries(3);
		smartCardConfiguration.setForceRestartPCSCD(false);
		smartCardConfiguration.setWaitStopPCSCD(2);
		smartCardConfiguration.setWaitStartPCSCD(4);
		smartCardConfiguration.setShowMessageRestartPCSCD(true);
		smartCardConfiguration.setReadRetry(3);

        pcscdConfiguration.setStartService(false);
        pcscdConfiguration.setStopService(false);

		ConfigurationBasePath configBasePath;
		configBasePath.setProjectName("SAES");
		configBasePath.setWorkingDirectory("SAESLocal");
		configBasePath.setLanguageImageDirectory("images");
		configBasePath.setBackupFileName("machineId");
		configBasePath.setVotingExperienceValidationScreensDirectory("VotingExperienceImages");

		configBasePath.setRulesBasePath(Smartmatic::SAES::Common::Configuration::RulesBasePathType::CONFIGURATION_PM_RULE);
		configBasePath.setLiveFileSystemBasePath("/live/image");
		
		configElectionFiles->setConfigBasePath (configBasePath);

        SecurityConfiguration security;

		SaltSourceType saltSource;

		guchar saltArray[20] = {
				  0x1, 0x2, 0x3, 0x4, 0x5
				, 0x6, 0x7, 0x8, 0x9, 0xa
		        , 0xb, 0xc, 0xd, 0xe, 0xf
		        , 0x10, 0x11, 0x12, 0x13, 0x14};

		Glib::ustring default_salt (g_base64_encode (saltArray, (gsize)sizeof (saltArray)));

		saltSource.setCalcSalt (true);
		saltSource.setSepChar ("|");
		saltSource.setDefaultSalt(default_salt.raw());

		SecurityFileConfiguration::ValidateCertifiedConfigSequence installationVCS;
        installationVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        installationFiles.setEncryptedData(true);
        installationFiles.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_NONE);
        installationFiles.setValidateSigned(false);
        installationFiles.setValidateCertifiedConfig( installationVCS );
        installationFiles.setCertifiedFilePath("");
        installationFiles.setCertifiedType(CertifiedType::CONFIGURATION_NONE);
        installationFiles.setValidateCertified(false);

        SecurityFileConfiguration::ValidateCertifiedConfigSequence externalVCS;
        externalVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        externalFiles.setEncryptedData(true);
        externalFiles.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_NONE);
        externalFiles.setValidateSigned(true);
        externalFiles.setValidateCertifiedConfig( externalVCS );
        externalFiles.setCertifiedFilePath("");
        externalFiles.setCertifiedType(CertifiedType::CONFIGURATION_NONE);
        externalFiles.setValidateCertified(false);

        SecurityFileConfiguration::ValidateCertifiedConfigSequence resourcesVCS;
        resourcesVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        resourcesFiles.setEncryptedData(true);
        resourcesFiles.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_NONE);
        resourcesFiles.setValidateSigned(true);
        resourcesFiles.setValidateCertifiedConfig( resourcesVCS );
        resourcesFiles.setCertifiedFilePath("");
        resourcesFiles.setCertifiedType(CertifiedType::CONFIGURATION_NONE);
        resourcesFiles.setValidateCertified(false);

        SecurityFileConfiguration::ValidateCertifiedConfigSequence internalVCS;
        internalVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        internalFiles.setEncryptedData(true);
        internalFiles.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_FULL);
        internalFiles.setValidateSigned(true);
        internalFiles.setValidateCertifiedConfig( internalVCS );
        internalFiles.setCertifiedFilePath(Path::Combine(configBasePath.getProjectName(), "machineKeys.p12"));
        internalFiles.setCertifiedType(CertifiedType::CONFIGURATION_PCKS12);
        internalFiles.setValidateCertified(false);

        SecurityFileConfiguration::ValidateCertifiedConfigSequence exchangeVCS;
        exchangeVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        exchangeFiles.setEncryptedData(true);
        exchangeFiles.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_FULL);
        exchangeFiles.setValidateSigned(true);
        exchangeFiles.setValidateCertifiedConfig( exchangeVCS );
        exchangeFiles.setCertifiedFilePath(Path::Combine(configBasePath.getProjectName(), "machineKeys.p12"));
        exchangeFiles.setCertifiedType(CertifiedType::CONFIGURATION_PCKS12);
        exchangeFiles.setValidateCertified(false);

        SecurityFileConfiguration::ValidateCertifiedConfigSequence voteVCS;
        voteVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        printedVoteData.setEncryptedData(false);
        printedVoteData.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_SIMPLE);
        printedVoteData.setValidateSigned(true);
        printedVoteData.setValidateCertifiedConfig( voteVCS );
        printedVoteData.setCertifiedFilePath(Path::Combine(configBasePath.getProjectName(), "machineKeys.p12"));
        printedVoteData.setCertifiedType(CertifiedType::CONFIGURATION_PCKS12);
        printedVoteData.setValidateCertified(false);

        SecurityFileConfiguration::ValidateCertifiedConfigSequence utilFilesVCS;
        utilFilesVCS.push_back(ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE);
        utilFiles.setEncryptedData(false);
        utilFiles.setSignedData(Smartmatic::SAES::Common::Configuration::SignedType::CONFIGURATION_FULL);
        utilFiles.setValidateSigned(true);
        utilFiles.setValidateCertifiedConfig( utilFilesVCS );
        utilFiles.setCertifiedFilePath(Path::Combine(configBasePath.getProjectName(), "machineKeys.p12"));
        utilFiles.setCertifiedType(CertifiedType::CONFIGURATION_PCKS12);
        utilFiles.setValidateCertified(false);

        security.setSecurityCryptoMode(SecurityCryptoMode::CONFIGURATION_CBC);
        security.setInstallationFiles(installationFiles);
        security.setExternalFiles(externalFiles);
		security.setResourcesFiles(resourcesFiles);
        security.setInternalFiles(internalFiles);
        security.setExchangeFiles(exchangeFiles);
        security.setUtilFiles(utilFiles);
        security.setPrintedVoteData(printedVoteData);
        security.setValidateCertifiedTime(TimeConfiguration::CONFIGURATION_NONE);

        security.setCertifiedTime("1970-01-01T00:00:00.00Z");
        security.setSaltSource(saltSource);
        security.setSecretKeyEncrypted(true);
        security.setForceReduceElection(false);
        security.setVerifySAESFolder(true);
        security.setImplementCACertificateFileName(false);
        security.setImplementItermediateCACertificates(false);
        security.setImplementTrustedCertificates(false);
        security.setSignedPVForm(false);

        security.setDigestAlg(DigestAlgType::CONFIGURATION_SHA1);
        security.setKeyDerivAlg(KeyDerivAlgType::CONFIGURATION_HMAC);
        security.setIterations(2048);
		security.setVerifyExternElements(false);
		security.setUseAsimetricKeyForTransmissionPackages(false);
		security.setIsCompressElection(true);
        security.setIsCompressVotingDevices(false);

		FileSystemVoteConfiguration fileSystemVote;
        fileSystemVote.setImplementRandom(true);
		fileSystemVote.setMaxfiles(5);
        fileSystemVote.setImplementTime(TimeConfiguration::CONFIGURATION_CONFIG_TIME);
        fileSystemVote.setFileSystemVoteTime("1970-01-01T00:00:00.00Z");
        fileSystemVote.setBackupMarkFile("markFile");

        security.setFileSystemVote(fileSystemVote);

        configSAESCommon->setMachineSecuritySchema(security);
        configSAESCommon->setConfigurationElectionFilesPath(*configElectionFiles);
		configSAESCommon->setConfigurationPrinter(*configPrinter);
		configSAESCommon->setOSConfigurationFiles(osConfig);
        configSAESCommon->setLogConfigurationReader(logConfigReader);
        configSAESCommon->setBEIDConfiguration(beidConfiguration);
        configSAESCommon->setSmartCardConfiguration(smartCardConfiguration);
        configSAESCommon->setPCSCDConfiguration(pcscdConfiguration);

        Smartmatic::ConfigurationTypes::NamespaceInfomap map;

#ifdef NAMESPACE_SAES_COMMON_CONFIGURATION
        map[""].name = NAMESPACE_SAES_COMMON_CONFIGURATION;
#endif
        map[""].schema = "";

		serializeSaesCommonConfiguration(ss,*configSAESCommon, map, "UTF-8");
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SAESCommon",ss.str());
		
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESCOMMON Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESCOMMON Error", "Error");
		exit (0);
	}

	delete(configSAESCommon);
	delete(configElectionFiles);
	delete(configPrinter);
}

PrinterBackendType & SAESCommonConfigurationManager::getPrinterBackendType()
{
    return (*configuration)->getConfigurationPrinter().getPrinterBackendType();
}

bool SAESCommonConfigurationManager::getStatusMonitorCancel()
{
    return (*configuration)->getConfigurationPrinter().getStatusMonitorCancel();
}

bool SAESCommonConfigurationManager::getDirectQrUseOptimization ()
{
    return (*configuration)->getConfigurationPrinter().getDirectQrUseOptimization ();
}

std::string SAESCommonConfigurationManager::getDirectQrCommandHeader ()
{
    return (*configuration)->getConfigurationPrinter().getDirectQrCommandHeader ();
}

std::string SAESCommonConfigurationManager::getDirectQrCommandFooter ()
{
    return (*configuration)->getConfigurationPrinter().getDirectQrCommandFooter ();
}

int SAESCommonConfigurationManager::getStatusMonitorTimeOut()
{
    return (*configuration)->getConfigurationPrinter().getStatusMonitorTimeOut();
}

bool SAESCommonConfigurationManager::isVerifyExternElements()
{
    return (*configuration)->getMachineSecuritySchema().getVerifyExternElements();
}

bool SAESCommonConfigurationManager::isCompressElection()
{
    return (*configuration)->getMachineSecuritySchema().getIsCompressElection();
}

bool SAESCommonConfigurationManager::isCompressVotingDevices()
{
    return (*configuration)->getMachineSecuritySchema().getIsCompressVotingDevices();
}

bool SAESCommonConfigurationManager::isUseAsimetricKeyForTransmissionPackages()
{
    return (*configuration)->getMachineSecuritySchema().getUseAsimetricKeyForTransmissionPackages();
}

SAESCommonConfigurationManager::~SAESCommonConfigurationManager()
{
	delete(configuration);
}

SecurityConfiguration & SAESCommonConfigurationManager::getSecurityConfiguration()
{
    return (*(getConfiguration()))->getMachineSecuritySchema();
}

BEIDConfiguration & SAESCommonConfigurationManager::getBEIDConfiguration()
{
	return (*(getConfiguration()))->getBEIDConfiguration();
}

SmartCardConfiguration & SAESCommonConfigurationManager::getSmartCardConfiguration()
{
	return (*(getConfiguration()))->getSmartCardConfiguration();
}

PCSCDConfiguration & SAESCommonConfigurationManager::getPCSCDConfiguration()
{
	return (*(getConfiguration()))->getPCSCDConfiguration();
}

FileSystemVoteConfiguration & SAESCommonConfigurationManager::getFileSystemVoteConfiguration()
{
    return getSecurityConfiguration().getFileSystemVote();
}

ConfigurationBasePath & SAESCommonConfigurationManager::getConfigBasePath()
{
	return (*(getConfiguration()))->getConfigurationElectionFilesPath().getConfigBasePath();
}

bool SAESCommonConfigurationManager::isPVInAllLanguages()
{
	return (*(getConfiguration()))->getConfigurationPrinter().getGeneratePVReportInAllLanguages();
}

bool SAESCommonConfigurationManager::isForceReduceElection()
{
	return (*(getConfiguration()))->getMachineSecuritySchema().getForceReduceElection();
}

OSConfigurationFiles & SAESCommonConfigurationManager::getOSConfigurationFiles()
{
	return ((*configuration)->getOSConfigurationFiles());
}

SAESCommonConfigurationManager * SAESCommonConfigurationManager::singleton_instance = NULL;

SAESCommonConfigurationManager *SAESCommonConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SAESCommonConfigurationManager ();

	return singleton_instance;
}
