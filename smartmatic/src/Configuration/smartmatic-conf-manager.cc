

#include "smartmatic-conf-manager.h"
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
using namespace Smartmatic::Configuration;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

ISMTTLog* SmartmaticConfigurationManager::logger = SMTTLogManager::GetLogger("Smartmatic.Configuration.SmartmaticConfigurationManager",GETTEXT_PACKAGE); ///< The smartmatic configuration manager logger


SmartmaticConfigurationManager::SmartmaticConfigurationManager()
{
	Initialize();
}

SmartmaticConfigurationManager::~SmartmaticConfigurationManager()
{
	if(configuration != NULL)
	{
		delete(configuration);
	}
}


void SmartmaticConfigurationManager::Initialize()
{
	configuration = NULL;
	try
	{
		string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SMTT"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new  auto_ptr<SmartmaticConfiguration>(parseSmartmaticConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
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
		ZenityWrapper::showError("Config SMTT Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SMTT Error", "Error");
		exit (0);
	}
}


auto_ptr<SmartmaticConfiguration>* SmartmaticConfigurationManager::getConfiguration()
{
	return configuration;
}

std::vector<std::string> SmartmaticConfigurationManager::getListOfResourcesPaths()
{
	std::vector<std::string> list;
	::xsd::cxx::tree::sequence< ::Smartmatic::ConfigurationTypes::String > pathsSequence = (*configuration)->getResourcePaths().getResourcePath ();
	for(unsigned int i = 0;i < pathsSequence.size();i++)
	{
		list.push_back(pathsSequence[i]) ;
	}
	return list;

}

bool SmartmaticConfigurationManager::isUseBeep()
{
	return getConfiguration()->get()->getSoundOutput().getUseBeep();
}

std::string SmartmaticConfigurationManager::getAppSound()
{
	return getConfiguration()->get()->getSoundOutput().getAppSound();
}

std::string SmartmaticConfigurationManager::getSoundFile(std::string sound)
{
	std::string soundFile;

	for(unsigned int i = 0;i < (*configuration)->getSoundOutput().getSoundConfigurations().size();i++)
	{
		if((*configuration)->getSoundOutput().getSoundConfigurations()[i].getName().compare(sound)==0)
		{
			if ((*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundFile().present())
			{
				soundFile = (*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundFile().get();
			}
			break;
		}
	}

	return soundFile;
}

std::vector<Smartmatic::System::Sounds::BeepDescriptor> SmartmaticConfigurationManager::GetSoundConfiguration(std::string sound)
{
	std::vector<Smartmatic::System::Sounds::BeepDescriptor> sounds;
	
	for(unsigned int i = 0;i < (*configuration)->getSoundOutput().getSoundConfigurations().size();i++)
	{
		if((*configuration)->getSoundOutput().getSoundConfigurations()[i].getName().compare(sound)==0)
		{
			for(unsigned int j = 0;j < (*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundConfiguration().size();j++)
			{
				int frecuency = (*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundConfiguration()[j].getFrequency();
				int time = (*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundConfiguration()[j].getTime();
				int repetitions = (*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundConfiguration()[j].getRepetitions();
				int timeBetweenRepetitions = (*configuration)->getSoundOutput().getSoundConfigurations()[i].getSoundConfiguration()[j].getTimeBetweenRepetitions();
				BeepDescriptor beepDescriptor(frecuency, time, repetitions, timeBetweenRepetitions);
				sounds.push_back(beepDescriptor);
			}
			break;
		}
	}

	return sounds;	
}

bool SmartmaticConfigurationManager::getImageStorageInMemory()
{
	return (*configuration)->getImageResources().getStoreInMemory();
}


void SmartmaticConfigurationManager::LoadDefault()
{
	SmartmaticConfiguration *configSmartmatic = new SmartmaticConfiguration();
	ResourcePaths *paths = new ResourcePaths();
	SoundOutput *soundOutput = new SoundOutput();
	::xsd::cxx::tree::sequence< SoundOutput::SoundConfigurationsType > *sequenceSoundConf = new ::xsd::cxx::tree::sequence< SoundOutput::SoundConfigurationsType >();
	::xsd::cxx::tree::sequence< ::Smartmatic::ConfigurationTypes::String > *pathsSequence
			= new ::xsd::cxx::tree::sequence< ::Smartmatic::ConfigurationTypes::String >();

	ImageResources *imageRes = new ImageResources();	
	try
	{
        stringstream ss;
		Smartmatic::ConfigurationTypes::String defaultString("defaultConfiguration");
		pathsSequence->push_back(DATADIR);
		//pathsSequence->push_back("/usr/local/share/");
		pathsSequence->push_back("/usr/local/");
		paths->setResourcePath(*pathsSequence);
		imageRes->setStoreInMemory(true);
		//sequenceSoundConf->

	////////////////////////////////////////////////
	//////////////////NOTES////////////////////////
		SoundDescriptorConfiguration soundDo;
		soundDo.setFrequency(261);
		soundDo.setTime(400);
		soundDo.setRepetitions(1);
		soundDo.setTimeBetweenRepetitions(0);
		
		SoundDescriptorConfiguration soundRe;
		soundRe.setFrequency(293);
		soundRe.setTime(400);
		soundRe.setRepetitions(1);
		soundRe.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundMi;
		soundMi.setFrequency(329);
		soundMi.setTime(400);
		soundMi.setRepetitions(1);
		soundMi.setTimeBetweenRepetitions(0);
		
		SoundDescriptorConfiguration soundFa;
		soundFa.setFrequency(349);
		soundFa.setTime(400);
		soundFa.setRepetitions(1);
		soundFa.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundSol;
		soundSol.setFrequency(391);
		soundSol.setTime(400);
		soundSol.setRepetitions(1);
		soundSol.setTimeBetweenRepetitions(0);
		
		SoundDescriptorConfiguration soundLa;
		soundLa.setFrequency(440);
		soundLa.setTime(400);
		soundLa.setRepetitions(1);
		soundLa.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundSi;
		soundSi.setFrequency(423);
		soundSi.setTime(200);
		soundSi.setRepetitions(0);
		soundSi.setTimeBetweenRepetitions(0);
	
		SoundDescriptorConfiguration soundDoPlus;
		soundDoPlus.setFrequency(223);
		soundDoPlus.setTime(50);
		soundDoPlus.setRepetitions(0);
		soundDoPlus.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundSmartmaticButton;
		soundSmartmaticButton.setFrequency(233);
		soundSmartmaticButton.setTime(50);
		soundSmartmaticButton.setRepetitions(0);
		soundSmartmaticButton.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundValidPassword;
		soundValidPassword.setFrequency(423);
		soundValidPassword.setTime(200);
		soundValidPassword.setRepetitions(0);
		soundValidPassword.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundVotePrint;
		soundVotePrint.setFrequency(1223);
		soundVotePrint.setTime(2000);
		soundVotePrint.setRepetitions(0);
		soundVotePrint.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundNone;
		soundNone.setFrequency(223);
		soundNone.setTime(50);
		soundNone.setRepetitions(0);
		soundNone.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundScanNormalVote;
		soundScanNormalVote.setFrequency(423);
		soundScanNormalVote.setTime(200);
		soundScanNormalVote.setRepetitions(0);
		soundScanNormalVote.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundScanBadVote;
		soundScanBadVote.setFrequency(261);
		soundScanBadVote.setTime(400);
		soundScanBadVote.setRepetitions(1);
		soundScanBadVote.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundScanDuplicatedVote;
		soundScanDuplicatedVote.setFrequency(440);
		soundScanDuplicatedVote.setTime(400);
		soundScanDuplicatedVote.setRepetitions(1);
		soundScanDuplicatedVote.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundBarcodeDataReceivedVote;
		soundBarcodeDataReceivedVote.setFrequency(440);
		soundBarcodeDataReceivedVote.setTime(500);
		soundBarcodeDataReceivedVote.setRepetitions(1);
		soundBarcodeDataReceivedVote.setTimeBetweenRepetitions(0);

		SoundDescriptorConfiguration soundBadVoterCardInsertion;
		soundBadVoterCardInsertion.setFrequency(440);
		soundBadVoterCardInsertion.setTime(400);
		soundBadVoterCardInsertion.setRepetitions(1);
		soundBadVoterCardInsertion.setTimeBetweenRepetitions(0);

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
		

		SoundConfigurations DateTime;
		DateTime.getSoundConfiguration().push_back(soundDoPlus);
		/*
		DateTime.getSoundConfiguration().push_back(soundFa);
		DateTime.getSoundConfiguration().push_back(soundSol);
		DateTime.getSoundConfiguration().push_back(soundLa);
		DateTime.getSoundConfiguration().push_back(soundSi);
		DateTime.getSoundConfiguration().push_back(soundLa);
		DateTime.getSoundConfiguration().push_back(soundSol);
		DateTime.getSoundConfiguration().push_back(soundMi);
		DateTime.getSoundConfiguration().push_back(soundDo);
		DateTime.getSoundConfiguration().push_back(soundRe);
		DateTime.getSoundConfiguration().push_back(soundMi);
		DateTime.getSoundConfiguration().push_back(soundFa);
		DateTime.getSoundConfiguration().push_back(soundRe);
		DateTime.getSoundConfiguration().push_back(soundRe);
		*/
		DateTime.setName("DateTimeSound");

		SoundConfigurations SmartmaticButton;
		SmartmaticButton.getSoundConfiguration().push_back(soundSmartmaticButton);
		SmartmaticButton.setName("SmartmaticButtonSound");
		SmartmaticButton.setSoundFile("button-02.wav");
		
		SoundConfigurations InstallationAzerty;
		InstallationAzerty.getSoundConfiguration().push_back(soundDoPlus);
		InstallationAzerty.setName("AzertySound");
		
		SoundConfigurations KeyPad;
		KeyPad.getSoundConfiguration().push_back(soundDoPlus);
		KeyPad.setName("KeyPadSound");
		
		SoundConfigurations Menu;
		Menu.getSoundConfiguration().push_back(soundDoPlus);
		Menu.setName("MenuSound");
		
		SoundConfigurations Diagnostics;
		Diagnostics.getSoundConfiguration().push_back(soundDoPlus);
		Diagnostics.setName("DiagnosticSound");

		SoundConfigurations QuestionVoteExp;
		QuestionVoteExp.getSoundConfiguration().push_back(soundDoPlus);
		QuestionVoteExp.setName("QuestionVoteSound");
		
		SoundConfigurations ConfirmationVoteExp;
		ConfirmationVoteExp.getSoundConfiguration().push_back(soundDoPlus);
		ConfirmationVoteExp.setName("ConfirmationVoteSound");
		
		SoundConfigurations VotePrint;
		VotePrint.getSoundConfiguration().push_back(soundVotePrint);
		VotePrint.setName("VotePrintSound");
		
		SoundConfigurations PartyVoteExp;
		PartyVoteExp.getSoundConfiguration().push_back(soundDoPlus);
		PartyVoteExp.setName("PartyVoteSound");
		
		SoundConfigurations BallotVoteExp;
		BallotVoteExp.getSoundConfiguration().push_back(soundNone);
		BallotVoteExp.setName("BallotVoteSound");

		SoundConfigurations InvalidPassword;
		InvalidPassword.getSoundConfiguration().push_back(soundSi);
		InvalidPassword.setName("InvalidPasswordSound");
		
		SoundConfigurations ValidPassword;
		ValidPassword.getSoundConfiguration().push_back(soundValidPassword);
		ValidPassword.setName("ValidPasswordSound");

		SoundConfigurations ScanNormalVote;
		ScanNormalVote.getSoundConfiguration().push_back(soundScanNormalVote);
		ScanNormalVote.setName("ScanNormalVoteSound");
		ScanNormalVote.setSoundFile("beep-02.wav");

		SoundConfigurations ScanBadVote;
		ScanBadVote.getSoundConfiguration().push_back(soundScanBadVote);
		ScanBadVote.setName("ScanBadVoteSound");
		ScanBadVote.setSoundFile("beep-04.wav");

		SoundConfigurations ScanDuplicatedVote;
		ScanDuplicatedVote.getSoundConfiguration().push_back(soundScanDuplicatedVote);
		ScanDuplicatedVote.setName("ScanDuplicatedVoteSound");
		ScanDuplicatedVote.setSoundFile("beep-08.wav");

		SoundConfigurations barcodeDataReceivedVoteSound;
		barcodeDataReceivedVoteSound.getSoundConfiguration().push_back(soundBarcodeDataReceivedVote);
		barcodeDataReceivedVoteSound.setName("BarcodeDataReceivedVoteSound");
		
		SoundConfigurations badVoterCardInsertion;
		badVoterCardInsertion.getSoundConfiguration().push_back(soundBadVoterCardInsertion);
		badVoterCardInsertion.setName("BadVoterCardInsertion");

		sequenceSoundConf->push_back (SmartmaticButton);
		sequenceSoundConf->push_back (DateTime);
		sequenceSoundConf->push_back (InstallationAzerty);
		sequenceSoundConf->push_back (KeyPad);
		sequenceSoundConf->push_back (Menu);
		sequenceSoundConf->push_back (Diagnostics);
		sequenceSoundConf->push_back (QuestionVoteExp);
		sequenceSoundConf->push_back (ConfirmationVoteExp);
		sequenceSoundConf->push_back (PartyVoteExp);
		sequenceSoundConf->push_back (BallotVoteExp);
		sequenceSoundConf->push_back (InvalidPassword);
		sequenceSoundConf->push_back (ValidPassword);
		sequenceSoundConf->push_back (VotePrint);
		sequenceSoundConf->push_back (ScanNormalVote);
		sequenceSoundConf->push_back (ScanBadVote);
		sequenceSoundConf->push_back (ScanDuplicatedVote);
		sequenceSoundConf->push_back (barcodeDataReceivedVoteSound);
		sequenceSoundConf->push_back (badVoterCardInsertion);
		
		soundOutput->setUseBeep(true);
		soundOutput->setAppSound("aplay -q");
		soundOutput->setSoundConfigurations(*sequenceSoundConf);
		configSmartmatic->setSoundOutput(*soundOutput);
		configSmartmatic->setResourcePaths (*paths);
		configSmartmatic->setImageResources (*imageRes);

        Smartmatic::ConfigurationTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_SMARTMATIC_CONFIGURATION;
        map[""].schema = "";

		serializeSmartmaticConfiguration(ss,*configSmartmatic, map, "UTF-8");
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SMTT",ss.str());

	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SMTT Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SMTT Error", "Error");
		exit (0);
	}

	delete(imageRes);
	delete(soundOutput);
	delete(sequenceSoundConf);
	delete(pathsSequence);
	delete(paths);
	delete(configSmartmatic);
}



SmartmaticConfigurationManager * SmartmaticConfigurationManager::singleton_instance = NULL; ///< The smartmatic configuration manager singleton instance


SmartmaticConfigurationManager *SmartmaticConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SmartmaticConfigurationManager ();

	return singleton_instance;
}
