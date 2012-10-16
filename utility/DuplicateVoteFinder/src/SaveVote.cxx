/*
 * SaveVote.cxx
 *
 *  Created on: 23/09/2011
 *      Author: soto
 */

#include "SaveVote.hxx"
#include <System/IO/File.h>

using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;

SaveVote::SaveVote()
{

}

SaveVote::~SaveVote()
{

}

bool SaveVote::open(std::string & file, SafeBuffer & bufferOut)
{
	File::openFileToBuffer(file, bufferOut);
	return bufferOut.GetSize() > 0;
}

bool SaveVote::save(std::string & file, SafeBuffer & bufferIn)
{
	return File::saveBufferToFile(bufferIn, file);
}
