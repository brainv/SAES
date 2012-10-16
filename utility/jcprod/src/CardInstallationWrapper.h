/*
 * JcopWrapper.h
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#ifndef JCOPWRAPPER_H_
#define JCOPWRAPPER_H_


#include "Exceptions/GpCommandException.h"


class CardInstallationWrapper {

public:

	CardInstallationWrapper();
	virtual ~CardInstallationWrapper();

	static bool isCardPresent ();
	static bool IsCardInitialized () throw (GpCommandException);
	static bool IsAppletInstalled () throw (GpCommandException);
	static bool IsCardFused () throw (GpCommandException);

	static void InitializeCard () throw (GpCommandException);
	static void FuseCard () throw (GpCommandException);
	static void InstallApplet () throw (GpCommandException);

private:

	// JCOP initialization APDUs

	static unsigned char select_root_applet[];
	static unsigned char boot_command[];
	static unsigned char generic_contact_protocol_0[];
	static unsigned char generic_contact_protocol_1[];
	static unsigned char data_block_pcd[];
	static unsigned char atr_setting_0[];
	static unsigned char atr_setting_1[];
	static unsigned char historical_bytes_0[];
	static unsigned char historical_bytes_1[];

	static unsigned char set_key_0[];
	static unsigned char set_key_version_0[];

	static unsigned char set_key_1[];
	static unsigned char set_key_version_1[];

	static unsigned char set_key_2[];
	static unsigned char set_key_version_2[];

	static unsigned char enable_card_mgr[];
	static unsigned char protect_card[];
	static unsigned char fuse_card[];

	static unsigned char identify[];

	// Install related APDUs

	static unsigned char isdid[];
	static unsigned char key[];
	static unsigned char enc_key[];
	static unsigned char mac_key[];
	static unsigned char kek_key[];
	static unsigned char appletAid[];
	static unsigned char packageAid[];
};

#endif /* JCOPWRAPPER_H_ */
