/**
 * @file	functionality.h
 *
 * @brief	Header file to the functionality class.
 */

#ifndef _FUNCTIONALITY_H_
#define _FUNCTIONALITY_H_
#include <glibmm.h>
#include <string>
#include <iostream>
#include <Log/ISMTTLog.h>
#include "FunctionalityChallengeConfiguration.h"
 
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
		class FunctionalityManager;

		/**
		 * @brief	Functionality class. 
		 *
		 * @author	Rafael.gasperi
		 * @date	28/04/2011
		 */

		template <class TMenuOptionDescriptor>
		class Functionality
		{

		public:

			/**
			 * @brief	Default constructor.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @tparam	TMenuOptionDescriptor	Type of the menu option descriptor.
			 */

			Functionality<TMenuOptionDescriptor>()
			:loaded(false)
			{}

			/**
			 * @brief	Finaliser.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @tparam	TMenuOptionDescriptor	Type of the menu option descriptor.
			 */

			virtual ~Functionality<TMenuOptionDescriptor>(){}

			/**
			 * @brief	Does this object.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @exception	e	Thrown when Excute() fails.
			 */

			void Do()
			{
				try
				{
					Execute();
				}
				catch(std::exception& e)
				{
					throw  e;
				}
			}

			/**
			 * @brief	Begins an execute.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			void BeginExecute();	

		 	/**
		 	 * @brief	Registers this object.
		 	 *
		 	 * @author	Rafael.gasperi
		 	 * @date	28/04/2011
		 	 *
		 	 * @exception	e	Thrown when .
		 	 *
		 	 * @param [in,out]	funct_manager	If non-null, manager for funct.
		 	 */

		 	void Register(FunctionalityManager<TMenuOptionDescriptor> *funct_manager)
			{
				try
				{
					funct_manager->Register(this);
				}
				catch(std::exception& e)
				{
					throw  e;
				}
			}

			/**
			 * @brief	Pure Virtual Function (Abstract Members)
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			virtual void DisplayUnableMessage() = 0;

			/**
			 * @brief	Executes this object.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			virtual void Execute() = 0;

			/**
			 * @brief	Return if this functionality can be executed
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 * @return	true if can execute functionality
			 */

			virtual bool CanExecute() = 0;

			/**
			 * @brief	Enables this object.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	true if it succeeds, false if it fails.
			 */

			virtual bool Enable() = 0;

			/**
			 * @brief	Gets the window title.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	The window title.
			 */

			virtual std::string GetWindowTitle() = 0;

			/**
			 * @brief	Gets the menu option type.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	The menu option type.
			 */

			virtual TMenuOptionDescriptor GetMenuOptionType() = 0;

			/**
			 * @brief	Locks the machine.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	true if it succeeds, false if it fails.
			 */

			virtual bool LockMachine() = 0;

			/**
			 * @brief	Virtual Function (Abstract Members)
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	true if it succeeds, false if it fails.
			 */

			virtual bool ChallengeIsEnable()
			{
				return false;
			}

			/**
			 * @brief	Gets the challenge configuration.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	The challenge configuration.
			 */

			virtual FunctionalityChallengeConfiguration getChallengeConfiguration()
			{
				FunctionalityChallengeConfiguration arg;
				return arg;
			}

			/**
			 * @brief	signals definitions.
			 */

			typedef sigc::signal<void> type_lock_machine;

			/**
			 * @brief	Locks the machine sigc.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	.
			 */

			type_lock_machine LockMachineSigc()
			{
				return m_lock_machine;
			};

			/**
			 * @brief	Gets if password is role
			 *
			 * @author	Luiggi.mendez
			 * @date	28/04/2011
			 */

			virtual bool GetIsRolePassword() = 0;

		protected:

			
			TMenuOptionDescriptor* optionType; ///< Type of the option

			
			void *operation_manager; ///< Manager for operation

			
			bool loaded; ///< true if the data was loaded

			
			type_lock_machine m_lock_machine; ///< The lock machine

			/**
			 * @brief	Gets the logger.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	null if it fails, else the logger.
			 */

			virtual Smartmatic::Log::ISMTTLog* getLogger() = 0;

			/**
			 * @brief	Gets the start log message.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	The start log message.
			 */

			virtual Glib::ustring getStartLogMessage() = 0;

			/**
			 * @brief	Gets the finish log message.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 *
			 * @return	The finish log message.
			 */

			virtual Glib::ustring getFinishLogMessage() = 0;
	
		private:


		};
	};
}

#endif // _FUNCTIONALITY_H_
