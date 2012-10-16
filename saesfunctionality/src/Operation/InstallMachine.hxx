/**
 * @file InstallMachine.hxx
 * @brief Header class install machine
 * @date 18/10/2011
 * @author Yadickson Soto
 */

#ifndef INSTALLMACHINE_HXX_
#define INSTALLMACHINE_HXX_

#include <Voting/VotingCenters/voting-centers-schema.hxx>
#include <Runtime/Environment/SaesInstallDirectories.hxx>
#include <Voting/ElectoralConfiguration.hxx>

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
			class InstallMachine
			{
			public:
				InstallMachine(
						Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDir,
						Smartmatic::SAES::Runtime::Environment::SaesInstallDirectories * installDir);
				virtual ~InstallMachine();

				/**
				 * @brief Method authentication machine
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 18/10/2011
				 * @param center
				 * @param password
				 * @return true is success
				 */
				bool authentication(
						std::string & center,
						std::string & password,
						bool centerCaseSensitive,
						Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

				bool install();

			private:

				bool login(
						Smartmatic::SAES::Runtime::Environment::SaesDirectories * dir,
						std::string & password);

				bool loadConfig(
						Smartmatic::SAES::Runtime::Environment::SaesDirectories * dir,
						Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);

				Smartmatic::SAES::Runtime::Environment::SaesDirectories * saesDir;
				Smartmatic::SAES::Runtime::Environment::SaesInstallDirectories * installDir;
				Smartmatic::SAES::Voting::VotingCenters::VotingCenter votingCenter;
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}

#endif /* INSTALLMACHINE_HXX_ */
