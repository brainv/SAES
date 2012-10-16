/**
 * @file	CitizenInfo.h
 *
 * @brief	Declares the citizen information class.
 */

#ifndef CITIZENINFO_H_
#define CITIZENINFO_H_

#include <string>

namespace Smartmatic
{
    namespace SAES
    {
    	namespace EID
		{
			/**
			 * @class	CitizenInfo
			 *
			 * @brief	Information about the citizen. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class CitizenInfo
			{
			public:

				/**
				 * @fn	CitizenInfo::CitizenInfo();
				 *
				 * @brief	Default constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				CitizenInfo();

				/**
				 * @fn	virtual CitizenInfo::~CitizenInfo();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				virtual ~CitizenInfo();

				/**
				 * @fn	std::string CitizenInfo::getFirstName();
				 *
				 * @brief	Clear the data
				 */

				void ClearData();

				/**
				 * @fn	std::string CitizenInfo::getFirstName();
				 *
				 * @brief	Gets the first name.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The first name.
				 */

				std::string getFirstName();

				/**
				 * @fn	std::string CitizenInfo::getSurname();
				 *
				 * @brief	Gets the surname.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The surname.
				 */

				std::string getSurname();

				/**
				 * @fn	std::string CitizenInfo::getGender();
				 *
				 * @brief	Gets the gender.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The gender.
				 */

				std::string getGender();

				/**
				 * @fn	std::string CitizenInfo::getDateOfBirth();
				 *
				 * @brief	Gets the date of birth.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The date of birth.
				 */

				std::string getDateOfBirth();

				/**
				 * @fn	std::string CitizenInfo::getLocationOfBirth();
				 *
				 * @brief	Gets the location of birth.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The location of birth.
				 */

				std::string getLocationOfBirth();

				/**
				 * @fn	std::string CitizenInfo::getNationality();
				 *
				 * @brief	Gets the nationality.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The nationality.
				 */

				std::string getNationality();

				/**
				 * @fn	std::string CitizenInfo::getNationalNumber();
				 *
				 * @brief	Gets the national number.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The national number.
				 */

				std::string getNationalNumber();

				/**
				 * @fn	std::string CitizenInfo::getSpecialOrganization();
				 *
				 * @brief	Gets the special organization.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The special organization.
				 */

				std::string getSpecialOrganization();

				/**
				 * @fn	std::string CitizenInfo::getMemberOfFamily();
				 *
				 * @brief	Gets the member of family.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The member of family.
				 */

				std::string getMemberOfFamily();

				/**
				 * @fn	std::string CitizenInfo::getAddressVersion();
				 *
				 * @brief	Gets the address version.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The address version.
				 */

				std::string getAddressVersion();

				/**
				 * @fn	std::string CitizenInfo::getStreet();
				 *
				 * @brief	Gets the street.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The street.
				 */

				std::string getStreet();

				/**
				 * @fn	std::string CitizenInfo::getZipCode();
				 *
				 * @brief	Gets the zip code.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The zip code.
				 */

				std::string getZipCode();

				/**
				 * @fn	std::string CitizenInfo::getMunicipality();
				 *
				 * @brief	Gets the municipality.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The municipality.
				 */

				std::string getMunicipality();

				/**
				 * @fn	std::string CitizenInfo::getCountry();
				 *
				 * @brief	Gets the country.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The country.
				 */

				std::string getCountry();

				/**
				 * @fn	std::string CitizenInfo::getSpecialStatus();
				 *
				 * @brief	Gets the special status.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The special status.
				 */

				std::string getSpecialStatus();

				/**
				 * @fn	std::string CitizenInfo::getValidity();
				 *
				 * @brief	Gets the validity.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The validity.
				 */

				std::string getValidity();

				/**
				 * @fn	std::string CitizenInfo::getEndValidity();
				 *
				 * @brief	Gets the end validity.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The end validity.
				 */

				std::string getEndValidity();

				/**
				 * @fn	void CitizenInfo::setFirstName(std::string arg);
				 *
				 * @brief	Sets a first name.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setFirstName(std::string arg);

				/**
				 * @fn	void CitizenInfo::setSurname(std::string arg);
				 *
				 * @brief	Sets a surname.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setSurname(std::string arg);

				/**
				 * @fn	void CitizenInfo::setGender(std::string arg);
				 *
				 * @brief	Sets a gender.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setGender(std::string arg);

				/**
				 * @fn	void CitizenInfo::setDateOfBirth(std::string arg);
				 *
				 * @brief	Sets a date of birth.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setDateOfBirth(std::string arg);

				/**
				 * @fn	void CitizenInfo::setLocationOfBirth(std::string arg);
				 *
				 * @brief	Sets a location of birth.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setLocationOfBirth(std::string arg);

				/**
				 * @fn	void CitizenInfo::setNationality(std::string arg);
				 *
				 * @brief	Sets a nationality.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setNationality(std::string arg);

				/**
				 * @fn	void CitizenInfo::setNationalNumber(std::string arg);
				 *
				 * @brief	Sets a national number.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setNationalNumber(std::string arg);

				/**
				 * @fn	void CitizenInfo::setSpecialOrganization(std::string arg);
				 *
				 * @brief	Sets a special organization.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setSpecialOrganization(std::string arg);

				/**
				 * @fn	void CitizenInfo::setMemberOfFamily(std::string arg);
				 *
				 * @brief	Sets a member of family.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setMemberOfFamily(std::string arg);

				/**
				 * @fn	void CitizenInfo::setAddressVersion(std::string arg);
				 *
				 * @brief	Sets the address version.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setAddressVersion(std::string arg);

				/**
				 * @fn	void CitizenInfo::setStreet(std::string arg);
				 *
				 * @brief	Sets a street.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setStreet(std::string arg);

				/**
				 * @fn	void CitizenInfo::setZipCode(std::string arg);
				 *
				 * @brief	Sets a zip code.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setZipCode(std::string arg);

				/**
				 * @fn	void CitizenInfo::setMunicipality(std::string arg);
				 *
				 * @brief	Sets a municipality.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setMunicipality(std::string arg);

				/**
				 * @fn	void CitizenInfo::setCountry(std::string arg);
				 *
				 * @brief	Sets a country.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setCountry(std::string arg);

				/**
				 * @fn	void CitizenInfo::setSpecialStatus(std::string arg);
				 *
				 * @brief	Sets a special status.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setSpecialStatus(std::string arg);

				/**
				 * @fn	void CitizenInfo::setValidity(std::string arg);
				 *
				 * @brief	Sets a validity.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setValidity(std::string arg);

				/**
				 * @fn	void CitizenInfo::setEndValidity(std::string arg);
				 *
				 * @brief	Sets an end validity.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	arg	The argument.
				 */

				void setEndValidity(std::string arg);

			protected:

			private:

				std::string firstName;  ///< First name
				std::string surname;	///< The surname
				std::string gender; ///< The gender
				std::string dateOfBirth;	///< Date of the birth
				std::string locationOfBirth;	///< The location of birth
				std::string nationality;	///< The nationality
				std::string nationalNumber; ///< The national number
				std::string specialOrganization;	///< The special organization
				std::string memberOfFamily; ///< The member of family
				std::string addressVersion; ///< The address version
				std::string street; ///< The street
				std::string zipCode;	///< The zip code
				std::string municipality;   ///< The municipality
				std::string country;	///< The country
				std::string specialStatus;  ///< The special status
				std::string validity;   ///< The validity
				std::string validityEnd;	///< The validity end
			};
		}
	}
}


#endif /* CITIZENINFO_H_ */
