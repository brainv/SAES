/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CryptoTest
 * Copyright (C)  2011 <>
 * 
 * CryptoTest is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CryptoTest is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CertificateValidationController.h"
#include <iostream>


using namespace Gtk;
using namespace Smartmatic::System::Security::Cryptography;

CertificateValidationController::CertificateValidationController()
{
	window = NULL;
	fixedContainer = NULL;
	comboPurpose = NULL;
	buttonValidate = NULL;
	entryTime = NULL;
	certificateToValidate = NULL;
	intermediateCA = NULL;
	trustedCertificate = NULL;
	RootCA = NULL;
	checkbuttonIgnoreCritical = NULL;
	checkbuttonCBIssuerCheck = NULL;
	checkbuttonCRLCheck = NULL;
	checkbuttonCRLCheckAll = NULL;
	checkbuttonPolicyCheck = NULL;
	checkbuttonExplicitPolicy = NULL;
	checkbuttonInhibitAny = NULL;
	checkbuttonX509Strict = NULL;
	checkbuttonExtendedCRLSupport = NULL;
	checkbuttonUseDeltas = NULL;
	checkbuttonNotifyPolicy = NULL;
	checkbuttonCheckSSSignature = NULL;
	checkbuttonInhibitMap = NULL;
	checkbuttonNoValidate = NULL;
	checkbuttonCheckTime = NULL;
	checkbuttonAllowProxyCert = NULL;
}

CertificateValidationController::~CertificateValidationController()
{
  // TODO Auto-generated destructor stub
  if(fixedContainer)
    delete(fixedContainer);
  if(comboPurpose)
    delete(comboPurpose);
  if(buttonValidate)
    delete(buttonValidate);
  if(certificateToValidate)
    delete(certificateToValidate);
  if(intermediateCA)
    delete(intermediateCA);
  if(trustedCertificate)
    delete(trustedCertificate);

  if(checkbuttonIgnoreCritical)
    delete(checkbuttonIgnoreCritical);
  if(checkbuttonCBIssuerCheck)
    delete(checkbuttonCBIssuerCheck);
  if(checkbuttonCRLCheck)
    delete(checkbuttonCRLCheck);
  if(checkbuttonCRLCheckAll)
    delete(checkbuttonCRLCheckAll);
  if(checkbuttonPolicyCheck)
    delete(checkbuttonPolicyCheck);
  if(checkbuttonExplicitPolicy)
    delete(checkbuttonExplicitPolicy);
  if(checkbuttonInhibitAny)
    delete(checkbuttonInhibitAny);
  if(checkbuttonX509Strict)
    delete(checkbuttonX509Strict);
  if(checkbuttonExtendedCRLSupport)
    delete(checkbuttonExtendedCRLSupport);
  if(checkbuttonUseDeltas)
    delete(checkbuttonUseDeltas);
  if(checkbuttonNotifyPolicy)
    delete(checkbuttonNotifyPolicy);
  if(checkbuttonCheckSSSignature)
    delete(checkbuttonCheckSSSignature);
  if(checkbuttonInhibitMap)
    delete(checkbuttonInhibitMap);


  if(entryTime)
    delete entryTime;
  if(RootCA)
    delete RootCA;

  if(checkbuttonNoValidate)
    delete checkbuttonNoValidate;
  if(checkbuttonCheckTime)
    delete checkbuttonCheckTime;
  if(checkbuttonAllowProxyCert)
    delete checkbuttonAllowProxyCert;
}

void CertificateValidationController::SetWindow(Gtk::Window* parentWindow)
{
	this->window = parentWindow;
}


Gtk::Fixed* CertificateValidationController::GetWidget( Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget("fixedCertificateValidation",this->fixedContainer);

  builder->get_widget("comboboxPurpose",this->comboPurpose);
  builder->get_widget("buttonValidateCert",this->buttonValidate);

  builder->get_widget("checkbuttonIgnoreCritical",this->checkbuttonIgnoreCritical);
  builder->get_widget("checkbuttonCBIssuerCheck",this->checkbuttonCBIssuerCheck);
  builder->get_widget("checkbuttonCRLCheck",this->checkbuttonCRLCheck);
  builder->get_widget("checkbuttonCRLCheckAll",this->checkbuttonCRLCheckAll);
  builder->get_widget("checkbuttonPolicyCheck",this->checkbuttonPolicyCheck);
  builder->get_widget("checkbuttonExplicitPolicy",this->checkbuttonExplicitPolicy);
  builder->get_widget("checkbuttonInhibitAny",this->checkbuttonInhibitAny);
  builder->get_widget("checkbuttonX509Strict",this->checkbuttonX509Strict);
  builder->get_widget("checkbuttonExtendedCRLSupport",this->checkbuttonExtendedCRLSupport);
  builder->get_widget("checkbuttonUseDeltas",this->checkbuttonUseDeltas);
  builder->get_widget("checkbuttonNotifyPolicy",this->checkbuttonNotifyPolicy);
  builder->get_widget("checkbuttonCheckSSSignature",this->checkbuttonCheckSSSignature);
  builder->get_widget("checkbuttonInhibitMap",this->checkbuttonInhibitMap);




  builder->get_widget("checkbuttonDoNotValidate",this->checkbuttonNoValidate);
  builder->get_widget("checkbuttonSetCheckTime",this->checkbuttonCheckTime);
  builder->get_widget("checkbuttonAllowProxyCert",this->checkbuttonAllowProxyCert);
  builder->get_widget("entryTime",entryTime);

  this->fixedContainer->set_visible();


  //Set up combo box
  m_refTreeModelPurpose = Gtk::ListStore::create(m_Columns);

  comboPurpose->set_model(m_refTreeModelPurpose);

  Gtk::TreeModel::Row row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 0;
  row[m_Columns.m_col_name] = "DEFAULT";

  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "SSLCLIENT";


  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "SSLSERVER";

  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "NSSSLSERVER";

  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 4;
  row[m_Columns.m_col_name] = "SMIMESIGN";

  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 5;
  row[m_Columns.m_col_name] = "SMIMEENCRYPT";

  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 6;
  row[m_Columns.m_col_name] = "CRL_SIGN";

  row = *(m_refTreeModelPurpose->append());
  row[m_Columns.m_col_id] = 7;
  row[m_Columns.m_col_name] = "ANY";

  comboPurpose->pack_start(m_Columns.m_col_id);
  comboPurpose->pack_start(m_Columns.m_col_name);
  comboPurpose->set_active(0);

  certificateToValidate= new CertificateFileChooseWidget("Certificate to validate");
  intermediateCA= new CertificateFileChooseWidget("intermediate CA");
  trustedCertificate= new CertificateFileChooseWidget("trusted Certificate");
  RootCA = new CertificateFileChooseWidget("CA File");

  certificateToValidate->SetWindow(window);
  intermediateCA->SetWindow(window);
  trustedCertificate->SetWindow(window);
  RootCA->SetWindow(window);

  fixedContainer->put(*certificateToValidate,10,5);
  fixedContainer->put(*RootCA,10,105);
  fixedContainer->put(*intermediateCA,10,205);
  fixedContainer->put(*trustedCertificate,10,305);
	
  this->buttonValidate->signal_clicked().connect( sigc::mem_fun(*this,
        &CertificateValidationController::on_btn_Validate_clicked) );
  return fixedContainer;
}

int CertificateValidationController::getPurpose()
{
  int id = 0;
  Gtk::TreeModel::iterator iter = comboPurpose->get_active();
  if(iter)
    {
      TreeModel::Row row = *iter;
      if(row)
        {
          id = row[m_Columns.m_col_id];
        }
    }
  return id;
}

CertificateValidationFlags CertificateValidationController::GetValidationFlags()
{
  int flags = 0;

  if(this->checkbuttonNoValidate->get_active())
    {
      flags |=VERIFY_DO_NOT_VALIDATE;
    }

  if(this->checkbuttonIgnoreCritical->get_active())
    {
      flags |=VERIFY_IGNORE_CRITICAL;
    }
  if(this->checkbuttonCBIssuerCheck->get_active())
    {
      flags |=VERIFY_CB_ISSUER_CHECK;
    }

  if(this->checkbuttonCRLCheck->get_active())
    {
      flags |=VERIFY_CRL_CHECK;
    }
  if(this->checkbuttonCRLCheckAll->get_active())
    {
      flags |=VERIFY_CRL_CHECK_ALL;
    }
  if(this->checkbuttonCRLCheckAll->get_active())
    {
      flags |=VERIFY_CRL_CHECK_ALL;
    }
  if(this->checkbuttonPolicyCheck->get_active())
    {
      flags |=VERIFY_POLICY_CHECK;
    }
  if(this->checkbuttonExplicitPolicy->get_active())
    {
      flags |=VERIFY_EXPLICIT_POLICY;
    }
  if(this->checkbuttonInhibitAny->get_active())
    {
      flags |=VERIFY_INHIBIT_ANY;
    }
  if(this->checkbuttonInhibitMap->get_active())
    {
      flags |=VERIFY_INHIBIT_MAP;
    }
  if(this->checkbuttonX509Strict->get_active())
    {
      flags |=VERIFY_X509_STRICT;
    }

  if(this->checkbuttonExtendedCRLSupport->get_active())
    {
      flags |=VERIFY_EXTENDED_CRL_SUPPORT;
    }

  if(this->checkbuttonUseDeltas->get_active())
    {
      flags |=VERIFY_USE_DELTAS;
    }
  if(this->checkbuttonNotifyPolicy->get_active())
    {
      flags |=VERIFY_NOTIFY_POLICY;
    }
  if(this->checkbuttonCheckSSSignature->get_active())
    {
      flags |=VERIFY_CHECK_SS_SIGNATURE;
    }
  if(this->checkbuttonCheckTime->get_active())
    {
      flags |=VERIFY_SET_CHECK_TIME;
    }
  if(this->checkbuttonAllowProxyCert->get_active())
    {
      flags |=VERIFY_ALLOW_PROXY_CERTS;
    }
  return (CertificateValidationFlags)flags;
}

void CertificateValidationController::on_btn_Validate_clicked()
{
 
  Glib::ustring caFile = RootCA->getFile();
  CertificatePurpose purpose = (CertificatePurpose) this->getPurpose();

  CertificateValidationFlags validationFlags = this->GetValidationFlags();

  Glib::ustring targetFile = certificateToValidate->getFile();
  Glib::ustring targetFilePassword = certificateToValidate->getPassword();
  CertUtil::CertFileFormat targetFormat = (CertUtil::CertFileFormat)certificateToValidate->getSelectedType();


  Glib::ustring unTrustedFile = intermediateCA->getFile();
  Glib::ustring unTrustedFilePassword = intermediateCA->getPassword();
  CertUtil::CertFileFormat unTrustedFormat = (CertUtil::CertFileFormat)intermediateCA->getSelectedType();


  Glib::ustring trustedFile = trustedCertificate->getFile();
  Glib::ustring trustedFilePassword = trustedCertificate->getPassword();
  CertUtil::CertFileFormat trustedFormat = (CertUtil::CertFileFormat)trustedCertificate->getSelectedType();

  CertificateValidator validator;

  Glib::TimeVal time;

  validator.SetOptions(validationFlags);
  if((validationFlags &VERIFY_SET_CHECK_TIME) != 0)
  {
      if(time.assign_from_iso8601(this->entryTime->get_text()) == false)
        {
          time.assign_current_time();
        }
      time_t validationTime = (time_t) time.as_double();
      validator.SetVerificationTime(validationTime);
  }

  validator.SetCACertificate(caFile,CertUtil::CertFormat_PEM);
  if(unTrustedFile.size())
    {
      if(unTrustedFormat != CertUtil::CertFormat_PKCS12)
      {
          validator.SetItermediateCACertificates(unTrustedFile,unTrustedFormat);
      }
      else
        {
          validator.SetItermediateCACertificatesFromPKCS12(unTrustedFile,unTrustedFilePassword);
        }

    }
  if(trustedFile.size())
    {
      if(trustedFormat != CertUtil::CertFormat_PKCS12)
      {
          validator.SetTrustedCertificates(trustedFile,trustedFormat);
      }
      else
        {
          validator.SetTrustedCertificatesFromPKCS12(trustedFile,trustedFilePassword);
        }

    }

  CertValidationResult result;

  if(targetFormat == CertUtil::CertFormat_PKCS12)
    {
      result =validator.VerifyPKCS12Certificate(targetFile,targetFilePassword,purpose);
    }
  else
    {
      result =  validator.VerifyX509Certificate(targetFile,targetFormat,purpose);
    }

  Glib::ustring msg = "Cert Ok: ";

  if(result.GetSucces())
  {
	  msg.append("true\n");
  }
  else
  {
	  msg.append("false\n");
  }

  msg.append( Glib::ustring::compose("Depth: %1\n", result.GetDepth()) );
  msg.append( Glib::ustring::compose("Detail: %1\n", GetMessage(result.GetDetail())) );

  std::cout << msg << std::endl;

  Gtk::MessageDialog dialog(*window, "Verify Result");
                 dialog.set_secondary_text(msg);
                 dialog.run();



}

Glib::ustring CertificateValidationController::GetMessage(TrustResultEnum verifyResult)
{
	Glib::ustring msg;
	switch(verifyResult)
	{
	case TRUST_OK:
		msg = "Certificate is trusted";
		break;
	case  TRUST_CANNOT_READ_TARGET:
		msg = "Cannot read target";
		break;

	case TRUST_INVALID_DATE:
		msg = "TRUST_INVALID_DATE";
		break;
	case TRUST_CANNOT_CREATE_STORE:
		msg = "TRUST_CANNOT_CREATE_STORE";
		break;
	case TRUST_CANNOT_READ_INTERMEDIATE_CA_CERTS:
		msg = "TRUST_CANNOT_READ_INTERMEDIATE_CA_CERTS";
		break;
	case TRUST_CANNOT_READ_TRUSTED_CERTS:
		msg = "TRUST_CANNOT_READ_TRUSTED_CERTS";
		break;
	case TRUST_ERR_UNABLE_TO_GET_CRL:
		msg = "TRUST_ERR_UNABLE_TO_GET_CRL";
		break;
	case  TRUST_UNABLE_TO_GET_ISSUER_CERT:
		msg = "TRUST_CANNOT_READ_TRUSTED_CERTS";
		break;
	case  TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
		msg = "TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE";
		break;
	case  TRUST_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
		msg = "TRUST_UNABLE_TO_DECRYPT_CRL_SIGNATURE";
		break;
	case  TRUST_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
		msg = "TRUST_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY";
		break;
	case  TRUST_CERT_SIGNATURE_FAILURE:
		msg = "TRUST_CERT_SIGNATURE_FAILURE";
		break;
	case  TRUST_CRL_SIGNATURE_FAILURE:
		msg = "TRUST_CRL_SIGNATURE_FAILURE";
		break;
	case  TRUST_CERT_NOT_YET_VALID:
		msg = "TRUST_CERT_NOT_YET_VALID";
		break;
	case  TRUST_CRL_NOT_YET_VALID:
		msg = "TRUST_CRL_NOT_YET_VALID";
		break;
	case  TRUST_CERT_HAS_EXPIRED:
		msg = "TRUST_CERT_HAS_EXPIRED";
		break;
	case  TRUST_ERR_CRL_HAS_EXPIRED:
		msg = "TRUST_ERR_CRL_HAS_EXPIRED";
		break;
	case  TRUST_ERROR_IN_CERT_NOT_BEFORE_FIELD:
		msg = "TRUST_ERROR_IN_CERT_NOT_BEFORE_FIELD";
		break;
	case  TRUST_ERROR_IN_CERT_NOT_AFTER_FIELD:
		msg = "TRUST_ERROR_IN_CERT_NOT_AFTER_FIELD";
		break;
	case  TRUST_ERROR_IN_CRL_LAST_UPDATE_FIELD:
		msg = "TRUST_ERROR_IN_CRL_LAST_UPDATE_FIELD";
		break;
	case  TRUST_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
		msg = "TRUST_ERROR_IN_CRL_NEXT_UPDATE_FIELD";
		break;
	case  TRUST_OUT_OF_MEM:
		msg = "TRUST_OUT_OF_MEM";
		break;
	case  TRUST_DEPTH_ZERO_SELF_SIGNED_CERT:
		msg = "TRUST_DEPTH_ZERO_SELF_SIGNED_CERT";
		break;
	case  TRUST_SELF_SIGNED_CERT_IN_CHAIN:
		msg = "TRUST_SELF_SIGNED_CERT_IN_CHAIN";
		break;
	case  TRUST_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
		msg = "TRUST_UNABLE_TO_GET_ISSUER_CERT_LOCALLY";
		break;
	case TRUST_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
		msg = "TRUST_UNABLE_TO_VERIFY_LEAF_SIGNATURE";
		break;
	case  TRUST_CERT_CHAIN_TOO_LONG:
		msg="TRUST_CERT_CHAIN_TOO_LONG";
		break;
	case        TRUST_ERR_CERT_REVOKED:
		msg="TRUST_ERR_CERT_REVOKED";
		break;
	case        TRUST_ERR_INVALID_CA:
		msg="TRUST_ERR_INVALID_CA";
		break;

	case        TRUST_INVALID_NON_CA:
		msg="TRUST_INVALID_NON_CA";
		break;
	case            TRUST_ERR_PATH_LENGTH_EXCEEDED:
		msg="TRUST_ERR_PATH_LENGTH_EXCEEDED";
		break;
	case        TRUST_ERR_PROXY_PATH_LENGTH_EXCEEDED:
		msg="TRUST_ERR_PROXY_PATH_LENGTH_EXCEEDED";
		break;
	case        TRUST_ERR_PROXY_CERTIFICATES_NOT_ALLOWED:
		msg="TRUST_ERR_PROXY_CERTIFICATES_NOT_ALLOWED";
		break;
	case        TRUST_ERR_INVALID_PURPOSE:
		msg="TRUST_ERR_INVALID_PURPOSE";
				break;
	case        TRUST_ERR_CERT_UNTRUSTED:
		msg="TRUST_ERR_CERT_UNTRUSTED";
				break;
	case        TRUST_ERR_CERT_REJECTED:
		msg = "TRUST_ERR_CERT_REJECTED";
		break;
	case        TRUST_ERR_APPLICATION_VERIFICATION:
		msg="TRUST_ERR_APPLICATION_VERIFICATION";
						break;
	case        TRUST_ERR_SUBJECT_ISSUER_MISMATCH:
		msg="TRUST_ERR_SUBJECT_ISSUER_MISMATCH";
						break;
	case        TRUST_ERR_AKID_SKID_MISMATCH:
		msg="TRUST_ERR_AKID_SKID_MISMATCH";
						break;
	case        TRUST_ERR_AKID_ISSUER_SERIAL_MISMATCH:
		msg="TRUST_ERR_AKID_ISSUER_SERIAL_MISMATCH";
						break;
	case        TRUST_ERR_KEYUSAGE_NO_CERTSIGN:
		msg="TRUST_ERR_KEYUSAGE_NO_CERTSIGN";
						break;
	case        TRUST_ERR_UNABLE_TO_GET_CRL_ISSUER:
		msg="TRUST_ERR_UNABLE_TO_GET_CRL_ISSUER";
						break;
	case        TRUST_ERR_UNHANDLED_CRITICAL_EXTENSION:
		msg="TRUST_ERR_UNHANDLED_CRITICAL_EXTENSION";
						break;
	case        TRUST_ERR_KEYUSAGE_NO_CRL_SIGN:
		msg="TRUST_ERR_KEYUSAGE_NO_CRL_SIGN";
						break;
	case        TRUST_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE:
		msg="TRUST_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE";
						break;
	case        TRUST_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION:
		msg="TRUST_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION";
						break;
	case        TRUST_ERR_INVALID_EXTENSION:
		msg="TRUST_ERR_INVALID_EXTENSION";
						break;
	case        TRUST_ERR_INVALID_POLICY_EXTENSION:
		msg="TRUST_ERR_INVALID_POLICY_EXTENSION";
						break;
	case        TRUST_ERR_NO_EXPLICIT_POLICY:
		msg="TRUST_ERR_NO_EXPLICIT_POLICY";
						break;
	case        TRUST_ERR_DIFFERENT_CRL_SCOPE:
		msg="TRUST_ERR_DIFFERENT_CRL_SCOPE";
						break;
	case        TRUST_ERR_UNSUPPORTED_EXTENSION_FEATURE:
		msg="TRUST_ERR_UNSUPPORTED_EXTENSION_FEATURE";
						break;
	case        TRUST_ERR_UNNESTED_RESOURCE:
		msg="TRUST_ERR_UNNESTED_RESOURCE";
						break;
	case        TRUST_ERR_PERMITTED_VIOLATION:
		msg="TRUST_ERR_PERMITTED_VIOLATION";
						break;
	case        TRUST_ERR_EXCLUDED_VIOLATION:
		msg="TRUST_ERR_EXCLUDED_VIOLATION";
						break;
	case        TRUST_ERR_SUBTREE_MINMAX:
		msg="TRUST_ERR_SUBTREE_MINMAX";
						break;
	case        TRUST_ERR_UNSUPPORTED_CONSTRAINT_TYPE:
		msg="TRUST_ERR_UNSUPPORTED_CONSTRAINT_TYPE";
						break;
	case        TRUST_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX:
		msg="TRUST_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX";
						break;
	case        TRUST_ERR_UNSUPPORTED_NAME_SYNTAX:
		msg="TRUST_ERR_UNSUPPORTED_NAME_SYNTAX";
						break;
	case        TRUST_ERR_CRL_PATH_VALIDATION_ERROR:
		msg="TRUST_ERR_CRL_PATH_VALIDATION_ERROR";
						break;
	default:
		msg = Glib::ustring::compose("%1", verifyResult);
		break;
	}

	return msg;
/*
	  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:

	    error= TRUST_UNABLE_TO_GET_ISSUER_CERT;
	    std::cout <<"unable to get issuer certificate"<<std::endl;
	    break;
	  case X509_V_ERR_UNABLE_TO_GET_CRL:

	    error= TRUST_ERR_UNABLE_TO_GET_CRL;
	    break;
	  case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
	    error= TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE;
	    std::cout <<"unable to decrypt certificate's signature"<<std::endl;
	    break;
	  case X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
	    std::cout <<"unable to decrypt CRL's signature"<<std::endl;
	    error=TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE;
	    break;
	  case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
	    std::cout <<"unable to decode issuer public key"<<std::endl;
	    error=TRUST_UNABLE_TO_DECRYPT_CRL_SIGNATURE;
	    break;
	  case X509_V_ERR_CERT_SIGNATURE_FAILURE:
	    std::cout <<"certificate signature failure"<<std::endl;
	    error=TRUST_CERT_SIGNATURE_FAILURE;
	    break;
	  case X509_V_ERR_CRL_SIGNATURE_FAILURE:
	    std::cout <<"CRL signature failure"<<std::endl;
	    error=TRUST_CERT_SIGNATURE_FAILURE;
	    break;
	  case X509_V_ERR_CERT_NOT_YET_VALID:
	    std::cout <<"certificate is not yet valid"<<std::endl;
	    error=TRUST_CERT_NOT_YET_VALID;
	    break;
	  case X509_V_ERR_CRL_NOT_YET_VALID:
	    std::cout <<"CRL is not yet valid"<<std::endl;
	    error=TRUST_CRL_NOT_YET_VALID;
	    break;
	  case X509_V_ERR_CERT_HAS_EXPIRED:
	    std::cout <<"certificate has expired"<<std::endl;
	    error=TRUST_CERT_HAS_EXPIRED;
	    break;
	  case X509_V_ERR_CRL_HAS_EXPIRED:
	    std::cout <<"CRL has expired"<<std::endl;
	    error=TRUST_ERR_CRL_HAS_EXPIRED;
	    break;
	  case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
	    std::cout <<"format error in certificate's notBefore field"<<std::endl;
	    error=TRUST_ERROR_IN_CERT_NOT_BEFORE_FIELD;
	    break;
	  case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
	    std::cout <<"format error in certificate's notAfter field"<<std::endl;
	    error=TRUST_ERROR_IN_CERT_NOT_AFTER_FIELD;
	    break;
	  case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
	    std::cout <<"format error in CRL's lastUpdate field"<<std::endl;
	    error=TRUST_ERROR_IN_CRL_LAST_UPDATE_FIELD;
	    break;
	  case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
	    std::cout <<"format error in CRL's nextUpdate field"<<std::endl;
	    error=TRUST_ERROR_IN_CRL_NEXT_UPDATE_FIELD;
	    break;
	  case X509_V_ERR_OUT_OF_MEM:
	    std::cout <<"out of memory"<<std::endl;
	    error=TRUST_OUT_OF_MEM;
	    break;
	  case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
	    std::cout <<"self signed certificate"<<std::endl;
	    error=TRUST_DEPTH_ZERO_SELF_SIGNED_CERT;
	    break;
	  case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
	    std::cout <<"self signed certificate in certificate chain"<<std::endl;
	    error=TRUST_SELF_SIGNED_CERT_IN_CHAIN;
	    break;
	  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
	    std::cout <<"unable to get local issuer certificate"<<std::endl;
	    error=TRUST_UNABLE_TO_GET_ISSUER_CERT_LOCALLY;
	    break;
	  case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
	    std::cout <<"unable to verify the first certificate"<<std::endl;
	    error=TRUST_UNABLE_TO_VERIFY_LEAF_SIGNATURE;
	    break;
	  case X509_V_ERR_CERT_CHAIN_TOO_LONG:
	    std::cout <<"certificate chain too long"<<std::endl;
	    error=TRUST_CERT_CHAIN_TOO_LONG;
	    break;
	  case X509_V_ERR_CERT_REVOKED:
	    std::cout <<"certificate revoked"<<std::endl;
	    error=TRUST_ERR_CERT_REVOKED;
	    break;
	  case X509_V_ERR_INVALID_CA:
	    std::cout <<"invalid CA certificate"<<std::endl;
	    error=TRUST_ERR_INVALID_CA;
	    break;
	  case X509_V_ERR_INVALID_NON_CA:
	    std::cout <<"invalid non-CA certificate (has CA markings)"<<std::endl;
	    error=TRUST_INVALID_NON_CA;
	    break;
	  case X509_V_ERR_PATH_LENGTH_EXCEEDED:
	    std::cout <<"path length constraint exceeded"<<std::endl;
	    error=TRUST_ERR_PATH_LENGTH_EXCEEDED;
	    break;
	  case X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED:
	    std::cout <<"proxy path length constraint exceeded"<<std::endl;
	    error=TRUST_ERR_PROXY_PATH_LENGTH_EXCEEDED;
	    break;
	  case X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED:
	    std::cout <<"proxy certificates not allowed, please set the appropriate flag"<<std::endl;
	    error=TRUST_ERR_PROXY_CERTIFICATES_NOT_ALLOWED;
	    break;
	  case X509_V_ERR_INVALID_PURPOSE:
	    std::cout <<"unsupported certificate purpose"<<std::endl;
	    error=TRUST_ERR_INVALID_PURPOSE;
	    break;
	  case X509_V_ERR_CERT_UNTRUSTED:
	    std::cout <<"certificate not trusted"<<std::endl;
	    error=TRUST_ERR_CERT_UNTRUSTED;
	    break;
	  case X509_V_ERR_CERT_REJECTED:
	    std::cout <<"certificate rejected"<<std::endl;
	    error=TRUST_ERR_CERT_REJECTED;
	    break;
	  case X509_V_ERR_APPLICATION_VERIFICATION:
	    std::cout <<"application verification failure"<<std::endl;
	    error=TRUST_ERR_APPLICATION_VERIFICATION;
	    break;
	  case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
	    std::cout <<"subject issuer mismatch"<<std::endl;
	    error=TRUST_ERR_SUBJECT_ISSUER_MISMATCH;
	    break;
	  case X509_V_ERR_AKID_SKID_MISMATCH:
	    std::cout <<"authority and subject key identifier mismatch"<<std::endl;
	    error=TRUST_ERR_AKID_SKID_MISMATCH;
	    break;
	  case X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH:
	    std::cout <<"authority and issuer serial number mismatch"<<std::endl;
	    error=TRUST_ERR_AKID_ISSUER_SERIAL_MISMATCH;
	    break;
	  case X509_V_ERR_KEYUSAGE_NO_CERTSIGN:
	    std::cout <<"key usage does not include certificate signing"<<std::endl;
	    error=TRUST_ERR_KEYUSAGE_NO_CERTSIGN;
	    break;
	  case X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER:
	    std::cout <<"unable to get CRL issuer certificate"<<std::endl;
	    error=TRUST_ERR_UNABLE_TO_GET_CRL_ISSUER;
	    break;
	  case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
	    std::cout <<"unhandled critical extension"<<std::endl;
	    error=TRUST_ERR_UNHANDLED_CRITICAL_EXTENSION;
	    break;
	  case X509_V_ERR_KEYUSAGE_NO_CRL_SIGN:
	    std::cout <<"key usage does not include CRL signing"<<std::endl;
	    error=TRUST_ERR_KEYUSAGE_NO_CRL_SIGN;
	    break;
	  case X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE:
	    std::cout <<"key usage does not include digital signature"<<std::endl;
	    error=TRUST_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE;
	    break;
	  case X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION:
	    std::cout <<"unhandled critical CRL extension"<<std::endl;
	    error=TRUST_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION;
	    break;
	  case X509_V_ERR_INVALID_EXTENSION:
	    std::cout <<"invalid or inconsistent certificate extension"<<std::endl;
	    error=TRUST_ERR_INVALID_EXTENSION;
	    break;
	  case X509_V_ERR_INVALID_POLICY_EXTENSION:
	    std::cout <<"invalid or inconsistent certificate policy extension"<<std::endl;
	    error=TRUST_ERR_INVALID_POLICY_EXTENSION;
	    break;
	  case X509_V_ERR_NO_EXPLICIT_POLICY:
	    std::cout <<"no explicit policy"<<std::endl;
	    error=TRUST_ERR_NO_EXPLICIT_POLICY;
	    break;
	  case X509_V_ERR_UNNESTED_RESOURCE:
	    error=TRUST_ERR_UNNESTED_RESOURCE;
	    std::cout <<"RFC 3779 resource not subset of parent's resources" <<std::endl;
	    break;

	    
	    // * Values not handled by OpenSSL 0.9.8
	    // * case X509_V_ERR_DIFFERENT_CRL_SCOPE:
	    //return("Different CRL scope");
	    error=TRUST_ERR_DIFFERENT_CRL_SCOPE;
	    break;
	  case X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE:
	    error=TRUST_ERR_UNSUPPORTED_EXTENSION_FEATURE;//return("Unsupported extension feature");
	    break;

	  case X509_V_ERR_PERMITTED_VIOLATION:

	    error=TRUST_ERR_PERMITTED_VIOLATION;//return("excluded subtree violation");
	    break;
	  case X509_V_ERR_EXCLUDED_VIOLATION:

	    error=TRUST_ERR_EXCLUDED_VIOLATION;//return("excluded subtree violation");
	    break;
	  case X509_V_ERR_SUBTREE_MINMAX:

	    error=TRUST_ERR_SUBTREE_MINMAX;//return("name constraints minimum and maximum not supported");
	    break;
	  case X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE:

	    error=TRUST_ERR_UNSUPPORTED_CONSTRAINT_TYPE;    //return("unsupported name constraint type");
	    break;
	  case X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX:

	    error=TRUST_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX;//return("unsupported or invalid name constraint syntax");
	    break;
	  case X509_V_ERR_UNSUPPORTED_NAME_SYNTAX:

	    error=TRUST_ERR_UNSUPPORTED_NAME_SYNTAX; //return("unsupported or invalid name syntax");
	    break;
	  case X509_V_ERR_CRL_PATH_VALIDATION_ERROR:

	    error=TRUST_ERR_CRL_PATH_VALIDATION_ERROR; //return("CRL path validation error");
	    break;*/
}


CertificateFileChooseWidget::CertificateFileChooseWidget(Glib::ustring Title):window(NULL)
{
	labelTitle.set_label(Title);
	labelPass.set_label("Password:");
	buttonSelectFile.set_label("...");

	m_refTreeModelType = Gtk::ListStore::create(m_Columns);

	comboType.set_model(m_refTreeModelType);

	Gtk::TreeModel::Row row = *(m_refTreeModelType->append());
	row[m_Columns.m_col_id] = 1;
	row[m_Columns.m_col_name] = "DER";

	row = *(m_refTreeModelType->append());
	row[m_Columns.m_col_id] = 3;
	row[m_Columns.m_col_name] = "PEM";

	row = *(m_refTreeModelType->append());
	row[m_Columns.m_col_id] = 5;
	row[m_Columns.m_col_name] = "PKCS12";

	comboType.pack_start(m_Columns.m_col_id);
	comboType.pack_start(m_Columns.m_col_name);
	comboType.set_active(0);

	comboType.set_size_request (140,35);
	entryFile.set_size_request (400,35);
	buttonSelectFile.set_size_request (50,35);
	hboxPrincipal.pack_start(comboType,Gtk::PACK_SHRINK);
	hboxPrincipal.pack_start(entryFile,Gtk::PACK_SHRINK);
	hboxPrincipal.pack_start(buttonSelectFile,Gtk::PACK_SHRINK);
	hboxPrincipal.show_all_children ();

	labelPass.set_size_request (140,35);
	entryPass.set_size_request (400,35);
	entryPass.set_sensitive (false);
	hboxPassword.pack_start(labelPass,Gtk::PACK_SHRINK);
	hboxPassword.pack_start(entryPass,Gtk::PACK_SHRINK);
	hboxPassword.show_all_children ();

	pack_start(labelTitle,Gtk::PACK_SHRINK);
	pack_start(hboxPrincipal,Gtk::PACK_SHRINK);
	pack_start(hboxPassword,Gtk::PACK_SHRINK);
	show_all_children();
	set_visible(true);
	
	this->buttonSelectFile.signal_clicked().connect( sigc::mem_fun(*this,
      &CertificateFileChooseWidget::on_btn_SelectFile_clicked) );

	this->comboType.signal_changed().connect(sigc::mem_fun(*this, &CertificateFileChooseWidget::on_combo_changed));
}


void CertificateFileChooseWidget::on_combo_changed()
{
	int id = 0;
	TreeModel::iterator iter = comboType.get_active();
	if(iter)
	{
		TreeModel::Row row = *iter;
		if(row)
		{
			id = row[m_Columns.m_col_id];
			if(id==5)
			{
				entryPass.set_sensitive (true);
			}
			else
			{
				entryPass.set_sensitive (false);
			}
		}
	}
}

int CertificateFileChooseWidget::getSelectedType()
{
	int id = 0;
	Gtk::TreeModel::iterator iter = comboType.get_active();
	if(iter)
	{
		TreeModel::Row row = *iter;
		if(row)
		{
			id = row[m_Columns.m_col_id];
		}
	}
	return id;
}

Glib::ustring CertificateFileChooseWidget::getPassword()
{
	return entryPass.get_text ();
}

Glib::ustring CertificateFileChooseWidget::getFile()
{
	return entryFile.get_text ();
}

CertificateFileChooseWidget::~CertificateFileChooseWidget()
{
}

void CertificateFileChooseWidget::SetWindow(Gtk::Window* parentWindow)
{
	 this->window = parentWindow;
}

void CertificateFileChooseWidget::on_btn_SelectFile_clicked()
{
  Gtk::FileChooserDialog dialog("Please choose a file",
      Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*window);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

//  Gtk::FileFilter filter_xml;
  //filter_xml.set_name("Xml files");
  //filter_xml.add_mime_type("text/xml");
  //dialog.add_filter(filter_xml);


  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
  case(Gtk::RESPONSE_OK):
                  {
    Glib::ustring filename = dialog.get_filename();
    this->entryFile.set_text(filename);
    break;
                  }
  case(Gtk::RESPONSE_CANCEL):
                  {
    std::cout << "Cancel clicked." << std::endl;
    break;
                  }
  default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }

}


