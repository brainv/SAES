/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#include "change-language-widget.h"
#include "Voting/set-language-functionality.h"
#include "Environment/Configurations/base-language-controller.h"
#include "Voting/Election/election-language-schema.hxx"
#include "System/IO/File.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Voting/Election/ElectionInstalationLanguages.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include "MenuWidget.hxx"

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
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

ISMTTLog* ChangeLanguageWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ChangeLanguageWidget",GETTEXT_PACKAGE);

ChangeLanguageWidget::ChangeLanguageWidget()
{
	set_shadow_type(SHADOW_NONE);
	this->saveFile = true;
	this->imageWidget = NULL;
	this->showMessage = false;
	this->labelMessage = NULL;
}

ChangeLanguageWidget::~ChangeLanguageWidget()
{
	
}

void ChangeLanguageWidget::init(Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories)
{
	this->directories = directories;
}

void ChangeLanguageWidget::SetShowMessage(bool shoMessageA)
{
	this->showMessage = shoMessageA;
};

void ChangeLanguageWidget::on_image_selected(std::string imageCode)
{
	MenuWidget::reloadMenu = true;

	list<Smartmatic::SAES::Voting::Election::Language> listLang =
	        Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->getLanguages();
	list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

	for(it = listLang.begin(); it != listLang.end(); it++)
	{
        if((it->getCode() == imageCode))
		{	
			string fileToCreate = directories->getLanguageLocalFileFullPath();

			Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->setInstallationLanguages(*it);
            Smartmatic::SAES::Voting::SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(it->getLanguage(), it->getCountry());
            //SetNewVotingLanguage(it->getCode());

            if (saveFile)
            {
                try
                {
                    Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->persistLanguage();
                }
                catch (CryptoException & ex)
                {
        	        std::stringstream ss;
        	        ss  << "FATAL - " << __func__ << " " << ex.what();
        	        logger->Debug(ss.str());
                }
                catch (SignedException & ex)
                {
        	        std::stringstream ss;
        	        ss  << "FATAL - " << __func__ << " " << ex.what();
        	        logger->Debug(ss.str());
                }
                catch (XmlException & ex)
                {
        	        std::stringstream ss;
        	        ss  << "FATAL - " << __func__ << " " << ex.what();
        	        logger->Debug(ss.str());
                }
                catch(...)
                {
        	        std::stringstream ss;
        	        ss  << "FATAL - " << __func__;
        	        logger->Debug(ss.str());
                }
            }

			if (labelMessage)
			{
				labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.ChangeLanguageWidget.MessageKey"));
			}

			logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ChangeLanguageWidget.LanguageChanged"));
			
			m_language_changed.emit();

			break;
		}
	}


}

bool ChangeLanguageWidget::loadDefaultLanguage()
{
	list<Smartmatic::SAES::Voting::Election::Language> listLang =
			Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->getLanguages();

    list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

	if ( listLang.size() == 1 )
	{
		on_image_selected( (*listLang.begin()).getCode() );
		return true;
	}

    for(it = listLang.begin(); it != listLang.end(); it++)
    {
        if(it->getIs_default())
        {
            Smartmatic::SAES::Voting::SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(it->getLanguage(), it->getCountry());
            return true;
        }
    }

    return false;
}

void ChangeLanguageWidget::initialize(std::list<Smartmatic::SAES::Voting::Election::Language>& listLang, bool showOnOneLanguage)
{
	this->remove();

	vector<string> imagesPath;
	vector<string> imagesCode;

	string imagesFolder;

	string folderDom = directories->getLanguageImageDirectoryFullPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
	string folderFlash = directories->getLanguageImageDirectoryFullPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH);

	if(Smartmatic::System::IO::Directory::DirectoryExists(folderDom))
	{
		imagesFolder = folderDom;
		logger->Debug("Load languages in DOM");
	}
	else if(Smartmatic::System::IO::Directory::DirectoryExists(folderFlash))
	{
		imagesFolder = folderFlash;
		logger->Debug("Load languages in Flash");
	}
	else
	{
		imagesFolder = directories->getLanguageImageInstalationDirectoryFullPath();
	}

    if (listLang.size() != 0)
    {
        list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

		if ( listLang.size() == 1 && !showOnOneLanguage )
		{
			on_image_selected( (*listLang.begin()).getCode() );
			return;
		}

        for(it = listLang.begin(); it != listLang.end(); it++)
        {
            Smartmatic::SAES::Voting::Election::Language lang = *it;
            string image = Path::Combine(imagesFolder , lang.getLanguage()+"_"+lang.getCountry() + ".img");
            imagesPath.push_back(image);
            imagesCode.push_back(lang.getCode());
        }
    }
    else
    {
        Gtk::Label* label = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.ChangeLanguageWidget.ConfigurationNotFound")));
        add(*label);
    	show_all_children ();
        return;
    }

	imageWidget = manage(new ImageSelectionWidget(imagesPath, imagesCode));
	imageWidget->clicked().connect(sigc::mem_fun(*this,&ChangeLanguageWidget::on_image_selected));

	clientAreaAlignment = manage(new Gtk::Alignment());
	clientAreaAlignment->add(*imageWidget);

	if(showMessage == true)
	{
		Gtk::VBox* box = manage(new Gtk::VBox());

		labelMessage = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.ChangeLanguageWidget.MessageKey")));

		Pango::FontDescription fontTitle = labelMessage->get_style()->get_font();
		fontTitle.set_size(16*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
		labelMessage->modify_font(fontTitle);

		Gtk::EventBox* eventBox = manage(new Gtk::EventBox());
		eventBox->set_name(SAESGUIConfigurationManager::Current()->GetChangeLanguageMessageWigdetEventboxName());
		eventBox->add(*labelMessage);
		eventBox->show_all();
		box->add(*eventBox);

		if((int)imagesPath.size() == 2)
			clientAreaAlignment->set_padding( 80, 150, 135, 135);
		else
			clientAreaAlignment->set_padding( 80, 150, 55, 55);

		box->add(*clientAreaAlignment);
		add(*box);
	}
	else
	{
		if((int)imagesPath.size() == 2)
		{
			clientAreaAlignment->set_padding( 150, 150, 135, 135);
		}
		else
		{
			clientAreaAlignment->set_padding( 150, 150, 55, 55);
		}

		add(*clientAreaAlignment);
	}

	Smartmatic::SAES::Functionality::Configuration::AppType apptoLaunch=
		Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration().getAppType();

	if(apptoLaunch == Smartmatic::SAES::Functionality::Configuration::AppType::CONFIGURATION_VOTINGONLY)
	{
		if((int)imagesPath.size() == 2)
		{
			imageWidget->set_spacing(50);
			clientAreaAlignment->set_padding( 70, 100, 80, 80);
		}
		else
		{
			clientAreaAlignment->set_padding( 150, 150, 55, 55);
		}
	}

	show_all_children ();
}

ChangeLanguageWidget::language_changed ChangeLanguageWidget::LanguageChanged()
{
	return m_language_changed;
};

void ChangeLanguageWidget::SetSaveFile(bool saveFileA)
{
	saveFile = saveFileA;
};
