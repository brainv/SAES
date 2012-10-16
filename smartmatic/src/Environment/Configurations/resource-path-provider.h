/**
 * @file	resource-path-provider.h
 *
 * @brief	Header file to the resource path provider class.
 */

#ifndef _RESOURCE_PATH_PROVIDER_H_
#define _RESOURCE_PATH_PROVIDER_H_

#include <vector>
#include <iostream>

namespace Smartmatic
{
	namespace Environment
	{
		/**
		 * @brief	Resource path provider. 
		 *
    	 * @author	Rafael.gasperi
    	 * 			 
		 * @date	28/04/2011
		 */

		class ResourcePathProvider
		{
		public:

			/**
			 * @brief	Gets a resource path.
			 *
			 * @author	Rafael.gasperi
			 * 			
			 * @date	28/04/2011
			 *
			 * @param	libPath			Full pathname of the library file.
			 * @param	relativePath	Full pathname of the relative file.
			 *
			 * @return	The resource path.
			 */

			std::string GetResourcePath(const std::string& libPath, const std::string& relativePath);

			/**
			 * @brief	Gets the current.
			 *
			 * @author	Rafael.gasperi
			 * 			 
			 * @date	28/04/2011
			 *
			 * @return	null if it fails, else.
			 */

			static ResourcePathProvider *Current();

		protected:

		private:

			
			std::vector<std::string> dirPaths; ///< The dir paths

			/**
			 * @brief	Default constructor.
			 *
			 * @author	Rafael.gasperi
			 * 			 
			 * @date	28/04/2011
			 */

			ResourcePathProvider();


			
			static ResourcePathProvider * singleton_instance; ///< The singleton instance
		};
	};
};




	
#endif // _RESOURCE_PATH_PROVIDER_H_
