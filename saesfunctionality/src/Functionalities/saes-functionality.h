/**
 * @file	saes-functionality.h
 *
 * @brief	Declares the SAES functionality class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk_functionalities
 * Copyright (C)  2010 <>
 * 
 * gtk_functionalities is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk_functionalities is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SAES_FUNCTIONALITY_H_
#define _SAES_FUNCTIONALITY_H_


#include "Functionalities/functionality.h"
#include "Operation/MachineOperationManager.hxx"
#include "Widgets/menu-option.h"
#include <string>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Functionality
		{
			template <class TMenuOptionDescriptor>

			/**
			 * @brief	SAES functionality. 
			 */

			class SAESFunctionality: public Smartmatic::Functionality::Functionality<TMenuOptionDescriptor>
			{

			public:

				/**
				 * @brief	Default constructor.
				 * @tparam	TMenuOptionDescriptor	Type of the menu option descriptor.
				 */

				SAESFunctionality<TMenuOptionDescriptor>()
				{
				}

				/**
				 * @brief	Finaliser.
				 * @tparam	TMenuOptionDescriptor	Type of the menu option descriptor.
				 */

				virtual ~SAESFunctionality<TMenuOptionDescriptor>()
				{
				}

				/**
				 * @brief	Sets an operation manager.
				 * @param [in,out]	manager	If non-null, the manager.
				 */

				void SetOperationManager(Smartmatic::SAES::Operation::MachineOperationManager *manager)
				{
					this->operation_manager = manager;
				}
			
		
				//Pure Virtual Function (Abstract Members)

				/**
				 * @brief	Executes this object.
				 */

				virtual void Execute() = 0;

				/**
				 * @brief	Return if this functionality can be executed
				 * @return	true if can execute functionality
				 */

				virtual bool CanExecute() = 0;

				/**
				 * @brief	Enables this object.
				 * @return	true if it succeeds, false if it fails.
				 */

				virtual bool Enable() = 0;

				/**
				 * @brief	Gets the window title.
				 * @return	The window title.
				 */

				virtual std::string GetWindowTitle() = 0;
				/**
				 * @brief	getter isshow window title.
				 * @return	true is show window title.
				 */

				virtual bool ShowWindowTitle(){ return true; };

				/**
				 * @brief	Gets the menu option type.
				 * @return	The menu option type.
				 */

				virtual TMenuOptionDescriptor GetMenuOptionType() = 0;

				/**
				 * @brief	Locks the machine.
				 * @return	true if it succeeds, false if it fails.
				 */

				virtual bool LockMachine() = 0;
	
			protected:
	
			private:

			};
		};
	}
}

#endif // _SAES_FUNCTIONALITY_H_
