/**
 * @file DynamicPathRollingFileAppender.cxx
 * @brief Body class DynamicPathRollingFileAppender
 * @date 15/07/2011
 * @author Yadickson Soto yadickson.soto@smartmatic.com
 */

#include "DynamicPathRollingFileAppender.hxx"
#include "CryptoLayout.hxx"
#include <log4cxx/helpers/stringhelper.h>
#include <log4cxx/helpers/thread.h>
#include <log4cxx/helpers/synchronized.h>
#include <log4cxx/helpers/loglog.h>
#include <iostream>

using namespace log4cxx;
using namespace log4cxx::helpers;
using namespace log4cxx::spi;

IMPLEMENT_LOG4CXX_OBJECT(DynamicPathRollingFileAppender)

std::map <std::string, Smartmatic::Log::BasePathInterface * > DynamicPathRollingFileAppender::iBasePathMap;

DynamicPathRollingFileAppender::DynamicPathRollingFileAppender()
: RollingFileAppender()
{
	createFile = true;
	forceClose = false;
}

DynamicPathRollingFileAppender::~DynamicPathRollingFileAppender()
{

}

void DynamicPathRollingFileAppender::setFile(const log4cxx::LogString& file,
	bool appendFlag,
        bool bufferedIO,
	size_t bufferSize,
        log4cxx::helpers::Pool& p)
{
	this->file = file;
	this->appendFlag = appendFlag;
	this->bufferedIO = bufferedIO;
	this->bufferSize = bufferSize;
}

void DynamicPathRollingFileAppender::append(const log4cxx::spi::LoggingEventPtr& event,
	log4cxx::helpers::Pool& p)
{
	synchronized sync(mutex);

	bool add = true;

	std::string fileFullPath = file;

	Smartmatic::Log::BasePathInterface * iBasePath = NULL;

	if ( iBasePathMap.find(basePathType) != iBasePathMap.end() )
	{
		iBasePath = iBasePathMap[basePathType];
	}

	if (iBasePath)
	{
		fileFullPath = iBasePath->getFileFullPath(fileFullPath);
		add = iBasePath->canWriter();
	}

	if (add && (createFile || forceClose))
	{
		FileAppender::setFile(fileFullPath);
		FileAppender::setFile(fileFullPath, appendFlag, bufferedIO, bufferSize, p);
		createFile = false;
	}

	if (add)
	{
		subAppend(event, p);

		if (forceClose)
		{
			closeWriter();
		}
	}
}

void DynamicPathRollingFileAppender::setOption(const log4cxx::LogString& option,
        const log4cxx::LogString& value)
{
	if (StringHelper::equalsIgnoreCase(option, LOG4CXX_STR("BASEPATHTYPE"), LOG4CXX_STR("basepathtype")))
	{
		synchronized sync(mutex);
		basePathType = value;
	}
	else if (StringHelper::equalsIgnoreCase(option, LOG4CXX_STR("FORCECLOSE"), LOG4CXX_STR("forceclose")))
	{
		synchronized sync(mutex);
		forceClose = StringHelper::toLowerCase(value) == "true";
	}
	else
	{
		RollingFileAppender::setOption(option, value);
	}
}

void DynamicPathRollingFileAppender::putBasePathInterface(Smartmatic::Log::BasePathInterface * iBasePath)
{
	if (iBasePath)
	{
		DynamicPathRollingFileAppender::iBasePathMap[iBasePath->getCode()] = iBasePath;
	}
}
