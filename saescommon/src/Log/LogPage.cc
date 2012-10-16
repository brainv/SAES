/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogPage.h"
using namespace Smartmatic::SAES::Log;

LogPage::LogPage(LogPage & logPage)
{
	this->pageNumber = logPage.getPageNumber();
	this->vectorPage = logPage.getPage();
}

LogPage::LogPage(unsigned int pageNumber, std::vector<LogLine> vectorPage)
{
	this->pageNumber = pageNumber;
	this->vectorPage = vectorPage;
}

unsigned int LogPage::getPageNumber()
{
	return this->pageNumber;
}

std::vector<LogLine> LogPage::getPage()
{
	return this->vectorPage;
}