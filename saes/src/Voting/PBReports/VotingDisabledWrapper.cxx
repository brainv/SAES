/**
 * @file VotingDisabledWrapper.cxx
 * @brief Body class voting disabled wrapper
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#include "VotingDisabledWrapper.hxx"
#include "System/guid-class.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Security/Encryption.hxx>
#include <sstream>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Runtime/Environment/saes-directories.h>

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

using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* VotingDisabledWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper",GETTEXT_PACKAGE);

VotingDisabledWrapper::VotingDisabledWrapper()
{
	votingDisabledInformation = NULL;
}

VotingDisabledWrapper::~VotingDisabledWrapper()
{
}

void VotingDisabledWrapper::persistence()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    serializeVotingDisabledInformation(os,*votingDisabledInformation, map, "UTF-8");

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getVotingDisabledFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getVotingDisabledFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
        Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
        		Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileFlash, fileDom);
    }

    logger->Audit("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper.PersistenceVotingDisabled");
}

bool VotingDisabledWrapper::load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
    	votingDisabledInformation = new VotingDisabledInformation();
    	VotingDisabledInformation::VotingDisabledSequence seq;
    	votingDisabledInformation->setVotingDisabled(seq);
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            votingDisabledInformation = new VotingDisabledInformation(*(parseVotingDisabledInformation(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::cerr << "FATAL - " << __func__ << e << std::endl;
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}


bool VotingDisabledWrapper::init ()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return load(directories.getVotingDisabledFileFullPath());
}

void VotingDisabledWrapper::addVotingDisabled(VotingDisabled & votingDisabled)
{
	GuidClass guidC = GuidClass::NewGuid();
	votingDisabled.setCustom_code((std::string)guidC.ToString());

	Glib::TimeVal time;
	time.assign_current_time();
	std::string now = time.as_iso8601();

	votingDisabled.setCreate_date(now);

	votingDisabledInformation->getVotingDisabled().push_back(votingDisabled);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper.AddVotingDisabled"));
}

void VotingDisabledWrapper::removeVotingDisabled(std::string customCode)
{
	for (VotingDisabledInformation::VotingDisabledIterator
         it (votingDisabledInformation->getVotingDisabled().begin ());
         it != votingDisabledInformation->getVotingDisabled().end ();
         ++it)
    {
		if ( customCode == (*it).getCustom_code() )
		{
			votingDisabledInformation->getVotingDisabled().erase(it);
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper.RemoveVotingDisabled"));
			break;
		}
    }
}

bool VotingDisabledWrapper::modifyVotingDisabled(VotingDisabled & votingDisabled)
{
	bool modify = false;

	for (VotingDisabledInformation::VotingDisabledIterator
         it (votingDisabledInformation->getVotingDisabled().begin ());
         it != votingDisabledInformation->getVotingDisabled().end ();
         ++it)
    {
		if ( votingDisabled.getCustom_code() == (*it).getCustom_code())
		{
			votingDisabled.setCreate_date((*it).getCreate_date());
			*it = votingDisabled;
			logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.VotingDisabledWrapper.ModifyVotingDisabled"));
			modify = true;
			break;
		}
    }

	if (!modify)
	{
		addVotingDisabled(votingDisabled);
	}

	return modify;
}

VotingDisabled VotingDisabledWrapper::getVotingDisabled(std::string customCode)
{
	VotingDisabled votingDisabled;

	for (VotingDisabledInformation::VotingDisabledIterator
         it (votingDisabledInformation->getVotingDisabled().begin ());
         it != votingDisabledInformation->getVotingDisabled().end ();
         ++it)
    {
		if ( customCode == (*it).getCustom_code())
		{
			votingDisabled = *it;
		}
    }

	return votingDisabled;
}

VotingDisabledInformation VotingDisabledWrapper::getVotingDisabledInformation()
{
	return *votingDisabledInformation;
}

void VotingDisabledWrapper::dispose ()
{
	if (votingDisabledInformation != NULL)
	{
		delete votingDisabledInformation;
		votingDisabledInformation = NULL;
	}
}
