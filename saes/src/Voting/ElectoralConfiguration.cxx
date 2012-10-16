/**
 * @file ElectoralConfiguration.cxx
 * @brief Body class electoral configuration
 */

#include "ElectoralConfiguration.hxx"
#include <Log/SMTTLogManager.h>
#include <Resources/election-string-resources-manager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Configuration/saes-language-controller.h>
#include <System/Compression/compression-class.h>
#include <Security/XmlSecResource.hxx>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Voting/Codi/CodiFileManager.hxx>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <sstream>

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

using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Compression;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* ElectoralConfiguration::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.ElectoralConfiguration",GETTEXT_PACKAGE);

ElectoralConfiguration::ElectoralConfiguration ()
{
    this->election = NULL;
	this->voteRecovery = NULL;
    this->votingDevice = NULL;
    this->maxBallotOptionByVote = 0;
    this->maxContestByBlankVote = 0;
    this->maxContestByVote = 0;
    this->maxCustomAttributeByVote = 0;
    this->reload = true;
    this->loadData = false;
}

ElectoralConfiguration::~ElectoralConfiguration ()
{
    dispose();
}

void ElectoralConfiguration::init (Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories, BasePathType type)
    throw (ElectionException, VotingDeviceException, CryptoException, SignedException, FileSystemException)
{
	if (!reload) return;

	this->directories = directories;

	dispose();

	logger->Debug("Init class");

    if (!Smartmatic::SAES::Security::XmlSecResource::getInstance()->validate(directories, type))
    {
        throw Smartmatic::System::Exception::FileSystemException(
                _("Smartmatic.SAES.Voting.ElectoralConfiguration.ErrorSignedElectoralResources"),
                N_("Smartmatic.SAES.Voting.ElectoralConfiguration.ErrorSignedElectoralResources"),
                logger);
    }

    std::string strVotingDevice;
    std::string fileVotingDevice = directories->getVotingDeviceFileFullPath(type);

    Smartmatic::System::SafeBuffer bufferVotingDevice;

    logger->Debug("Open xml file " + fileVotingDevice);

    Smartmatic::SAES::Security::Encryption::getInstance()->decryptoFileToBuffer(fileVotingDevice,
    		bufferVotingDevice,
            Smartmatic::SAES::Security::Encryption::EXTERNAL_FILE);

    if (SAESCommonConfigurationManager::Current()->isCompressVotingDevices())
    {
        std::stringstream ssc;
        ssc << "Decompress xml data of file " << fileVotingDevice;
        logger->Debug(ssc.str());

        Smartmatic::System::SafeBuffer inflate;
        CompressionClass::Inflate(bufferVotingDevice, inflate);

        if (inflate.GetSize() > 0)
        {
        	strVotingDevice.assign((char *)inflate.GetData(), inflate.GetSize());
        	strVotingDevice.resize(inflate.GetSize());
        }
        else
        {
        	logger->Debug("File " + fileVotingDevice + " not compress.");
        }
    }
    else if (bufferVotingDevice.GetSize() > 0)
    {
        strVotingDevice.assign((char *)bufferVotingDevice.GetData(), bufferVotingDevice.GetSize());
        strVotingDevice.resize(bufferVotingDevice.GetSize());
    }
    else
    {
    	logger->Debug("Error open xml file " + fileVotingDevice);
    }

    std::istringstream istrVotingDevice(strVotingDevice);
    this->votingDevice = ElectoralFactory::getVotingDevice(istrVotingDevice);

    std::string protectionKey = votingDevice->getFirstVotingDevice().getKeys().getProtection_key();

    logger->Debug("Protection Key = " + protectionKey);

    Smartmatic::SAES::Security::Encryption::getInstance()->initSigned(directories, protectionKey);
    Smartmatic::SAES::Security::Encryption::getInstance()->validateSignedString(strVotingDevice,
            Smartmatic::SAES::Security::Encryption::EXTERNAL_FILE);

    std::string fileElectoral = directories->getElectionFileFullPath(type);
    std::string electoralData = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(fileElectoral,
            Smartmatic::SAES::Security::Encryption::EXTERNAL_FILE,
            Smartmatic::SAES::Security::Encryption::UP_KEY,
            SAESCommonConfigurationManager::Current()->isCompressElection());
    std::istringstream istrElectoral (electoralData);

    this->election = ElectoralFactory::getElection(istrElectoral);
	this->voteRecovery = new Smartmatic::SAES::Voting::Vote::VoteRecovery (this);
    Smartmatic::SAES::Resources::ElectionStringResourcesManager::Current()->init(directories, type);
}

void ElectoralConfiguration::dispose ()
{
	logger->Debug("Dispose class");

    if (election != NULL)
    {
        delete election;
        election = NULL;
    }
    if (votingDevice != NULL)
    {
        delete votingDevice;
        votingDevice = NULL;
    }
	if (voteRecovery != NULL)
    {
        delete voteRecovery;
        voteRecovery = NULL;
    }

	mapBallotOptionsListByContestParty.clear();
	mapBallotOptionsPartyByContest.clear();
	mapBallotOptionsPrincipalByContestParty.clear();
	mapBallotOptionsStandInByContestParty.clear();
	mapContestCode.clear();
	mapContestGroupByCode.clear();
	mapContestParty.clear();
	mapEligibleOptionsList.clear();
	mapEligibleOptionsListByContest.clear();
	mapEligibleOptionsListByContestParty.clear();
	mapEligibleOptionsListByParty.clear();
	mapEligibleOptionsPrincipal.clear();
	mapEligibleOptionsPrincipalByContest.clear();
	mapEligibleOptionsPrincipalByContestParty.clear();
	mapEligibleOptionsPrincipalByParty.clear();
	mapEligibleOptionsStandIn.clear();
	mapEligibleOptionsStandInByContest.clear();
	mapEligibleOptionsStandInByContestParty.clear();
	mapEligibleOptionsStandInByParty.clear();
	mapListContestByContestGroup.clear();

	allCodeBallot.clear();
	partyCodeByBallotOptionCode.clear();

	ballotList.clear();
	contestGroupList.clear();
	contestParty.clear();
	eligibleOptionByBallotOptionCodeMap.clear();
	eligibleOptionByEligibleOptionCodeMap.clear();
	listContest.clear();
	listContestCode.clear();
	listLVG.clear();

	maxBallotOptionByContest.clear();
	maxListBallotOptionByContestParty.clear();
	maxPrincipalBallotOptionByContestParty.clear();
	maxStandInBallotOptionByContestParty.clear();

	reload = true;
	loadData = false;
}

Election::ElectionWrapper * ElectoralConfiguration::getElection () throw (ElectionException)
{
    if (election == NULL)
    {
        throw ElectionException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.ObjectElectionNull"),
        		N_("Smartmatic.SAES.Voting.ElectoralConfiguration.ObjectElectionNull"), logger);
    }

    return election;
}

VotingDevice::VotingDeviceWrapper * ElectoralConfiguration::getVotingDevice () throw (VotingDeviceException)
{
    if (votingDevice == NULL)
    {
        throw VotingDeviceException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.ObjectVotingDeviceNull"),
        		N_("Smartmatic.SAES.Voting.ElectoralConfiguration.ObjectVotingDeviceNull"), logger);
    }

    return votingDevice;
}

std::list <std::string> ElectoralConfiguration::getLanguageListFullName(bool onlyDefaultTrue, bool onlyLanguage)
{
    std::list <std::string> list;

    std::list <Smartmatic::SAES::Voting::Election::Language> languages = getLanguageList(onlyDefaultTrue);
    std::list<Smartmatic::SAES::Voting::Election::Language>::iterator it;

    for(it = languages.begin();
        it != languages.end();
        it++)
    {
      Glib::ustring lang = (*it).getLanguage();
      Glib::ustring country = (*it).getCountry();

      if (country.length() == 0)
      {
          country = lang;
      }

      if (!onlyLanguage)
      {
    	  lang = lang.lowercase();
      }
      else
      {
    	  lang = lang.uppercase();
      }

      country = country.uppercase();

      if(country.empty())
          list.push_back(lang);
      else if (!onlyLanguage)
          list.push_back(lang + "_" + country);
      else
    	  list.push_back("_" + lang);
    }

    return list;
}

std::list <Smartmatic::SAES::Voting::Election::Language> ElectoralConfiguration::getLanguageList(bool onlyDefaultTrue)
{
	std::list <Smartmatic::SAES::Voting::Election::Language> languages;

	Smartmatic::SAES::Voting::Election::Languages::LanguageSequence & sequence (getLanguages().getLanguage());
	Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

	for (it = sequence.begin();
			it != sequence.end();
			it++)
	{
		if( (*it).getIs_default() || !onlyDefaultTrue)
		{
			languages.push_back(*it);
		}
	}

    return languages;
}

Smartmatic::SAES::Voting::Election::Languages & ElectoralConfiguration::getLanguages ()
{
	if ( votingDevice->IsLanguagesPresent () )
	{
		return votingDevice->getLanguages ();
	}

	return election->getLanguages ();
}

Smartmatic::SAES::Voting::Vote::VoteRecovery * ElectoralConfiguration::getVoteRecovery() throw (VoteRecoveryException)
{
    if (voteRecovery == NULL)
    {
        throw VoteRecoveryException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.ObjectVoteRecoveryNull"),
        		N_("Smartmatic.SAES.Voting.ElectoralConfiguration.ObjectVoteRecoveryNull"), logger);
    }

    return voteRecovery;
}

void ElectoralConfiguration::createMap()
	throw (ElectionException, VotingDeviceException)
{
	logger->Debug("Start create map");

	Smartmatic::SAES::Voting::Election::Ballots ballots = election->getBallots();
	Smartmatic::SAES::Voting::Election::Ballots::BallotIterator ballotIterator;

	for(ballotIterator = ballots.getBallot().begin(); ballotIterator != ballots.getBallot().end(); ballotIterator++)
	{
		Smartmatic::SAES::Voting::Election::Ballot_cards::Ballot_cardIterator ballotCardIterator;

		for(ballotCardIterator = ballotIterator->getBallot_cards().getBallot_card().begin();
				ballotCardIterator != ballotIterator->getBallot_cards().getBallot_card().end();
				ballotCardIterator++)
		{
			Smartmatic::SAES::Voting::Election::Contests::ContestIterator contestIterator;

			for(contestIterator = ballotCardIterator->getContests().getContest().begin();
					contestIterator != ballotCardIterator->getContests().getContest().end();
					contestIterator++)
			{
				Smartmatic::SAES::Voting::Election::Contest contest = *contestIterator;

				if (!isContestValidate(contest))
				{
					continue;
				}

				listContest.push_back(contest);
				listContestCode.push_back(contest.getCode());
				ballotList.push_back((*ballotIterator));

				Smartmatic::SAES::Voting::Election::Eligibles_options::Eligible_optionIterator eligibleOptionIterator;

				for(eligibleOptionIterator = contestIterator->getEligibles_options().getEligible_option().begin();
						eligibleOptionIterator != contestIterator->getEligibles_options().getEligible_option().end();
						eligibleOptionIterator++)
				{
					Smartmatic::SAES::Voting::Election::Eligible_option eligibleOption = *eligibleOptionIterator;

					(eligibleOptionByEligibleOptionCodeMap[contest.getCode()])[eligibleOption.getCode()] = eligibleOption;

					Smartmatic::SAES::Voting::Election::Ballot_options::Ballot_optionIterator ballotOptionIterator;

					for(ballotOptionIterator = eligibleOption.getBallot_options().getBallot_option().begin();
							ballotOptionIterator != eligibleOption.getBallot_options().getBallot_option().end();
							ballotOptionIterator++)
					{
						(eligibleOptionByBallotOptionCodeMap[contest.getCode()])[ballotOptionIterator->getCode()] = eligibleOption;
					}
				}
			}
		}
	}

	reduceElectionContests();

	std::list < Smartmatic::SAES::Voting::Election::Contest >::iterator itcontest;

	for ( itcontest = listContest.begin();
			itcontest != listContest.end();
			itcontest++)
	{
	   std::string contestCode = (*itcontest).getCode();

	   mapContestCode[contestCode] = (*itcontest);

	   std::list < Smartmatic::SAES::Voting::Election::Ballot_option > listParties;
	   getElection()->getBallotOptionPartyByContest ( (*itcontest), listParties, Smartmatic::SAES::Voting::Election::Category::ELECTION_PRINCIPAL );
	   mapBallotOptionsPartyByContest[contestCode] = listParties;

	   std::list < Smartmatic::SAES::Voting::Election::Ballot_option > listBallotOptionPartyList;
	   std::list < Smartmatic::SAES::Voting::Election::Ballot_option > listBallotOptionPrincipal;
	   std::list < Smartmatic::SAES::Voting::Election::Ballot_option > listBallotOptionStandIn;

	   getElection()->getBallotOptionsListByContest((*itcontest), listBallotOptionPartyList, true);
	   getElection()->getBallotOptionsByContest((*itcontest), listBallotOptionPrincipal, Smartmatic::SAES::Voting::Election::Category::ELECTION_PRINCIPAL, true);
	   getElection()->getBallotOptionsByContest((*itcontest), listBallotOptionStandIn, Smartmatic::SAES::Voting::Election::Category::ELECTION_STAND_IN, true);

	   mapEligibleOptionsListByContest[contestCode] = listBallotOptionPartyList;
	   mapEligibleOptionsPrincipalByContest[contestCode] = listBallotOptionPrincipal;
	   mapEligibleOptionsStandInByContest[contestCode] = listBallotOptionStandIn;

	   std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > mapBallotOptionPartyList;
	   std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > mapBallotOptionPrincipal;
	   std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > mapBallotOptionStandIn;

	   getElection()->getMapBallotOptionsListByContest((*itcontest), mapBallotOptionPartyList);
	   getElection()->getMapBallotOptionsByContest((*itcontest), mapBallotOptionPrincipal, Smartmatic::SAES::Voting::Election::Category::ELECTION_PRINCIPAL);
	   getElection()->getMapBallotOptionsByContest((*itcontest), mapBallotOptionStandIn, Smartmatic::SAES::Voting::Election::Category::ELECTION_STAND_IN);

	   mapEligibleOptionsList[contestCode] = mapBallotOptionPartyList;
	   mapEligibleOptionsPrincipal[contestCode] = mapBallotOptionPrincipal;
	   mapEligibleOptionsStandIn[contestCode] = mapBallotOptionStandIn;
	}

	std::list < std::string >::iterator it;
	maxPartiesByAllContest = 0;

	for ( it = listContestCode.begin();
		 it != listContestCode.end();
		 it++)
	{
	   std::string contestCode = (*it);
	   std::list < Smartmatic::SAES::Voting::Election::Party > listParty;

	   getElection()->getPartysByContestCode(contestCode, listParty);

	   mapContestParty[contestCode] = listParty;

	   if (maxPartiesByAllContest < listParty.size())
	   {
		   maxPartiesByAllContest = listParty.size();
	   }
	}

	for ( itcontest = listContest.begin();
			itcontest != listContest.end();
			itcontest++)
	{
		std::string contestCode = (*itcontest).getCode();

		std::list < Smartmatic::SAES::Voting::Election::Party > & listParty (mapContestParty[contestCode]);
		std::list < Smartmatic::SAES::Voting::Election::Party >::iterator itp;

		for (itp = listParty.begin(); itp != listParty.end(); itp++)
		{
			std::string partyCode = (*itp).getCode();

			std::list < Smartmatic::SAES::Voting::Election::Ballot_option > list;
			std::list < Smartmatic::SAES::Voting::Election::Ballot_option > listP;
			std::list < Smartmatic::SAES::Voting::Election::Ballot_option > listS;

			getElection()->getBallotOptionsListByContestParty((*itcontest), (*itp), list);
			getElection()->getBallotOptionsByContestParty((*itcontest), (*itp), listP, Smartmatic::SAES::Voting::Election::Category::ELECTION_PRINCIPAL);
			getElection()->getBallotOptionsByContestParty((*itcontest), (*itp), listS, Smartmatic::SAES::Voting::Election::Category::ELECTION_STAND_IN);

			mapBallotOptionsListByContestParty[contestCode][partyCode] = list;
			mapBallotOptionsPrincipalByContestParty[contestCode][partyCode] = listP;
			mapBallotOptionsStandInByContestParty[contestCode][partyCode] = listS;

			std::list < std::string > listCode;
			std::list < std::string >::iterator itCode;
			getElection()->getAllBallotOptionsListCodeByContestParty((*itcontest), (*itp), listCode);

			allCodeBallot[contestCode][partyCode] = listCode;

			for (itCode = listCode.begin();
					itCode != listCode.end();
					itCode++)
			{
				partyCodeByBallotOptionCode[*itCode] = partyCode;
			}

			std::list < Smartmatic::SAES::Voting::Election::Eligible_option > listE;
			std::list < Smartmatic::SAES::Voting::Election::Eligible_option > listEP;
			std::list < Smartmatic::SAES::Voting::Election::Eligible_option > listES;

			getElection()->fillAllEligibleOptionsByContestParty( (*itcontest), (*itp), listE, listEP, listES);

			mapEligibleOptionsListByContestParty[contestCode][partyCode] = listE;
			mapEligibleOptionsPrincipalByContestParty[contestCode][partyCode] = listEP;
			mapEligibleOptionsStandInByContestParty[contestCode][partyCode] = listES;
		}
	}

	std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group >::iterator itlvg;
	Smartmatic::SAES::Voting::VotingDevice::Voting_device vd = getVotingDevice()->getFirstVotingDevice();
	getVotingDevice()->getLogicalVoterGroupList(vd, listLVG);

	for (itlvg = listLVG.begin(); itlvg != listLVG.end(); itlvg++)
	{
		std::list < Smartmatic::SAES::Voting::Election::Contest > listC;
		std::string contestGroupCode = getVotingDevice()->getLogicalVoterGroup( vd, (*itlvg).getCode()).getContest_group_code ();

		getElection()->getContestByContestGroup(contestGroupCode, listC);
		mapListContestByContestGroup[contestGroupCode] = listC;

		Smartmatic::SAES::Voting::Election::Contest_group contestGroup = getElection()->getContestGroup(contestGroupCode);
		contestGroupList.push_back(contestGroup);
		mapContestGroupByCode[contestGroupCode] = contestGroup;
	}

	reduceElectionContestGroups();

	getVotingDevice()->getRegionCategoryList(regionCategoryList);

	verifyIntegrityData();

	logger->Debug("End create map");
}

void ElectoralConfiguration::calculateMax ()
	throw (ElectionException, VotingDeviceException)
{
	logger->Debug("Start calculate max");

	maxContestByVote = 0;
	maxBallotOptionByVote = 0;

	std::list < Smartmatic::SAES::Voting::Election::Contest >::iterator it;

	maxContestByBlankVote = getContestList().size();

	for ( it = getContestList().begin();
		 it != getContestList().end();
		 it++)
	{
	   std::string contestCode = (*it).getCode();

	   Smartmatic::SAES::Voting::Election::Party party;
	   int maxCount = getElection ()->getMaxBallotOptionsByContest( *it, party );
	   maxBallotOptionByContest[ contestCode ] = maxCount;
	   contestParty[ contestCode ] = ( party.getName() != NULL ? party.getName().get() : "none" );

	   std::list < Smartmatic::SAES::Voting::Election::Party > & partys (mapContestParty[contestCode]);
	   std::list < Smartmatic::SAES::Voting::Election::Party >::iterator itp;

	   for (itp = partys.begin();
			itp != partys.end();
			itp++)
	   {
		   std::string partyCode = (*itp).getCode();
		   int countList, countPrincipal, countStandIn;

		   getElection ()->getCountBallotOptionsByContestParty((*it), (*itp), countList, countPrincipal, countStandIn);

		   maxListBallotOptionByContestParty[ contestCode ][ partyCode ] = countList;
		   maxPrincipalBallotOptionByContestParty[ contestCode ][ partyCode ] = countPrincipal;
		   maxStandInBallotOptionByContestParty[ contestCode ][ partyCode ] = countStandIn;
	   }
	}

	std::string maxContextGroup = "none";
    std::string maxContextGroupBallotOptions = "none";

	std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group >::iterator itlvg;

	for (itlvg = listLVG.begin();
			itlvg != listLVG.end();
			itlvg++)
	{
		Smartmatic::SAES::Voting::Election::Contest_group & contestGroup ( getElection()->getContestGroup((*itlvg).getContest_group_code()) );
		Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeSequence & seq( contestGroup.getContest_code() );

		unsigned int maxContest = seq.size();

		if (maxContest > maxContestByVote)
		{
			maxContestByVote = maxContest;
			maxContextGroup = contestGroup.getCode();
		}

		unsigned int maxBallots = 0;

		Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeIterator itseq;

		for (itseq = seq.begin();
			 itseq != seq.end();
			 itseq++)
		{
			unsigned int value = maxBallotOptionByContest[(*itseq)];
			maxBallots += value;
		}

		if (maxBallots > maxBallotOptionByVote)
		{
			maxBallotOptionByVote = maxBallots;
			maxContextGroupBallotOptions = contestGroup.getCode();
		}
	}

	Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group & lvg ( getVotingDevice()->getLogicalVoterGroupByContestGroupCode(maxContextGroup) );
	maxCustomAttributeByVote = 0;

	if (lvg.getCustom_attributes() != NULL)
	{
		Smartmatic::SAES::Voting::VotingDevice::Custom_attributes & ca (lvg.getCustom_attributes().get());
		Smartmatic::SAES::Voting::VotingDevice::Custom_attributes::Custom_attributeSequence & seq (ca.getCustom_attribute());
		Smartmatic::SAES::Voting::VotingDevice::Custom_attributes::Custom_attributeIterator itCA;

		for (itCA = seq.begin();
		     itCA != seq.end();
		     itCA++)
		{
			 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
			 bool caOk = getVotingDevice()->GetCustomAttributeDefinition((*itCA).getCode(), caDefs);

			 if (caOk && caDefs.getMachine_type() == Smartmatic::SAES::Voting::VotingDevice::Machine_type::VOTING_DEVICES_VM)
			 {
				 std::string value = Smartmatic::SAES::Resources::ElectionStringResourcesManager::Current()->getResource((*itCA).getValue());

				 if (!value.empty())
				 {
					 maxCustomAttributeByVote++;
				 }
			 }
		}
	}

	logger->Debug("--------------------------------------------------------------------------------------");

	std::stringstream cc;
    cc << "MaxContestByVote : " << maxContestByVote << " in ContestGroup : " << maxContextGroup;
    logger->Debug(cc.str());

	std::stringstream ss;
    ss << "MaxBallotOptionByVote : " << maxBallotOptionByVote << " in ContestGroup : " << maxContextGroupBallotOptions;
    logger->Debug(ss.str());

	std::stringstream ca;
    ca << "MaxCustomAttributeByVote : " << maxCustomAttributeByVote;
    logger->Debug(ca.str());

    logger->Debug("--------------------------------------------------------------------------------------");

	viewInfo(maxContextGroup);
	viewInfo(maxContextGroupBallotOptions);

	logger->Debug("End calculate max");
}

void ElectoralConfiguration::reduceElectionContests ()
	throw (ElectionException, VotingDeviceException)
{
    Smartmatic::SAES::Voting::Election::Ballots & ballots ( election->getBallots() );

    std::list < Smartmatic::SAES::Voting::Election::Contest > internalList;
    internalList.insert(internalList.begin(), listContest.begin(), listContest.end());

    for (Smartmatic::SAES::Voting::Election::Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
    	Smartmatic::SAES::Voting::Election::Ballot_cards & ballotCards ( election->getBallotCards( *b ) );

       for (Smartmatic::SAES::Voting::Election::Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
    	   Smartmatic::SAES::Voting::Election::Contests & contests ( election->getContests( *bc ) );
    	   Smartmatic::SAES::Voting::Election::Contests::ContestSequence & seq (contests.getContest());
    	   Smartmatic::SAES::Voting::Election::Contests::ContestIterator cit;
    	   Smartmatic::SAES::Voting::Election::Contests::ContestIterator citAux;

          std::list < Smartmatic::SAES::Voting::Election::Contest >::iterator it;

          cit = seq.begin();
          citAux = cit;

          while (cit != seq.end())
          {
              bool found = false;

              for (it = internalList.begin();
            		  it != internalList.end();
            		  it++)
              {
            	  if ((*cit).getCode() == (*it).getCode())
            	  {
            		  found = true;
            		  internalList.erase(it);
            		  break;
            	  }
              }

              if (found)
              {
            	  cit++;
            	  citAux++;
              }
              else
              {
            	  seq.erase(cit);
            	  cit = citAux;
              }
          }
       }
    }
}

void ElectoralConfiguration::reduceElectionContestGroups ()
	throw (ElectionException, VotingDeviceException)
{
	Smartmatic::SAES::Voting::Election::Contest_groups & contestGroups ( election->getContestGroups() );
	Smartmatic::SAES::Voting::Election::Contest_groups::Contest_groupSequence & seq (contestGroups.getContest_group());
	Smartmatic::SAES::Voting::Election::Contest_groups::Contest_groupIterator cit;
	Smartmatic::SAES::Voting::Election::Contest_groups::Contest_groupIterator citAux;

    std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group > internalList;
    internalList.insert(internalList.begin(), listLVG.begin(), listLVG.end());

	std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group >::iterator it;

	cit = seq.begin();
	citAux = cit;

	while (cit != seq.end())
	{
		bool found = false;

		for (it = internalList.begin();
				it != internalList.end();
				it++)
		{
			if ((*cit).getCode() == (*it).getContest_group_code())
			{
				found = true;
				internalList.erase(it);
				break;
			}
		}

		if (found)
		{
			cit++;
			citAux++;
		}
		else
		{
			seq.erase(cit);
			cit = citAux;
		}
	}
}

void ElectoralConfiguration::verifyIntegrityData ()
	throw (ElectionException, VotingDeviceException)
{
	// Verify contest in contest groups

	Smartmatic::SAES::Voting::Election::Contest_groups & contestGroups ( election->getContestGroups() );
	Smartmatic::SAES::Voting::Election::Contest_groups::Contest_groupSequence & seq (contestGroups.getContest_group());
	Smartmatic::SAES::Voting::Election::Contest_groups::Contest_groupIterator it;

	for (it = seq.begin();
			it != seq.end();
			it++)
	{
		Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeSequence & cseq ((*it).getContest_code());
		Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeIterator cit;

		for (cit = cseq.begin();
				cit != cseq.end();
				cit++)
		{
			election->getContest(*cit);
		}
	}

	// Verify exists one voting booth

	if (getVotingDevice()->getFirstVotingDevice().getVoting_booths().getVoting_booth().size() == 0)
	{
		logger->Debug("Voting booth not found.");
		throw VotingDeviceException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.VotingBoothNotFound"),
				N_("Smartmatic.SAES.Voting.ElectoralConfiguration.VotingBoothNotFound"), logger);
	}

	// Verify exists one region hierarchies

	if (getVotingDevice()->getFirstVotingDevice().getVoting_booths().getVoting_booth()[0].getRegion_hierarchies().getRegion_hierarchy().size() == 0)
	{
		logger->Debug("Region hierarchies not found.");
		throw VotingDeviceException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.RegionHierarchiesNotFound"),
				N_("Smartmatic.SAES.Voting.ElectoralConfiguration.RegionHierarchiesNotFound"), logger);
	}

	// Verify exists one operation mode

	if (getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode().size() == 0)
	{
		logger->Debug("Operation mode not found.");
		throw VotingDeviceException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.OperationModeNotFound"),
				N_("Smartmatic.SAES.Voting.ElectoralConfiguration.OperationModeNotFound"), logger);
	}

	// Verify exists one role

	if (getVotingDevice()->getFirstVotingDevice().getOperation_modes().getOperation_mode()[0].getRoles().getRole().size() == 0)
	{
		logger->Debug("Role not found.");
		throw VotingDeviceException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.RoleNotFound"),
				N_("Smartmatic.SAES.Voting.ElectoralConfiguration.RoleNotFound"), logger);
	}

	// Verify CODI files

	if (SAESConfigurationManager::Current()->getCodiFileConfiguration().getEnableCodi())
	{
		std::list<Smartmatic::SAES::Voting::Election::Contest>::iterator cit;
		Smartmatic::SAES::Voting::Codi::CodiFileManager codiFiles;
		std::string file;

		for (cit = listContest.begin();
				cit != listContest.end();
				cit++)
		{
			codiFiles.getInputContestFileName((*cit).getCustom_code(), file);
			std::string filePath = Path::Combine(directories->getCodiFilesFolderFullPath(), file);

			if (!File::canOpenFile(filePath))
			{
				logger->Debug("Codi file " + filePath + " not found.");
				throw ElectionException(_("Smartmatic.SAES.Voting.ElectoralConfiguration.CodiFileNotFound"),
						N_("Smartmatic.SAES.Voting.ElectoralConfiguration.CodiFileNotFound"), logger);
			}
		}
	}
}

void ElectoralConfiguration::viewInfo(std::string contextGroup)
{
	try
	{
		Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group & lvg ( getVotingDevice()->getLogicalVoterGroupByContestGroupCode(contextGroup) );

		std::stringstream ss;
		ss << "ContextGroup : " << contextGroup << " - LVG : " << lvg.getCode();
		logger->Debug(ss.str());

		if (lvg.getCustom_attributes() != NULL)
		{
			Smartmatic::SAES::Voting::VotingDevice::Custom_attributes & ca (lvg.getCustom_attributes().get());
			Smartmatic::SAES::Voting::VotingDevice::Custom_attributes::Custom_attributeSequence & seq (ca.getCustom_attribute());
			Smartmatic::SAES::Voting::VotingDevice::Custom_attributes::Custom_attributeIterator itCA;

			logger->Debug("######################################################################################");

			for (itCA = seq.begin();
			     itCA != seq.end();
			     itCA++)
			{
				std::stringstream cc;
				cc << "CustomAttribute : " << (*itCA).getCode() << " - Value : " << Smartmatic::SAES::Resources::ElectionStringResourcesManager::Current()->getResource((*itCA).getValue());
				logger->Debug(cc.str());
			}

			logger->Debug("######################################################################################");
		}

		std::list <Smartmatic::SAES::Voting::Election::Contest> listC;
		std::list <Smartmatic::SAES::Voting::Election::Contest>::iterator itC;

		getElection ()->getContestOrderByContestClassByContestGroup(contextGroup, listC);

		for (itC = listC.begin();
			 itC != listC.end();
			 itC++)
		{
			std::stringstream cc;
			Smartmatic::SAES::Voting::Election::Contest_class & contestClass (getElection()->getContestClass((*itC).getContest_class_code()));
			cc << "ContestCode : " << (*itC).getCode() << " - ContestName : " << contestClass.getCustom_code() << " - Party : " << getPartyByMaxBallotOptionContestCode((*itC).getCode()) << " - BallotOptions : " << getMaxBallotOptionByContestCode((*itC).getCode());
			logger->Debug(cc.str());
		}
	}
	catch(...)
	{

	}

	logger->Debug("--------------------------------------------------------------------------------------");
}

Smartmatic::SAES::Voting::Election::Ballot_option ElectoralConfiguration::getBallotOptionListFromBallotOptionCode(std::string contestCode, std::string ballotOptionCode)
{
	Smartmatic::SAES::Voting::Election::Eligible_option & eligibleOption = (eligibleOptionByBallotOptionCodeMap[contestCode])[ballotOptionCode];

	if (eligibleOption.getParent_code() != "")
	{
		Smartmatic::SAES::Voting::Election::Eligible_option & eligibleOptionList = (eligibleOptionByEligibleOptionCodeMap[contestCode])[eligibleOption.getParent_code()];
		Smartmatic::SAES::Voting::Election::Ballot_options & ballotOptions (eligibleOptionList.getBallot_options());

		for (Smartmatic::SAES::Voting::Election::Ballot_options::Ballot_optionIterator
			b (ballotOptions.getBallot_option ().begin ());
			b != ballotOptions.getBallot_option ().end ();
			++b)
		{
			ballotOptionCode = (*b).getCode();
			break;
		}
	}

	return (mapEligibleOptionsList[contestCode])[ballotOptionCode];
}

void ElectoralConfiguration::notReload ()
{
	reload = false;
}

bool ElectoralConfiguration::isContestValidate ( Smartmatic::SAES::Voting::Election::Contest & contest )
{
	bool validate = false;

	Smartmatic::SAES::Voting::VotingDevice::Logical_voter_groups & lvgs (getVotingDevice()->getLogicalVoterGroups());
	Smartmatic::SAES::Voting::VotingDevice::Logical_voter_groups::Logical_voter_groupIterator it;

	for (it = lvgs.getLogical_voter_group().begin();
		 it != lvgs.getLogical_voter_group().end() && !validate;
		 it++)
	{
		std::string contestGroupCode = (*it).getContest_group_code();
		Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeSequence cgs = getElection()->getContestGroup(contestGroupCode).getContest_code();
		Smartmatic::SAES::Voting::Election::Contest_group::Contest_codeIterator itcg;

		for (itcg = cgs.begin();
			 itcg != cgs.end() && !validate;
			 itcg++)
		{
			validate = ((*itcg) == contest.getCode());
		}
	}

	return validate;
}

void ElectoralConfiguration::loadAllData()
	throw (Smartmatic::System::Exception::ElectionException,
			Smartmatic::System::Exception::VotingDeviceException)
{
	if (!loadData)
	{
		logger->Debug("Load all data");
		loadData = true;
		createMap();
		calculateMax();

		if (SAESCommonConfigurationManager::Current()->isForceReduceElection() && !VotingCenters::VotingCentersWrapper::getInstance()->isInstall())
		{
			Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
			getElection()->persistence(directories);
		}
	}
}

unsigned int ElectoralConfiguration::getMaxBallotOptionsByVote ()
{
    return maxBallotOptionByVote;
}

unsigned int ElectoralConfiguration::getMaxContestByVote ()
{
    return maxContestByVote;
}

unsigned int ElectoralConfiguration::getMaxContestByBlankVote ()
{
    return maxContestByBlankVote;
}

unsigned int ElectoralConfiguration::getMaxCustomAttributeByVote ()
{
    return maxCustomAttributeByVote;
}

std::map < std::string, int > & ElectoralConfiguration::getMaxBallotOptionByContestCode()
{
    return maxBallotOptionByContest;
}

unsigned int ElectoralConfiguration::getMaxBallotOptionByContestCode ( std::string contestCode )
{
    return maxBallotOptionByContest[ contestCode ];
}

std::string ElectoralConfiguration::getPartyByMaxBallotOptionContestCode ( std::string contestCode )
{
    return contestParty[ contestCode ];
}

unsigned int ElectoralConfiguration::getCountListBallotOptionByContestParty ( std::string contestCode, std::string partyCode )
{
	return maxListBallotOptionByContestParty[contestCode][partyCode];
}

unsigned int ElectoralConfiguration::getCountPrincipalBallotOptionByContestParty ( std::string contestCode, std::string partyCode )
{
	return maxPrincipalBallotOptionByContestParty[contestCode][partyCode];
}

unsigned int ElectoralConfiguration::getCountStandInBallotOptionByContestParty ( std::string contestCode, std::string partyCode )
{
	return maxStandInBallotOptionByContestParty[contestCode][partyCode];
}

unsigned int ElectoralConfiguration::getCountBallotOptionByContestParty ( std::string contestCode, std::string partyCode)
{
	unsigned int total = 0;

	total += maxListBallotOptionByContestParty[contestCode][partyCode];
	total += maxPrincipalBallotOptionByContestParty[contestCode][partyCode];
	total += maxStandInBallotOptionByContestParty[contestCode][partyCode];

	return total;
}

void ElectoralConfiguration::getCountBallotOptionByContestParty ( std::string contestCode, std::string partyCode, int & countList, int & countPrincipal, int & countStandIn )
{
	countList = maxListBallotOptionByContestParty[contestCode][partyCode];
	countPrincipal = maxPrincipalBallotOptionByContestParty[contestCode][partyCode];
	countStandIn = maxStandInBallotOptionByContestParty[contestCode][partyCode];
}

std::list < std::string > & ElectoralConfiguration::getAllCodeBallotOptionByContestParty(std::string contestCode, std::string partyCode )
{
	return allCodeBallot[contestCode][partyCode];
}

std::map <std::string, std::map < std::string, std::list <std::string> > > & ElectoralConfiguration::getAllCodeBallotOptionByContestParty()
{
	return allCodeBallot;
}

std::string ElectoralConfiguration::getPartyCodeByBallotOptionCode(std::string ballotCode)
{
	return partyCodeByBallotOptionCode[ballotCode];
}

Smartmatic::SAES::Voting::Election::Eligible_option & ElectoralConfiguration::getEligibleOptionFromEligibleOptionCode(std::string contestCode, std::string eligibleOptionCode)
{
	return (eligibleOptionByEligibleOptionCodeMap[contestCode])[eligibleOptionCode];
}

Smartmatic::SAES::Voting::Election::Eligible_option & ElectoralConfiguration::getEligibleOptionFromBallotOptionCode(std::string contestCode, std::string ballotOptionCode)
{
	return (eligibleOptionByBallotOptionCodeMap[contestCode])[ballotOptionCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getEligibleOptionsListByContestCode (std::string contestCode)
{
	return mapEligibleOptionsListByContest[contestCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getEligibleOptionsPrincipalByContestCode (std::string contestCode)
{
	return mapEligibleOptionsPrincipalByContest[contestCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getEligibleOptionsStandInByContestCode (std::string contestCode)
{
	return mapEligibleOptionsStandInByContest[contestCode];
}

std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getMapEligibleOptionsListByContestCode (std::string contestCode)
{
	return mapEligibleOptionsList[contestCode];
}

std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getMapEligibleOptionsPrincipalByContestCode (std::string contestCode)
{
	return mapEligibleOptionsPrincipal[contestCode];
}

std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getMapEligibleOptionsStandInByContestCode (std::string contestCode)
{
	return mapEligibleOptionsStandIn[contestCode];
}

Smartmatic::SAES::Voting::Election::Contest & ElectoralConfiguration::getContestByCode (std::string code)
{
	return mapContestCode[code];
}

std::list < Smartmatic::SAES::Voting::Election::Party > & ElectoralConfiguration::getListPartyByContestCode (std::string code)
{
	return mapContestParty[code];
}

std::list < Smartmatic::SAES::Voting::Election::Contest > & ElectoralConfiguration::getListContestByContestGroupCode (std::string code)
{
	return mapListContestByContestGroup[code];
}

std::list < Smartmatic::SAES::Voting::Election::Contest > & ElectoralConfiguration::getContestList()
{
	return listContest;
}

std::list < std::string > & ElectoralConfiguration::getContestCodeList()
{
	return listContestCode;
}

std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group > & ElectoralConfiguration::getLogicalVoterGroupList()
{
	return listLVG;
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getBallotOptionsListByContestParty(std::string contestCode, std::string partyCode)
{
	return mapBallotOptionsListByContestParty[contestCode][partyCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getBallotOptionsPrincipalByContestParty(std::string contestCode, std::string partyCode)
{
	return mapBallotOptionsPrincipalByContestParty[contestCode][partyCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getBallotOptionsStandInByContestParty(std::string contestCode, std::string partyCode)
{
	return mapBallotOptionsStandInByContestParty[contestCode][partyCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & ElectoralConfiguration::getBallotOptionPartyByContest(std::string contestCode)
{
	return mapBallotOptionsPartyByContest[contestCode];
}

unsigned int ElectoralConfiguration::getMaxPartiesByAllContest()
{
	return maxPartiesByAllContest;
}

std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & ElectoralConfiguration::getEligibleOptionsListByContestParty(std::string contestCode, std::string partyCode)
{
	return mapEligibleOptionsListByContestParty[contestCode][partyCode];
}

std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & ElectoralConfiguration::getEligibleOptionsPrincipalByContestParty(std::string contestCode, std::string partyCode)
{
	return mapEligibleOptionsPrincipalByContestParty[contestCode][partyCode];
}

std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & ElectoralConfiguration::getEligibleOptionsStandInByContestParty(std::string contestCode, std::string partyCode)
{
	return mapEligibleOptionsStandInByContestParty[contestCode][partyCode];
}

std::list <Smartmatic::SAES::Voting::Election::Contest_group> & ElectoralConfiguration::getContestGroups()
{
	return contestGroupList;
}

Smartmatic::SAES::Voting::Election::Contest_group & ElectoralConfiguration::getContestGroup(std::string contestGroupCode)
{
	return mapContestGroupByCode[contestGroupCode];
}

std::list < Smartmatic::SAES::Voting::Election::Ballot > & ElectoralConfiguration::getBallots()
{
	return ballotList;
}

std::list <Smartmatic::SAES::Voting::VotingDevice::Region_category> & ElectoralConfiguration::getRegionCategoryList()
{
	return regionCategoryList;
}

void ElectoralConfiguration::getFileNamesByLanguages(std::string file, std::list <std::string> & fileNames, bool allLanguages, unsigned int delta, bool onlyLanguage)
{
	fileNames.clear();

    std::list <std::string>::iterator itl;
    std::list <std::string> languages = getLanguageListFullName(true, onlyLanguage);

    if (getLanguageListFullName().size() > delta)
    {
		for (itl = languages.begin();
			 itl != languages.end();
			 itl++)
		{
			std::string tmpFile = Path::GetFileNameWithOutExtension(file) + (*itl) + Path::GetFileExtension(file);
			fileNames.push_back(tmpFile);
		}
    }
    else if (allLanguages)
    {
        std::string currentLanguage = SAESLanguageController::getActualLanguage();
		std::string tmpFile = Path::GetFileNameWithOutExtension(file) + currentLanguage + Path::GetFileExtension(file);
		fileNames.push_back(tmpFile);
    }
    else
    {
    	fileNames.push_back(file);
    }
}
