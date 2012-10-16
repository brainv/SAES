/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C)  2011 <>
 * 
 * @file	saes-common-language-controller.h
 *
 * @brief	Declares the saes common language controller class.
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SAES_COMMON_LANGUAGE_CONTROLLER_H_
#define _SAES_COMMON_LANGUAGE_CONTROLLER_H_

#include "Environment/Configurations/base-language-controller.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Common
		{
			namespace Configuration
			{
				/**
				 * @class	SAESCommonLanguageController
				 *
				 * @brief	Saes common language controller. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class SAESCommonLanguageController: public Smartmatic::Environment::BaseLanguageController
				{
				public:

						/**
						 * @fn	string SAESCommonLanguageController::getPackageName();
						 *
						 * @brief	Gets the package name.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @return	The package name.
						 */

						std::string getPackageName();

						/**
						 * @fn	string SAESCommonLanguageController::getLocaleDir();
						 *
						 * @brief	Gets the locale dir.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @return	The locale dir.
						 */

						std::string getLocaleDir();

						/**
						 * @fn	SAESCommonLanguageController::SAESCommonLanguageController();
						 *
						 * @brief	Default constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						SAESCommonLanguageController();

						/**
						 * @fn	SAESCommonLanguageController::~SAESCommonLanguageController();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						virtual ~SAESCommonLanguageController();
				protected:

				private:

				};
			}
		}
	}
}

#endif // _SAES_COMMON_LANGUAGE_CONTROLLER_H_
