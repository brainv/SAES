/**
 * @file	saes-functionality-language-controller.h
 *
 * @brief	Declares the SAES functionality language controller class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C)  2011 <>
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

#ifndef _SAES_FUNCTIONALITY_LANGUAGE_CONTROLLER_H_
#define _SAES_FUNCTIONALITY_LANGUAGE_CONTROLLER_H_

#include "Environment/Configurations/base-language-controller.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Functionality
		{
			namespace Configuration
			{
				/**
				 * @brief	Saes functionality language controller. 
				 */

				class SAESFunctionalityLanguageController:public Smartmatic::Environment::BaseLanguageController
				{
				public:

						/**
						 * @brief	obtains the package name.
						 * @return	The package name.
						 */

						std::string getPackageName();

						/**
						 * @brief	obtains the locale dir.
						 * @return	The locale dir.
						 */

						std::string getLocaleDir();

						/**
						 * @brief	Default constructor.
						 */

						SAESFunctionalityLanguageController();

						/**
						 * @brief	Finaliser.
						 */

						virtual ~SAESFunctionalityLanguageController();
		
				protected:
						

				private:
				};
			}
		}
	}
}

#endif // _SAES_FUNCTIONALITY_LANGUAGE_CONTROLLER_H_
