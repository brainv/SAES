/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Voting/set-language-functionality.h"
#include "System/IO/File.h"
#include "Runtime/Environment/saes-directories.h"
#include "Voting/Election/ElectionInstalationLanguages.h"
#include "Environment/Configurations/base-language-controller.h"
#include "Resources/election-string-resources-manager.h"
#include <gtkmm.h>

using namespace std;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Resources;

static std::string currentLanguageCode = "en";

SetLanguageFunctionality::SetLanguageFunctionality()
{

}

SetLanguageFunctionality::~SetLanguageFunctionality()
{
	
}

std::string SetLanguageFunctionality::getCurrentLanguageCode ()
{
    return currentLanguageCode;
}

bool SetLanguageFunctionality::SetNewVotingLanguage(std::string codeLanguage)
{
    list<Smartmatic::SAES::Voting::Election::Language> listLang =
            Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->getLanguages();
    list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

    for(it = listLang.begin(); it != listLang.end(); it++)
    {
        if(it->getCode() == codeLanguage)
        {
            currentLanguageCode = codeLanguage;
            BaseLanguageController::LocalizeApplication(it->getLanguage(), it->getCountry());
            ElectionStringResourcesManager::Current()->setCurrentCulture(it->getCustom_code());
            return true;
        }
    }

    return false;
}

void SetLanguageFunctionality::getCurrentLanguageCountry(std::string & language, std::string & country)
{
    BaseLanguageController::GetActualLanguage( language, country );
}

bool SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(std::string language, std::string country)
{
    list<Smartmatic::SAES::Voting::Election::Language> listLang =
            Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->getLanguages();
    list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

    Glib::ustring li = language;
    Glib::ustring ci = country;
    li = li.lowercase();
    ci = ci.uppercase();

    //Set environment languages
    BaseLanguageController::LocalizeApplication(li.c_str(), ci.c_str());

    for(it = listLang.begin(); it != listLang.end(); it++)
    {
            Glib::ustring lf = it->getLanguage();
            Glib::ustring cf = it->getCountry();
            lf = lf.lowercase();
            cf = cf.uppercase();

            if(li == lf && ci == cf)
            {
                    ElectionStringResourcesManager::Current()->setCurrentCulture(it->getCustom_code());
                    return true;
            }
    }

    return false;
}
