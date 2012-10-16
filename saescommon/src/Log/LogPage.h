/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C) Smart Matic 2011 <>
 * 
 * @file	LogPage.h
 *
 * @brief	Declares the log page class.
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

#ifndef _LOGPAGE_H_
#define _LOGPAGE_H_
#include <vector>
#include <Log/LogLine.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Log
		{
			/**
			 * @class	LogPage
			 *
			 * @brief	Log page. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class LogPage
			{
			public:

				/**
				 * @fn	LogPage::LogPage()
				 *
				 * @brief	Default constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				LogPage(){}

				/**
				 * @fn	LogPage::LogPage(LogPage & logPage);
				 *
				 * @brief	Copy constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param [in,out]	logPage	The log page.
				 */

				LogPage(LogPage & logPage);

				/**
				 * @fn	LogPage::LogPage(unsigned int pageNumber, std::vector<LogLine> vectorPage);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	pageNumber	The page number.
				 * @param	vectorPage	The vector page.
				 */

				LogPage(unsigned int pageNumber, std::vector<LogLine> vectorPage);

				/**
				 * @fn	unsigned int LogPage::getPageNumber();
				 *
				 * @brief	Gets the page number.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The page number.
				 */

				unsigned int getPageNumber();

				/**
				 * @fn	std::vector<LogLine> LogPage::getPage();
				 *
				 * @brief	Gets the page.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The page.
				 */

				std::vector<LogLine> getPage();
			protected:

			private:
				unsigned int pageNumber;	///< The page number
				std::vector<LogLine> vectorPage;	///< The vector page
			};
		}
	}
}

#endif // _LOGPAGE_H_
