/**
 * @file CryptoBase.cxx
 * @brief Body class crypto base
 * @date 20/03/2012
 * @author Yadickson Soto
 */

#include "CryptoBase.hxx"

using namespace Smartmatic::System::Security::Cryptography;

CryptoBase::CryptoBase(CryptoPKCS12 * cryptoPKCS12, const EVP_CIPHER * cipherMode)
{
	this->cryptoPKCS12 = cryptoPKCS12;
	this->cert = NULL;
	this->cipherMode = cipherMode;
}

CryptoBase::CryptoBase(const X509 * cert, const EVP_CIPHER * cipherMode)
{
	this->cryptoPKCS12 = NULL;
	this->cert = cert;
	this->cipherMode = cipherMode;
}

CryptoBase::~CryptoBase()
{

}

