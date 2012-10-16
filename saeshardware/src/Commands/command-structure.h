/**
 * @file	command-structure.h
 *
 * @brief	Declares the command structure class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * commandstructure
 * Copyright (C)  2010 <>
 * 
 * commandstructure is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * commandstructure is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef _COMMAND_STRUCTURE_H_
#define _COMMAND_STRUCTURE_H_

#include "Connections/i-connection.h"


namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				namespace sections
				{
					//this enum defines each section of the command structure and allow to
					//determine how the sections will be ordered.
					// 

					/**
					 * @brief	This enum defines each section of the command structure and allow to
					 *          determine how the sections will be ordered.
					 */

					enum SectionsOfCommand
					{

						Sender, 
						MAC,	
						Lenght,
						Noise,
						MultiByte,
						CommandByte,
						Data,
						Checksum,
						Trailer,
						EncryptedData ///< ONLY USE THIS ENUM VALUE ("EncryptedData") TO ADD A SECTION TO THE COMMAND THAT REPRESENTS
									///< THE 4 SECTIONS NOISE,COMMANDBYTE,MULTIBYTE AND DATA  IN THAT SPECIFIC
									///< ORDER AND ENCRYPTED (IF YOU WANT TO SCRAMBLE NOISE,COMMANDBYTE,MULTIBYTE AND DATA
									///< DONT USE THIS ENUM VALUE AND INSTEAD USE THE INDIVIDUAL ENUM VALUES "Noise","MultiByte"
									///< CommandByte" AND "Data"
					};
				}

				/**
				 * @brief	Interface to define the contract that each provider of the sender Section must accomplish. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderSender
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderSender() {}

					/**
					 * @brief	Gets the sender.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The sender.
					 */

					virtual std::vector<unsigned char> getSender() = 0;
				};

				/**
				 * @brief	Interface to define the contract that each provider of the  MAC must accomplish
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderMAC
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderMAC() {}

					/**
					 * @brief	Gets the encrypted mac.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	encryptedData	Information describing the encrypted data
					 *
					 * @return	The encrypted mac.
					 */

					virtual std::vector<unsigned char> getEncryptedMAC(std::vector<unsigned char> encryptedData) = 0;

					/**
					 * @brief	Gets the normal mac.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The normal mac.
					 */

					virtual std::vector<unsigned char> getNormalMAC() = 0;
				};

				/**
				 * @brief	Interface to define the contract that each provider of the  Encryption (generally CommandData+Noise) must accomplish. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderEncryption
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderEncryption() {}

					/**
					 * @brief	Gets an encrypted data.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	commandData	Information describing the command.
					 * @param	noise	   	The noise.
					 *
					 * @return	The encrypted data.
					 */

					virtual std::vector<unsigned char> getEncryptedData(std::vector<unsigned char> commandData, std::vector<unsigned char> noise) = 0;
				};

				/**
				 * @brief	Interface to define the contract that each provider of the Noise must accomplish. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderNoise
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderNoise() {}

					/**
					 * @brief	Gets the noise.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The noise.
					 */

					virtual std::vector<unsigned char> getNoise() = 0;
				};

				/**
				 * @brief	Interface to define the contract that each provider of the Lenght must accomplish.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderLenght
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderLenght() {}

					/**
					 * @brief	Gets the lenght.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	commandDataSize	Size of the command data.
					 *
					 * @return	The lenght.
					 */

					virtual std::vector<unsigned char> getLenght(int commandDataSize) = 0;
				};

				/**
				 * @brief	Interface to define the contract that each provider of the CheckSum must accomplish.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderCheckSum
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderCheckSum() {}

					/**
					 * @brief	Gets the check sum.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	commandData	Information describing the command data
					 *
					 * @return	The check sum.
					 */

					virtual std::vector<unsigned char> getCheckSum(std::vector<unsigned char> commandData) = 0;
				};

				/**
				 * @brief	Interface to define the contract that each provider of the trailer must accomplish. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IProviderTrailer
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IProviderTrailer() {}

					/**
					 * @brief	Gets the trailer.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The trailer.
					 */

					virtual std::vector<unsigned char> getTrailer() = 0;
				};

				/**
				 * @brief	Interface to define the method launched on a received response. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IResponseListener
				{
				public:

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~IResponseListener() {}

					/**
					 * @brief	Response event.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual void  responseEvent() = 0;
				};

				/**
				 * @brief	Base class that defines the basic structure of all commands. It contains sections Sender,
				 * 			MAC, Lenght, Noise, MultiByteIdentifier, CommandByte and Data. Each section can be of any
				 * 			lenght or non-existant. The class receives the providers for some sections, and the children should
				 * 			define other specific sections like MultiByteIdentifier, CommandByte and Data.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class CommandStructure: public IResponseListener
				{


				protected:
					// These vectors define the sub-sections of the data that is sent to the MTD. It is implicitly understood
					// that most commands independently of the MTD will also have this sub-sections
					
					std::vector<unsigned char> MultiByteIdentifier; ///< Identifier for the multi byte
					std::vector<unsigned char> CommandByte; ///< The command byte
					std::vector<unsigned char> Data;	///< The data
					int retriesToSend ; ///< The retries to send
					int retriesToRecive;	///< The retries to receive
					int timeBetweenRetryuS; ///< The time between retries
					int charsExpected;  ///< The characters expected
					bool hasResponse;   ///< true if has response
					bool hasEncryption; ///< true if has encryption
					bool success;   ///< true if the operation was a success, false if it failed

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual void Initialize() = 0;

					/**
					 * @brief	Gets the order of command.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual	void getOrderOfCommand() = 0;

					/**
					 * @brief	Executes the command on the connetion provider.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	connectionProvider	If non-null, the connection provider.
					 *
					 * @return	.
					 */

					virtual std::vector<unsigned char> Execute(Smartmatic::SAES::HW::Connections::IConnection* connectionProvider) = 0;

					/**
					 * @brief	Analyze response from the connection provider.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	connectionProvider	If non-null, the connection provider.
					 * @param	response				  	The response.
					 *
					 * @return	.
					 */

					virtual std::vector<unsigned char> analyzeResponse(Smartmatic::SAES::HW::Connections::IConnection* connectionProvider, std::vector<unsigned char> response);

					/**
					 * @brief	This method finds out if the response is the correct one.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	response	The response.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool ProccessResponse(std::vector<unsigned char> response);

					
					std::vector<sections::SectionsOfCommand> OrderOfCommand;	///< this vector must be passed in the initialization of the command and will allow to determine the order of the sections

	
				private:
					std::vector<unsigned char> Sender;  ///< The sender of the sections
					std::vector<unsigned char> MAC; ///< The mac of the sections
					std::vector<unsigned char> CheckSum;	///< The check sum of the sections
					std::vector<unsigned char> Trailer; ///< The trailer of the sections
					std::vector<unsigned char> Lenght;  ///< The lenght of the sections
					std::vector<unsigned char> Noise;   ///< The noise of the sections
					std::vector<unsigned char> fullData;	///< this vector represents the full formed command
					std::vector<unsigned char> response;	///< this vector represents the response received after sending the command, if such a response is available
	
					std::vector<IResponseListener*> responseListeners;  ///< the listeners of the event defined by the IResponseListenerInterface when expecting an asynchronous response

					struct thread_args
					{

						CommandStructure* This ;	///< Pointer to and instance of the command structure.
						void*connectionPtr ;	///< Pointer to the connection.

						/**
						 * @brief	Constructor.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @param [in,out]	t	The current command structure
						 * @param [in,out]	p	The void pointer to the connection.
						 */

						thread_args( CommandStructure* t, void* p ): This(t), connectionPtr(p) {}
					};

					/**
					 * @brief	Executes the thread operation.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	threadArgs	If non-null, the thread arguments.
					 *
					 * @return	null if it fails, else.
					 */

					static void* runThread(void *threadArgs)
					{
						thread_args* tf_args = static_cast<thread_args*>(threadArgs);
						//CommandStructure* This = tf_args->This;
						//IConnection* connection =(IConnection*)  tf_args-> connectionPtr;
						//int result = This->runAsynchronousResponse(connection);
						delete  tf_args ;
						return NULL; 
					}

					/**
					 * @brief	Executes the asynchronous response operation.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	connectionPtr	If non-null, the connection pointer.
					 *
					 * @return	.
					 */

					int runAsynchronousResponse(Smartmatic::SAES::HW::Connections::IConnection *connectionPtr);

				public:

					/**
					 * @brief	Response event.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void responseEvent();

					/**
					 * @brief	Sets the characters expected.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	expected	The expected.
					 */

					void setCharsExpected(int expected);

					/**
					 * @brief	Adds a raw data. 
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 */

					void addRawData(unsigned char data);

					/**
					 * @brief	Clears the raw data.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void clearRawData();

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					CommandStructure();

					/**
					 * @brief	Query if this object is success.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if success, false if not.
					 */

					bool isSuccess();

					/**
					 * @brief	Query if this object has response.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if response, false if not.
					 */

					bool HasResponse();

					/**
					 * @brief	Gets the response.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The response.
					 */

					std::vector<unsigned char> getResponse();

					/**
					 * @brief	Adds a listener. 
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	responseListener	If non-null, the response listener.
					 */

					void addListener(IResponseListener* responseListener);

					/**
					 * @brief	Clears the listeners.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void clearListeners();

					/**
					 * @brief	Erase listener by index.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	index	Zero-based index of the.
					 */

					void eraseListenerByIndex(int index);

					/**
					 * @brief	Erase teh first apperance of a specific listener.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	responseListener	If non-null, the response listener.
					 */

					void eraseSpecificListener(IResponseListener* responseListener);

					/**
					 * @brief	Adds a section. 
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	section	The section.
					 */

					void addSection(sections::SectionsOfCommand section);

					/**
					 * @brief	Clears the sections.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void clearSections();

					/**
					 * @brief	Erase section by index.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	index	Zero-based index of the.
					 */

					void eraseSectionByIndex(int index);

					/**
					 * @brief	Erase the first appearence of the specific enum.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	section	The section.
					 */

					void eraseSpecificSection(sections::SectionsOfCommand section);

					/**
					 * @brief	Begins a send data in an asynchronous way.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	connectionProvider	If non-null, the connection provider.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool beginSendData(Smartmatic::SAES::HW::Connections::IConnection* connectionProvider);

					/**
					 * @brief	Sends a data in a synchronous way
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	connectionProvider	If non-null, the connection provider.
					 *
					 * @return	.
					 */

					virtual std::vector<unsigned char> sendData(Smartmatic::SAES::HW::Connections::IConnection* connectionProvider);

					/**
					 * @brief	It allows to determine each section and to sort the order of the command, and get the data.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	send	  	If non-null, the send.
					 * @param [in,out]	mac		  	If non-null, the mac.
					 * @param [in,out]	lenght	  	If non-null, the lenght.
					 * @param [in,out]	noise	  	If non-null, the noise.
					 * @param [in,out]	encryption	If non-null, the encryption.
					 * @param [in,out]	checksum  	If non-null, the checksum.
					 * @param [in,out]	trailer   	If non-null, the trailer.
					 *
					 * @return	The data.
					 */

					std::vector<unsigned char> GetData(IProviderSender *send,IProviderMAC *mac, IProviderLenght *lenght,
					IProviderNoise *noise, IProviderEncryption *encryption, IProviderCheckSum *checksum,
                                                IProviderTrailer *trailer);

				};
			}
		}
	}
}

#endif // _COMMAND_STRUCTURE_H_

