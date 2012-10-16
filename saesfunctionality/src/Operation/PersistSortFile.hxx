/**
 * @file PersistSort.hxx
 * @brief Header class persist votes sort
 * @date 24/08/2011
 * @author Yadickson Soto
 */

#ifndef PERSISTSORTFILE_HXX_
#define PERSISTSORTFILE_HXX_

#include <iostream>
#include <list>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace Operation
		{
			/**
			 * @class PersistSort
			 * @brief Class persist votes sort
			 * @date 24/08/2011
			 * @author Yadickson Soto
			 */
			class PersistSortFile
			{
			public:
				/**
				 * @brief Class constructor
				 * @param type basse path type
				 * @param marfFile mark file name
				 * @param sortFile flag config sort files
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				PersistSortFile(Smartmatic::SAES::Common::Configuration::BasePathType type,
						std::string markFile,
						bool sortFile);

				/**
				 * @brief Class destroy
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				~PersistSortFile();

				/**
				 * @brief Method getter folder votes name
				 * @return folder name full path
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				std::string getFolder();

				/**
				 * @brief Method getter mark file name
				 * @return mark file name full path
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				std::string getMarkFile();

				/**
				 * @brief Method getter is sort file votes
				 * @return true is sort file votes
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				bool isSortFile();

				/**
				 * @brief Method update date for votes
				 * @param date new date config
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				void updateDate(std::string date);

				/**
				 * @brief Method add new file to sort
				 * @param file new file to sort
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				void addFile(std::string file);

				/**
				 * @brief Method persist file list
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				void persistFiles();

				/**
				 * @brief Method recover votes
				 * @return true is validate recover votes
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				bool recoverVotes();

			private:

				/**
				 * @brief Method getter file list to sort
				 * @return string file list to sort, separate with space " "
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				std::string getListFile();

				/**
				 * @brief Method getter only tmp vote files
				 * @param listTmp list vote files
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				void getVoteFile(std::list <std::string> & listTmp);

				/**
				 * @brief Method validate vote files
				 * @param listTmp list vote files
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				void validateVotes(std::list <std::string> & listTmp);

				/**
				 * @brief Method rename valid vote files
				 * @param listTmp list vote files
				 *
				 * @date 24/08/2011
				 * @author Yadickson Soto
				 */
				void renameVotes(std::list <std::string> & listTmp);

				Smartmatic::SAES::Common::Configuration::BasePathType type; ///< base path type
				std::string markFile; ///< mark file name
				std::string date; ///< date for votes

				bool sortFile; ///< flag sort files
				std::list <std::string> files; ///< file list to sort
				Smartmatic::SAES::Runtime::Environment::SaesDirectories directories; ///< directories
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* PERSISTSORTFILE_HXX_ */
