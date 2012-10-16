/**
 * @file MasterMemoryParser.cpp
 * @brief Body class master memory parser
 * @date 18/05/2011
 * @author yadickson Soto
 */

#include "Runtime/Environment/MasterMemoryParser.h"
#include <System/IO/File.h>
#include <fstream>

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

MasterMemoryParser::MasterMemoryParser()
{

}

MasterMemoryParser::~MasterMemoryParser()
{

}

bool MasterMemoryParser::Load(std::string filePath)
{
	bool validate = false;

	std::string line;
	std::ifstream ifs(filePath.c_str());

	if(ifs.is_open())
	{
		getline(ifs, line);
		ifs.close();
	}

	validate = !line.empty();

	if (validate)
	{
		MemoryInfo info(line);
		memoryInfo.setSerial(info.getSerial());
		memoryInfo.setDevice(info.getDevice());
		memoryInfo.setPath(info.getPath());
		memoryInfo.setMount(info.isMount());
	}

	return validate;
}

MemoryInfo MasterMemoryParser::getMemoryInfo()
{
	return memoryInfo;
}
