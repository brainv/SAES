/**
 * @file XMLRoffTransformer.cpp
 * @brief Body class XMLRoffTransformer, xml to pdf runtime
 * @date 28/04/2011
 * @author Yadickson Soto
 */

#include "XMLRoffTransformer.h"
#include <System/Runtime/ProcessLauncher.h>
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

using namespace Smartmatic::System::XSLFO;
using namespace Smartmatic::Log;

ISMTTLog* XMLRoffTransformer::logger = SMTTLogManager::GetLogger("Smartmatic.System.XSLFO.XMLRoffTransformer",GETTEXT_PACKAGE);

XMLRoffTransformer::XMLRoffTransformer()
{
	format = TRANSFORM_AUTO;
	backend = TRANSFORM_CAIRO;
	compat = TRANSFORM_COMPAT;
}

XMLRoffTransformer::~XMLRoffTransformer()
{

}

void XMLRoffTransformer::setFormat(XMLRoffTransformer::TransformFormat format)
{
	this->format = format;
}

void XMLRoffTransformer::setBackend(XMLRoffTransformer::TransformBackend backend)
{
	this->backend = backend;
}

void XMLRoffTransformer::setCompat(XMLRoffTransformer::TransformCompat compat)
{
	this->compat = compat;
}

bool XMLRoffTransformer::transformFile(std::string outputFile, std::string inputFile, std::string templateFile)
{
	logger->Debug("Execute transformation");

	std::string command;
	command.append("xmlroff -o ");
	command.append(outputFile);
	command.append(" --format=");
	switch(format)
	{
		case TRANSFORM_AUTO:
			command.append("auto");
			break;
		case TRANSFORM_PDF:
			command.append("pdf");
			break;
		case TRANSFORM_POSTSCRIPT:
			command.append("postscript");
			break;
		case TRANSFORM_SVG:
			command.append("svg");
			break;
	}

	command.append(" --backend=");
	switch(backend)
	{
		case TRANSFORM_CAIRO:
			command.append("cairo");
			break;
		case TRANSFORM_GP:
			command.append("gp");
			break;
	}
	switch(compat)
	{
		case TRANSFORM_COMPAT:
			command.append(" --compat");
			break;
		case TRANSFORM_NOCOMPAT:
			command.append(" --nocompat");
			break;
	}
	command.append(" ");
	command.append(inputFile);
	command.append(" ");
	command.append(templateFile);

	return Smartmatic::System::Runtime::ProcessLauncher::RunProcessThroughSystem(command) == 0;
}
