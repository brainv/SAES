
#include "smartmatic-language-controller.h"

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


SmartmaticLanguageController::SmartmaticLanguageController()
{
	
}


SmartmaticLanguageController::~SmartmaticLanguageController()
{
}


string SmartmaticLanguageController::getPackageName()
{
	return GETTEXT_PACKAGE;
}


string SmartmaticLanguageController::getLocaleDir()
{
	return GNOMELOCALEDIR;
}

