/**
 * @file InstallMachine.cxx
 * @brief Body class install machine
 * @date 18/10/2011
 * @author Yadickson Soto
 */

#include "InstallMachine.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Runtime/Environment/EnvironmentBuilder.hxx>
#include <Security/SecretKey.h>
#include <glibmm.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Security;

ISMTTLog* InstallMachine::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.InstallMachine",GETTEXT_PACKAGE);

InstallMachine::InstallMachine(SaesDirectories * saesDir, SaesInstallDirectories * installDir)
: saesDir(saesDir), installDir(installDir)
{

}

InstallMachine::~InstallMachine()
{

}

bool InstallMachine::authentication(
		std::string & center,
		std::string & password,
		bool centerCaseSensitive,
		ElectoralConfiguration * electoralConfiguration)
{
	bool validate = false;

	bool isInstall;

	std::string folder;
	std::string programUnit;

	isInstall = VotingCentersWrapper::getInstance()->isInstall();

	if (!isInstall)
	{
		std::list< VotingCenter > & votingCenters (VotingCentersWrapper::getInstance()->getVotingCenters());
		std::list< VotingCenter >::iterator it;

        for (it = votingCenters.begin();
             it != votingCenters.end();
             it++)
        {
        	std::string interCenter = (*it).getCode();

        	if (!centerCaseSensitive)
        	{
            	Glib::ustring ss;
            	ss = (*it).getCode();
            	interCenter = ss.lowercase();
            	ss = center;
            	center = ss.lowercase();
        	}

            if (interCenter == center)
            {
            	votingCenter = (*it);
                folder = (*it).getFolder_name();
                programUnit = ((*it).getProgram_unit() != NULL ? (*it).getProgram_unit().get() : "");
                break;
            }
        }
	}
	else
	{
		VotingCentersWrapper::getInstance()->getInstallationVotingCenter(votingCenter);
		folder = votingCenter.getFolder_name();
		programUnit = (votingCenter.getProgram_unit() != NULL ? votingCenter.getProgram_unit().get() : "");
	}

    bool secretKeyEncrypted = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getSecretKeyEncrypted();

    if (!secretKeyEncrypted && password != folder && password != "AZERTY")
    {
        password = "";
    }

	if (!folder.empty() && !password.empty())
	{
		if (!isInstall)
		{
			installDir->setWorkingPath(folder);
			installDir->setProgramUnitName(programUnit);

			std::string currentDirectoryPath = installDir->getBasePath();

			if(Smartmatic::System::IO::Directory::DirectoryExists(currentDirectoryPath))
			{
				logger->Debug("Load " + currentDirectoryPath);
				validate = login(installDir, password) && loadConfig(installDir, electoralConfiguration);
			}
			else
			{
				logger->Debug("ERROR - Load " + currentDirectoryPath);
			}
		}
		else
		{
			validate = login(saesDir, password) && loadConfig(saesDir, electoralConfiguration);
		}
	}

	if (validate)
	{
		logger->Debug("Login ok");
	}
	else
	{
		logger->Debug("ERROR - authentication machine");
	}

	return validate;
}


bool InstallMachine::login(SaesDirectories * dir, std::string & password)
{
	bool validate = false;
	BasePathType type = VotingCentersWrapper::getInstance()->getMasterDevice();

	try
	{
		std::string secretKeyFile = dir->getSecretKeyFileFullPath(type);
		std::string upKeyFile = dir->getUPKeyFileFullPath(type);

		if (File::canOpenFile(secretKeyFile))
		{
			logger->Debug("Open secret key file in " + secretKeyFile);
			SecretKey sk(secretKeyFile, password);
			Smartmatic::SAES::Security::Encryption::getInstance()->initCrypto(sk, Smartmatic::SAES::Security::Encryption::SECRET_KEY);
		}
		if (File::canOpenFile(upKeyFile))
		{
			logger->Debug("Open up key file in " + upKeyFile);
			SecretKey sk(upKeyFile, password);
			Smartmatic::SAES::Security::Encryption::getInstance()->initCrypto(sk, Smartmatic::SAES::Security::Encryption::UP_KEY);
		}
		validate = true;
	}
	catch (...)
	{
        logger->Debug("Error secret key in " + type);
	}

	return validate;
}


bool InstallMachine::loadConfig(
		SaesDirectories * dir,
		ElectoralConfiguration * electoralConfiguration)
{
	bool validate = false;
	BasePathType type = VotingCentersWrapper::getInstance()->getMasterDevice();

	try
	{
        electoralConfiguration->init(dir, type);
        validate = true;
	}
	catch (...)
	{
        logger->Debug("Error load config in " + type);
	}

	return validate;
}

bool InstallMachine::install()
{
	bool validate = true;

	if (!VotingCentersWrapper::getInstance()->isInstall())
	{
		EnvironmentBuilder builder;
		builder.install(installDir, saesDir);

		try
		{
			VotingCentersWrapper::getInstance()->setInstallationVotingCenter(votingCenter);
			VotingCentersWrapper::getInstance()->persistVotingCenters();
		}
		catch(...)
		{
			logger->Debug("FATAL - persistVotingCenters");
			validate = false;
		}
	}

	return validate;
}
