/**
 * @file SaesProgramUnitDirectory.hxx
 * @brief Header class saes directories for up structure
 * @date 14/11/2011
 * @author Yadickson Soto
 */

#ifndef SAESPROGRAMUNITDIRECTORIES_HXX_
#define SAESPROGRAMUNITDIRECTORIES_HXX_

#include <Runtime/Environment/SaesInstallDirectories.hxx>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
				/**
				 * @class SaesProgramUnitDirectory
				 * @brief Class saes directories for up structure
				 * @date 14/11/2011
				 * @author Yadickson Soto
				 * @see SaesInstallDirectories
				 */
            	class SaesProgramUnitDirectories : public SaesInstallDirectories
				{
				public:
    				/**
    				 * @brief Class constructor
    				 * @date 14/11/2011
    				 * @author Yadickson Soto
    				 */
					SaesProgramUnitDirectories();

    				/**
    				 * @brief Class destroy
    				 * @date 14/11/2011
    				 * @author Yadickson Soto
    				 */
					virtual ~SaesProgramUnitDirectories();

    				/**
    				 * @brief Method getter working directory folder name
    				 * @return working directory folder name
    				 * @date 14/11/2011
    				 * @author Yadickson Soto
    				 */
					virtual std::string getWorkingDirectoryFolderName();

    				/**
    				 * @brief Method getter election file full path
    				 * @param type base path type
    				 * @return election file full path
    				 * @date 14/11/2011
    				 * @author Yadickson Soto
    				 */
					virtual std::string getElectionFileFullPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
                            Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM );

				private:

    				/**
    				 * @brief Method getter program unit name path
    				 * @return program unit name path
    				 * @date 14/11/2011
    				 * @author Yadickson Soto
    				 */
					std::string getProgramUnitNamePath();

    				/**
    				 * @brief Method getter program unit path
    				 * @param type base path type
    				 * @return program unit path
    				 * @date 14/11/2011
    				 * @author Yadickson Soto
    				 */
					std::string getProgramUnitPath( Smartmatic::SAES::Common::Configuration::BasePathType type =
					        Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM );
				};
            }
        }
    }
}
#endif /* SAESPROGRAMUNITDIRECTORIES_HXX_ */
