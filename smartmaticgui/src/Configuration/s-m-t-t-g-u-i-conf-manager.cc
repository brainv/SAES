/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
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

#include "s-m-t-t-g-u-i-conf-manager.h"
#include <Configuration/configuration-persistence-manager.h>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
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
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

ISMTTLog* SMTTGUIConfigurationManager::logger = SMTTLogManager::GetLogger("Smartmatic.Configuration.SMTTGUIConfigurationManager",GETTEXT_PACKAGE);

SMTTGUIConfigurationManager::SMTTGUIConfigurationManager()
{
	Initialize();
}


SMTTGUIConfigurationManager::~SMTTGUIConfigurationManager()
{
	if(configuration != NULL)
	{
		delete(configuration);
	}
}

void SMTTGUIConfigurationManager::Initialize()
{
	configuration = NULL;

	try
	{
		string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SMTTGUI"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new  auto_ptr<SmartmaticGUIConfiguration>(parseSmartmaticGUIConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
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
		ZenityWrapper::showError("Config SMTTGUI Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SMTTGUI Error", "Error");
		exit (0);
	}
}

auto_ptr<SmartmaticGUIConfiguration>* SMTTGUIConfigurationManager::getConfiguration()
{
	return configuration;
}

void SMTTGUIConfigurationManager::LoadDefault()
{
	SmartmaticGUIConfiguration configGUI;
//	SoundConfigurations* soundsConfiguration = new SoundConfigurations();
//	SoundConfigurations::SoundConfigurationSequence *seqsoundsConfiguration = new SoundConfigurations::SoundConfigurationSequence();
	BasicWindowConfiguration configBasicWindow;
	EventSoundsConfiguration eventSounds;
	AZERTYKeyboardWidgetConfiguration azertyConf;
	
	EntryPassPhraseConfiguration entryConf(EntryPassPhraseConfiguration::CONFIGURATION_CASESENSITIVE);
	ButtonsQuestionConfiguration buttonsQuestionConfiguration(ButtonsQuestionConfiguration::CONFIGURATION_ACCEPT_CANCEL);
	ButtonLabelSizeConfiguration buttonConf;

	GenderConfiguration genderConfiguration;
	GenderConfiguration::FemaleSequence fseq;
	GenderConfiguration::MaleSequence mseq;

	fseq.push_back("F");
	fseq.push_back("f");
	fseq.push_back("V");
	fseq.push_back("v");

	genderConfiguration.setFemale(fseq);

	mseq.push_back("M");
	mseq.push_back("m");

	genderConfiguration.setMale(mseq);

	try
	{
		stringstream ss;
	
		Smartmatic::ConfigurationTypes::String defaultString("defaultConfiguration");
		
		configBasicWindow.setHeight(1024);//mv
		configBasicWindow.setWidth(768);//mv
		//configBasicWindow.setHeight(600);//mp
		//configBasicWindow.setWidth(1024);//mp
		configBasicWindow.setHeaderHeight(85);
		configBasicWindow.setTitleHeight(85);
		configBasicWindow.setBottomHeight(85);
		configBasicWindow.setHorizontalPadding(5);
		configBasicWindow.setVerticalPadding(5);
		configGUI.setBasicWindowConfiguration (configBasicWindow);

		azertyConf.setShowChars(false);
		
		eventSounds.setSmartmaticButtonSound("SmartmaticButtonSound");
		eventSounds.setKeypadSound("KeyPadSound");//keypadsound
		eventSounds.setConfirmationDialogSound("ConfirmationVoteSound");//ConfirmationDialogSound
		eventSounds.setChooseDialogSound("QuestionVoteSound");//ChooseDialogSound
		eventSounds.setAzertyKeypadSound("AzertySound");
		eventSounds.setMenuSound("MenuSound");

		buttonConf.setAllButtons(13);
		buttonConf.setMenuButtons(14);

		configGUI.setEventSoundsConfiguration(eventSounds);
		configGUI.setAZERTYKeyboardWidgetConfiguration(azertyConf);

		configGUI.setEntryPassPhraseConfiguration(entryConf);
		configGUI.setButtonLabelSizeConfiguration(buttonConf);
		configGUI.setButtonsQuestionConfiguration(buttonsQuestionConfiguration);
		configGUI.setGenderConfiguration(genderConfiguration);

		/*
		SoundDescriptorConfiguration* soundNormalType = new SoundDescriptorConfiguration();
		soundNormalType->setFrequency(100);
		soundNormalType->setTime(400);
		soundNormalType->setRepetitions(1);
		soundNormalType->setTimeBetweenRepetitions(0);
		soundNormalType->setSoundType(SoundType::CONFIGURATION_NORMAL);

		SoundDescriptorConfiguration* soundAuthenticationType = new SoundDescriptorConfiguration();
		soundAuthenticationType->setFrequency(420);
		soundAuthenticationType->setTime(400);
		soundAuthenticationType->setRepetitions(1);
		soundAuthenticationType->setTimeBetweenRepetitions(0);
		soundAuthenticationType->setSoundType(SoundType::CONFIGURATION_AUTHENTICATION);

		SoundDescriptorConfiguration* soundElectionType = new SoundDescriptorConfiguration();
		soundElectionType->setFrequency(200);
		soundElectionType->setTime(2500);
		soundElectionType->setRepetitions(1);
		soundElectionType->setTimeBetweenRepetitions(0);
		soundElectionType->setSoundType(SoundType:: CONFIGURATION_ELECTION);
		
		SoundDescriptorConfiguration* soundMenuType = new SoundDescriptorConfiguration();
		soundMenuType->setFrequency(800);
		soundMenuType->setTime(400);
		soundMenuType->setRepetitions(1);
		soundMenuType->setTimeBetweenRepetitions(0);
		soundMenuType->setSoundType(SoundType::CONFIGURATION_MENU);

		SoundDescriptorConfiguration* okType = new SoundDescriptorConfiguration();
		okType->setFrequency(1200);
		okType->setTime(400);
		okType->setRepetitions(1);
		okType->setTimeBetweenRepetitions(0);
		okType->setSoundType(SoundType::CONFIGURATION_OK);

		SoundDescriptorConfiguration* errorType = new SoundDescriptorConfiguration();
		errorType->setFrequency(1600);
		errorType->setTime(400);
		errorType->setRepetitions(1);
		errorType->setTimeBetweenRepetitions(0);
		errorType->setSoundType(SoundType::CONFIGURATION_ERROR);

		SoundDescriptorConfiguration* keypadType = new SoundDescriptorConfiguration();
		keypadType->setFrequency(200);
		keypadType->setTime(400);
		keypadType->setRepetitions(1);
		keypadType->setTimeBetweenRepetitions(0);
		keypadType->setSoundType(SoundType::CONFIGURATION_KEYPAD);

		SoundDescriptorConfiguration* activationType = new SoundDescriptorConfiguration();
		activationType->setFrequency(800);
		activationType->setTime(400);
		activationType->setRepetitions(1);
		activationType->setTimeBetweenRepetitions(0);
		activationType->setSoundType(SoundType::CONFIGURATION_ACTIVATION);
		
		seqsoundsConfiguration->push_back(*soundNormalType);
		seqsoundsConfiguration->push_back(*soundAuthenticationType);
		seqsoundsConfiguration->push_back(*soundElectionType);
		seqsoundsConfiguration->push_back(*soundMenuType);
		seqsoundsConfiguration->push_back(*okType);
		seqsoundsConfiguration->push_back(*errorType);
		seqsoundsConfiguration->push_back(*keypadType);
		seqsoundsConfiguration->push_back(*activationType);
		
		soundsConfiguration->setSoundConfiguration(*seqsoundsConfiguration);
		configGUI->setSoundConfigurations(*soundsConfiguration);
			*/

        Smartmatic::ConfigurationTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_SMARTMATIC_GUI_CONFIGURATION;
        map[""].schema = "";

		serializeSmartmaticGUIConfiguration(ss,configGUI, map, "UTF-8");
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SMTTGUI",ss.str());
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SMTTGUI Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SMTTGUI Error", "Error");
		exit (0);
	}
}

/*
BeepDescriptor SMTTGUIConfigurationManager::GetSoundDescriptor(SoundType soundType)
{
	BeepDescriptor beepDescriptor;

	SoundConfigurations::SoundConfigurations* soundconfigurations = &(*SMTTGUIConfigurationManager::Current()->getConfiguration())->getSoundConfigurations();
	SoundConfigurations::SoundConfigurationSequence sequence = soundconfigurations->getSoundConfiguration();

	for(SoundConfigurations::SoundConfigurationIterator i (sequence.begin());	i != sequence.end();++i)
	{
		const SoundDescriptorConfiguration & soundDescritor (*i);

		if(soundDescritor.getSoundType() == soundType)
		{
			int frecuency = soundDescritor.getFrequency();
			int time = soundDescritor.getTime();
			int repetitions = soundDescritor.getRepetitions();
			int timeBetweenRepetitions = soundDescritor.getTimeBetweenRepetitions();
			BeepDescriptor beepDescriptor2 (frecuency, time, repetitions, timeBetweenRepetitions);
			beepDescriptor = beepDescriptor2;
		}
	}

	return beepDescriptor;	
}
*/
SMTTGUIConfigurationManager * SMTTGUIConfigurationManager::singleton_instance = NULL;

SMTTGUIConfigurationManager *SMTTGUIConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SMTTGUIConfigurationManager ();

	return singleton_instance;
}

int SMTTGUIConfigurationManager::getAllButtonsSize()
{
	return(*configuration)->getButtonLabelSizeConfiguration().getAllButtons();
}

int SMTTGUIConfigurationManager::getMenuButtonsSize()
{
	return(*configuration)->getButtonLabelSizeConfiguration().getMenuButtons();
}

bool SMTTGUIConfigurationManager::getAZERTYShowPass()
{
	return(*configuration)->getAZERTYKeyboardWidgetConfiguration().getShowChars();
}

std::string SMTTGUIConfigurationManager::getSmartmaticButtonSound()
{
	return(*configuration)->getEventSoundsConfiguration().getSmartmaticButtonSound();
}

std::string SMTTGUIConfigurationManager::getKeypadSound()
{
	return(*configuration)->getEventSoundsConfiguration().getKeypadSound();
}

std::string SMTTGUIConfigurationManager::getAzertyKeypadSound()
{
	return(*configuration)->getEventSoundsConfiguration().getAzertyKeypadSound();
}

std::string SMTTGUIConfigurationManager::getConfirmationDialogSound()
{
	return(*configuration)->getEventSoundsConfiguration().getConfirmationDialogSound();
}

std::string SMTTGUIConfigurationManager::getChooseDialogSound()
{
	return(*configuration)->getEventSoundsConfiguration().getChooseDialogSound();
}

std::string SMTTGUIConfigurationManager::getMenuSound()
{
	return(*configuration)->getEventSoundsConfiguration().getMenuSound();
}

EntryPassPhraseConfiguration::Value SMTTGUIConfigurationManager::getEntryConfiguration()
{
	return(*configuration)->getEntryPassPhraseConfiguration();
}

ButtonsQuestionConfiguration::Value SMTTGUIConfigurationManager::getButtonsQuestionConfiguration()
{
	return (*configuration)->getButtonsQuestionConfiguration();
}

GenderConfiguration SMTTGUIConfigurationManager::getGenderConfiguration()
{
	return (*configuration)->getGenderConfiguration();
}

void SMTTGUIConfigurationManager::getGenderFemaleConfiguration(std::list <std::string> & list)
{
	list.clear();
	GenderConfiguration::FemaleSequence seq = getGenderConfiguration().getFemale();
	GenderConfiguration::FemaleIterator it;

	for (it = seq.begin();
			it != seq.end();
			it++)
	{
		list.push_back((*it));
	}
}

void SMTTGUIConfigurationManager::getGenderMaleConfiguration(std::list <std::string> & list)
{
	list.clear();
	GenderConfiguration::MaleSequence seq = getGenderConfiguration().getMale();
	GenderConfiguration::MaleIterator it;

	for (it = seq.begin();
			it != seq.end();
			it++)
	{
		list.push_back((*it));
	}
}
