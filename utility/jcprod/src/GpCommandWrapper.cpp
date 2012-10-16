/*
 * GpCommandWrapper.cpp
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#include <iostream>
#include <string.h>
#include "GpCommandWrapper.h"

#define BUFLEN 1024
#define FILENAMELEN 256

#define HANDLE_ERROR(x, y) \
	if (OPGP_ERROR_CHECK( ( x ) )) { \
		std::stringstream ss;      \
		ss << ( x ).errorMessage; \
		throw GpCommandException ( ss.str () ); }

#define TRACE(x) std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": " << ( x ) << std::endl;

#define INST_PARAM_LEN 14
#define INST_PARAMS { 0x05, 0x08, 0x05, 0x30, 0x08, 0x00, 0x33, 0x33, 0x72, 0x63, 0x14, 0x15, 0x56, 0x97 }
#define PRIVILEGE 2

#define CARD_INVALID 0x80100067
#define READER_NOT_AVAILABLE 0x80100017
#define READER_NOT_FOUND 0x80100009
#define CARD_NOT_INSERTED 0x8010000C

#define MAX_AID_LEN 10

//
//================ Static initializations  ========================
//

long GpCommandWrapper::status_not_inserted = 0x8010000C;
long GpCommandWrapper::reader_not_available = 0x80100017;
long GpCommandWrapper::reader_not_found = 0x80100009;
long GpCommandWrapper::card_invalid = 0x80100067;


//
//================ Life Cycle ========================
//

GpCommandWrapper::GpCommandWrapper()
{
	selectedAID = (unsigned char*)malloc (MAX_AID_LEN * sizeof (unsigned char));
}

GpCommandWrapper::~GpCommandWrapper()
{
	delete (selectedAID);
}

//
//================ Command Implementation ========================
//


void GpCommandWrapper::mGpEstablishContext ()
throw (GpCommandException)
{
	std::string lib_name = "gppcscconnectionplugin";
	std::string lib_version = "1.0.1";
	OPGP_ERROR_STATUS status;

	OPGP_ERROR_CREATE_NO_ERROR (status);

	memcpy (cardContext.libraryName, lib_name.c_str (), lib_name.length() + 1 );
	memcpy (cardContext.libraryVersion, lib_version.c_str (), lib_version.length () + 1);

	cardContext.libraryHandle = NULL;
	cardContext.librarySpecific = NULL;

	status = OPGP_establish_context(&cardContext);

	HANDLE_ERROR (status, "establish_context failed with error 0x");
}

void GpCommandWrapper::mGpReleaseContext ()
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_release_context(&cardContext);

	HANDLE_ERROR (status, "release_context failed with error 0x");
}

GpCommandWrapper::CardStatusEnumType GpCommandWrapper::mGpCardConnect ()
throw (GpCommandException)
{
	char buf[BUFLEN + 1];
	unsigned long readerStrLen = BUFLEN;
	std::string reader_name = "";

	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_list_readers (cardContext, buf, &readerStrLen);

	HANDLE_ERROR(status, "list_readers failed with error 0x");

	reader_name.assign (buf);
	int protocol = OPGP_CARD_PROTOCOL_T0 | OPGP_CARD_PROTOCOL_T1;

	status = OPGP_card_connect (cardContext, reader_name.c_str (), &cardInfo, protocol);

	switch (status.errorCode)
	{
	case OPGP_ERROR_STATUS_SUCCESS:
		return INSERTED;
	case CARD_INVALID:
		return INVALID;
	case READER_NOT_AVAILABLE:
	case READER_NOT_FOUND:
		return READER_UNAVAILABLE;
	case CARD_NOT_INSERTED:
		return NOT_INSERTED;
	default:
		std::cout << "Unknown error code" << std::endl;
		return NOT_INSERTED;
	}
}


void GpCommandWrapper::mGpDisconnect ()
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_card_disconnect(cardContext, &cardInfo);

	HANDLE_ERROR (status, "card_disconnect() returns 0x");
}

void GpCommandWrapper::mGpSelect (PBYTE aid, unsigned long aidLen)
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	status = OPGP_select_application (cardContext, cardInfo, aid, aidLen);

	HANDLE_ERROR (status, "select_application() returns 0x");

	memcpy (selectedAID, aid, aidLen);
	selectedAIDLen = aidLen;
}

void GpCommandWrapper::mOpenSecureChannel (
		  unsigned char scp
		, unsigned char scpImpl
		, unsigned char* key
		, unsigned char* enc_key
		, unsigned char* mac_key
		, unsigned char* kek_key
		, unsigned char keySetVersion
		, unsigned char keyIndex
		, unsigned char securityLevel
		, unsigned char keyDerivation)
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	if ( scp == 0 || scpImpl == 0)
	{
		status = GP211_get_secure_channel_protocol_details(cardContext, cardInfo,
				&scp,
				&scpImpl);

		HANDLE_ERROR (status, "GP211_get_secure_channel_protocol_details() returns 0x");
	}

	status = GP211_mutual_authentication(cardContext, cardInfo,
			key,
			enc_key,
			mac_key,
			kek_key,
			keySetVersion,
			keyIndex,
			scp,
			scpImpl,
			securityLevel,
			keyDerivation,
			&securityInfo211);

	HANDLE_ERROR (status, "mutual_authentication() returns 0x");
}


void GpCommandWrapper::mGpDelete (unsigned char* aid, unsigned long aidLen)
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR (status);

	OPGP_AID AIDs[1];
	DWORD receiptLen = 10;

	memcpy (AIDs[0].AID, aid, aidLen);
	AIDs[0].AIDLength = (BYTE)aidLen;

	GP211_RECEIPT_DATA receipt[10];

	status = GP211_delete_application(cardContext, cardInfo, &securityInfo211,
			AIDs, 1,
			(GP211_RECEIPT_DATA *)receipt,
			&receiptLen);

	HANDLE_ERROR (status, "delete() returns 0x");
}

void GpCommandWrapper::mGpInstall ( std::string capPath )
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	OPGP_LOAD_FILE_PARAMETERS loadFileParams;
	DWORD receiptDataAvailable = 0;
	DWORD receiptDataLen = 0;

	unsigned char instParams[INST_PARAM_LEN] = INST_PARAMS;

	unsigned char priv = PRIVILEGE;

	status = OPGP_read_executable_load_file_parameters ((char *)capPath.c_str (), &loadFileParams);

	HANDLE_ERROR (status, "read_executable_load_file_parameters() returns 0x");

	status = GP211_install_for_load (cardContext, cardInfo, &securityInfo211,
			(PBYTE)loadFileParams.loadFileAID.AID, loadFileParams.loadFileAID.AIDLength,
			(PBYTE)selectedAID, selectedAIDLen, // previously selected ISD (CardManager)
			NULL, NULL,
			loadFileParams.loadFileSize,
			0,      //optionStr.vDataLimit,          // jvictor
			0  );   //optionStr.nvDataLimit);        // jvictor

	HANDLE_ERROR (status, "install_for_load() returns 0x");

	status = GP211_load(cardContext, cardInfo, &securityInfo211,
			NULL, 0,
			(char *)capPath.c_str (),
			NULL, &receiptDataLen, NULL);

	HANDLE_ERROR (status, "load() returns 0x");

	GP211_RECEIPT_DATA receipt;

	status = GP211_install_for_install_and_make_selectable (
			cardContext, cardInfo, &securityInfo211,
			(PBYTE)loadFileParams.loadFileAID.AID, loadFileParams.loadFileAID.AIDLength,
			(PBYTE)loadFileParams.appletAIDs[0].AID, loadFileParams.appletAIDs[0].AIDLength,
			(PBYTE)loadFileParams.appletAIDs[0].AID, loadFileParams.appletAIDs[0].AIDLength,
			priv,
			0, // vDataLimit
			0, //nvDataLimit,
			(PBYTE)instParams,
			(unsigned long) sizeof (instParams),
			NULL, // No install token
			&receipt,
			&receiptDataAvailable);

	HANDLE_ERROR (status, "install_for_install_and_make_selectable() returns 0x");
}


void GpCommandWrapper::mGpSendAPDU (
		  const unsigned char* apdu
		, const unsigned long apduLen
        , unsigned char* apdu_response
        , unsigned long& apdu_response_len)
throw (GpCommandException)
{
	OPGP_ERROR_STATUS status;
	OPGP_ERROR_CREATE_NO_ERROR(status);

	BYTE recvAPDU[258];
	DWORD recvAPDULen = 258;

	// Install for Load

	status = GP211_send_APDU (
			cardContext, cardInfo,
			&securityInfo211, //NULL,
			(PBYTE)apdu, apduLen,
			recvAPDU, &recvAPDULen);

	HANDLE_ERROR (status, "send_APDU() returns 0x");

	if (apdu_response != NULL)
	{
		memcpy (apdu_response, recvAPDU, recvAPDULen);
		apdu_response_len = recvAPDULen;
	}
}

