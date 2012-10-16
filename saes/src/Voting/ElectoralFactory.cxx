/**
 * @file ElectoralFactory.cxx
 * @brief Body class ElectoralFactory
 */

#include "ElectoralFactory.hxx"
#include <stdio.h>
#include <System/IO/File.h>
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::Log;

ISMTTLog* ElectoralFactory::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.ElectoralFactory",GETTEXT_PACKAGE);

ElectionWrapper * ElectoralFactory::getElection (std::istream & xml) throw (ElectionException)
{
    ElectionWrapper * election = NULL;

    try
    {
       std::auto_ptr < Election::Election > p ( parseElection( xml, ElectionTypes::Flags::dont_validate ) );
       election = new ElectionWrapper( *p.get() );
    }
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
        std::stringstream ss;
		ss<< "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e;
		logger->Debug(ss.str());
		throw ElectionException(_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorXMLSchema"),
				N_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorXMLSchema"),
				logger);
	}
    catch (std::exception & ex)
    {
        std::stringstream ss;
		ss<< "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << ex.what();
		logger->Debug(ss.str());
	 	throw ElectionException( _("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"), 
	 			N_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"),
	 			logger);
    }
    catch (...)
    {
        std::stringstream ss;
		ss<< "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__;
		logger->Debug(ss.str());
       throw ElectionException( _("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"), 
    		   N_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"),
    		   logger);
	}
    return election;
}

VotingDeviceWrapper * ElectoralFactory::getVotingDevice (std::istream & xml) throw (VotingDeviceException)
{
    VotingDeviceWrapper * votingDevice = NULL;

    try
    {
       std::auto_ptr < VotingDevice::Voting_devices > p ( parseVoting_devices( xml, VotingDeviceTypes::Flags::dont_validate ) );
       votingDevice = new VotingDeviceWrapper( *p.get() );
    }
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
        std::stringstream ss;
		ss<< "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e;
		logger->Debug(ss.str());
       throw VotingDeviceException( _("Smartmatic.SAES.Voting.ElectoralFactory.ErrorXMLSchema"),
    		   N_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorXMLSchema"),
    		   logger );
	}
    catch (std::exception & ex)
    {
        std::stringstream ss;
		ss<< "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << ex.what();
		logger->Debug(ss.str());
		throw VotingDeviceException( _("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"),
				N_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"),
				logger);
    }
    catch (...)
    {
        std::stringstream ss;
		ss<< "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ ;
		logger->Debug(ss.str());
		throw VotingDeviceException( _("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"),
				N_("Smartmatic.SAES.Voting.ElectoralFactory.ErrorParseXml"),
				logger);
    }

    return votingDevice;
}
