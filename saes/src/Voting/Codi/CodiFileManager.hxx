/**
 * @file CodiFileManager.hxx
 * @brief Header codi file manager
 * @date 14/02/2012
 * @author Yadickson Soto
 */

#ifndef CODIFILEMANAGER_HXX_
#define CODIFILEMANAGER_HXX_

#include <string>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace Voting
		{
			namespace Codi
			{
				/**
				 * @class CodiFileManager
				 * @brief Class codi file manager
				 * @date 14/02/2012
				 * @author Yadickson Soto
				 */
				class CodiFileManager
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 14/02/2012
					 * @author Yadickson Soto
					 */
					CodiFileManager();

					/**
					 * @brief Method getter input file name by contest code
					 * @param customCode custom code
					 * @param file result file name
					 * @date 22/02/2012
					 * @author Yadickson Soto
					 */
					static void getInputContestFileName(std::string customCode, std::string & file);

					/**
					 * @brief Method getter output file name by contest code
					 * @param customCode custom code
					 * @param file result file name
					 * @param codiMachine codi machine
					 * @param customniscode custom niscode
					 * @date 22/02/2012
					 * @author Yadickson Soto
					 */
					static void getOutputContestFileName(
							std::string customCode,
							std::string & file,
							std::string codiMachine,
							std::string codiVotingType,
							std::string customniscode);

					/**
					 * @brief Class destroy
					 * @date 14/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~CodiFileManager();

				private:

					enum CodiType
					{
						 CK		///< (CK) Chambre
						,SE		///< (SE) Sénat
						,EU		///< (EU) Parlement européen
						,VL		///< (VL) Parlement flamand
						,WL		///< (WL) Parlement wallon
						,BR		///< (BR) Parlement de la Région de Bruxelles-Capitale
						,DE		///< (DE) Parlement de la Communauté germanophone
						,PR		///< (PR) Conseils provinciaux
						,CG		///< (CG) Conseils communaux
						,DI		///< (DI) Conseils de district (à Anvers)
						,CS		///< (CS) Conseils de CPAS

					}; ///< Codi type

					/**
					 * @brief Method getter type file
					 * @param electionType election type
					 * @param files type files
					 * @param typeFile result type file
					 * @date 14/02/2012
					 * @author Yadickson Soto
					 */
					static void getTypeFile(std::string electionType, const char * files[], std::string & typeFile);

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* CODIFILEMANAGER_HXX_ */
