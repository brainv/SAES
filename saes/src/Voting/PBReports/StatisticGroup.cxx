/**
 * @file StatisticGroup.cxx
 * @brief Body class StatisticGroup
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

#include "StatisticGroup.hxx"

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

StatisticGroup::StatisticGroup()
{
    this->nameKey = "";
    this->editInfoKey = "";
    this->blockerInfoKey = "";
    this->state = false;
    this->vertical = false;
    this->pivot = 0;
}

StatisticGroup::~StatisticGroup()
{
    list.clear();
}

void StatisticGroup::addStatistic(StatisticWrapper * statistic)
{
    list.push_back(statistic);
}

std::string StatisticGroup::getName()
{
    return _(nameKey.c_str());
}

void StatisticGroup::setNameKey(std::string nameKey)
{
    this->nameKey = nameKey;
}

std::string StatisticGroup::getNameKey()
{
    return nameKey;
}

std::list<StatisticWrapper*> StatisticGroup::getStatistics()
{
    return list;
}
void StatisticGroup::setEditInfoKey(std::string editInfoKey)
{
    this->editInfoKey = editInfoKey;
}

std::string StatisticGroup::getEditInfoKey()
{
    return editInfoKey;
}

void StatisticGroup::setBlockerInfoKey(std::string blockerInfoKey)
{
    this->blockerInfoKey = blockerInfoKey;
}

std::string StatisticGroup::getBlockerInfoKey()
{
    return blockerInfoKey;
}

void StatisticGroup::setState(bool state)
{
    this->state = state;
}

bool StatisticGroup::getState()
{
    return state;
}

std::string StatisticGroup::getInfoKey()
{
    return state ? getEditInfoKey() : getBlockerInfoKey();
}

std::string StatisticGroup::getInfo()
{
    return _(getInfoKey().c_str());
}

void StatisticGroup::setVerticalFilling(bool vertical)
{
	this->vertical = vertical;
}

bool StatisticGroup::isVerticalFilling()
{
	return vertical;
}

void StatisticGroup::setPivot(unsigned int pivot)
{
	this->pivot = pivot;
}

unsigned int StatisticGroup::getPivot()
{
	return pivot;
}

