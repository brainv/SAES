/**
 * @file CertificateValidator.cpp
 * @brief Body class certificate validator
 * @date 07/04/2011
 * @author Freddy Gomez
 */

#include "System/Security/Cryptography/CertificateValidator.h"
#include "System/Security/Cryptography/CryptoPKCS12.hxx"

#include <stdio.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/safestack.h>
#include <Log/SMTTLogManager.h>
#include <System/Security/Cryptography/CertUtil.h>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::System::Security::Cryptography;

/*Open ssl prototypes*/
typedef struct pw_cb_data
{
  const void *password;
  const char *prompt_info;
} PW_CB_DATA;

static STACK_OF(X509) * GetCertificateStacks(Glib::ustring& certPath, CertUtil::CertFileFormat format, Glib::ustring& password,CryptoPKCS12* pkcs12Obj );

//X509 *load_cert(const char *file, CertFileFormat format, const char *pass, ENGINE *e, const char *cert_descrip);
int password_callback(char *buf, int bufsiz, int verify,PW_CB_DATA *cb_tmp);
static int cb(int ok, X509_STORE_CTX *ctx);
int initVerify();
void policies_print(BIO *out, X509_STORE_CTX *ctx);
static void nodes_print(BIO *out, const char *name,
    STACK_OF(X509_POLICY_NODE) *nodes);
static int load_certs_crls(BIO *err, const char *file, CertUtil::CertFileFormat format,
    const char *pass, ENGINE *e, const char *desc,
    STACK_OF(X509) **pcerts, STACK_OF(X509_CRL) **pcrls);

static int check(X509_STORE *ctx, X509* target,
    STACK_OF(X509) *uchain, STACK_OF(X509) *tchain,
    STACK_OF(X509_CRL) *crls, ENGINE *e,TrustResultEnum& error, int& depth);

X509_STORE * CreateAndConfigureStore(X509_VERIFY_PARAM *vpm );

X509_VERIFY_PARAM * CreateAndInitializeParameters(CertificateValidationFlags flags, CertificatePurpose purpose, time_t checkTime);

void LookupCA(X509_STORE * cert_ctx, Glib::ustring path, CertUtil::CertFileFormat format);

CertValidationResult::CertValidationResult()
{
  this->depth = 0;
   this->detail = TRUST_OK;
}
CertValidationResult::CertValidationResult(CertValidationResult& x)
{
  this->depth = x.depth;
    this->detail = x.detail;
}

CertValidationResult::CertValidationResult(int depthA, TrustResultEnum detailA)
{
  this->depth = depthA;
  this->detail = detailA;
}
CertValidationResult::~CertValidationResult()
{

}
bool CertValidationResult::GetSucces()
{
  return this->detail == TRUST_OK;
}

TrustResultEnum CertValidationResult::GetDetail()
{
  return this->detail;
}

void CertValidationResult::SetDetail(TrustResultEnum val)
{
  this->detail = val;
}
int CertValidationResult::GetDepth()
{

  return this->depth;
}
void CertValidationResult::SetDepth(int newDepth)
{
  this->depth = newDepth;
}

ISMTTLog* CertificateValidator::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.CertificateValidator",GETTEXT_PACKAGE);


CertificateValidator::CertificateValidator()
{
  // TODO Auto-generated constructor stub
  usingIntermediateCA = false;
  usingTrustedCert = false;
  validationFlags = VERIFY_NO_FLAGS;
}

CertificateValidator::~CertificateValidator()
{
  // TODO Auto-generated destructor stub
}

void CertificateValidator::SetOptions(CertificateValidationFlags flags)
{
  validationFlags = (CertificateValidationFlags)(validationFlags |flags);
}

void CertificateValidator::ClearOptions(CertificateValidationFlags flags)
{
  validationFlags = (CertificateValidationFlags)(validationFlags& (~flags));
}


void CertificateValidator::SetVerificationTime(time_t time)
{
  checkTime = time;
}

void CertificateValidator::ClearVerificationTime()
{
  validationFlags = (CertificateValidationFlags) (validationFlags & (~VERIFY_SET_CHECK_TIME));
}


//This would be the Root CA
void CertificateValidator::SetCACertificate(Glib::ustring certPath, CertUtil::CertFileFormat format)
{
  certAuthorityPath = certPath;
  certAuthorityFormat = format;

}

//These would be the certs in the chain, untrusted cert for open ssl
void CertificateValidator::SetItermediateCACertificates(Glib::ustring certPath, CertUtil::CertFileFormat format)
{
  usingIntermediateCA = true;
  intermediateCAFormat = format;
  intermediateCAPath = certPath;

}
void CertificateValidator::SetItermediateCACertificatesFromPKCS12(Glib::ustring certPath, Glib::ustring password)
{
  usingIntermediateCA = true;
  intermediateCAFormat = CertUtil::CertFormat_PKCS12;
  intermediateCAPath = certPath;
  intermediateCAFilePassword = password;
}

//These would be the others trusted cert
void CertificateValidator::SetTrustedCertificates(Glib::ustring certPath, CertUtil::CertFileFormat format)
{
  usingTrustedCert = true;
  trustedCertFormat = format;
  trustedCertPath = certPath;

}
void CertificateValidator::SetTrustedCertificatesFromPKCS12(Glib::ustring certPath, Glib::ustring password)
{
  usingTrustedCert = true;
  trustedCertFormat = CertUtil::CertFormat_PKCS12;
  trustedCertPath = certPath;
  trustedCertFilePassword = password;
}

CertValidationResult CertificateValidator::VerifyX509Certificate(Glib::ustring certPath,CertUtil::CertFileFormat format, CertificatePurpose purpose )
{
  CertValidationResult retVal(0,TRUST_OK);
  initVerify();
  //Get certificate to validate
  X509 *x=NULL;

  x = CertUtil::LoadCertificate(certPath, format);
  if(x == NULL)
    {
      retVal.SetDetail(TRUST_CANNOT_READ_TARGET);
    }
  else
    {
      retVal = VerifyX509Certificate(x, purpose);
    }
  if (x != NULL)
    X509_free(x);

  return retVal;
}


CertValidationResult CertificateValidator::VerifyX509Certificate(OpenSSLCryptoX509 * cert, CertificatePurpose purpose )
{
  CertValidationResult retVal(0,TRUST_OK);
  initVerify();
  retVal = VerifyX509Certificate(cert->getOpenSSLX509(), purpose);
  return retVal;
}

CertValidationResult CertificateValidator::VerifyPKCS12Certificate(Glib::ustring certPath,Glib::ustring password,  CertificatePurpose purpose )
{
  CertValidationResult retVal(0,TRUST_OK);
  initVerify();
  try
  {
      std::string path = certPath;
      std::string pass = password;

      CryptoPKCS12 pkcs12 (path, pass);

      retVal = VerifyX509Certificate(pkcs12.getCertified(), purpose);
  }
  catch(...)
  {
      retVal.SetDetail(TRUST_CANNOT_READ_TARGET);
  }
  return retVal;
}

CertValidationResult CertificateValidator::VerifyX509Certificate(X509 * cert, CertificatePurpose purpose )
{
  CertValidationResult retVal(0,TRUST_OK);
    STACK_OF(X509) *untrusted = NULL, *trusted = NULL;
    X509_STORE *cert_ctx=NULL;
    X509_VERIFY_PARAM * vp = NULL;
    X509 *x=NULL;
    bool loaderr = false;
    TrustResultEnum detail =TRUST_OK ;
    int depth = 0;

    if((this->validationFlags &  VERIFY_DO_NOT_VALIDATE) != 0)
      return retVal;
    try
    {

        x = cert;
        CryptoPKCS12 untrustedPKCS12;
        CryptoPKCS12 trustedPKCS12;

        vp = CreateAndInitializeParameters(validationFlags, purpose, checkTime);
        cert_ctx= CreateAndConfigureStore(vp);

        if(cert_ctx != NULL)
          {
            //Load the CA
            LookupCA(cert_ctx,this->certAuthorityPath,this->certAuthorityFormat);

            if(usingIntermediateCA)
            {
                untrusted = GetCertificateStacks(this->intermediateCAPath, this->intermediateCAFormat, this->intermediateCAFilePassword,&untrustedPKCS12 );
                if(untrusted == NULL)
                  {
                    loaderr = false;
                    retVal.SetDetail(TRUST_CANNOT_READ_INTERMEDIATE_CA_CERTS);
                  }
            }

            if(usingTrustedCert && loaderr == false)
            {
                trusted = GetCertificateStacks(this->trustedCertPath, this->trustedCertFormat, this->trustedCertFilePassword, &trustedPKCS12 );
                if(trusted == NULL)
                  {
                    loaderr = false;
                    retVal.SetDetail(TRUST_CANNOT_READ_TRUSTED_CERTS);
                  }
            }
            if(loaderr == false)
            {
                //Check the certificate
                check(cert_ctx, x, untrusted, trusted,NULL, NULL, detail, depth);
                retVal.SetDepth(depth);
                retVal.SetDetail(detail);
            }
          }
        else
          {
            retVal.SetDetail(TRUST_CANNOT_CREATE_STORE);
          }


    }
    catch(std::exception& exc)
    {
        retVal.SetDetail(TRUST_CANNOT_READ_TARGET);
    }
    if (cert_ctx != NULL)
      X509_STORE_free(cert_ctx);
    if (vp)
      X509_VERIFY_PARAM_free(vp);
    if(untrusted)
      sk_X509_pop_free(untrusted, X509_free);
    if(trusted)
      sk_X509_pop_free(trusted, X509_free);
    return retVal;
}

X509_STORE * CreateAndConfigureStore( X509_VERIFY_PARAM *vpm )
{
  X509_STORE * cert_ctx=NULL;
  cert_ctx = X509_STORE_new();
  cert_ctx->verify_cb=cb;

  //Set parameters
  X509_STORE_set1_param(cert_ctx, vpm);


  return cert_ctx;
}



X509_VERIFY_PARAM * CreateAndInitializeParameters(CertificateValidationFlags flags, CertificatePurpose purpose, time_t checkTime)
{
  unsigned long verifyFlags = 0;
  //set purpose
  X509_VERIFY_PARAM * vp =  X509_VERIFY_PARAM_new();

  //set purpose
  if(purpose != DefaultPurpose)
    X509_VERIFY_PARAM_set_purpose(vp, (int)purpose);

  //set flags
  if((flags & VERIFY_IGNORE_CRITICAL) != 0)
    verifyFlags |= X509_V_FLAG_IGNORE_CRITICAL;
  if((flags & VERIFY_CB_ISSUER_CHECK) != 0)
    verifyFlags |= X509_V_FLAG_CB_ISSUER_CHECK;
  if((flags & VERIFY_CRL_CHECK) != 0)
    verifyFlags |= X509_V_FLAG_CRL_CHECK;
  if((flags & VERIFY_CRL_CHECK_ALL) != 0)
    verifyFlags |=X509_V_FLAG_CRL_CHECK_ALL;
  if((flags & VERIFY_POLICY_CHECK ) != 0)
    verifyFlags |=X509_V_FLAG_POLICY_CHECK;
  if((flags & VERIFY_EXPLICIT_POLICY)!= 0)
    verifyFlags |=X509_V_FLAG_EXPLICIT_POLICY;
  if((flags & VERIFY_INHIBIT_ANY) != 0)
    verifyFlags |=X509_V_FLAG_INHIBIT_ANY;
  if((flags & VERIFY_X509_STRICT)!= 0)
    verifyFlags |=X509_V_FLAG_X509_STRICT;
  if((flags & VERIFY_NOTIFY_POLICY) != 0)
    verifyFlags |=X509_V_FLAG_NOTIFY_POLICY;

#ifdef X509_V_FLAG_CHECK_SS_SIGNATURE
  if((flags & VERIFY_CHECK_SS_SIGNATURE)!= 0)
    verifyFlags |=X509_V_FLAG_CHECK_SS_SIGNATURE;
#endif

  if((flags & VERIFY_ALLOW_PROXY_CERTS)!= 0)
      verifyFlags |=X509_V_FLAG_ALLOW_PROXY_CERTS;

#ifdef X509_V_FLAG_EXTENDED_CRL_SUPPORT
  if((flags & VERIFY_EXTENDED_CRL_SUPPORT) ==1)    //Not supported in version 0.9.8 openssl
      verifyFlags |=X509_V_FLAG_EXTENDED_CRL_SUPPORT;
#endif

#ifdef X509_V_FLAG_USE_DELTAS
  if((flags & VERIFY_USE_DELTAS) ==1)              //Not supported in version 0.9.8 openssl
      verifyFlags |=X509_V_FLAG_USE_DELTAS;
#endif

  if((flags & VERIFY_SET_CHECK_TIME)!= 0)
  {
      X509_VERIFY_PARAM_set_time(vp, checkTime);
  }

  X509_VERIFY_PARAM_set_flags(vp, verifyFlags);

  return vp;
}

void LookupCA(X509_STORE * cert_ctx, Glib::ustring path, CertUtil::CertFileFormat format)
{
  X509_LOOKUP *lookup=NULL;
  lookup=X509_STORE_add_lookup(cert_ctx,X509_LOOKUP_file());
  int fileformat = 0;

  if( format == CertUtil::CertFormat_PEM)
    fileformat = X509_FILETYPE_PEM;
  else if(format == CertUtil::CertFormat_DER)
    fileformat = X509_FILETYPE_ASN1;
  else
    fileformat = X509_FILETYPE_DEFAULT;


  X509_LOOKUP_load_file(lookup,path.c_str(),fileformat);

}

STACK_OF(X509)* GetCertificateStacks(Glib::ustring& certPath, CertUtil::CertFileFormat format, Glib::ustring& password,CryptoPKCS12* pkcs12Obj )
{
  STACK_OF(X509)* stack = NULL;
  if(format == CertUtil::CertFormat_PKCS12)
    {
      std::string path = certPath;
      std::string pass = password;
      try
      {
          pkcs12Obj->Load(path, pass);
          stack = pkcs12Obj->getCertificatesAuthorities();
      }
      catch(...){}
    }
  else
    {
      load_certs_crls(NULL, certPath.c_str(), format,NULL, NULL, "cert chain",&stack, NULL);
   }

  return stack;
}

/*Open SSL source*/
int password_callback(char *buf, int bufsiz, int verify,
    PW_CB_DATA *cb_tmp)
{
  return 0;
}

static int cb(int ok, X509_STORE_CTX *ctx)
{

  return ok;

  int cert_error = X509_STORE_CTX_get_error(ctx);
  X509 *current_cert = X509_STORE_CTX_get_current_cert(ctx);


  if (!ok)
    {
      if (current_cert)
        {
          X509_NAME_print_ex_fp(stdout,
              X509_get_subject_name(current_cert),
              0, XN_FLAG_ONELINE);
          printf("\n");
        }

      //printf("%serror %d at %d depth lookup:%s\n",
        //  ctx->parent ? "[CRL path]" : "",
          //    cert_error,
            //  X509_STORE_CTX_get_error_depth(ctx),
             // X509_verify_cert_error_string(cert_error));
      switch(cert_error)
      {
      case X509_V_ERR_NO_EXPLICIT_POLICY:
        policies_print(NULL, ctx);
        break;
      case X509_V_ERR_CERT_HAS_EXPIRED:

        // since we are just checking the certificates, it is
         // ok if they are self signed. But we should still warn
         // the user.
         //

      case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
        // Continue after extension errors too
      case X509_V_ERR_INVALID_CA:
      case X509_V_ERR_INVALID_NON_CA:
      case X509_V_ERR_PATH_LENGTH_EXCEEDED:
      case X509_V_ERR_INVALID_PURPOSE:
      case X509_V_ERR_CRL_HAS_EXPIRED:
      case X509_V_ERR_CRL_NOT_YET_VALID:
      case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
        ok = 0;
        break;

      }
      CertificateValidator::logger->Debug( "Verify callback error" );
      return ok;

    }
  if (cert_error == X509_V_OK && ok == 2)
    policies_print(NULL, ctx);

  return(ok);
}
static void nodes_print(BIO *out, const char *name,
    STACK_OF(X509_POLICY_NODE) *nodes)
{
  X509_POLICY_NODE *node;
  int i;
  BIO_printf(out, "%s Policies:", name);
  if (nodes)
    {
      BIO_puts(out, "\n");
      for (i = 0; i < sk_X509_POLICY_NODE_num(nodes); i++)
        {
          node = sk_X509_POLICY_NODE_value(nodes, i);
          X509_POLICY_NODE_print(out, node, 2);
        }
    }
  else
    BIO_puts(out, " <empty>\n");
}

void policies_print(BIO *out, X509_STORE_CTX *ctx)
{
  X509_POLICY_TREE *tree;
  int explicit_policy;
  int free_out = 0;
  if (out == NULL)
    {
      out = BIO_new_fp(stderr, BIO_NOCLOSE);
      free_out = 1;
    }
  tree = X509_STORE_CTX_get0_policy_tree(ctx);
  explicit_policy = X509_STORE_CTX_get_explicit_policy(ctx);

  BIO_printf(out, "Require explicit Policy: %s\n",
      explicit_policy ? "True" : "False");

  nodes_print(out, "Authority", X509_policy_tree_get0_policies(tree));
  nodes_print(out, "User", X509_policy_tree_get0_user_policies(tree));
  if (free_out)
    BIO_free(out);
}


int initVerify()
{
  static int initialized = 0;
  if (initialized)
    return 1;
  initialized = 1;


  //do_pipe_sig();

  CRYPTO_malloc_init();
  ERR_load_crypto_strings();
  OPENSSL_add_all_algorithms_noconf();
  OPENSSL_config(NULL);

  return 1;
}

static int load_certs_crls(BIO *err, const char *file, CertUtil::CertFileFormat format,
    const char *pass, ENGINE *e, const char *desc,
    STACK_OF(X509) **pcerts, STACK_OF(X509_CRL) **pcrls)
{
  int i;
  BIO *bio;
  STACK_OF(X509_INFO) *xis = NULL;
  X509_INFO *xi;
  PW_CB_DATA cb_data;
  int rv = 0;

  cb_data.password = pass;
  cb_data.prompt_info = file;

  if (format != CertUtil::CertFormat_PEM)
    {
      BIO_printf(err,"bad input format specified for %s\n", desc);
      return 0;
    }

  if (file == NULL)
    bio = BIO_new_fp(stdin,BIO_NOCLOSE);
  else
    bio = BIO_new_file(file, "r");

  if (bio == NULL)
    {
      BIO_printf(err, "Error opening %s %s\n",
          desc, file ? file : "stdin");
      ERR_print_errors(err);
      return 0;
    }

  xis = PEM_X509_INFO_read_bio(bio, NULL,
      (pem_password_cb *)password_callback, &cb_data);

  BIO_free(bio);

  if (pcerts)
    {
      *pcerts = sk_X509_new_null();
      if (!*pcerts)
        goto end;
    }

  if (pcrls)
    {
      *pcrls = sk_X509_CRL_new_null();
      if (!*pcrls)
        goto end;
    }

  for(i = 0; i < sk_X509_INFO_num(xis); i++)
    {
      xi = sk_X509_INFO_value (xis, i);
      if (xi->x509 && pcerts)
        {
          if (!sk_X509_push(*pcerts, xi->x509))
            goto end;
          xi->x509 = NULL;
        }
      if (xi->crl && pcrls)
        {
          if (!sk_X509_CRL_push(*pcrls, xi->crl))
            goto end;
          xi->crl = NULL;
        }
    }

  if (pcerts && sk_X509_num(*pcerts) > 0)
    rv = 1;

  if (pcrls && sk_X509_CRL_num(*pcrls) > 0)
    rv = 1;

  end:

  if (xis)
    sk_X509_INFO_pop_free(xis, X509_INFO_free);

  if (rv == 0)
    {
      if (pcerts)
        {
          sk_X509_pop_free(*pcerts, X509_free);
          *pcerts = NULL;
        }
      if (pcrls)
        {
          sk_X509_CRL_pop_free(*pcrls, X509_CRL_free);
          *pcrls = NULL;
        }
      BIO_printf(err,"unable to load %s\n",
          pcerts ? "certificates" : "CRLs");
      ERR_print_errors(err);
    }
  return rv;
}

static int check(X509_STORE *ctx, X509* target,
    STACK_OF(X509) *uchain, STACK_OF(X509) *tchain,
    STACK_OF(X509_CRL) *crls, ENGINE *e, TrustResultEnum& error, int& depth)
{
  X509 *x=NULL;
  int i=0,ret=0;
  X509_STORE_CTX *csc;
  int trustError =0;

  //X509 *tmp;

  error = TRUST_CANNOT_CREATE_STORE;
  depth = 1;

  x =target;
  if (x == NULL)
    goto end3;

  //Print cert
  // X509_print_fp(stdout, x);

  csc = X509_STORE_CTX_new();
  if (csc == NULL)
    {
      //ERR_print_errors(bio_err);
      goto end3;
    }
  //X509_STORE_set_flags(ctx, 0);
  if(!X509_STORE_CTX_init(csc,ctx,x,uchain))
    {
      //ERR_print_errors(bio_err);
      goto end3;
    }
  if(tchain) X509_STORE_CTX_trusted_stack(csc, tchain);
  if (crls)
    X509_STORE_CTX_set0_crls(csc, crls);

  i=X509_verify_cert(csc);//verify the cert

  trustError = X509_STORE_CTX_get_error(csc);
  depth=  X509_STORE_CTX_get_error_depth(csc);
  X509_STORE_CTX_free(csc);
  switch (trustError)
  {
  case X509_V_OK:
    error = TRUST_OK;
    CertificateValidator::logger->Debug("Certificate is trusted");
    break;
  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:

    error= TRUST_UNABLE_TO_GET_ISSUER_CERT;
    CertificateValidator::logger->Debug("unable to get issuer certificate");
    break;
  case X509_V_ERR_UNABLE_TO_GET_CRL:

    error= TRUST_ERR_UNABLE_TO_GET_CRL;
    break;
  case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
    error= TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE;
    CertificateValidator::logger->Debug("unable to decrypt certificate's signature");
    break;
  case X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
    CertificateValidator::logger->Debug("unable to decrypt CRL's signature");
    error=TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE;
    break;
  case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
    CertificateValidator::logger->Debug("unable to decode issuer public key");
    error=TRUST_UNABLE_TO_DECRYPT_CRL_SIGNATURE;
    break;
  case X509_V_ERR_CERT_SIGNATURE_FAILURE:
    CertificateValidator::logger->Debug("certificate signature failure");
    error=TRUST_CERT_SIGNATURE_FAILURE;
    break;
  case X509_V_ERR_CRL_SIGNATURE_FAILURE:
    CertificateValidator::logger->Debug("CRL signature failure");
    error=TRUST_CERT_SIGNATURE_FAILURE;
    break;
  case X509_V_ERR_CERT_NOT_YET_VALID:
    CertificateValidator::logger->Debug("certificate is not yet valid");
    error=TRUST_CERT_NOT_YET_VALID;
    break;
  case X509_V_ERR_CRL_NOT_YET_VALID:
    CertificateValidator::logger->Debug("CRL is not yet valid");
    error=TRUST_CRL_NOT_YET_VALID;
    break;
  case X509_V_ERR_CERT_HAS_EXPIRED:
    CertificateValidator::logger->Debug("certificate has expired");
    error=TRUST_CERT_HAS_EXPIRED;
    break;
  case X509_V_ERR_CRL_HAS_EXPIRED:
    CertificateValidator::logger->Debug("CRL has expired");
    error=TRUST_ERR_CRL_HAS_EXPIRED;
    break;
  case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
    CertificateValidator::logger->Debug("format error in certificate's notBefore field");
    error=TRUST_ERROR_IN_CERT_NOT_BEFORE_FIELD;
    break;
  case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
    CertificateValidator::logger->Debug("format error in certificate's notAfter field");
    error=TRUST_ERROR_IN_CERT_NOT_AFTER_FIELD;
    break;
  case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
    CertificateValidator::logger->Debug("format error in CRL's lastUpdate field");
    error=TRUST_ERROR_IN_CRL_LAST_UPDATE_FIELD;
    break;
  case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
    CertificateValidator::logger->Debug("format error in CRL's nextUpdate field");
    error=TRUST_ERROR_IN_CRL_NEXT_UPDATE_FIELD;
    break;
  case X509_V_ERR_OUT_OF_MEM:
    CertificateValidator::logger->Debug("out of memory");
    error=TRUST_OUT_OF_MEM;
    break;
  case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
    CertificateValidator::logger->Debug("self signed certificate");
    error=TRUST_DEPTH_ZERO_SELF_SIGNED_CERT;
    break;
  case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
    CertificateValidator::logger->Debug("self signed certificate in certificate chain");
    error=TRUST_SELF_SIGNED_CERT_IN_CHAIN;
    break;
  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
    CertificateValidator::logger->Debug("unable to get local issuer certificate");
    error=TRUST_UNABLE_TO_GET_ISSUER_CERT_LOCALLY;
    break;
  case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
    CertificateValidator::logger->Debug("unable to verify the first certificate");
    error=TRUST_UNABLE_TO_VERIFY_LEAF_SIGNATURE;
    break;
  case X509_V_ERR_CERT_CHAIN_TOO_LONG:
    CertificateValidator::logger->Debug("certificate chain too long");
    error=TRUST_CERT_CHAIN_TOO_LONG;
    break;
  case X509_V_ERR_CERT_REVOKED:
    CertificateValidator::logger->Debug("certificate revoked");
    error=TRUST_ERR_CERT_REVOKED;
    break;
  case X509_V_ERR_INVALID_CA:
    CertificateValidator::logger->Debug("invalid CA certificate");
    error=TRUST_ERR_INVALID_CA;
    break;
  case X509_V_ERR_INVALID_NON_CA:
    CertificateValidator::logger->Debug("invalid non-CA certificate (has CA markings)");
    error=TRUST_INVALID_NON_CA;
    break;
  case X509_V_ERR_PATH_LENGTH_EXCEEDED:
    CertificateValidator::logger->Debug("path length constraint exceeded");
    error=TRUST_ERR_PATH_LENGTH_EXCEEDED;
    break;
  case X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED:
    CertificateValidator::logger->Debug("proxy path length constraint exceeded");
    error=TRUST_ERR_PROXY_PATH_LENGTH_EXCEEDED;
    break;
  case X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED:
    CertificateValidator::logger->Debug("proxy certificates not allowed, please set the appropriate flag");
    error=TRUST_ERR_PROXY_CERTIFICATES_NOT_ALLOWED;
    break;
  case X509_V_ERR_INVALID_PURPOSE:
    CertificateValidator::logger->Debug("unsupported certificate purpose");
    error=TRUST_ERR_INVALID_PURPOSE;
    break;
  case X509_V_ERR_CERT_UNTRUSTED:
    CertificateValidator::logger->Debug("certificate not trusted");
    error=TRUST_ERR_CERT_UNTRUSTED;
    break;
  case X509_V_ERR_CERT_REJECTED:
    CertificateValidator::logger->Debug("certificate rejected");
    error=TRUST_ERR_CERT_REJECTED;
    break;
  case X509_V_ERR_APPLICATION_VERIFICATION:
    CertificateValidator::logger->Debug("application verification failure");
    error=TRUST_ERR_APPLICATION_VERIFICATION;
    break;
  case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
    CertificateValidator::logger->Debug("subject issuer mismatch");
    error=TRUST_ERR_SUBJECT_ISSUER_MISMATCH;
    break;
  case X509_V_ERR_AKID_SKID_MISMATCH:
    CertificateValidator::logger->Debug("authority and subject key identifier mismatch");
    error=TRUST_ERR_AKID_SKID_MISMATCH;
    break;
  case X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH:
    CertificateValidator::logger->Debug("authority and issuer serial number mismatch");
    error=TRUST_ERR_AKID_ISSUER_SERIAL_MISMATCH;
    break;
  case X509_V_ERR_KEYUSAGE_NO_CERTSIGN:
    CertificateValidator::logger->Debug("key usage does not include certificate signing");
    error=TRUST_ERR_KEYUSAGE_NO_CERTSIGN;
    break;
  case X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER:
    CertificateValidator::logger->Debug("unable to get CRL issuer certificate");
    error=TRUST_ERR_UNABLE_TO_GET_CRL_ISSUER;
    break;
  case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
    CertificateValidator::logger->Debug("unhandled critical extension");
    error=TRUST_ERR_UNHANDLED_CRITICAL_EXTENSION;
    break;
  case X509_V_ERR_KEYUSAGE_NO_CRL_SIGN:
    CertificateValidator::logger->Debug("key usage does not include CRL signing");
    error=TRUST_ERR_KEYUSAGE_NO_CRL_SIGN;
    break;
  case X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE:
    CertificateValidator::logger->Debug("key usage does not include digital signature");
    error=TRUST_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE;
    break;
  case X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION:
    CertificateValidator::logger->Debug("unhandled critical CRL extension");
    error=TRUST_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION;
    break;
  case X509_V_ERR_INVALID_EXTENSION:
    CertificateValidator::logger->Debug("invalid or inconsistent certificate extension");
    error=TRUST_ERR_INVALID_EXTENSION;
    break;
  case X509_V_ERR_INVALID_POLICY_EXTENSION:
    CertificateValidator::logger->Debug("invalid or inconsistent certificate policy extension");
    error=TRUST_ERR_INVALID_POLICY_EXTENSION;
    break;
  case X509_V_ERR_NO_EXPLICIT_POLICY:
    CertificateValidator::logger->Debug("no explicit policy");
    error=TRUST_ERR_NO_EXPLICIT_POLICY;
    break;
  case X509_V_ERR_UNNESTED_RESOURCE:
    error=TRUST_ERR_UNNESTED_RESOURCE;
    CertificateValidator::logger->Debug("RFC 3779 resource not subset of parent's resources" );
    break;

    /*
     * Values not handled by OpenSSL 0.9.8
     * case X509_V_ERR_DIFFERENT_CRL_SCOPE:
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

  ret=0;

  end3:

  if (i > 0)
    {
      CertificateValidator::logger->Debug( "Trust Ok");
      ret=1;
    }

  return(ret);
}


