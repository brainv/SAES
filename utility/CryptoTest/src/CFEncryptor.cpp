/*
 * CFEncryptor.cpp
 *
 *  Created on: Apr 21, 2011
 *      Author: fgomez
 */

#include "CFEncryptor.h"
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/IO/Directory.h>
#include <System/IO/File.h>
#include <System/IO/Path.h>
#include <System/XML/DomXml.hxx>
#include <Security/Encryption.hxx>
#include <System/Security/Crypto.hxx>
#include <System/Security/Signed.hxx>
#include <fstream>

using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::XML;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Common::Security;

CFEncryptor::CFEncryptor():
signFiles(false),
encryptFiles(false),
protectSecretKey(false),
inputPath(""),
outPutPath(""),
signingCertPath(""),
signingCertPassword("")
{
	// TODO Auto-generated constructor stub

}

CFEncryptor::~CFEncryptor() {
	// TODO Auto-generated destructor stub
}


void CFEncryptor::Run(bool runAsync)
{
    if (inputPath.length() == 0)
    {
        std::cout << "FATAL - inputPath empty" << std::endl;
        UpdateMessage("FATAL - inputPath empty");
        return;
    }

    if (outPutPath.length() == 0)
    {
        std::cout << "FATAL - outPutPath empty" << std::endl;
        UpdateMessage("FATAL - outPutPath empty");
        return;
    }

    //Launch a thread
	if(runAsync)
	{

		//put it in a thread and wait for finish
		//TODO: need a way to know when it is done, dont mind for now
		Glib::Thread::create(
		sigc::mem_fun(*this, &CFEncryptor::InnerThreadBoddy), true);

	}
	else
	{
		InnerThreadBoddy();
	}
}

void CFEncryptor::UpdateMessage(Glib::ustring msg)
{
	msgs.push_back(msg);
	updateMessage.emit();
}

void CFEncryptor::FillWithMessages(std::list<Glib::ustring>& msg)
{
	msg.assign(msgs.begin(),msgs.end());
	msgs.clear();
}

void CFEncryptor::InnerThreadBoddy()
{
    initKey = Encryption::getInstance()->getInitKey();

    try
    {
        std::vector <std::string> folderList;
        std::vector <std::string>::iterator itfolder;
        std::vector <std::string>::iterator itfile;

        std::string orig = inputPath.c_str();
        std::string dest = outPutPath.c_str();

        Directory dir;
        dir.GetSubDirectories(this->inputPath, folderList, true, true);

        for (itfolder = folderList.begin();
                itfolder != folderList.end();
                itfolder++)
        {
            std::string inputFilePath = Path::Combine(orig, (*itfolder));
            std::string outputFilePath = Path::Combine(dest, (*itfolder));

            std::vector <std::string> fileList;
            dir.GetFiles(inputFilePath, fileList, false, true);

            dir.Mkdir(outputFilePath);

            for (itfile = fileList.begin();
                 itfile != fileList.end();
                 itfile++)
            {
                std::string inputFile = Path::Combine(inputFilePath,(*itfile));
                std::string outputFile = Path::Combine(outputFilePath,(*itfile));

                if ((*itfile) == "default-languages.xml" || (*itfile) == "voting-centers.xml")
                {
                    std::cout << "Process " << (*itfile) << std::endl;

                    UpdateMessage(Glib::ustring::compose("Process %1", inputFile));
                    saveXmlFile(inputFile, outputFile, false);
                }
                else if ((*itfile) == "secret-key")
                {
                    std::cout << "Process secret-key : " << inputFile << std::endl;
                    UpdateMessage(Glib::ustring::compose("Process secret-key : %1", inputFile));

                    SecretKey secretKey(inputFile, "");

                    unsigned char * key;
                    int leng;
                    key = (unsigned char *)secretKey.getKey(leng);

                    SafeBuffer buffer (key, leng);
                    this->secretKey = buffer;

                    File::copyFile(inputFile, outputFile);
                }
                else if ((*itfile).find(".xml") != (*itfile).npos)
                {
                    std::cout << "Process File " << (*itfile) << std::endl;
                    UpdateMessage(Glib::ustring::compose("Process File %1", inputFile));
                    saveXmlFile(inputFile, outputFile, true);
                }
                else
                {
                    File::copyFile(inputFile, outputFile);
                }
            }
        }
    }
    catch (std::exception & ex)
    {
        std::cout << "FATAL - " << ex.what() << std::endl;
        UpdateMessage(Glib::ustring::compose("FATAL - %1", ex.what()));
    }


    finished.emit();
}

void CFEncryptor::saveFile (std::string & inputFile, std::string & outputFile, bool withSecretKey)
{
    try
    {
        if (this->encryptFiles)
        {
            Crypto objCrypto;
            objCrypto.init(Crypto::KEY_AES_256, Crypto::MODE_AES_ECB, true);
            const unsigned char * key;

            if (withSecretKey)
            {
                key = secretKey.GetData();
            }
            else
            {
                key = initKey.GetData();
            }

            objCrypto.cryptoFileToFile(inputFile, outputFile, key);
        }
        else
        {
            std::string data;
            File::readFile(inputFile, data);

            std::ofstream myfile(outputFile.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

            if (myfile.is_open())
            {
                myfile.write((const char *)data.c_str(), data.length());
                myfile.close();
            }
        }
    }
    catch (CryptoException & ex)
    {
        std::cout << "FATAL - " << ex.what() << std::endl;
    }
    catch (std::exception & ex)
    {
        std::cout << "FATAL - " << ex.what() << std::endl;
    }
}
void CFEncryptor::saveXmlFile (std::string & inputFile, std::string & outputFile, bool withSecretKey)
{
    try
    {
        std::string certKey = this->signingCertPassword;
        std::string certFile = this->signingCertPath;

        xercesc::DOMDocument * doc = NULL;
        Smartmatic::System::XML::DomXml dom;
        doc = dom.fileToDom(inputFile);

        if (this->signFiles)
        {
            Signed objSigned;
            objSigned.loadPKCS12(certKey, certFile);
            objSigned.signedRSADOM(doc, Signed::FULL_SIGNED);
        }

        std::string data;
        dom.domToString(doc, data);

        SafeBuffer inputBuffer((unsigned char *)data.c_str(), data.length());
        SafeBuffer outputBuffer;

        if (this->encryptFiles)
        {
            Crypto objCrypto;
            objCrypto.init(Crypto::KEY_AES_256, Crypto::MODE_AES_ECB, true);
            const unsigned char * key;

            if (withSecretKey)
            {
                key = secretKey.GetData();
            }
            else
            {
                key = initKey.GetData();
            }

            objCrypto.cryptoBufferToBuffer(inputBuffer, outputBuffer, key);
        }
        else
        {
            outputBuffer = inputBuffer;
        }

        std::ofstream myfile(outputFile.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

        if (myfile.is_open())
        {
            myfile.write((const char *)outputBuffer.GetData(), outputBuffer.GetSize());
            myfile.close();
        }
    }
    catch (CryptoException & ex)
    {
        std::cout << "FATAL - " << ex.what() << std::endl;
    }
    catch (SignedException & ex)
    {
        std::cout << "FATAL - " << ex.what() << std::endl;
    }
    catch (std::exception & ex)
    {
        std::cout << "FATAL - " << ex.what() << std::endl;
    }
}
