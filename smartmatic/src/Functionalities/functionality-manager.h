/**
 * @file	functionality-manager.h
 *
 * @brief	Header file to the functionality manager class.
 */

#ifndef _FUNCTIONALITY_MANAGER_H_
#define _FUNCTIONALITY_MANAGER_H_

#include <map>
#include "Functionalities/functionality.h"
#include "Functionalities/menu-option-descriptor.h"
#include <iostream>

namespace Smartmatic
{
	namespace Functionality
	{
		/**
		 * @brief	Manager for functionalities class. 
		 *
		 * @author	Rafael.gasperi
		 * @date	28/04/2011
		 */

		template <class TMenuOptionDescriptor>
		class FunctionalityManager
		{
			protected:


			///< The functionalities
			std::map<TMenuOptionDescriptor, Functionality<TMenuOptionDescriptor>* > functionalities;

			///< The functionalities connected
			std::vector<Functionality<TMenuOptionDescriptor>*> functionalitiesConnected;

			public:

			/**
			 * @brief	Default constructor.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			FunctionalityManager();

			/**
			 * @brief	signals definitions.
			 */

			typedef sigc::signal<void> type_lock_machine;

			type_lock_machine LockMachine();

			/**
			 * @brief	Executes the option selected operation.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @exception	e	Thrown when .
			 *
			 * @param	menuDesc	Information describing the menu.
			 *
			 * @return	true if it succeeds, false if it fails.
			 */

			bool ExecuteOptionSelected(TMenuOptionDescriptor menuDesc);
			/**
			 * @brief	Registers this object.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @exception	e	Thrown when .
			 *
			 * @param [in,out]	funct	If non-null, the funct.
			 */

			void Register(Functionality<TMenuOptionDescriptor> *funct);

			/**
			 * @brief	Gets the functionality manager.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	.
			 */

			virtual ~ FunctionalityManager();

			/**
			 * @brief	Executes the challenge operation.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @param [in,out]	funct	If non-null, the funct.
			 *
			 * @return	true if it succeeds, false if it fails.
			 */

			virtual bool ExecuteChallenge(Functionality<TMenuOptionDescriptor>* funct);

			private:
			
			type_lock_machine m_lock_machine; ///< The lock machine

			/**
			 * @brief	Locks the machine signal.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			void LockMachineSignal();
			
		};
	}
}

#include "functionality-manager.hpp"

#endif // _FUNCTIONALITY_MANAGER_H_
