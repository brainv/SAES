/**
 * @file StatisticWrapper.cxx
 * @brief Body class StatisticManager
 */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StatisticWrapper.hxx"

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

using namespace Smartmatic::SAES::Voting::PBReports;

StatisticWrapper::StatisticWrapper()
 : StatisticType ()
{
    this->edit = false;
    this->calculated = false;
    this->required = false;
    this->setNameKey("");
    this->setDescriptionKey("");
    this->setCode("");
    this->setValue("");
    this->mask = "";
    this->regex = "";
    this->mandatory = false;
    this->max = 250;
    this->width = -1;
    this->height = -1;
}

StatisticWrapper::StatisticWrapper(StatisticType & statistic)
 : StatisticType (statistic)
{
	this->edit = false;
	this->calculated = false;
	this->required = false;
}

StatisticWrapper::~StatisticWrapper()
{
}

void StatisticWrapper::setEdit(bool edit)
{
    this->edit = edit;
}

bool StatisticWrapper::isEdit()
{
    return edit && !calculated;
}

void StatisticWrapper::setCalculated(bool calculated)
{
    this->calculated = calculated;
}

bool StatisticWrapper::isCalculated()
{
    return calculated;
}

void StatisticWrapper::setRequired(bool required)
{
    this->required = required;
}

bool StatisticWrapper::isRequired()
{
    return required;
}
std::string StatisticWrapper::getName()
{
    return _(getNameKey().c_str());
}

std::string StatisticWrapper::getDescription()
{
    return _(getDescriptionKey().c_str());
}

unsigned int StatisticWrapper::getMax()
{
	return max;
}

void StatisticWrapper::setMax(unsigned int max)
{
	this->max = max;
}

std::string StatisticWrapper::getMask()
{
	return mask;
}

void StatisticWrapper::setMask(std::string mask)
{
	this->mask = mask;
}

std::string StatisticWrapper::getRegex()
{
	return regex;
}

void StatisticWrapper::setRegex(std::string regex)
{
	this->regex = regex;
}

Smartmatic::SAES::Configuration::StatisticElementType StatisticWrapper::getType()
{
	return type;
}

void StatisticWrapper::setType(Smartmatic::SAES::Configuration::StatisticElementType type)
{
	this->type = type;
}

int StatisticWrapper::getWidth()
{
	return this->width;
}

int StatisticWrapper::getHeight()
{
	return this->height;
}

void StatisticWrapper::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void StatisticWrapper::setMandatory(bool mandatory)
{
	this->mandatory = mandatory;
}

bool StatisticWrapper::isMandatory()
{
	return mandatory;
}
