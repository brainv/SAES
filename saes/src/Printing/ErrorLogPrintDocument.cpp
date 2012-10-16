/**
 * @file ErrorLogPrintDocument.cpp
 * @brief Body class error log print document
 * @date 04/05/2011
 * @author Rafael Ferrero
 */

#include "ErrorLogPrintDocument.h"
#include <Voting/ElectoralConfiguration.hxx>

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

using namespace Smartmatic::SAES::Printing;


ErrorLogPrintDocument::ErrorLogPrintDocument(Smartmatic::SAES::Log::LogReader* reader,
		Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
: LogPrintDocument (reader, electoralConfiguration)
{
	// TODO Auto-generated constructor stub

}

ErrorLogPrintDocument::~ErrorLogPrintDocument()
{
	// TODO Auto-generated destructor stub
}


std::string ErrorLogPrintDocument::GetLogDocName ()
{
	return _("Smartmatic.SAES.Printing.ErrorLogPrintDocument");
}
