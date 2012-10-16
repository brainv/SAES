/**
 * @file GeneratedImagesWrapper.cxx
 * @brief Body class generated images
 */

#include "GeneratedImagesWrapper.hxx"
#include <System/IO/Path.h>
#include <Security/Encryption.hxx>
#include "Log/ISMTTLog.h"
#include <Log/SMTTLogManager.h>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include <iostream>
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

using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Screen;
using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;

ISMTTLog* GeneratedImagesWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Screen.GeneratedImagesWrapper",GETTEXT_PACKAGE);

GeneratedImagesWrapper::GeneratedImagesWrapper()
{

}

GeneratedImagesWrapper::~GeneratedImagesWrapper()
{

}

void GeneratedImagesWrapper::Persist(string folder)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

	string fullFileName = Path::Combine( folder, directories.getXMLImageFileName());

	logger->Debug("Creating File: " + fullFileName);

    Smartmatic::SAES::Voting::Screen::NamespaceInfomap map;
    map[""].name = NAMESPACE_SCREEN;
    map[""].schema = "";

    std::ostringstream os;
    serializeGeneratedImages(os,generatedImages, map, "UTF-8");

    logger->Debug("File " + fullFileName + " parsed.");
    std::string data = os.str();

	ofstream myfile;
	myfile.open (fullFileName.c_str());
	myfile << data;
	myfile.close();
}

GeneratedImages & GeneratedImagesWrapper::getGeneratedImages()
{
	return generatedImages;
}
