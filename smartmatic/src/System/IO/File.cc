/**
 * @file File.cc
 * @brief Body class File
 */

#include "File.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <System/Security/Cryptography/MsgDigestUtil.h>
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

using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::Log;

ISMTTLog* File::logger = SMTTLogManager::GetLogger("Smartmatic.System.IO.File",GETTEXT_PACKAGE);

bool File::canOpenFile (std::string file)
{
    try
    {
       std::ifstream ifile(file.c_str());

       if (ifile)
       {
           std::ifstream ifs;
           ifs.exceptions (std::ifstream::badbit | std::ifstream::failbit);
           ifs.open (file.c_str());
           ifs.close();
           return true;
       }
    }
    catch (std::ifstream::failure & ex)
    {
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
    }

    return false;
}

bool File::readFile(std::string file, std::string & content)
{
	try
	{
		std::ifstream ifs;
		ifs.exceptions (std::ifstream::badbit | std::ifstream::failbit);
		ifs.open (file.c_str());

		std::string contents((std::istreambuf_iterator<char>(ifs)),
		    std::istreambuf_iterator<char>());

		content = contents;

		ifs.close();

		return true;
	}
	catch (std::ifstream::failure & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	return false;
}


bool File::readLastLine(std::string file, std::string & content)
{
	try
	{
		std::ifstream ifs;
		ifs.exceptions (std::ifstream::badbit | std::ifstream::failbit);
		ifs.open (file.c_str());

		std::string contents;
		while(ifs.good())
		{
			getline(ifs, contents);
		}

		content = contents;

		ifs.close();

		return true;
	}
	catch (std::ifstream::failure & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	return false;
}


bool File::findLine(std::string file, std::string & content, std::string contentText)
{
	try
	{
		bool have = false;
		std::ifstream ifs;
		ifs.exceptions (std::ifstream::badbit | std::ifstream::failbit);
		ifs.open (file.c_str());

		std::string contents;
		while(ifs.good() && have == false)
		{
			getline(ifs, contents);

			if(contents.find(contentText) != std::string::npos)
			{
				content = contents;
				have = true;
			}
		}

		ifs.close();

		return true;
	}
	catch (std::ifstream::failure & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	return false;
}


bool File::DeleteFile(std::string fullPath)
{
	if(remove(fullPath.c_str()) != 0)
		return false;
	else
		return true;
}

bool File::copyFile(std::string & inputFile, std::string & outputFile)
{
    if (!canOpenFile(inputFile))
    {
        return false;
    }

    std::ifstream ifile(inputFile.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    int size;
    unsigned char * data = NULL;

    if (ifile.is_open())
    {
        size = ifile.tellg();
        data = new unsigned char [size];
        ifile.seekg (0, std::ios::beg);
        ifile.read ((char *)data, size);
        ifile.close();
    }
    else
    {
        return false;
    }

    std::ofstream ofile(outputFile.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

    if (ofile.is_open())
    {
        ofile.write ((char *)data, size);
        ofile.close();
        delete[] data;
        return true;
    }
    else
    {
        delete[] data;
        return false;
    }
}

bool File::saveBufferToFile(SafeBuffer & buffer, std::string & file)
{
    bool success = false;

    if (buffer.GetSize() > 0)
    {
		std::ofstream ofile(file.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

		if (ofile.is_open())
		{
			ofile.write ((char *)buffer.GetData(), buffer.GetSize());
			ofile.close();
			success = true;
		}
    }
    else
    {
    	success = true;
    }

    return success;
}

bool File::openFileToBuffer(std::string & file, Smartmatic::System::SafeBuffer & dataOut)
{
	bool validate = false;

    std::ifstream ifFile(file.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    int size;
    unsigned char * data = NULL;

    if (ifFile.is_open())
    {
        size = ifFile.tellg();
        data = new unsigned char [size];
        ifFile.seekg (0, std::ios::beg);
        ifFile.read ((char *)data, size);
        ifFile.close();

        dataOut.AddData(data, size);
        delete[] data;

        validate = true;
    }

    return validate;
}

bool File::compareFiles(std::string & fileOne, std::string & fileTwo)
{
    bool validate = false;

    logger->Debug("Compare files " + fileOne + " - " + fileTwo);

    if (canOpenFile(fileOne) && canOpenFile(fileTwo))
    {
        try
        {
        	SafeBuffer md5sumFileOne = MsgDigestUtil::FileDigest(fileOne, MsgDigestUtil::DGSTUTIL_MD5);
        	SafeBuffer md5sumFileTwo = MsgDigestUtil::FileDigest(fileTwo, MsgDigestUtil::DGSTUTIL_MD5);
            validate = (md5sumFileOne == md5sumFileTwo);
        }
        catch(...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
        }
    }

    logger->Debug("Compare files " + std::string(validate ? "Success": "Fail"));
    return validate;
}

void File::getHashFile(std::string & file, Smartmatic::System::SafeBuffer & dataOut)
{
    if (canOpenFile(file))
    {
        try
        {
        	dataOut = MsgDigestUtil::FileDigest(file, MsgDigestUtil::DGSTUTIL_SHA1);
        }
        catch(...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
        }
    }
}

bool File::renameFile(std::string oldName, std::string newName)
{
	return rename( oldName.c_str() , newName.c_str() ) == 0;
}
