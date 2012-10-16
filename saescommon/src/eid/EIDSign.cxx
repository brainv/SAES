/**
 * @file EIDSign.cxx
 * @brief Body class eid sign
 * @date 20/07/2011
 * @author Yadickson Soto
 */

#include "EIDSign.hxx"
#include <iostream>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include "pkcs11/cryptoki.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Log;

ISMTTLog* EIDSign::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.EID.EIDSign",GETTEXT_PACKAGE);

bool EIDSign::singPCKS11( Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & dataOut )
{
	CK_RV LastRV = CKR_OK;
	CK_FUNCTION_LIST_PTR p11;

	const char *P11_PATH = "libbeidpkcs11.so";

	void * dllPtr = NULL;
	void (*symPtr)(CK_FUNCTION_LIST_PTR_PTR ppFunctionList) = NULL;

	/* Open the PKCS11 API shared library, and inform the user if there is an
	* error */
	dllPtr = dlopen(P11_PATH, RTLD_NOW);
	if (!dllPtr)
	{
		logger->Debug("Library libbeidpkcs11.so not found.");
		return false;
	}
	/* Get the list of the PKCS11 functions this token supports */
	symPtr = (void (*)(CK_FUNCTION_LIST_PTR_PTR ppFunctionList))dlsym(dllPtr, "C_GetFunctionList");
	if (!symPtr)
	{
		logger->Debug("Error getting function list.");
		return false;
	}
	symPtr(&p11);

	//Initialize PKCS#11
	LastRV=p11->C_Initialize(NULL);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_Initialize failed.");
		return false;
	}

	//Get the list of reader with card (we are only interested with the first one)
	CK_SLOT_ID p11_slot=0;
	CK_ULONG p11_num_slots=1;
	LastRV=p11->C_GetSlotList(TRUE, &p11_slot, &p11_num_slots);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_GetSlotList failed.");
		return false;
	}

	//Open the P11 session
	CK_SESSION_HANDLE p11_session = CK_INVALID_HANDLE;
	LastRV=p11->C_OpenSession(p11_slot,CKF_SERIAL_SESSION | CKF_RW_SESSION,NULL, NULL, &p11_session);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_OpenSession failed.");
		return false;
	}

	//Find the signature private key
	CK_ATTRIBUTE attrs[2];
	CK_OBJECT_CLASS cls = CKO_PRIVATE_KEY;
	CK_ULONG id=3;
	CK_OBJECT_HANDLE signaturekey=CK_INVALID_HANDLE;
	CK_ULONG count;

	attrs[0].type = CKA_CLASS;
	attrs[0].pValue = &cls;
	attrs[0].ulValueLen = sizeof(cls);
	attrs[1].type = CKA_ID;
	attrs[1].pValue = &id;
	attrs[1].ulValueLen = sizeof(id);

	LastRV=p11->C_FindObjectsInit(p11_session,attrs,2);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_FindObjectsInit failed.");
		return false;
	}

	LastRV=p11->C_FindObjects(p11_session, &signaturekey, 1, &count);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_FindObjects failed.");
		return false;
	}

	if(count==0)
	{
		logger->Debug("Signature key not found.");
		return false;
	}

	LastRV=p11->C_FindObjectsFinal(p11_session);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_FindObjectsFinal failed.");
		return false;
	}

	//Initialize the signature
	CK_MECHANISM	mech;
	mech.mechanism=CKM_SHA1_RSA_PKCS;
	mech.pParameter=NULL;
	mech.ulParameterLen=0;
	LastRV=p11->C_SignInit(p11_session, &mech, signaturekey);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_SignInit failed.");
		return false;
	}

	//Open the data to sign
	unsigned char signature[1024];
	CK_ULONG sig_len = sizeof(signature);
	unsigned char *data = (unsigned char*)dataIn.GetData();
	CK_ULONG data_len = dataIn.GetSize();

	//Sign the data
	LastRV=p11->C_Sign(p11_session, data, data_len, signature, &sig_len);
	delete(data);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_Sign failed.");
		return false;
	}

	//Close the session
	LastRV=p11->C_CloseSession(p11_session);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_CloseSession failed.");
		return false;
	}

	//Finalize PKCS#11
	LastRV=p11->C_Finalize(NULL);

	if(LastRV != CKR_OK)
	{
		logger->Debug("C_Finalize failed.");
		return false;
	}

	dataOut.AddData(signature, sig_len);

	if (dllPtr)
	{
		dlclose(dllPtr);
	}

	return true;
}
