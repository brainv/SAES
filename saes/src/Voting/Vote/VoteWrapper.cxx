/**
 * @file VoteWrapper.cxx
 * @brief Body class vote wrapper
 */

#include "VoteWrapper.hxx"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <glibmm.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include "Resources/election-string-resources-manager.h"
#include <Security/Encryption.hxx>
#include <System/SafeBuffer.h>
#include <System/Utils/StringUtils.hxx>
#include "VoteCode.hxx"
#include <System/Compression/compression-class.h>
#include <sstream>
#include <iostream>
#include <System/Encoding/Base64Encoder.h>
#include <System/Exception/RSAException.h>

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

using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::SAES::Exceptions::Voting::Vote;



ISMTTLog* VoteWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Vote.VoteWrapper",GETTEXT_PACKAGE);

VoteWrapper::VoteWrapper()
{

}

VoteWrapper::~VoteWrapper()
{

}

std::string VoteWrapper::generateCode(Vote & vote)
{
    return VoteCode::generateComposeCode(vote);
}

bool VoteWrapper::voteFileToVote(std::string & file, Vote & vote)
{
	try
	{
		std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(
				file,
				Smartmatic::SAES::Security::Encryption::EXCHANGE_FILE,
				Smartmatic::SAES::Security::Encryption::SECRET_KEY);

		std::istringstream istr (data);
		vote = (*(Smartmatic::SAES::Voting::Vote::parseV(istr, Smartmatic::SAES::Voting::VoteTypes::Flags::dont_validate)));
	}
	catch(...)
	{
		logger->Debug("ERROR - load vote file " + file);
		return false;
	}

	return true;
}

 void VoteWrapper::voteToString(const Vote & vote, std::string& outStringVote)
    throw (Smartmatic::System::Exception::XmlException)
{
    std::ostringstream str;

    VoteTypes::NamespaceInfomap mapv;
    mapv[""].name = NAMESPACE_VOTING_VOTE;
    mapv[""].schema = "";

    try
    {
        serializeV(str, vote, mapv, "UTF-8", VoteTypes::Flags::dont_validate);
        outStringVote = str.str();
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
        std::stringstream ss;
        ss << "FATAL - " << __func__ << e;
        logger->Error(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.Vote.VoteWrapper.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.Vote.VoteWrapper.ErrorSerializaData"), logger);
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "FATAL - " << __func__;
        logger->Error(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.Vote.VoteWrapper.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.Vote.VoteWrapper.ErrorSerializaData"), logger);
    }
}

Smartmatic::SAES::Voting::PBReports::PVVote VoteWrapper::voteToPVVote(
        Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Vote & vote)
{
    logger->Debug("Start vote to pvvote");

    Smartmatic::SAES::Voting::PBReports::PVVote pvVote;
    Smartmatic::SAES::Voting::Election::ElectionWrapper * election;
    Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper * votingDevice;

    election = electoralConfiguration->getElection();
    votingDevice = electoralConfiguration->getVotingDevice();
    VotingDevice::Voting_device firstVotingDevice = votingDevice->getFirstVotingDevice();

    /*********************************************************************/

    std::string lvgCode = vote.getLogicalVoterGroup();
    std::string lvgDummyCode = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();
    std::string lvgNameKey = "";

    if (lvgCode != lvgDummyCode)
    {
        VotingDevice::Logical_voter_group lvg = votingDevice->getLogicalVoterGroup(firstVotingDevice, lvgCode);
        std::string lvgCode = lvg.getCode();
        std::string lvgCustomCode = lvg.getCustom_code();
        std::string lvgNameKey = lvg.getName_key();

        std::string toComposeLVG =  _("Smartmatic.SAES.Voting.Vote.VoteWrapper.LogicalVoterGroup");
        lvgNameKey = Glib::ustring::compose(toComposeLVG,
                lvgCode,
                lvgCustomCode,
                ElectionStringResourcesManager::Current()->getResource(lvgNameKey));
    }

    pvVote.setLogical_voter_group(lvgNameKey);

    /*********************************************************************/

    std::string pvCode = vote.getCode();
    pvVote.setVote_code(pvCode);

    /*********************************************************************/

    std::string pvVotingDeviceCode = firstVotingDevice.getCode();
    pvVote.setVoting_device_code(pvVotingDeviceCode);

    /*********************************************************************/

    Vote::Vote::SSequence & seqContest (vote.getSelections());
    Vote::Vote::SIterator seqConstIterator;
    std::string contestDummyCode = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getContestCode();

    Smartmatic::SAES::Voting::PBReports::PVVote::ContestSequence seqpvContest;

    for (seqConstIterator = seqContest.begin();
         seqConstIterator != seqContest.end();
         seqConstIterator++)
    {
        Vote::SType s = (*seqConstIterator);
        std::string contestCode = s.getContest();

        if (contestCode == contestDummyCode) continue;

        Smartmatic::SAES::Voting::PBReports::PVContest pvContest;
        Smartmatic::SAES::Voting::PBReports::PVContest::PrincipalsSelectedSequence pvPSeq;
        Smartmatic::SAES::Voting::PBReports::PVContest::StandInSelectedSequence pvSSeq;

        Election::Contest contest = electoralConfiguration->getContestByCode(contestCode);

        std::string pvReportName = "";
        std::string contestTitle = contest.getTitle_key();
        std::string contestAbstract = contest.getAbstract_key();
        std::string contestHelp = contest.getHelp_key();

        std::string pvParty = "";
        std::string pvPartyName = "";
        std::string pvPartyAbreviation = "";
        std::string pvPartyOrder = "";

        Selection::BSequence & seqbo (s.getBallotOptions());
        Selection::BIterator itbo;

        pvContest.setNull_info(seqbo.size() == 0 ?
                _("Smartmatic.SAES.Voting.Vote.VoteWrapper.VoteNULL") :
                _("Smartmatic.SAES.Voting.Vote.VoteWrapper.VoteNotNULL"));

        std::list<std::string> codes;

        for (itbo = seqbo.begin();
             itbo != seqbo.end();
             itbo++)
        {
            codes.push_back((*itbo));
        }

        /********************************************************************************/

        std::list <Election::Ballot_option> boList;
        std::list <Election::Ballot_option> boPrincipal;
        std::list <Election::Ballot_option> boStandIn;

        election->getBallotOptionsListByContest ( contest, codes, boList );
        election->getBallotOptionsByContest ( contest, codes, boPrincipal, Election::Category::ELECTION_PRINCIPAL );
        election->getBallotOptionsByContest ( contest, codes, boStandIn, Election::Category::ELECTION_STAND_IN );

        std::list <Election::Ballot_option>::iterator it;

        /* list */

        for (it = boList.begin();
             it != boList.end();
             it++)
        {
            if (it == boList.begin())
            {
                getPartyInfo(*it,
                        pvPartyAbreviation,
                        pvPartyName);
            }

            Election::Eligible_option eo = electoralConfiguration->getEligibleOptionFromBallotOptionCode(contest.getCode(), (*it).getCode());
            pvPSeq.push_back(getCandidateInfo(eo, (*it)));
        }

        /* principal */

        for (it = boPrincipal.begin();
             it != boPrincipal.end();
             it++)
        {
            if (it == boPrincipal.begin())
            {
                getPartyInfo(*it,
                        pvPartyAbreviation,
                        pvPartyName);
            }

            Election::Eligible_option eo = electoralConfiguration->getEligibleOptionFromBallotOptionCode(contest.getCode(), (*it).getCode());
            pvPSeq.push_back(getCandidateInfo(eo, (*it)));
        }

        /* stand in */

        for (it = boStandIn.begin();
             it != boStandIn.end();
             it++)
        {
            if (it == boPrincipal.begin())
            {
                getPartyInfo(*it,
                        pvPartyAbreviation,
                        pvPartyName);
            }

            Election::Eligible_option eo = electoralConfiguration->getEligibleOptionFromBallotOptionCode(contest.getCode(), (*it).getCode());
            pvSSeq.push_back(getCandidateInfo(eo, (*it)));
        }

        /********************************************************************************/

        Glib::ustring toComposeContest =  _("Smartmatic.SAES.Voting.Vote.VoteWrapper.Contest");
        pvReportName = Glib::ustring::compose(toComposeContest,
                ElectionStringResourcesManager::Current()->getResource(contestTitle),
                ElectionStringResourcesManager::Current()->getResource(contestAbstract),
                ElectionStringResourcesManager::Current()->getResource(contestHelp));

        Glib::ustring toComposeParty =  _("Smartmatic.SAES.Voting.Vote.VoteWrapper.Party");
        pvParty = Glib::ustring::compose(toComposeParty,
                ElectionStringResourcesManager::Current()->getResource(pvPartyName),
                ElectionStringResourcesManager::Current()->getResource(pvPartyAbreviation),
                ElectionStringResourcesManager::Current()->getResource(pvPartyOrder));

        pvContest.setPv_report_name(pvReportName);
        pvContest.setPv_party_name(pvParty);
        pvContest.setPrincipalsSelected(pvPSeq);
        pvContest.setStandInSelected(pvSSeq);
        seqpvContest.push_back(pvContest);
    }

    pvVote.setContest(seqpvContest);

    logger->Debug("Success vote to pvvote");
    return pvVote;
}

void VoteWrapper::getPartyInfo(Election::Ballot_option & ballotOption,
        std::string & pvPartyAbreviation,
        std::string & pvPartyName)
{
    if (ballotOption.getParty().getAbbreviation() != NULL)
    {
        pvPartyAbreviation = ballotOption.getParty().getAbbreviation().get();
    }

    if (ballotOption.getParty().getName() != NULL)
    {
        pvPartyName = ballotOption.getParty().getName().get();
    }
}

Smartmatic::SAES::Voting::PBReports::PVCandidate VoteWrapper::getCandidateInfo(
        Election::Eligible_option & eligibleOption, Election::Ballot_option & ballotOption)
{
    Smartmatic::SAES::Voting::PBReports::PVCandidate candidate;
    std::string pvCandidateInfo = "";
    long long unsigned int pvCandidateTallyPosition = 0;
    static std::string pvCharacter = SAESConfigurationManager::Current()->getPrintVoteConfiguration().getBallotOptionNameSeparator();

    pvCandidateInfo = eligibleOption.getBallot_name_key();
    pvCandidateTallyPosition = ballotOption.getTally_position();
    pvCandidateInfo = Smartmatic::System::Utils::StringUtils::replaceAll(pvCandidateInfo, pvCharacter, " ");

    std::stringstream ss;
    ss << pvCandidateTallyPosition;

    std::string pvName;
    std::string toComposeCandidate =  _("Smartmatic.SAES.Voting.Vote.VoteWrapper.Candidate");
    pvName = Glib::ustring::compose(toComposeCandidate,
            ElectionStringResourcesManager::Current()->getResource(pvCandidateInfo),
            ElectionStringResourcesManager::Current()->getResource(ss.str()));

    candidate.setInfo(pvName);
    return candidate;
}

bool VoteWrapper::validateVote(
        Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
        Vote & vote)
{
    bool success = true;

    success = validateVoteCode(vote) && success;
    success = validateLogicalVoterGroupVote(electoralConfiguration, vote) && success;
    success = validateVotingDeviceCodeVote(electoralConfiguration, vote) && success;

    if (!success)
    {
        logger->Debug("Error validate vote");
    }
    return success;
}

bool VoteWrapper::validateVoteCode(Vote & vote)
{
    return VoteCode::validateCode(vote) && VoteCode::validateChecksum(vote);
}

bool VoteWrapper::validateLogicalVoterGroupVote(
    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
    Vote & vote)
{
    Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper * votingDevice;

    votingDevice = electoralConfiguration->getVotingDevice();
    VotingDevice::Voting_device firstVotingDevice = votingDevice->getFirstVotingDevice();

    std::string lvgCode = vote.getLogicalVoterGroup();
    std::string lvgDummyCode = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();

    if (lvgCode != lvgDummyCode)
    {
        try
        {
            votingDevice->getLogicalVoterGroup(firstVotingDevice, lvgCode);
        }
        catch(...)
        {
            logger->Debug("Error getter logical voter group " + lvgCode);
            return false;
        }
    }

    return true;
}

bool VoteWrapper::validateVotingDeviceCodeVote(
    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
    Vote & vote)
{
    Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper * votingDevice;

    votingDevice = electoralConfiguration->getVotingDevice();
    VotingDevice::Voting_device firstVotingDevice = votingDevice->getFirstVotingDevice();

    std::string vdCode = firstVotingDevice.getCode();

    if (vote.getVotingDeviceCode() != vdCode)
    {
        logger->Debug("Error in voting device code " + vote.getVotingDeviceCode() + " != " + vdCode);
        return false;
    }

    return true;
}

void VoteWrapper::packVoteForQR(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, const Vote & vote, Smartmatic::System::SafeBuffer& outBuffer, bool deflate)
{
	 static Smartmatic::SAES::Configuration::VoteQRCodeModeEnum mode = SAESConfigurationManager::Current()->getPrintVoteConfiguration().getVoteQRCodeMode();
	 std::string strVote;
	 SafeBuffer dataIn;
	 SafeBuffer dataDeflate;

	 switch(mode)
	 {
	 case Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_XMLREDUCED:
		 //process vote

		 Voting::Vote::VoteWrapper::getReducedXmlVoteString(electoralConfiguration,vote,strVote);
		 Encryption::getInstance()->signedXml(strVote, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);
		 break;
	 case Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_XMLFULL:
		 Voting::Vote::VoteWrapper::voteToString(vote,strVote);
		 Encryption::getInstance()->signedXml(strVote, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);
		 break;
	 case Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_SIZEOPTIMIZED:
		 Voting::Vote::VoteWrapper::getSizeOptimizedVoteString(electoralConfiguration, vote, strVote);
		 break;
	 }

	//std::string str;
	//voteToString(vote, str);
	//logger->Debug(str);

	//logger->Debug(strVote);

	//setup data for compression
	dataIn.AddData((unsigned char *)strVote.c_str(), strVote.length());

	//compress data

	if (deflate)
	{
		Smartmatic::System::Compression::CompressionClass::Deflate(dataIn, dataDeflate);
		Smartmatic::SAES::Security::Encryption::getInstance()->cryptoBufferToBuffer(dataDeflate, outBuffer, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);
	}
	else
	{
		Smartmatic::SAES::Security::Encryption::getInstance()->cryptoBufferToBuffer(dataIn, outBuffer, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);
	}
}

void VoteWrapper::getReducedXmlVoteString(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Vote vote, std::string& outStringVote)
{

	std::map <std::string, std::string> codedSeletions = electoralConfiguration->getVoteRecovery()->LogicalToRecovery (vote);

	 Vote::Vote::SSequence& sequenceS(vote.getSelections ());
	 Vote::Vote::SIterator its = sequenceS.begin();
	 while(its != sequenceS.end())
	 {
		 //clear the list and write the coded selections
		 its->setContestCodedSelections(codedSeletions[its->getContest()]);
		 its->getBallotOptions().clear();
		 its++;
	 }
	//serialize the vote
	 VoteWrapper::voteToString(vote, outStringVote);
}

void VoteWrapper::getExpandedXmlVote(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Vote& inOutVote)
throw (QRVoteInvalidFormatException)
{
	std::map <std::string, std::string> codedSeletions;

	Vote::Vote::SSequence& sequenceS(inOutVote.getSelections ());
	Vote::Vote::SIterator its = sequenceS.begin();

	//Build the map
	while(its != sequenceS.end())
	{
		//clear the list and write the coded selections
		if(its->getContestCodedSelections().present())
		{
			codedSeletions[its->getContest()] = its->getContestCodedSelections().get();
			its->getContestCodedSelections().reset();
		}
		else
		{
			//throw and exception
			throw QRVoteInvalidFormatException(_("Smartmatic.SAES.Voting.Vote.VoteWrapper.InvalidXmlDataFormat"), N_("Smartmatic.SAES.Voting.Vote.VoteWrapper.InvalidXmlDataFormat"),logger);
		}
		its++;
	}

	//Get the vote with the selections
	electoralConfiguration->getVoteRecovery()->RecoveryToLogical(codedSeletions,inOutVote);

}

bool VoteWrapper::unpackVoteFromQR(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Smartmatic::System::SafeBuffer& inBuffer, Vote & outVote, bool inflate)
{
	static Smartmatic::SAES::Configuration::VoteQRCodeModeEnum mode = SAESConfigurationManager::Current()->getPrintVoteConfiguration().getVoteQRCodeMode();

	Smartmatic::System::SafeBuffer decryptBuffer;
	Smartmatic::SAES::Security::Encryption::getInstance()->decryptoBufferToBuffer(inBuffer, decryptBuffer, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);

	Smartmatic::System::SafeBuffer inflateData;

	if (inflate)
	{
		Smartmatic::System::Compression::CompressionClass::Inflate(decryptBuffer, inflateData);
	}
	else
	{
		inflateData.AddData(decryptBuffer);
	}

	if(inflateData.GetSize() > 0)
	{
		std::string inflatedString;
		inflatedString.append((const char *)inflateData.GetData(),inflateData.GetSize());
		//inflatedString.resize(inflateData.GetSize());
		std::istringstream ss( inflatedString );

		switch(mode)
		{
		case Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_XMLFULL:
			Smartmatic::SAES::Security::Encryption::getInstance()->validateSignedString(inflatedString, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);
			outVote = (*(Smartmatic::SAES::Voting::Vote::parseV(ss, Smartmatic::SAES::Voting::VoteTypes::Flags::dont_validate)));
			break;
		case Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_XMLREDUCED:
			Smartmatic::SAES::Security::Encryption::getInstance()->validateSignedString(inflatedString, Smartmatic::SAES::Security::Encryption::PRINTED_VOTE);
			outVote = (*(Smartmatic::SAES::Voting::Vote::parseV(ss, Smartmatic::SAES::Voting::VoteTypes::Flags::dont_validate)));
			Voting::Vote::VoteWrapper::getExpandedXmlVote(electoralConfiguration, outVote);
			break;
		case Smartmatic::SAES::Configuration::VoteQRCodeModeEnum::CONFIGURATION_SIZEOPTIMIZED:
			Voting::Vote::VoteWrapper::getVoteFromSizeOptimizedString(electoralConfiguration, inflatedString, outVote);
			break;
		}

		//std::string str;
		//voteToString(outVote, str);
		//logger->Debug(str);
		//logger->Debug(inflatedString);
	}
	else
	{
		return false;
	}
	return true;
}

void VoteWrapper::getSizeOptimizedVoteString(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, const Vote& vote, std::string& outStringVote)
{

	//the format is: "VoteCode","LVG code","device code","lang code","mode","c1-code","c1-selection",..,"cn-code","cn-selection",,"signaure"

	std::string separator = ",";

	std::map <std::string, std::string> codedSeletions = electoralConfiguration->getVoteRecovery()->LogicalToRecovery (vote);
	std::map <std::string, std::string>::iterator it;

	//write vote code
	outStringVote.append(vote.getCode());
	outStringVote.append(separator);
	//write lvg code
	outStringVote.append(vote.getLogicalVoterGroup());
	outStringVote.append(separator);
	//write voting device code
	outStringVote.append(vote.getVotingDeviceCode());
	outStringVote.append(separator);
	//write lan code
	outStringVote.append(vote.getLan_code());
	outStringVote.append(separator);
	//write Mode
	outStringVote.append(vote.getMode());
	outStringVote.append(separator);

	//write selections
	for ( it=codedSeletions.begin() ; it != codedSeletions.end(); it++ )
	{
		//write contest
		outStringVote.append(it->first);
		outStringVote.append(separator);
		//write coded selection
		outStringVote.append(it->second);
		outStringVote.append(separator);
	}

	outStringVote.append(separator);
	//compute signature
	SafeBuffer buff((unsigned char*) outStringVote.c_str(), outStringVote.length());
	SafeBuffer signature;
	Encryption::getInstance()->SignDataWithPersonalCertificate(buff, signature);
	outStringVote.append(signature.GetBase64Data());
	//outStringVote.append(separator);
	//outStringVote.append(separator);

}

void VoteWrapper::getVoteFromSizeOptimizedString(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, std::string& stringVote, Vote& outVote )
throw (QRVoteInvalidFormatException, QRVoteSignatureException)
{
	//vote = "vcode,lgvcode,vdcode,langcoce,mode,c1-code,c1-selection,c2-code,c2-selections,,signaturevalue";

	std::map <std::string, std::string> codedSeletions;

	int sigPos = stringVote.rfind(",,");
	int posTmp;

	CheckFindResult(sigPos);

	std::string signature = stringVote.substr(sigPos + 2); //add 2 for the separator
	std::string data = stringVote.substr(0, sigPos +2);

	//verify signature
	SafeBuffer buff((unsigned char*)data.c_str(), data.length());
	SafeBuffer signatureBuff;
	Base64Encoder::ConvertFromBase64(signature, signatureBuff);

	//Evaluate signature
	try
	{
		if(Encryption::getInstance()->VerifySignatureWithPersonalCertificate(buff, signatureBuff) == false)
		{
			throw QRVoteSignatureException(_("Smartmatic.SAES.Voting.Vote.VoteWrapper.InvalidSignature"), N_("Smartmatic.SAES.Voting.Vote.VoteWrapper.InvalidSignature"),logger);
		}
	}
	catch(Smartmatic::System::Exception::RSAException &)
	{
		throw QRVoteSignatureException(_("Smartmatic.SAES.Voting.Vote.VoteWrapper.UnexpectedSignatureError"), N_("Smartmatic.SAES.Voting.Vote.VoteWrapper.UnexpectedSignatureError"),logger);
	}
	//Set vote code
	int pos = 0;
	int fieldSize = stringVote.find(",",pos);
	CheckFindResult(fieldSize);
	std::string var = stringVote.substr(pos, fieldSize);
	outVote.setCode(var);

	//set lgv code
	pos += fieldSize +1;
	posTmp = stringVote.find(",",pos);
	CheckFindResult(posTmp);
	fieldSize =  posTmp - pos;
	var = stringVote.substr(pos, fieldSize);
	outVote.setLogicalVoterGroup(var);

	//set voting device code
	pos += fieldSize +1;
	posTmp = stringVote.find(",",pos);
	CheckFindResult(posTmp);
	fieldSize =  posTmp - pos;
	var = stringVote.substr(pos, fieldSize);
	outVote.setVotingDeviceCode(var);

	//set languaje code
	pos += fieldSize +1;
	posTmp = stringVote.find(",",pos);
	CheckFindResult(posTmp);
	fieldSize =  posTmp - pos;
	var = stringVote.substr(pos, fieldSize);
	outVote.setLan_code(var);

	//Set mode
	pos += fieldSize +1;
	posTmp = stringVote.find(",",pos);
	CheckFindResult(posTmp);
	fieldSize =  posTmp - pos;
	var = stringVote.substr(pos, fieldSize);
	outVote.setMode(var);


	while (pos < sigPos -2)
	{

		pos += fieldSize +1;
		fieldSize = stringVote.find(",",pos) - pos;

		if(fieldSize <= 0)
			break;

		std::string contest = stringVote.substr(pos, fieldSize);
		pos += fieldSize +1;
		posTmp = stringVote.find(",",pos);
		CheckFindResult(posTmp);

		fieldSize =  posTmp - pos;

		std::string sel = stringVote.substr(pos, fieldSize);
		codedSeletions[contest] =sel;
	}

	electoralConfiguration->getVoteRecovery()->RecoveryToLogical(codedSeletions,outVote);
}

void VoteWrapper::CheckFindResult(int markPosition) throw (Smartmatic::SAES::Exceptions::Voting::Vote::QRVoteInvalidFormatException)
{
	size_t val = markPosition;
	if(val == std::string::npos )
	{
		throw QRVoteInvalidFormatException(_("Smartmatic.SAES.Voting.Vote.VoteWrapper.InvalidDataFormat"), N_("Smartmatic.SAES.Voting.Vote.VoteWrapper.InvalidDataFormat"),logger);
	}
}

