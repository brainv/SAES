/**
 * @file MemoryEventParser.cpp
 * @brief Body class memory event parser
 * @date 18/05/2011
 * @author Yadickson Soto
 */

#include "Runtime/Environment/MemoryEventParser.h"
#include <System/IO/Directory.h>
#include <System/IO/File.h>
#include <fstream>
#include <iostream>
#include <map>

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

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;

MemoryEventParser::MemoryEventParser()
{

}

MemoryEventParser::~MemoryEventParser()
{

}

void MemoryEventParser::Load(std::string filePath)
{
    umountedMemories.clear();
    mountedMemories.clear();

    std::map < std::string, MemoryInfo > mapMountedMemories;
    std::map < std::string, MemoryInfo >::iterator it;

    if (File::canOpenFile(filePath))
    {
        std::string line;
        std::ifstream ifs(filePath.c_str());

        if(ifs.is_open())
        {
            while (ifs.good())
            {
                getline(ifs, line);

                if (line.empty()) continue;

                MemoryInfo info(line);

                if (info.isRemove())
                {
                	umountedMemories.push_back(info);
                }
                else if (info.isMount() && Directory::DirectoryExists(info.getPath()))
                {
                	mapMountedMemories[info.getDevice()] = info;
                }
            }

            ifs.close();
        }
    }

    for (it = mapMountedMemories.begin();
    		it != mapMountedMemories.end();
    		it++)
    {
        mountedMemories.push_back((*it).second);
    }
}

std::vector<MemoryInfo> & MemoryEventParser::getUmountedMemories()
{
	return umountedMemories;
}

std::vector<MemoryInfo> & MemoryEventParser::getMountedMemories()
{
	return mountedMemories;
}

MemoryInfo MemoryEventParser::getLastDetection()
{
    return lastMemoryInfo;
}

MemoryEventParser::MemoryEventType MemoryEventParser::LastEvent()
{
    return eventType;
}
