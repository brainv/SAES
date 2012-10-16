/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
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

/**
 * @file	compression-class.cc
 * @brief	Body file to the compression class class.
 */

#include "System/Compression/compression-class.h"
#include <assert.h>
#include <queue>
#include <string.h>
#include <sstream>
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

using namespace Smartmatic::System::Compression;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

ISMTTLog* CompressionClass::logger = SMTTLogManager::GetLogger("Smartmatic.System.Compression.CompressionClass",GETTEXT_PACKAGE);

#define CHUNK 16384 ///< chunk size

gint CompressionClass::Deflate(const gpointer data, gint size,gpointer* dest, gint& outputSize, gint level )
{
	int ret = Z_STREAM_ERROR;

	try
	{
	guint bytesReadyThisTime;
	z_stream strm;
	guchar* out = new guchar[CHUNK];
	gint totalSize(0);

	/* allocate deflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	std::queue<SafeBuffer*> buffers;
	ret = deflateInit(&strm, level);

	if (ret == Z_OK)
	{
		//init input datat
		strm.next_in = static_cast<unsigned char*>(const_cast<void*>(data));
		strm.avail_in = size;

		/* run deflate() on input until output buffer not full, finish
			compression if all of source has been read in */
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = deflate(&strm, Z_FINISH);    /* no bad return value */
			assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
			bytesReadyThisTime = CHUNK - strm.avail_out;

			if(bytesReadyThisTime)
			{
				buffers.push(new SafeBuffer(out,bytesReadyThisTime));
				totalSize+=bytesReadyThisTime;
			}

		} while (strm.avail_out == 0);

		//TODO: use exceptions instead of assert, take care of free the memory chunk
		assert(strm.avail_in == 0);     /* all input will be used */
		assert(ret == Z_STREAM_END);        /* stream will be complete */
		/* clean up */
		(void)deflateEnd(&strm);
		delete [](out);
		//Create a big buffer
		*dest = g_malloc(totalSize);
		outputSize = totalSize;
		out = static_cast<guchar*>(*dest);

		while (!buffers.empty())
		{
			SafeBuffer * chunk = buffers.front();

			memcpy(out,chunk->GetData(), chunk->GetSize());
			out+=chunk->GetSize();
			delete (chunk);		
			buffers.pop();
		}

	}
	else
	{
		//Clear temporal buffer
		delete [](out);
	}
	}
	catch(...)
	{

	}
	return ret;
}

gint CompressionClass::Inflate(const gpointer data, gint size,gpointer* dest, gint& outputSize, int & avail)
{
	int ret = Z_STREAM_ERROR;

	try
	{
	unsigned bytesReadyThisTime;
	z_stream strm;
	guchar* out = new guchar[CHUNK];
	gint totalSize(0);
	std::queue<SafeBuffer*> buffers;
	avail = 0;

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	//set this for memoery allocation analysis
	strm.avail_in = size;
	strm.next_in = static_cast<unsigned char*>(const_cast<void*>(data));
	ret = inflateInit(&strm);
	if (ret != Z_OK)
	{
		delete [](out);
		return ret;
	}

	//Set it again
	strm.avail_in = size;
	strm.next_in = static_cast<unsigned char*>(const_cast<void*>(data));

	/* run inflate() on input until output buffer not full */
	do {
		strm.avail_out = CHUNK;
		strm.next_out = out;
		ret = inflate(&strm, Z_NO_FLUSH);
		assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
		switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */
				break;
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				break;
			default:
				break;
		}
		if(ret < 0)
			break;
		bytesReadyThisTime = CHUNK - strm.avail_out;
		if(bytesReadyThisTime)
		{
			buffers.push(new SafeBuffer(out,bytesReadyThisTime));
			totalSize+=bytesReadyThisTime;
		}
	} while (strm.avail_out == 0); //Keep providing output buffer if current one is empty

	delete [](out);
	/* clean up and return */
	logger->Debug("InflateEnd");
	viewText(inflateEnd(&strm));

	//TODO: use exceptions to handle error
	if(ret < 0)
	{
		outputSize = 0;
		//clear the buffers
		while (!buffers.empty())
		{	
			SafeBuffer* chunk = buffers.front();
			delete (chunk);		
			buffers.pop();
		}		
	}
	else
	{
		*dest = g_malloc(totalSize);
		outputSize = totalSize;
		out = static_cast<guchar*>(*dest);
		while (!buffers.empty())
		{
			SafeBuffer* chunk = buffers.front();
			memcpy(out,chunk->GetData(), chunk->GetSize());
			out+=chunk->GetSize();
			delete (chunk);		
			buffers.pop();
		}
	}

	avail = strm.avail_in;
	}
	catch (...)
	{
		avail = 0;
	}

	return ret;
}

gint CompressionClass::Inflate(
        SafeBuffer & dataIn,
        SafeBuffer & dataOut)
{
    gpointer result(NULL);
    gint resultSize;
    int avail;
    gint exit = Inflate((void*)dataIn.GetData(), dataIn.GetSize(), &result, resultSize, avail);
    dataOut.AddData((unsigned char *)result, resultSize);

    g_free(result);
    return exit;
}

gint CompressionClass::Deflate(
        SafeBuffer & dataIn,
        SafeBuffer & dataOut,
        gint level)
{
    gpointer result(NULL);
    gint resultSize;

    gint exit = Deflate((void*)dataIn.GetData(), dataIn.GetSize(), &result, resultSize, level);
    dataOut.AddData((unsigned char *)result, resultSize);

    g_free(result);
    return exit;
}

gint CompressionClass::Inflate(
        SafeBuffer & dataIn,
        std::list <SafeBuffer * > & listDataOut)
{
	int avail = 0;
	int total = dataIn.GetSize();

	int process = 0;
	int current = 0;

	gint exit = 0;

	do
    {
		SafeBuffer data((unsigned char*)dataIn.GetData() + current, total);

        gpointer result(NULL);
        gint resultSize;

        exit = Inflate((void*)data.GetData(), data.GetSize(), &result, resultSize, avail);
		SafeBuffer * dataOut = new SafeBuffer((unsigned char *)result, resultSize);

		g_free(result);

		process = total - avail;
		total -= process;
		current += process;

		{
			std::stringstream ss;
			ss << "Total data : " << data.GetSize();
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "Process data : " << process;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "Not process data : " << avail;
			logger->Debug(ss.str());
		}

		{
			std::stringstream ss;
			ss << "Data out size : " << dataOut->GetSize();
			logger->Debug(ss.str());
		}

		viewText(exit);

		if (exit == Z_OK || exit == Z_STREAM_END)
		{
			listDataOut.push_back(dataOut);
		}
		else if (exit == Z_DATA_ERROR)
		{
			listDataOut.push_back(dataOut);
			break;
		}
    }
    while(avail != 0);

	{
		std::stringstream ss;
		ss << "List size : " << listDataOut.size();
		logger->Debug(ss.str());
	}

	return exit;
}

void CompressionClass::viewText(gint value)
{

	switch (value)
	{
		case Z_OK:
			logger->Debug("Z_OK");
			break;
		case Z_STREAM_END:
			logger->Debug("Z_STREAM_END");
			break;
		case Z_NEED_DICT:
			logger->Debug("Z_NEED_DICT");
			break;
		case Z_ERRNO:
			logger->Debug("Z_ERRNO");
			break;
		case Z_STREAM_ERROR:
			logger->Debug("Z_STREAM_ERROR");
			break;
		case Z_DATA_ERROR:
			logger->Debug("Z_DATA_ERROR");
			break;
		case Z_MEM_ERROR:
			logger->Debug("Z_MEM_ERROR");
			break;
		case Z_BUF_ERROR:
			logger->Debug("Z_BUF_ERROR");
			break;
		case Z_VERSION_ERROR:
			logger->Debug("Z_VERSION_ERROR");
			break;
	}
}
