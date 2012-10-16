/**
 * @file EnvironmentBuilder.hxx
 * @brief Header class environment build
 * @date 15/11/2011
 * @author Yadickson Soto
 */

#ifndef ENVIRONMENTBUILDER_HXX_
#define ENVIRONMENTBUILDER_HXX_

#include <Runtime/Environment/saes-directories.h>
#include <Runtime/Environment/SaesInstallDirectories.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
				class EnvironmentBuilder
				{
				public:
					EnvironmentBuilder();
					virtual ~EnvironmentBuilder();
					virtual bool install(
							SaesInstallDirectories * orig,
							SaesDirectories * dest);

				protected:

					void getFileList ( SaesDirectories * dir, std::vector <std::string> & list );
					void getFolderList ( SaesDirectories * dir, std::vector <std::string> & list );

				private:
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
            }
        }
    }
}

#endif /* ENVIRONMENTBUILDER_HXX_ */
