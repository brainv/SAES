
#include "base-language-controller.h"
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
extern int _nl_msg_cat_cntr;
#else
#define _(String) (String) ///<macro without gettext
static int _nl_msg_cat_cntr;
#endif

#define N_(String) (String) ///<macro for gettext not translate

#include <unistd.h>
#include <stdlib.h>
#include <glibmm.h>
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Utils;

ISMTTLog* BaseLanguageController::logger = SMTTLogManager::GetLogger("Smartmatic.Environment.BaseLanguageController",GETTEXT_PACKAGE); ///< The base language controller logger

bool BaseLanguageController::setLanguage = false;

BaseLanguageController::BaseLanguageController()
{
	
}

BaseLanguageController::~BaseLanguageController()
{
}

std::string BaseLanguageController::actLanguage = ""; ///< The base language controller act language

std::string BaseLanguageController::actCountry = ""; ///< The base language controller act country


void BaseLanguageController::LocalizeApplication(const char * newLanguage, const char * newCountry)
{
  std::string lang ;
  std::string locale;

  lang.append(newLanguage);
  locale.append(newCountry);

  LocalizeApplication(lang, locale);

}


void BaseLanguageController::LocalizeApplication(std::string& newLanguage, std::string& newCountry)
{
	if (newLanguage.empty())
	{
		logger->Debug("ERROR - language requested");
		return;
	}

	Glib::ustring lang = newLanguage;
	Glib::ustring country = newCountry;
    std::stringstream ss;

    if ( country == "" ) country = lang;

	actLanguage = lang.lowercase();
	actCountry = country.uppercase();

    std::string fullLanguageName;
    fullLanguageName = actLanguage;
    fullLanguageName += "_";
    fullLanguageName += actCountry;

    FullLocalizeApplication(fullLanguageName);
}

void BaseLanguageController::FullLocalizeApplication(std::string fullLanguage)
{
    std::string langMacro;

    if(getenv("LANGUAGE"))
      langMacro = "LANGUAGE";
    else
      langMacro = "LANG";


    if(fullLanguage.size() > 0)
    {
        std::string curLang;
        std::stringstream ss;
        curLang.append(getenv(langMacro.c_str()));

        if(setenv (langMacro.c_str(), actLanguage.c_str(), 1))
        {
            logger->Debug("Cannot set new language");
        }
        else /* Make change known.  */
        {
            ++_nl_msg_cat_cntr;
        }
    }

    if(fullLanguage.size()>0)
    {
    	Glib::ustring lang;
    	Glib::ustring country;

        std::list < std::string > listLang = StringUtils::split(fullLanguage, "_");
        std::list < std::string >::iterator itl;

        int count = 0;

        for( itl = listLang.begin();
        	 itl != listLang.end();
        	 itl++, count++)
        {
        	if (count == 0)
        	{
        		lang = country = (*itl);
        	}
        	else
        	{
        		country = (*itl);
        	}
        }

    	actLanguage = lang.lowercase();
    	actCountry = country.uppercase();

        std::string curLocale;
        fullLanguage += ".utf8";

        curLocale.append(setlocale (LC_ALL, NULL));

        if (curLocale != fullLanguage)
        {
            std::stringstream ss;
			ss << "Changing Locale. From: ";
			ss << curLocale << " To: " << fullLanguage;
			logger->Debug(ss.str());

			curLocale = setlocale (LC_ALL, fullLanguage.c_str());

			BaseLanguageController::setLanguage = true;
        }
    }
}

void BaseLanguageController::GetActualLanguage(std::string& actualLanguage, std::string& actualCountry)
{
	actualLanguage = actLanguage;
	actualCountry = actCountry;
}

std::string BaseLanguageController::getActualLanguage()
{
    return actLanguage + "_" + actCountry;
}

void BaseLanguageController::InitializeLanguage()
{
    std::stringstream ss;
    ss << "Look into: ";
    ss << this->getLocaleDir() << " - " << "Library: "  << this->getPackageName();
    logger->Debug(ss.str());

    bindtextdomain (this->getPackageName().c_str(),this->getLocaleDir().c_str());
    bind_textdomain_codeset(this->getPackageName().c_str(), "UTF-8");
}

