/**
 * @file IDCardWidgetCloseVotation.cxx
 * @brief Body class id card close voting
 * @date 04/05/2012
 * @author Yadickson Soto
 */

#include "IDCardWidgetCloseVotation.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* IDCardWidgetCloseVotation::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseVotation",GETTEXT_PACKAGE);

IDCardWidgetCloseVotation::IDCardWidgetCloseVotation()
:IDCardWidget(N_("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseVotation.IdCardMessage"),
              N_("Smartmatic.SAES.GUI.Widgets.IDCardWidgetCloseVotation.IdCardMessageConfirm"),
              true)
{
	idConfig = SAESGUIConfigurationManager::Current()->getIDCardProcessConfiguration().getCloseVotation();
	ShowElements();
}

IDCardWidgetCloseVotation::~IDCardWidgetCloseVotation()
{
	dispose();
}
