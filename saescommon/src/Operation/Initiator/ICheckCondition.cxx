/**
 * @file ICheckCondition.cxx
 * @brief body interface for check condition
 */

#include "ICheckCondition.hxx"

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

using namespace Smartmatic::SAES::Operation::Initiator;

ICheckCondition::ICheckCondition ( TestStatus::Tests test, std::string msg, std::string img, std::string imgError )
{
    this->test = test;
    this->message = msg;
    this->imageFilename = img;
    this->imageErrorFilename = imgError;
}

ICheckCondition::~ICheckCondition()
{

}

TestStatus::Tests ICheckCondition::whois ()
{
    return test;
}

std::string ICheckCondition::getMessage()
{
    return _(message.c_str());
}

std::string ICheckCondition::getImageFilename()
{
    return imageFilename;
}

std::string ICheckCondition::getImageErrorFilename()
{
    return imageErrorFilename;
}
