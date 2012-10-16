/*
 * SaesInstallDirectories.hxx
 *
 *  Created on: 14/11/2011
 *      Author: soto
 */

#ifndef SAESINSTALLDIRECTORIES_HXX_
#define SAESINSTALLDIRECTORIES_HXX_

#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
				class SaesInstallDirectories : public SaesDirectories
				{
				public:

					SaesInstallDirectories();
					virtual ~SaesInstallDirectories();

					virtual void setWorkingPath( std::string workingPath );
					virtual void setProgramUnitName( std::string programUnitName );

				protected:
					std::string workingPath;
					std::string programUnitName;
				};
            }
        }
    }
}

#endif /* SAESINSTALLDIRECTORIES_HXX_ */
