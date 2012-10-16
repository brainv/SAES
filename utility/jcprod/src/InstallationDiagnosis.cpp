/*
 * InstallationDiagnosis.cpp
 *
 *  Created on: Oct 3, 2011
 *      Author: Marcel Cordoví
 */

#include <fstream>
#include <string.h>
#include <iostream>
#include "GpCommandWrapper.h"
#include "InstallationDiagnosis.h"

#define APDU_HEAD_LEN 5
#define READ_HEAD_LEN 2
#define SW_LEN 2

#define MAKE_SHORT(x,y) ( ( x ) << 8 ) | ( y )

#define APPLET_AID {0xF0, 0x00, 0x00, 0x00, 0x62, 0x03, 0x01, 0x0C, 0x01, 0x01}

#define VERIFY_GLB_PIN {0x80, 0xF1, 0x00, 0x00, 0x08, 0x33, 0x33, 0x72, 0x63, 0x14, 0x15, 0x56, 0x97, 0x01}
#define SET_PASS_PIN   {0x80, 0xF3, 0x00, 0x00, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}
#define VERIFY_PASS_PIN {0x80, 0xF2, 0x00, 0x00, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x01}

#define KEY      {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}
#define KEK_KEY  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}
#define ENC_KEY  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}
#define MAC_KEY  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f}

#define TRACE(x) std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": " << ( x ) << std::endl;

unsigned char InstallationDiagnosis::applet_aid[] = APPLET_AID;
unsigned char InstallationDiagnosis::verify_glb_pin_apdu[] = VERIFY_GLB_PIN;
unsigned char InstallationDiagnosis::set_pass_pin_apdu[] = SET_PASS_PIN;
unsigned char InstallationDiagnosis::verify_pass_pin_apdu[] = VERIFY_PASS_PIN;

unsigned char InstallationDiagnosis::key[] = KEY;
unsigned char InstallationDiagnosis::enc_key[] = ENC_KEY;
unsigned char InstallationDiagnosis::mac_key[] = MAC_KEY;
unsigned char InstallationDiagnosis::kek_key[] = KEK_KEY;


InstallationDiagnosis::InstallationDiagnosis()
{
	// TODO Auto-generated constructor stub
}

InstallationDiagnosis::~InstallationDiagnosis()
{
	// TODO Auto-generated destructor stub
}

void InstallationDiagnosis::random_fill (unsigned char* buffer, size_t bufLen)
{
	std::ifstream ifs_random;
	ifs_random.open ("/dev/urandom");
	ifs_random.read ((char*)buffer, bufLen);
	ifs_random.close ();
}

bool InstallationDiagnosis::TestInstallation ()
{
	GpCommandWrapper cmd;
	ApduType data_apdu;
	bool success = false;
	unsigned int offset = 0;
	short bytes_left = 0;
	unsigned long res_len;
	unsigned char data[1024];
	unsigned char rcv_data[1024];
	unsigned char data_apdu_buff[sizeof (ApduType)];
	unsigned char response_apdu[260];

	memset (data_apdu.data, 0, sizeof (data_apdu.data));
	memset (response_apdu, 0, sizeof (response_apdu));

	random_fill (data, sizeof (data));

	try
	{
		cmd.mGpEstablishContext();
		cmd.mGpCardConnect();
		cmd.mGpSelect (applet_aid, sizeof (applet_aid));

		cmd.mOpenSecureChannel (
						  GP211_SCP02            // scp
						, GP211_SCP01_IMPL_i15   // scpImpl
						, key
						, enc_key
						, mac_key
						, kek_key
						, 0                      // keySetVersion
						, 0                      // keyIndex
						, GP211_SCP02_SECURITY_LEVEL_C_DEC_C_MAC // securityLevel
						, OPGP_DERIVATION_METHOD_NONE            // keyDerivation
		);

		cmd.mGpSendAPDU(verify_glb_pin_apdu, sizeof (verify_glb_pin_apdu), NULL, res_len);
		cmd.mGpSendAPDU(set_pass_pin_apdu, sizeof (set_pass_pin_apdu), NULL, res_len);
		cmd.mGpSendAPDU(verify_pass_pin_apdu, sizeof (verify_pass_pin_apdu), NULL, res_len);

		// open

		data_apdu.cla = APLT_CLA;
		data_apdu.ins = INS_SET_DATA;
		data_apdu.p1 = P1_OPEN_FILE;
		data_apdu.p2 = 0x00;
		data_apdu.lc = 0x00;

		memcpy (data_apdu_buff, &data_apdu, APDU_HEAD_LEN);
		cmd.mGpSendAPDU (data_apdu_buff, APDU_HEAD_LEN, NULL, res_len);

		// write

		data_apdu.p1 = P1_WRITE_FILE;
		data_apdu.lc = 0x80;

		while (offset < sizeof (data))
		{
			memcpy (data_apdu.data, data + offset, data_apdu.lc);
			offset += data_apdu.lc;

			if (offset >= sizeof (data))
				data_apdu.p2 = 0x01; // write last block and close

			memcpy (data_apdu_buff, &data_apdu, sizeof (ApduType));

			cmd.mGpSendAPDU (data_apdu_buff, (APDU_HEAD_LEN + data_apdu.lc), NULL, res_len);

			// Enviar un comando con data más larga de lo que indica el cl ocaciones errores del tipo:
			// A APDU command can't be recognized as a valid T=0 protocol Case 1-4 ISO7816-4 APDU
			// cuando se usa canal seguro con nivel 3 de seguridad.
		}

		// read

		data_apdu.ins = INS_GET_DATA;
		data_apdu.p1 = P1_RESET_OFFSET;
		data_apdu.p2 = 0x00;
		data_apdu.lc = 0xFF;

		memcpy (data_apdu_buff, &data_apdu, APDU_HEAD_LEN);

		offset = 0;
		bytes_left = sizeof (rcv_data);

		while ( bytes_left > 2 )
		{
			cmd.mGpSendAPDU (data_apdu_buff, APDU_HEAD_LEN, response_apdu, res_len);

			res_len -= READ_HEAD_LEN + SW_LEN;

			memcpy (rcv_data + offset, response_apdu + 2, res_len);

			bytes_left = MAKE_SHORT (response_apdu[0], response_apdu[1]);
			offset += res_len;

			data_apdu.p1 = 0x00;
			data_apdu.lc = bytes_left > 0xFF ? 0xFF : bytes_left + READ_HEAD_LEN;
			memcpy (data_apdu_buff, &data_apdu, APDU_HEAD_LEN);
		}

		// clear the data file

		data_apdu.ins = INS_SET_DATA;
		data_apdu.p1 = P1_OPEN_FILE;
		data_apdu.p2 = P2_COMMIT_FILE;
		data_apdu.lc = 0x00;

		memcpy (data_apdu_buff, &data_apdu, APDU_HEAD_LEN);
		cmd.mGpSendAPDU (data_apdu_buff, APDU_HEAD_LEN, NULL, res_len);

		cmd.mGpDisconnect();
		cmd.mGpReleaseContext();

		success = memcmp ((void *)rcv_data, (void *)data, sizeof (data)) == 0;
	}
	catch (GpCommandException& e)
	{
		success = false;
	}

	// TODO clear random data in the card

	return success;
}
