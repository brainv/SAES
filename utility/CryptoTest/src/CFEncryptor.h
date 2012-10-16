/*
 * CFEncryptor.h
 *
 *  Created on: Apr 21, 2011
 *      Author: fgomez
 */

#ifndef CFENCRYPTOR_H_
#define CFENCRYPTOR_H_

#include <glibmm.h>
#include <System/SafeBuffer.h>
#include <list>


class CFEncryptor {
public:
	CFEncryptor();
	virtual ~CFEncryptor();



	Glib::Dispatcher finished;

	Glib::Dispatcher updateMessage;

	void ExcludeFileSigning(){signFiles = false;}
	void SetSigningCertificate(Glib::ustring& path, Glib::ustring& password)
	{
		signFiles = true;
		signingCertPath = path;
		signingCertPassword = password;
	}

	void SetEncryptFiles(bool whetherEncrypt){encryptFiles =whetherEncrypt; }

	void SetProtectSecretKey(bool whetherProtectSecret){protectSecretKey = whetherProtectSecret;}


	void SetNewInputPath(Glib::ustring& newInput){ inputPath = newInput;}
	void SetNewOutputPath(Glib::ustring& newOutput){outPutPath = newOutput;}

	void Run(bool runAsync);

	void FillWithMessages(std::list<Glib::ustring>& msg);


private:

	void InnerThreadBoddy();

	void UpdateMessage(Glib::ustring msg);

    void saveFile (std::string & origFile, std::string & destFile, bool withSecretKey);
    void saveXmlFile (std::string & origFile, std::string & destFile, bool withSecretKey);

	bool signFiles;
	bool encryptFiles;
	bool protectSecretKey;

	std::list<Glib::ustring> msgs;

	Glib::ustring inputPath;
	Glib::ustring outPutPath;

	Glib::ustring signingCertPath;
	Glib::ustring signingCertPassword;

	Smartmatic::System::SafeBuffer initKey;
    Smartmatic::System::SafeBuffer secretKey;

};

#endif /* CFENCRYPTOR_H_ */
