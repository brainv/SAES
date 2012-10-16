/**
 * @file guid-class.cc
 * @brief Body class utility guid
 */
/*
 * smartmatic
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
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

#include "System/guid-class.h"
#include <glibmm.h>
#include <uuid.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include "System/Encoding/Base64Encoder.h"

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

using namespace Smartmatic::System;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::Log;

ISMTTLog* GuidClass::logger = SMTTLogManager::GetLogger("Smartmatic.System.GuidClass",GETTEXT_PACKAGE);

GuidClass GuidClass::NewGuid(bool strongest)
{
	return GuidClass(strongest);
}

GuidClass::GuidClass()
{
	uuid_clear(this->underlyingUUID);
}

GuidClass::GuidClass(bool strongest)
{
        if(strongest)
          uuid_generate_random(this->underlyingUUID);
        else
          uuid_generate(this->underlyingUUID);
}

GuidClass::GuidClass(std::string stringParam) throw (GuIdException)
{
	gchar* vals = static_cast<gchar*>(g_malloc(stringParam.length()+2));

	gint copied = stringParam.copy(vals, stringParam.length()+2);

	//set null termination
	*(vals +copied) = 0;
	*(vals +copied+1) = 0;

	if(uuid_parse(vals, this->underlyingUUID) != 0)
		 throw GuIdException(_("Smartmatic.System.GuidClass.ParseError"),
				 N_("Smartmatic.System.GuidClass.ParseError"),
				 logger);

	g_free(vals);

}

GuidClass::GuidClass(const Smartmatic::System::GuidClass& guid)
{
	uuid_copy(this->underlyingUUID, guid.underlyingUUID);
}

GuidClass::~GuidClass()
{
	uuid_clear(this->underlyingUUID);
}

GuidClass GuidClass::Parse(std::string stringParam) throw (GuIdException)
{
	GuidClass retVal (stringParam);

	return retVal;	
}

std::string GuidClass::ToString() const
{

	char buffer[38] = {0};
	uuid_unparse_lower(this->underlyingUUID, buffer);

	std::string retVal(buffer);
	
	return retVal;
}

std::string GuidClass::ToBase64String() const
{
	return Base64Encoder::ConvertToBase64(this->underlyingUUID, 16);
}

SafeBuffer GuidClass::toSafeBuffer() const
{
    return SafeBuffer ((unsigned char*)this->underlyingUUID, 16);
}

bool GuidClass::operator== (const Smartmatic::System::GuidClass& right)
{
        return uuid_compare(this->underlyingUUID, right.underlyingUUID) == 0;
}

bool GuidClass::operator!=(const Smartmatic::System::GuidClass& right)
{
        return uuid_compare(this->underlyingUUID, right.underlyingUUID) != 0;
}
