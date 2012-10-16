/*
 * CitizenInfo.cpp
 *
 *  Created on: Apr 20, 2011
 *      Author: Gerardo Hernandez
 */

#include "CitizenInfo.h"

using namespace Smartmatic::SAES::EID;

CitizenInfo::CitizenInfo()
{
	firstName = "";
	surname = "";
	gender = "";
	dateOfBirth = "";
	locationOfBirth = "";
	nationality = "";
	nationalNumber = "";
	specialOrganization = "";
	memberOfFamily = "";
	addressVersion = "";
	street = "";
	zipCode = "";
	municipality = "";
	country = "";
	specialStatus = "";

}

CitizenInfo::~CitizenInfo()
{
	// TODO Auto-generated destructor stub
}

void CitizenInfo::ClearData()
{
	firstName = "";
	surname = "";
	gender = "";
	dateOfBirth = "";
	locationOfBirth = "";
	nationality = "";
	nationalNumber = "";
	specialOrganization = "";
	memberOfFamily = "";
	addressVersion = "";
	street = "";
	zipCode = "";
	municipality = "";
	country = "";
	specialStatus = "";
}

std::string CitizenInfo::getFirstName()
{
	return firstName;
}

std::string CitizenInfo::getSurname()
{
	return surname;
}

std::string CitizenInfo::getGender()
{
	return gender;
}
std::string CitizenInfo::getDateOfBirth()
{
	return dateOfBirth;
}

std::string CitizenInfo::getLocationOfBirth()
{
	return locationOfBirth;
}

std::string CitizenInfo::getNationality()
{
	return nationality;
}

std::string CitizenInfo::getNationalNumber()
{
	return nationalNumber;
}

std::string CitizenInfo::getSpecialOrganization()
{
	return specialOrganization;
}
std::string CitizenInfo::getMemberOfFamily()
{
	return memberOfFamily;
}
std::string CitizenInfo::getAddressVersion()
{
	return addressVersion;
}
std::string CitizenInfo::getStreet()
{
	return street;
}
std::string CitizenInfo::getZipCode()
{
	return zipCode;
}
std::string CitizenInfo::getMunicipality()
{
	return municipality;
}
std::string CitizenInfo::getCountry()
{
	return country;
}
std::string CitizenInfo::getSpecialStatus()
{
	return specialStatus;
}

void CitizenInfo::setFirstName(std::string arg)
{
	firstName = arg;
}

void CitizenInfo::setSurname(std::string arg)
{
	surname = arg;
}

void CitizenInfo::setGender(std::string arg)
{
	gender = arg;
}

void CitizenInfo::setDateOfBirth(std::string arg)
{
	dateOfBirth = arg;
}

void CitizenInfo::setLocationOfBirth(std::string arg)
{
	locationOfBirth = arg;
}

void CitizenInfo::setNationality(std::string arg)
{
	nationality = arg;
}

void CitizenInfo::setNationalNumber(std::string arg)
{
	nationalNumber = arg;
}

void CitizenInfo::setSpecialOrganization(std::string arg)
{
	specialOrganization = arg;
}

void CitizenInfo::setMemberOfFamily(std::string arg)
{
	memberOfFamily = arg;
}

void CitizenInfo::setAddressVersion(std::string arg)
{
	addressVersion = arg;
}

void CitizenInfo::setStreet(std::string arg)
{
	street = arg;
}

void CitizenInfo::setZipCode(std::string arg)
{
	zipCode = arg;
}

void CitizenInfo::setMunicipality(std::string arg)
{
	municipality = arg;
}

void CitizenInfo::setCountry(std::string arg)
{
	country = arg;
}

void CitizenInfo::setSpecialStatus(std::string arg)
{
	specialStatus = arg;
}

void CitizenInfo::setValidity(std::string arg)
{
	validity = arg;
}

std::string CitizenInfo::getValidity()
{
	return validity;
}

void CitizenInfo::setEndValidity(std::string arg)
{
	validityEnd = arg;
}

std::string CitizenInfo::getEndValidity()
{
	return validityEnd;
}
