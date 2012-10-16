/*
 * GpCommandException.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: root
 */

#include "GpCommandException.h"

GpCommandException::GpCommandException(std::string message)
{
	mMessage = message;
}

GpCommandException::~GpCommandException()
throw ()
{
}

