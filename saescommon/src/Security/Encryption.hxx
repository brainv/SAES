/**
 * @file	Encryption.hxx
 *
 * @brief	encryption class.
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#ifndef __ENCRYPTION__H__
#define __ENCRYPTION__H__

#include <System/SafeBuffer.h>
#include <System/guid-class.h>
#include <System/Security/Signed.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <System/Exception/XmlException.hxx>
#include <System/Security/Crypto.hxx>
#include <vector>
#include <glibmm.h>

#include "Security/SecretKey.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
    namespace SAES
    {
        namespace Security
        {
            /**
             * @class Encryption
             * @brief Header class Encryption
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date 04-04-2011
             */
            class Encryption
            {
            public:
                /**
                 * @brief enum UseKeyType
                 */
                typedef enum
                {
                     SECRET_KEY /**<Use secret key*/
                    ,UP_KEY /**<UP key*/
                    ,VERIFICATION_KEY /**<verification key*/
                    ,INIT_KEY /**<use init key*/
                }UseKeyType;

                /**
                 * @brief enum ResourceFileType
                 */
                typedef enum
                {
                     INSTALL_FILE /**<install file*/
                    ,EXTERNAL_FILE /**<external file*/
                    ,INTERNAL_FILE /**<internal file*/
                    ,RESOURCE_FILE /**<resource file*/
                    ,EXCHANGE_FILE /**<exchange file*/
                    ,UTIL_FILE /**<util file*/
                    ,PRINTED_VOTE /**<printed vote*/
                }ResourceFileType;

            private:

                /**
                 * @fn	Encryption::Encryption();
                 *
                 * @brief	Class constructor.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 */

                Encryption();

            public:

                /**
                 * @fn	Encryption::~Encryption();
                 *
                 * @brief	Class destroy.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 */

                ~Encryption();

                /**
                 * @fn	void Encryption::initCrypto(Smartmatic::SAES::Common::Security::SecretKey& secretKey) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	Method for init crypto class.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	secretKey	SecretKey object containing the key for decryption of the secret file
                 * @param	ukt		The ukt.
                 * @throw CryptoException.
                 */

                void initCrypto(Smartmatic::SAES::Common::Security::SecretKey& key,
                		UseKeyType ukt = SECRET_KEY)
                    throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	void Encryption::initSigned(Smartmatic::SAES::Runtime::Environment::SaesDirectories directories,
                 * 		std::string & signedKey) throw (Smartmatic::System::Exception::SignedException,
                 * 		Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	Method for init class.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param	directories		 	The directories.
                 * @param [in,out]	signedKey	secret key for signed
                 * 								@throw SignedException.
                 */

                void initSigned(Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories, std::string & signedKey)
                    throw (Smartmatic::System::Exception::SignedException,
                           Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	void Encryption::signedXml(std::string & xml,
                 * 		ResourceFileType rft) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException);
                 *
                 * @brief	method to signed DOMElement.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	xml	DOM document signed
                 * 						@throw SignedException.
                 * @param	rft		   	The rft.
                 */

                void signedXml(std::string & xml, ResourceFileType rft)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException);

                /**
                 * @fn	void Encryption::signedDOM(xercesc::DOMDocument * doc,
                 * 		ResourceFileType rft) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException);
                 *
                 * @brief	method to signed DOMElement.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	doc	DOM document signed
                 * 						@throw SignedException.
                 * @param	rft		   	The rft.
                 */

                void signedDOM(xercesc::DOMDocument * doc, ResourceFileType rft)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException);

                /**
                 * @fn	void Encryption::signedFile(std::string & file,
                 * 		ResourceFileType rft) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException,
                 * 		Smartmatic::System::Exception::XmlException);
                 *
                 * @brief	method to signed file.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	file	file signed.
                 * @param	rft				The rft.
                 *
                 * ### throw	SignedException	@throw XmlException.
                 */

                void signedFile(std::string & file, ResourceFileType rft)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException,
                                Smartmatic::System::Exception::XmlException);

                void cryptoDOMToBuffer(xercesc::DOMDocument * doc, Smartmatic::System::SafeBuffer & dataOut,
                        ResourceFileType rft,
                        UseKeyType ukt,
                        bool pad = true) throw (Smartmatic::System::Exception::CryptoException);


                /**
                 * @fn	void Encryption::cryptoDOMToFile(xercesc::DOMDocument * doc, std::string & file,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to crypto DOMElement.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	doc 	DOM document signed.
                 * @param [in,out]	file	crypto file
                 * 							@throw CryptoException.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 */

                void cryptoDOMToFile(xercesc::DOMDocument * doc, std::string & file,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	void Encryption::cryptoStringToFile(std::string & data, std::string & file,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to crypto file.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	data to crypto.
                 * @param [in,out]	file	crypto file
                 * 							@throw CryptoException.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 */

                void cryptoStringToFile(std::string & data, std::string & file,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void cryptoStringToFile(std::string & data, std::string & file,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void cryptoBufferToFile(Smartmatic::System::SafeBuffer & dataIn, std::string & file,
                        Encryption::ResourceFileType rft,
                        Encryption::UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void cryptoBufferToFile(Smartmatic::System::SafeBuffer & dataIn, std::string & file,
                        Encryption::UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method crypto buffer to buffer
                 * @param dataIn data in
                 * @param dataOut data out
                 * @param key key
                 * @param pad padding
                 * @author Yadickson Soto
                 * @date 02/03/2012
                 */
                void cryptoBufferToBuffer(Smartmatic::System::SafeBuffer & dataIn,
                		Smartmatic::System::SafeBuffer & dataOut,
                		Smartmatic::System::SafeBuffer key,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	void Encryption::decryptoFileToString(std::string & file, std::string & data,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to decrypto file to string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	file	crypto file.
                 * @param [in,out]	data	data string.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * ### throw	CryptoException	@throw XmlException.
                 */

                void decryptoFileToString(std::string & file, std::string & data,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);


                void decryptoFileToString(std::string & file, std::string & data,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void decryptoFileToBuffer(std::string & file,
                		Smartmatic::System::SafeBuffer & dataOut,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void decryptoFileToBuffer(std::string & file,
                		Smartmatic::System::SafeBuffer & dataOut,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method decrypto buffer to buffer
                 * @param dataIn data in
                 * @param dataOut data out
                 * @param key key
                 * @param pad padding
                 * @author Yadickson Soto
                 * @date 02/03/2012
                 */
                void decryptoBufferToBuffer(Smartmatic::System::SafeBuffer & dataIn,
                		Smartmatic::System::SafeBuffer & dataOut,
                		Smartmatic::System::SafeBuffer key,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	void Encryption::validateSignedString(std::string & data,
                 * 		ResourceFileType rft) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException);
                 *
                 * @brief	method to validate DOMElement.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	string data to validate
                 * 							@throw SignedException.
                 * @param	rft				The rft.
                 */

                void validateSignedString(std::string & data, ResourceFileType rft)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException);

                /**
                 * @fn	void Encryption::validateSignedDOM(xercesc::DOMDocument * doc,
                 * 		ResourceFileType rft) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException);
                 *
                 * @brief	method to validate DOMElement.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	doc	DOM document to validate
                 * 						@throw SignedException.
                 * @param	rft		   	The rft.
                 */

                void validateSignedDOM(xercesc::DOMDocument * doc, ResourceFileType rft)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException);

                /**
                 * @fn	void Encryption::validateSignedFile(std::string & file,
                 * 		ResourceFileType rft) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException,
                 * 		Smartmatic::System::Exception::XmlException);
                 *
                 * @brief	method to validate file.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	file	file to validate.
                 * @param	rft				The rft.
                 *
                 * ### throw	SignedException	@throw XmlException.
                 */

                void validateSignedFile(std::string & file, ResourceFileType rft)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException,
                                Smartmatic::System::Exception::XmlException);

                /**
                 * @fn	std::string Encryption::openXmlFile(std::string & file, ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException,
                 * 		Smartmatic::System::Exception::XmlException);
                 *
                 * @brief	method to open xml file.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	file	file to validate.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * @return	istream file
                 * 			@throw CryptoException.
                 *
                 * ### throw	SignedException	@throw XmlException.
                 */

                std::string openXmlFile(std::string & file,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool isCompressed = false,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException,
                                Smartmatic::System::Exception::XmlException);

                /**
                 * @fn	void Encryption::saveXmlFile(std::string & data, std::string & file, ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException,
                 * 		Smartmatic::System::Exception::SignedException,
                 * 		Smartmatic::System::Exception::XmlException);
                 *
                 * @brief	method to save data to xml file.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	data to file.
                 * @param [in,out]	file	save file
                 * 							@throw CryptoException.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * ### throw	SignedException	@throw XmlException.
                 */

                void saveXmlFile(std::string & data, std::string & file,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool compress = false,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException,
                                Smartmatic::System::Exception::SignedException,
                                Smartmatic::System::Exception::XmlException);

                /**
                 * @fn	static Encryption * Encryption::getInstance();
                 *
                 * @brief	Method getter instance class.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @return	instance class.
                 */

                static Encryption * getInstance();

                /**
                 * @fn	Smartmatic::System::SafeBuffer Encryption::cryptoBuffer(Smartmatic::System::SafeBuffer & data,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to crypto string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	to crypto.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * @return	data crypto
                 * 			@throw CryptoException.
                 */

                void cryptoBufferToBuffer(Smartmatic::System::SafeBuffer & data,
                		Smartmatic::System::SafeBuffer & dataOut,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void cryptoBufferToBuffer(Smartmatic::System::SafeBuffer & data,
                		Smartmatic::System::SafeBuffer & dataOut,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	Smartmatic::System::SafeBuffer Encryption::cryptoString(std::string & data,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to crypto string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	to crypto.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * @return	data crypto
                 * 			@throw CryptoException.
                 */

                void cryptoStringToBuffer(std::string & data,
                		Smartmatic::System::SafeBuffer & dataOut,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	std::string Encryption::decryptoString(Smartmatic::System::SafeBuffer & buffer,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to decrypto string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	buffer	decrypto.
                 * @param	rft			  	The rft.
                 * @param	ukt			  	The ukt.
                 *
                 * @return	data decrypto
                 * 			@throw CryptoException.
                 */

                std::string decryptoBufferToString(Smartmatic::System::SafeBuffer & buffer,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	Smartmatic::System::SafeBuffer Encryption::decryptoBuffer(Smartmatic::System::SafeBuffer & buffer,
                 * 		ResourceFileType rft,
                 * 		UseKeyType ukt = SECRET_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to decrypto string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	buffer	decrypto.
                 * @param	rft			  	The rft.
                 * @param	ukt			  	The ukt.
                 *
                 * @return	data decrypto
                 * 			@throw CryptoException.
                 */

                void decryptoBufferToBuffer(Smartmatic::System::SafeBuffer & buffer,
                		Smartmatic::System::SafeBuffer & dataOut,
                        ResourceFileType rft,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void decryptoBufferToBuffer(Smartmatic::System::SafeBuffer & buffer,
                		Smartmatic::System::SafeBuffer & dataOut,
                        UseKeyType ukt = SECRET_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	std::string Encryption::cryptoStringToB64(std::string & data, ResourceFileType rft,
                 * 		UseKeyType ukt = VERIFICATION_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to crypto string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	to crypto.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * @return	data crypto to b64
                 * 			@throw CryptoException.
                 */

                std::string cryptoStringToB64(std::string & data,
                        ResourceFileType rft,
                        UseKeyType ukt = VERIFICATION_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn  std::string Encryption::cryptoStringToB64(std::string & data, ResourceFileType rft,
                 *      UseKeyType ukt = VERIFICATION_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief   method to crypto string.
                 *
                 * @author  Cesar.bonilla
                 * @date    4/28/2011
                 *
                 * @param [in,out]  data    to crypto.
                 * @param   ukt             The ukt.
                 *
                 * @return  data crypto to b64
                 *          @throw CryptoException.
                 */

                std::string cryptoStringToB64(std::string & data,
                        UseKeyType ukt = VERIFICATION_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn	std::string Encryption::decryptoB64ToString(std::string & data, ResourceFileType rft,
                 * 		UseKeyType ukt = VERIFICATION_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief	method to decrypto string.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	data	b64 to decrypto.
                 * @param	rft				The rft.
                 * @param	ukt				The ukt.
                 *
                 * @return	data decrypto
                 * 			@throw CryptoException.
                 */

                std::string decryptoB64ToString(std::string & data,
                        ResourceFileType rft,
                        UseKeyType ukt = VERIFICATION_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @fn  std::string Encryption::decryptoB64ToString(std::string & data, ResourceFileType rft,
                 *      UseKeyType ukt = VERIFICATION_KEY) throw (Smartmatic::System::Exception::CryptoException);
                 *
                 * @brief   method to decrypto string.
                 *
                 * @author  Cesar.bonilla
                 * @date    4/28/2011
                 *
                 * @param [in,out]  data    b64 to decrypto.
                 * @param   rft             The rft.
                 * @param   ukt             The ukt.
                 *
                 * @return  data decrypto
                 *          @throw CryptoException.
                 */

                std::string decryptoB64ToString(std::string & data,
                        UseKeyType ukt = VERIFICATION_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);

                void decryptoB64ToBuffer(std::string & data,
                		Smartmatic::System::SafeBuffer & dataOut,
                        UseKeyType ukt = VERIFICATION_KEY,
                        bool pad = true)
                        throw (Smartmatic::System::Exception::CryptoException);


                void SignDataWithPersonalCertificate(Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & dataOut);
                bool VerifySignatureWithPersonalCertificate(Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & signature);

                /**
                 * @fn	Smartmatic::System::SafeBuffer Encryption::getInitKey() const;
                 *
                 * @brief	method getter init key.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @return	init key.
                 *
                 * ### param	sizeInitKey	size init key.
                 */

                const Smartmatic::System::SafeBuffer & getInitKey() const;

                /**
                 * @fn	Smartmatic::System::Security::Cryptography::DigestBuffer Encryption::getVerificationKey() const;
                 *
                 * @brief	method getter compose key.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @return	compose key.
                 */

                Smartmatic::System::SafeBuffer getVerificationKey() const;

                /**
                 * @fn	void Encryption::setOpeningCode(Smartmatic::System::SafeBuffer & openingCode);
                 *
                 * @brief	method setter opening code.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	openingCode	opening code.
                 *
                 * ### param	sizeOpeningCode	size opening code.
                 */

                void setOpeningCode(Smartmatic::System::GuidClass & openingCode);

                const Smartmatic::System::GuidClass & getOpeningCode();

                /**
                 * @fn	void Encryption::setMachineTime(double machineTime);
                 *
                 * @brief	Sets a machine time.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param	machineTime	Time of the machine.
                 */

                void setMachineTime(double machineTime);

                /**
                 * @fn	const Smartmatic::SAES::Common::Security::SecretKey& Encryption::getSecretKey ()
                 *
                 * @brief	Gets the secret key.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @return	The secret key.
                 */

                const Smartmatic::SAES::Common::Security::SecretKey& getSecretKey();

                /**
                 * @fn  Smartmatic::System::Security::Signed::SignedType Encryption::signedData(ResourceFileType rft);
                 *
                 * @brief   Signed data.
                 *
                 * @author  Cesar.bonilla
                 * @date    4/28/2011
                 *
                 * @param   rft The rft.
                 *
                 * @return  .
                 */

                Smartmatic::System::Security::Signed::SignedType signedData(ResourceFileType rft);

                /**
                 * @fn  bool Encryption::validateSigned(ResourceFileType rft);
                 *
                 * @brief   Validate signed.
                 *
                 * @author  Cesar.bonilla
                 * @date    4/28/2011
                 *
                 * @param   rft The rft.
                 *
                 * @return  true if it succeeds, false if it fails.
                 */

                bool validateSigned(ResourceFileType rft);

                /**
                 * @fn  bool Encryption::cryptoData(ResourceFileType rft);
                 *
                 * @brief   Crypto data.
                 *
                 * @author  Cesar.bonilla
                 * @date    4/28/2011
                 *
                 * @param   rft The rft.
                 *
                 * @return  true if it succeeds, false if it fails.
                 */

                bool cryptoData(ResourceFileType rft);

                /**
                 * @fn	const unsigned char * Encryption::getUseKey(UseKeyType ukt) const;
                 *
                 * @brief	method getter user key config.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param	ukt		use key type.
                 * @param 	result	a safe buffer with the key.
                 */

                void getUseKey(Smartmatic::System::SafeBuffer & result, UseKeyType ukt) const;

                /**
                 *
                 * @brief	method getter user key string.
                 *
                 * @author	Yadickson Soto
                 * @date	15/02/2012
                 *
                 * @param	ukt	use key type.
                 *
                 * @return	string use key type
                 */

                std::string getUseKeyString(UseKeyType ukt);

                /**
                 * @brief	method getter compose key
                 *
                 * @author	Yadickson Soto
                 * @date	26/07/2011
                 *
                 * @param	key
                 *
                 * @return	a safe buffer with the iv.
                 */
                void getComposeKey(const Smartmatic::System::SafeBuffer & key, Smartmatic::System::SafeBuffer & result, unsigned int length);

                /**
                 * @brief	method getter user iv
                 *
                 * @author	Yadickson Soto
                 * @date	26/07/2011
                 *
                 * @param	key
                 *
                 * @return	a safe buffer with the iv.
                 */
                void getUseIV(Smartmatic::System::SafeBuffer & key, Smartmatic::System::SafeBuffer & result, unsigned int length = 0);

                unsigned int getKeyLength();
                unsigned int getIVLength();

                Smartmatic::System::Security::Crypto::KeySize getKeySize();

                Smartmatic::System::Security::Crypto::Mode getModeType();

                /**
                 * @brief method getter signed secret key
                 * @return signed secret key
                 * @date 02/03/2012
                 * @author Yadickson Soto
                 */
                std::string getSignedSecretKey();

            private:

                static Encryption * instance; ///< The instance
                Smartmatic::System::GuidClass openingCode; ///< The opening code
                Smartmatic::SAES::Common::Security::SecretKey * m_SecretKey;  ///< The secret key
                Smartmatic::SAES::Common::Security::SecretKey * m_UPKey;  ///< The up key
                Smartmatic::System::SafeBuffer initKey; ///< init key

				static std::string initKeyBase64;   ///< The fourth initialise key base 6
                std::string signedSecretKey;	///< The signed secret key
                double machineTime; ///< Time of the machine

                /**
                 * @fn	void Encryption::configSigned(Smartmatic::System::Security::Signed & objSigned,
                 * 		Smartmatic::System::Security::Cryptography::CertificateValidator * validator,
                 * 		ResourceFileType rft);
                 *
                 * @brief	method config signed object.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param [in,out]	objSigned	signed object.
                 * @param [in,out]	validator	If non-null, the validator.
                 * @param	rft				 	resource file type.
                 */

                void configSigned(Smartmatic::System::Security::Signed & objSigned,
                        Smartmatic::System::Security::Cryptography::CertificateValidator * validator, ResourceFileType rft);

                /**
                 * @fn	int Encryption::getCertificateValidatorFlags(ResourceFileType rft);
                 *
                 * @brief	method getter certificate validator flags.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @param	rft	resource file type.
                 *
                 * @return	certificate validator flags.
                 */

                int getCertificateValidatorFlags(ResourceFileType rft);

                /**
                 * @fn	time_t Encryption::getCertificateValidatorTime();
                 *
                 * @brief	method getter certificate validator time.
                 *
                 * @author	Cesar.bonilla
                 * @date	4/28/2011
                 *
                 * @return	certificate validator time.
                 */

                time_t getCertificateValidatorTime();

                Smartmatic::System::Security::Crypto::KeySize keySize; ///< key size
                Smartmatic::System::Security::Crypto::Mode modeType; //< symmetric cipher
                static Smartmatic::Log::ISMTTLog* logger; ///< The logger
                Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories;	///< The directories
                Glib::Mutex mutex; ///< sync mutex
            };
        }
    }
}

#endif /*__ENCRYPTION__H__*/
