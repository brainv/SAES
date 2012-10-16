/*
 * JcopWrapper.cpp
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#include <iostream>
#include <string.h>
#include "GpCommandWrapper.h"
#include "CardInstallationWrapper.h"



#define TRACE(x) std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": " << ( x ) << std::endl;

#define CAP_PATH "./VotingCard.cap"


//select ROOT applet: AID 2f 46 a8 58 2b 61 f5 da 2f 79 9c f7 b4 20 18 75 00
#define SELECT_ROOT_APPLET {0X00, 0XA4, 0X04, 0X00, 0X10, 0X2f, 0X46, 0Xa8, 0X58, 0X2b, 0X61, 0Xf5, 0Xda, 0X2f, 0X79, 0X9c, 0Xf7, 0Xb4, 0X20, 0X18, 0X75, 0X00}

// issue the BOOT command
#define BOOT_COMMAND {0X00, 0XF0, 0X00, 0X00}

//Set generic contact protocol
#define GENERIC_CONTACT_PROTOCOL_0 {0XC0, 0XD6, 0X01, 0X22, 0X01, 0X0B}
#define GENERIC_CONTACT_PROTOCOL_1 {0XC0, 0XD6, 0X01, 0X45, 0X01, 0X0B}

//set size of data block to PCD for T=1 protocol
#define DATA_BLOCK_PCD {0xC0, 0xD6, 0x01, 0x20, 0x01, 0xFE}

//set ATR settings for cold an warn reset
#define ATR_SETTING_0 {0XC0, 0XD6, 0X01, 0X24, 0X09, 0X08, 0XF0, 0X18, 0X00, 0X00, 0X81, 0X31, 0XFE, 0X45}
#define ATR_SETTING_1 {0XC0, 0XD6, 0X01, 0X47, 0X09, 0X08, 0XF0, 0X18, 0X00, 0X00, 0X81, 0X31, 0XFE, 0X45}

//set ATR historical bytes
#define HOSTORICAL_BYTES_0 {0XC0, 0XD6, 0X01, 0X34, 0X0E, 0X0D, 0X50, 0X56, 0X5F, 0X4A, 0X43, 0X4F, 0X50, 0X32, 0X31, 0X76, 0X32, 0X33, 0X32}
#define HOSTORICAL_BYTES_1 {0XC0, 0XD6, 0X01, 0X57, 0X0E, 0X0D, 0X50, 0X56, 0X5F, 0X4A, 0X43, 0X4F, 0X50, 0X32, 0X31, 0X76, 0X32, 0X33, 0X32}

//set key   404142434445464748494A4B4C4D4E4F
#define SET_KEY_0 {0XC0, 0XD6, 0X03, 0Xcd, 0X10, 0X40, 0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47, 0X48, 0X49, 0X4A, 0X4B, 0X4C, 0X4D, 0X4E, 0X4F}

//set key  version
#define SET_KEY_VERSION_0 {0XC0, 0XD6, 0X03, 0Xc9, 0X01, 0X01}

//set key   404142434445464748494A4B4C4D4E4F
#define SET_KEY_1 {0XC0, 0XD6, 0X03, 0Xe9, 0X10, 0X40, 0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47, 0X48, 0X49, 0X4A, 0X4B, 0X4C, 0X4D, 0X4E, 0X4F}
//set key  version
#define SET_KEY_VERSION_1 {0XC0, 0XD6, 0X03, 0Xe5, 0X01, 0X01}

//set key   404142434445464748494A4B4C4D4E4F
#define SET_KEY_2 {0XC0, 0XD6, 0X04, 0X05, 0X10, 0X40, 0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47, 0X48, 0X49, 0X4A, 0X4B, 0X4C, 0X4D, 0X4E, 0X4F}
//set key  version
#define SET_KEY_VERSION_2 {0XC0, 0XD6, 0X04, 0X01, 0X01, 0X01}

//Initialize the card. enable card manager
#define ENABLE_CARD_MGR {0xC0, 0xD6, 0x03, 0x6A, 0x02, 0xF8, 0x07}

//issue protect command.
#define PROTECT_CARD {0x00, 0x10, 0x00, 0x00}

//issue FUSE command. Disable the ROOT applet.
#define FUSE_CARD {0x00, 0x00, 0x00, 0x00}


#define IDENTIFY_APDU {0x00, 0xA4, 0x04, 0x00, 0x09, 0xA0, 0x00, 0x00, 0x01, 0x67, 0x41, 0x30, 0x00, 0xFF, 0x00}


#define ISD_AID  {0xa0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00}
#define KEY      {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}
#define KEK_KEY  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}
#define ENC_KEY  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}
#define MAC_KEY  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}

#define APP_AID {0xF0, 0x00, 0x00, 0x00, 0x62, 0x03, 0x01, 0x0C, 0x01, 0x01};
#define PKG_AID {0xF0, 0x00, 0x00, 0x00, 0x62, 0x03, 0x01, 0x0C, 0x01};


unsigned char CardInstallationWrapper::select_root_applet[] = SELECT_ROOT_APPLET;
unsigned char CardInstallationWrapper::boot_command[] = BOOT_COMMAND;
unsigned char CardInstallationWrapper::generic_contact_protocol_0[] = GENERIC_CONTACT_PROTOCOL_0;
unsigned char CardInstallationWrapper::generic_contact_protocol_1[] = GENERIC_CONTACT_PROTOCOL_1;
unsigned char CardInstallationWrapper::data_block_pcd[] = DATA_BLOCK_PCD;
unsigned char CardInstallationWrapper::atr_setting_0[] = ATR_SETTING_0;
unsigned char CardInstallationWrapper::atr_setting_1[] = ATR_SETTING_1;
unsigned char CardInstallationWrapper::historical_bytes_0[] = HOSTORICAL_BYTES_0;
unsigned char CardInstallationWrapper::historical_bytes_1[] = HOSTORICAL_BYTES_1;

unsigned char CardInstallationWrapper::set_key_0[] = SET_KEY_0;
unsigned char CardInstallationWrapper::set_key_version_0[] = SET_KEY_VERSION_0;

unsigned char CardInstallationWrapper::set_key_1[] = SET_KEY_1;
unsigned char CardInstallationWrapper::set_key_version_1[] = SET_KEY_VERSION_1;

unsigned char CardInstallationWrapper::set_key_2[] = SET_KEY_2;
unsigned char CardInstallationWrapper::set_key_version_2[] = SET_KEY_VERSION_2;

unsigned char CardInstallationWrapper::enable_card_mgr[] = ENABLE_CARD_MGR;
unsigned char CardInstallationWrapper::protect_card[] = PROTECT_CARD;
unsigned char CardInstallationWrapper::fuse_card[] = FUSE_CARD;


unsigned char CardInstallationWrapper::identify[] = IDENTIFY_APDU;

unsigned char CardInstallationWrapper::isdid[] = ISD_AID;
unsigned char CardInstallationWrapper::key[] = KEY;
unsigned char CardInstallationWrapper::enc_key[] = ENC_KEY;
unsigned char CardInstallationWrapper::mac_key[] = MAC_KEY;
unsigned char CardInstallationWrapper::kek_key[] = KEK_KEY;
unsigned char CardInstallationWrapper::appletAid[] = APP_AID;
unsigned char CardInstallationWrapper::packageAid[] = PKG_AID;



CardInstallationWrapper::CardInstallationWrapper()
{
}

CardInstallationWrapper::~CardInstallationWrapper()
{
	// TODO Auto-generated destructor stub
}

bool CardInstallationWrapper::isCardPresent ()
{
	GpCommandWrapper cmd;
	bool connected = false;

	try
	{
		cmd.mGpEstablishContext();

		switch ( cmd.mGpCardConnect () )
		{
		case GpCommandWrapper::INSERTED:
			connected = true;
			cmd.mGpDisconnect ();
			break;
		case GpCommandWrapper::INVALID:
			connected = false; //TODO: throw an exception
			break;
		case GpCommandWrapper::NOT_INSERTED:
			connected = false;
			break;
		case GpCommandWrapper::READER_UNAVAILABLE:
			connected = false; //TODO: throw an exception
			break;
		default:
			TRACE ( "WARNING: unknown card state" );
			break;
		}

		cmd.mGpReleaseContext ();
	}
	catch (GpCommandException& e)
	{
		TRACE (e.what());
		connected = false;
	}

	return connected;
}

bool CardInstallationWrapper::IsCardFused ()
throw (GpCommandException)
{
	GpCommandWrapper cmd;
	unsigned char recvAPDU[258];
	unsigned long recvAPDULen = 258;
	bool fused = false;

//	unsigned char identify[] = IDENTIFY_APDU;

	try
	{
		cmd.mGpEstablishContext();
		cmd.mGpCardConnect();

		cmd.mGpSendAPDU(identify, sizeof (identify), recvAPDU, recvAPDULen);

		cmd.mGpDisconnect();
		cmd.mGpReleaseContext();
	}
	catch (GpCommandException& e)
	{
		TRACE (e.what());
	}

	fused = recvAPDU[14] != 0;

	return fused;
}

bool CardInstallationWrapper::IsCardInitialized ()
throw (GpCommandException)
{
	GpCommandWrapper cmd;
	bool need_to_initialize = false;
	unsigned char isid[8] = ISD_AID;

	cmd.mGpEstablishContext();
	cmd.mGpCardConnect();

	try
	{
		cmd.mGpSelect (isid, sizeof (isid));
	}
	catch (GpCommandException& e)
	{
		need_to_initialize = true;
	}

	cmd.mGpDisconnect();
	cmd.mGpReleaseContext();

	return ! need_to_initialize;
}

bool CardInstallationWrapper::IsAppletInstalled ()
throw (GpCommandException)
{
	GpCommandWrapper cmd;
	bool need_to_install = false;
	unsigned char appletAid[] = APP_AID;

	cmd.mGpEstablishContext();
	cmd.mGpCardConnect();

	try
	{
		cmd.mGpSelect (appletAid, sizeof (appletAid));
	}
	catch (GpCommandException& e)
	{
		need_to_install = true;
	}

	cmd.mGpDisconnect();
	cmd.mGpReleaseContext();

	return ! need_to_install;
}

void CardInstallationWrapper::InstallApplet ()
throw (GpCommandException)
{
	GpCommandWrapper cmd;

	try
	{
		cmd.mGpEstablishContext();
		cmd.mGpCardConnect();

		cmd.mGpSelect(isdid, sizeof (isdid));

		cmd.mOpenSecureChannel (
				  0         // scp
				, 0         // scpImpl
				, key
				, enc_key
				, mac_key
				, kek_key
				, 0         // keySetVersion
				, 0         // keyIndex
				, 1         // securityLevel
				, OPGP_DERIVATION_METHOD_NONE // keyDerivation
		);

		cmd.mGpInstall(CAP_PATH);

		cmd.mGpDisconnect();
		cmd.mGpReleaseContext();
	}
	catch (GpCommandException& e)
	{

		TRACE (e.what());
		throw;
	}
}

void CardInstallationWrapper::InitializeCard ()
throw (GpCommandException)
{
	GpCommandWrapper cmd;
	unsigned long res_ln;

	try
	{
		cmd.mGpEstablishContext();
		cmd.mGpCardConnect();

		cmd.mGpSendAPDU(select_root_applet, sizeof (select_root_applet), NULL, res_ln);
		cmd.mGpSendAPDU(boot_command, sizeof (boot_command), NULL, res_ln);
		cmd.mGpSendAPDU(generic_contact_protocol_0, sizeof (generic_contact_protocol_0), NULL, res_ln);
		cmd.mGpSendAPDU(generic_contact_protocol_1, sizeof (generic_contact_protocol_1), NULL, res_ln);
		cmd.mGpSendAPDU(data_block_pcd, sizeof (data_block_pcd), NULL, res_ln);
		cmd.mGpSendAPDU(atr_setting_0, sizeof (atr_setting_0), NULL, res_ln);
		cmd.mGpSendAPDU(atr_setting_1, sizeof (atr_setting_1), NULL, res_ln);
		cmd.mGpSendAPDU(historical_bytes_0, sizeof (historical_bytes_0), NULL, res_ln);
		cmd.mGpSendAPDU(historical_bytes_1, sizeof (historical_bytes_1), NULL, res_ln);

		cmd.mGpSendAPDU(set_key_0, sizeof (set_key_0), NULL, res_ln);
		cmd.mGpSendAPDU(set_key_version_0, sizeof (set_key_version_0), NULL, res_ln);

		cmd.mGpSendAPDU(set_key_1, sizeof (set_key_1), NULL, res_ln);
		cmd.mGpSendAPDU(set_key_version_1, sizeof (set_key_version_1), NULL, res_ln);

		cmd.mGpSendAPDU(set_key_2, sizeof (set_key_2), NULL, res_ln);
		cmd.mGpSendAPDU(set_key_version_2, sizeof (set_key_version_2), NULL, res_ln);

		cmd.mGpSendAPDU(enable_card_mgr, sizeof (enable_card_mgr), NULL, res_ln);

		cmd.mGpDisconnect();
		cmd.mGpReleaseContext();
	}
	catch (GpCommandException& e)
	{
		TRACE (e.what());
		throw;
	}
}

void CardInstallationWrapper::FuseCard ()
throw (GpCommandException)
{
	GpCommandWrapper cmd;
	unsigned long res_ln;

	try
	{
		cmd.mGpEstablishContext();
		cmd.mGpCardConnect();

		cmd.mGpSendAPDU(select_root_applet, sizeof (select_root_applet), NULL, res_ln);
		cmd.mGpSendAPDU(protect_card, sizeof (protect_card), NULL, res_ln);
		cmd.mGpSendAPDU(fuse_card, sizeof (fuse_card), NULL, res_ln);

		cmd.mGpDisconnect();
		cmd.mGpReleaseContext();
	}
	catch (GpCommandException& e)
	{
		TRACE (e.what());
		throw;
	}
}
