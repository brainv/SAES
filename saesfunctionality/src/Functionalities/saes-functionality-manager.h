/**
 * @file	saes-functionality-manager.h
 *
 * @brief	Declares the SAES functionality manager class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
	 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SAES_FUNCTIONALITY_MANAGER_H_
#define _SAES_FUNCTIONALITY_MANAGER_H_
#include <Functionalities/functionality-manager.h>
#include "saes-menu-option-descriptor.h"
#include "Functionalities/functionality.h"
#include "Windows/password-window.h"

namespace Smartmatic
{
	namespace	SAES
	{

		namespace	Functionality
		{
			/**
			 * @brief	Manager for SAES functionalities. 
			 */

			class SaesFunctionalityManager: public Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor>
			{
				public:

				/**
				 * @brief	Gets the current SAES Functionality Manager.
				 * @return	null if it fails, else.
				 */

				static SaesFunctionalityManager* Current();
				 /**
				  * @brief	Finaliser.
				  */

				 ~SaesFunctionalityManager()
				{
				}

				 /**
				  * @brief	Executes the challenge operation.
				  * @param [in,out]	funct	If non-null, the funct.
				  * @return	true if it succeeds, false if it fails.
				  */

				 bool ExecuteChallenge(Smartmatic::Functionality::Functionality<Smartmatic::Functionality::MenuOptionDescriptor>* funct);

				protected:

				private:

					/**
					 * @brief	Default constructor.
					 */

					SaesFunctionalityManager(): Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor>()
					{}
					
					static SaesFunctionalityManager* singleton_instance;	///< The singleton instance

			};
		}
	}
}

#endif // _SAES_FUNCTIONALITY_MANAGER_H_
