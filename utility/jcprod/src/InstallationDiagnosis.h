/*
 * InstallationDiagnosis.h
 *
 *  Created on: Oct 3, 2011
 *      Author: Marcel Cordoví
 */

#ifndef INSTALLATIONDIAGNOSIS_H_
#define INSTALLATIONDIAGNOSIS_H_


#define APLT_CLA 0x80; // CLA for the voting card applet

#define INS_VER_GLB_PIN 0xF1; // INS for VerifyGlobalPIN

#define INS_VER_PSS_PIN  0xF2; // INS for verifyPaswordPIN
#define INS_SET_PSS_PIN  0xF3; // INS for setPaswordPIN
#define INS_GET_PSS_PIN  0xF4; // INS for getPaswordPIN

#define INS_SET_PSSWRD 0xF5; // INS for setPasword
#define INS_GET_PSSWRD 0xF6; // INS for getPasword

#define INS_SET_DATA   0xF7; // INS for setDataFile
#define P1_OPEN_FILE   0x01; // P1  for setDataFile
#define P1_WRITE_FILE  0x02; // P1  for setDataFile
#define P1_ABORT_FILE  0x03; // P1  for setDataFile
#define P2_COMMIT_FILE 0x01; // P2  for setDataFile

#define INS_GET_DATA    0xF8; // INS for getDataFile
#define P1_RESET_OFFSET 0x01; // P1  for getDataFile


#define INS_GET_VERSION  0x89; // INS for getVersion
#define VER_MAJOR    0x31;
#define VER_MINOR    0x30;
#define VER_REVISION 0x33;

class InstallationDiagnosis {

public:

	typedef struct Apdu
	{
		unsigned char cla;
		unsigned char ins;
		unsigned char p1;
		unsigned char p2;
		unsigned char lc;
		unsigned char data[256];

	} ApduType;

	InstallationDiagnosis();
	virtual ~InstallationDiagnosis();

	static bool TestInstallation ();

private:

	static unsigned char applet_aid[];

	static unsigned char verify_glb_pin_apdu[];
	static unsigned char set_pass_pin_apdu[];
	static unsigned char verify_pass_pin_apdu[];

	static unsigned char key[];
	static unsigned char enc_key[];
	static unsigned char mac_key[];
	static unsigned char kek_key[];

	static void random_fill (unsigned char* buffer, size_t bufLen);
};

#endif /* INSTALLATIONDIAGNOSIS_H_ */
