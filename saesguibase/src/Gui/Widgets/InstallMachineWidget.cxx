/**
 * @file InstallMachineWidget.cxx
 * @brief Body class install machine widget
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#include "InstallMachineWidget.hxx"

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

InstallMachineWidget::InstallMachineWidget()
: Smartmatic::GUI::Widgets::StepWidget()
{
}

InstallMachineWidget::~InstallMachineWidget()
{

}
