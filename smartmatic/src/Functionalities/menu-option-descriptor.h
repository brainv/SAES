/**
 * @file	option-descriptor.h
 *
 * @brief	Header file to the menu option descriptor class.
 */

#ifndef _MENU_OPTION_DESCRIPTOR_H_
#define _MENU_OPTION_DESCRIPTOR_H_
#include <glibmm/ustring.h>
#include <iostream>

namespace Smartmatic
{
	namespace Functionality
	{
		/**
		 * @brief	Menu option descriptor class. 
		 *
		 * @author	Rafael.gasperi
		 * 			
		 * @date	28/04/2011
		 */

		class MenuOptionDescriptor
		{
		public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 */

				MenuOptionDescriptor();

				/**
				 * @brief	Gets the menu option.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 *
				 * @return	The menu option.
				 */

				const Glib::ustring& getMenuOption() const;

				/**
				 * @brief	Gets the  menu.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getIsMenu() const;

				/**
				 * @brief	Less-than comparison operator.
				 *
				 * @author	Rafael.gasperi
				 * 			
				 * @date	28/04/2011
				 *
				 * @param	other	The other.
				 *
				 * @return	true if the first parameter is less than the second.
				 */

				bool operator<(const MenuOptionDescriptor& other) const;

		protected:

				/**
				 * @brief	Sets a menu option.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param [in,out]	specificOption	The specific option.
				 */

				void setMenuOption(Glib::ustring& specificOption);
				
		private:

			
			Glib::ustring option; ///< The option
		};
	

	}
}

#endif // _MENU_OPTION_DESCRIPTOR_H_
