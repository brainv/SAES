/*
 * GpCommandWrapper.h
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#ifndef GPCOMMANDWRAPPER_H_
#define GPCOMMANDWRAPPER_H_

#include <glibmm.h>
#include <globalplatform/globalplatform.h>
#include "Exceptions/GpCommandException.h"

#define AIDLen 16;

class GpCommandWrapper
{

public:

	typedef enum PrivEnum
	{
		PRIV1,
		PRIV2,
		PRIV3,
		PRIV4

	}PrivEnumType;

	typedef enum CardStatusEnum
	{
		INSERTED,
		INVALID,
		NOT_INSERTED,
		READER_UNAVAILABLE

	} CardStatusEnumType;

	GpCommandWrapper();

	virtual ~GpCommandWrapper();

	void mGpEstablishContext () throw (GpCommandException);
	void mGpReleaseContext () throw (GpCommandException);

	CardStatusEnumType mGpCardConnect () throw (GpCommandException);
	void mGpDisconnect () throw (GpCommandException);

	void mOpenSecureChannel (
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
	throw (GpCommandException);

	void mGpSelect (unsigned char* aid, unsigned long aidLen) throw (GpCommandException);
	void mGpDelete (unsigned char* aid, unsigned long aidLen) throw (GpCommandException);

	void mGpInstall (std::string capPath) throw (GpCommandException);

	void mGpSendAPDU (
			  const unsigned char* apdu
			, const unsigned long apduLen
			, unsigned char* apdu_response
			, unsigned long& apdu_response_len)
	throw (GpCommandException);


private:

	OPGP_CARD_CONTEXT cardContext;
	OPGP_CARD_INFO cardInfo;
	GP211_SECURITY_INFO securityInfo211;

	unsigned long selectedAIDLen;
	unsigned char* selectedAID;

	static long status_not_inserted;
	static long reader_not_available;
	static long reader_not_found;
	static long card_invalid;

};

#endif /* GPCOMMANDWRAPPER_H_ */
