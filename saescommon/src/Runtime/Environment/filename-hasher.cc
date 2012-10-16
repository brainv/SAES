/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <glib.h>
#include <System/Security/Cryptography/MsgDigestUtil.h>
#include "Runtime/Environment/filename-hasher.h"

using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::Security::Cryptography;

FileNameHasher::FileNameHasher()
{

}

FileNameHasher::~FileNameHasher()
{

}

std::string FileNameHasher::GetFileNameHasher(std::string name)
{	
	SafeBuffer buffer = MsgDigestUtil::Digest (name, MsgDigestUtil::DGSTUTIL_SHA1);
	return FileNameHasher::GetValidBase64(buffer);
}

std::string FileNameHasher::GetFileNameHasher(unsigned char * name, int nameLeng )
{
	SafeBuffer buffer = MsgDigestUtil::Digest (name, nameLeng, MsgDigestUtil::DGSTUTIL_SHA1);
	return FileNameHasher::GetValidBase64(buffer);
}


std::string FileNameHasher::GetValidBase64(SafeBuffer & buffer_inner)
{
	Glib::ustring invalidName = buffer_inner.GetBase64Data();
	std::string validName = FileNameHasher::ReplaceInvalidCharacters(invalidName);
	return validName;
}

std::string FileNameHasher::ReplaceInvalidCharacters(std::string name)
{
	char invalidCharacters[12] = {'/','\\',':','*','\"','\'','<','>','\?','|', ',', '.'};

	for(int i= 0; i < (int)sizeof(invalidCharacters);i++)
	{
		char newVal = (char)( (int)'A' +(i/2));
		replace(name.begin(), name.end(), invalidCharacters[i], newVal);
	}
	
	return name;
}

