/**
 * @file EIDReader.cxx
 * @brief Body class eid reader
 * @date 20/07/2011
 * @author Yadickson Soto
 */

#include "EIDRead.hxx"
#include "EIDUtils.hxx"
#include <iostream>
#include <System/IO/File.h>
#include "beidlib/eidlibException.h"
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

#define IMAGE_TEMP_PATH "/tmp/beid-image"

using namespace eIDMW;
using namespace Smartmatic::SAES::EID;
using namespace Smartmatic::Log;

ISMTTLog* EIDRead::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.EID.EIDRead",GETTEXT_PACKAGE);

//*****************************************************************************
// Get the data and dump to the screen
// Beware: The data coming from the cards is encoded in UTF8!
//*****************************************************************************
void EIDRead::getSISData( CitizenInfo & info, BEID_SISCard& card )
{
	logger->Debug("Getter SYS Data Info.");

	BEID_SisId& eid = card.getID();

	info.setFirstName(EIDUtils::utf8ToAnsi(eid.getName()));
	info.setSurname(eid.getSurname());
	info.setGender(eid.getGender ());
	info.setDateOfBirth(eid.getDateOfBirth());
	info.setLocationOfBirth(" ");
	info.setNationality(" ");
	info.setNationalNumber(" ");
	info.setSpecialOrganization(" ");
	info.setMemberOfFamily(" ");
	info.setAddressVersion(" ");
	info.setStreet(" ");
	info.setZipCode(" ");
	info.setMunicipality(" ");
	info.setCountry(" ");
	info.setSpecialStatus(" ");
	info.setValidity(eid.getValidityBeginDate());
	info.setEndValidity(eid.getValidityEndDate());
}

//*****************************************************************************
// Get the data from a Belgian SIS card
//*****************************************************************************
void EIDRead::getSISCardData( CitizenInfo & info, BEID_ReaderContext& readerContext )
{
	BEID_SISCard& card = readerContext.getSISCard();
	EIDRead::getSISData( info, card );
}

//*****************************************************************************
// Get the data and dump to the screen
// Beware: The data coming from the cards is encoded in UTF8!
//*****************************************************************************
void EIDRead::getEIDData( CitizenInfo & info, BEID_EIDCard& card )
{
	logger->Debug("Getter EID Data Info.");

	BEID_EId&	  eid  = card.getID();

	if ( card.isTestCard() )
	{
		card.setAllowTestCard(true);
	}

	info.setFirstName(eid.getFirstName());
	info.setSurname(eid.getSurname());
	info.setGender(eid.getGender ());
	info.setDateOfBirth(eid.getDateOfBirth());
	info.setLocationOfBirth(eid.getLocationOfBirth());
	info.setNationality(eid.getNationality());
	info.setNationalNumber(eid.getNationalNumber());
	info.setSpecialOrganization(eid.getSpecialOrganization());
	info.setMemberOfFamily(eid.getMemberOfFamily());
	info.setAddressVersion(eid.getAddressVersion());
	info.setStreet(eid.getStreet());
	info.setZipCode(eid.getZipCode());
	info.setMunicipality(eid.getMunicipality());
	info.setCountry(eid.getCountry());
	info.setSpecialStatus(eid.getSpecialStatus());
	info.setValidity(eid.getValidityBeginDate());
	info.setEndValidity(eid.getValidityEndDate());

}

//*****************************************************************************
// Get the data from a Belgian kids EID card
//*****************************************************************************
void EIDRead::getKidsCardData( CitizenInfo & info, BEID_ReaderContext& readerContext )
{
	BEID_KidsCard& card = readerContext.getKidsCard();
	EIDRead::getEIDData(info, card);
}

//*****************************************************************************
// Get the data from a Belgian foreigner EID card
//*****************************************************************************
void EIDRead::getForeignerCardData( CitizenInfo & info, BEID_ReaderContext& readerContext )
{
	BEID_ForeignerCard& card = readerContext.getForeignerCard();
	EIDRead::getEIDData(info, card);
}
//*****************************************************************************
// Get the data from a Belgian EID card
//*****************************************************************************
void EIDRead::getEidCardData( CitizenInfo & info, BEID_ReaderContext& readerContext )
{
	BEID_EIDCard& card = readerContext.getEIDCard();
	EIDRead::getEIDData(info, card);
}

Glib::RefPtr<Gdk::Pixbuf> EIDRead::getEIDPicture( BEID_EIDCard& card )
{
	logger->Debug("Getter EID Picture Info.");

	if ( card.isTestCard() )
	{
		card.setAllowTestCard(true);
	}

	BEID_Picture& picture = card.getPicture();

	const unsigned char* pictureData = picture.getData().GetBytes();
	unsigned int pictureSize = picture.getData().Size();

	Smartmatic::System::SafeBuffer buffer((unsigned char*)pictureData, pictureSize);
	std::string file = IMAGE_TEMP_PATH;
	Glib::RefPtr<Gdk::Pixbuf> img;

	if (Smartmatic::System::IO::File::saveBufferToFile(buffer, file))
	{
		img = Gdk::Pixbuf::create_from_file(file);
		Smartmatic::System::IO::File::DeleteFile(file);
	}

	return img;
}

Glib::RefPtr<Gdk::Pixbuf> EIDRead::getKidsCardPicture( BEID_ReaderContext& readerContext )
{
	BEID_KidsCard& card = readerContext.getKidsCard();
	return EIDRead::getEIDPicture(card);
}

Glib::RefPtr<Gdk::Pixbuf> EIDRead::getForeignerCardPicture( BEID_ReaderContext& readerContext )
{
	BEID_ForeignerCard& card = readerContext.getForeignerCard();
	return EIDRead::getEIDPicture(card);
}

Glib::RefPtr<Gdk::Pixbuf> EIDRead::getEidCardPicture( BEID_ReaderContext& readerContext )
{
	BEID_EIDCard& card = readerContext.getEIDCard();
	return EIDRead::getEIDPicture(card);
}
