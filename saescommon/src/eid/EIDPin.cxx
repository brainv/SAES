/**
 * @file EIDPing.cxx
 * @brief Body class eid ping
 * @date 21/07/2011
 * @author Yadickson Soto
 */

#include "EIDPin.hxx"
#include <iostream>
#include <sstream>
#include "beidlib/eidlibException.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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

using namespace eIDMW;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Log;

ISMTTLog* EIDPin::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.EID.EIDPin",GETTEXT_PACKAGE);

EIDPin::EIDPin()
{

}

EIDPin::~EIDPin()
{

}

bool EIDPin::verify( BEID_EIDCard &card, unsigned long & count )
{
	bool validate = false;
	count = 0;

	try
	{
		if (card.getPins().getPinByNumber(0).verifyPin("",count))
		{
			validate = true;
		}
		else if(count == 0)
		{
			logger->Debug("verify pin canceled");
		}
		else
		{
			std::stringstream ss;
			ss << "verify pin failed (" << count << " tries left)";
			logger->Debug(ss.str());
		}

	}
	catch(...)
	{
		std::stringstream ss;
		ss << "FATAL - Exception unknown. (" << __func__ << ")";
		logger->Debug(ss.str());
	}

	return validate;
}
