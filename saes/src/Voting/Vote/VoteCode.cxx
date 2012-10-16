/**
 * @file VoteCode.cxx
 * @brief Body class vote code
 */

#include "VoteCode.hxx"
#include <System/guid-class.h>
#include <Security/Encryption.hxx>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <System/Security/Cryptography/MsgDigestUtil.h>
#include <System/Security/CRC32Calculator.hxx>
#include <System/Security/Crypto.hxx>
#include <stdlib.h>
#include <string.h>
#include <System/Utils/StringUtils.hxx>
#include <System/Encoding/Base64Encoder.h>
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

using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::Log;

#define SIZE_ELEMENT_CODE 16

ISMTTLog* VoteCode::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Vote.VoteCode", GETTEXT_PACKAGE);

VoteCode::VoteCode()
{

}

VoteCode::~VoteCode()
{

}

std::string VoteCode::generateComposeCode(const Vote & vote)
{
	logger->Debug("Generate compose code");

    SafeBuffer code = Smartmatic::System::GuidClass::NewGuid().toSafeBuffer();
    SafeBuffer checksum;
    generateChecksum(vote, checksum);

    SafeBuffer toCRC = code;
    toCRC.AddData(checksum);

    SafeBuffer crc32;
    CRC32Calculator::getCRC32(toCRC, crc32);

    SafeBuffer composeCode;
    getComposeCode(code, checksum, crc32, composeCode);

    std::string voteCode = composeCode.GetBase64Data();

	logger->Debug("compose code = " + voteCode);
	logger->Debug("checksum = " + checksum.GetBase64Data());

    return voteCode;
}

void VoteCode::generateChecksum(const Vote & vote, SafeBuffer & checksum)
{
    VoteChecksumType cks = SAESConfigurationManager::Current()->getVoteChecksum();

    switch (cks)
    {
        case VoteChecksumType::CONFIGURATION_MD5:
            getMD5Checksum(vote, checksum);
            break;
        case VoteChecksumType::CONFIGURATION_CRC32:
            getCR32Checksum(vote, checksum);
            break;
        default:
            getMD5Checksum(vote, checksum);
            break;
    }
}

void VoteCode::getComposeCode(
        SafeBuffer & code,
        SafeBuffer & checksum,
        SafeBuffer & crc32,
        SafeBuffer & dataOut)
{
    SafeBuffer compose;
    compose.AddData (code);
    compose.AddData(checksum);
    cryptoCode(compose, crc32, dataOut);
}

void VoteCode::getVoteCode(std::string composeCode, SafeBuffer & dataOut)
{
    SafeBuffer buffer;
    decryptoCode(composeCode, buffer);
    dataOut.AddData ((unsigned char*)buffer.GetData(), SIZE_ELEMENT_CODE);
}

void VoteCode::getChecksum(std::string composeCode, SafeBuffer & dataOut)
{
    SafeBuffer buffer;
    decryptoCode(composeCode, buffer);

    if (buffer.GetData() != NULL && buffer.GetSize() > 0)
    {
        const unsigned char * data = buffer.GetData() + SIZE_ELEMENT_CODE;
        dataOut.AddData((unsigned char*)data, SIZE_ELEMENT_CODE);
    }
}

void VoteCode::getCRC32(std::string composeCode, SafeBuffer & dataOut)
{
    SafeBuffer buffer;
    decryptoCode(composeCode, buffer);

    if (buffer.GetData() != NULL && buffer.GetSize() > 0)
    {
        const unsigned char * data = buffer.GetData() + SIZE_ELEMENT_CODE * 2;
        dataOut.AddData((unsigned char*)data, buffer.GetSize() - (SIZE_ELEMENT_CODE * 2));
    }
}

void VoteCode::getVoteCode(const Vote & vote, SafeBuffer & dataOut)
{
    getVoteCode(vote.getCode(), dataOut);
}

void VoteCode::getChecksum(const Vote & vote, SafeBuffer & dataOut)
{
    getChecksum(vote.getCode(), dataOut);
}

bool VoteCode::validateCode(const Vote & vote)
{
	logger->Debug("Validate code");

    SafeBuffer code;
    getVoteCode(vote, code);

    SafeBuffer checksum;
    getChecksum(vote, checksum);

    SafeBuffer checksumGen;
    generateChecksum(vote, checksumGen);

    SafeBuffer toCRC;
    toCRC.AddData(code);
    toCRC.AddData(checksum);
    SafeBuffer crc32Calculate;

    bool validate;
    std::string composeCode = vote.getCode();

    SafeBuffer result;

    if (!SAESConfigurationManager::Current()->isUseShortVoteCode())
    {
        CRC32Calculator::getCRC32(toCRC, crc32Calculate);
        SafeBuffer crc32;
        getCRC32(composeCode, crc32);

        getComposeCode(code, checksum, crc32Calculate, result);

        validate = crc32Calculate.GetBase64Data() == crc32.GetBase64Data() &&
               result.GetBase64Data() == composeCode;
    }
    else
    {
    	getComposeCode(code, checksum, crc32Calculate, result);
        validate = result.GetBase64Data() == composeCode;
    }

    validate = validate && checksum.GetBase64Data() == checksumGen.GetBase64Data();

	logger->Debug("compose code = " + composeCode);
	logger->Debug("checksum = " + checksum.GetBase64Data());

	logger->Debug("compose code gen = " + result.GetBase64Data());
	logger->Debug("checksum gen = " + checksumGen.GetBase64Data());

	logger->Debug(std::string("Validate Vote Code ") + (validate ? "Success":"Fail"));

    return validate;
}

bool VoteCode::validateChecksum(const Vote & vote)
{
	bool validate = false;

    SafeBuffer checksum;
    getChecksum(vote, checksum);
    SafeBuffer genChecksum;
    generateChecksum(vote, genChecksum);

    validate = checksum.GetBase64Data() == genChecksum.GetBase64Data();

    logger->Debug(std::string("Validate Checksum ") + (validate ? "Success":"Fail"));

    return validate;
}

bool VoteCode::validateCode(std::string composeCode)
{
	bool validate = false;

    SafeBuffer code;
    getVoteCode(composeCode, code);

    SafeBuffer checksum;
    getChecksum(composeCode, checksum);

    SafeBuffer toCRC;
    toCRC.AddData(code);
    toCRC.AddData(checksum);

    SafeBuffer crc32Calculate;

    if (!SAESConfigurationManager::Current()->isUseShortVoteCode())
    {
        CRC32Calculator::getCRC32(toCRC, crc32Calculate);
        SafeBuffer crc32;
        getCRC32(composeCode, crc32);
        SafeBuffer result;
        getComposeCode(code, checksum, crc32Calculate, result);

        validate = crc32Calculate.GetBase64Data() == crc32.GetBase64Data() &&
               result.GetBase64Data() == composeCode;
    }
    else
    {
    	SafeBuffer result;
    	getComposeCode(code, checksum, crc32Calculate, result);
        validate = result.GetBase64Data() == composeCode;
    }

    logger->Debug(std::string("Validate String Code ") + (validate ? "Success":"Fail"));

    return validate;
}

bool VoteCode::sortSelectionVote(
        Smartmatic::SAES::Voting::Vote::Selection first,
        Smartmatic::SAES::Voting::Vote::Selection second)
{
    std::string contestFirst(first.getContest());
    std::string contestSecond(second.getContest());

    return contestFirst < contestSecond;
}

bool VoteCode::sortBallotVote(
        std::string first,
        std::string second)
{
    return first < second;
}

void VoteCode::getCR32Checksum(const Vote & vote, SafeBuffer & dataOut)
{
    long int checksum = 0;

    Vote::SSequence sSequence = vote.getSelections();

    std::vector<Smartmatic::SAES::Voting::Vote::Selection> selection(
            sSequence.begin(), sSequence.end());

    std::vector<Smartmatic::SAES::Voting::Vote::Selection>::iterator its;

    std::string contestDummy = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getContestCode();
    std::string ballotDummy = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getBallotOptionCode();

    for (its = selection.begin();
         its != selection.end();
         its++)
    {
        Selection s = (*its);
        std::string contest = s.getContest();

        if (contest == contestDummy) continue;

        Selection::BSequence bSequence = (*its).getBallotOptions();
        std::vector<std::string> ballots(bSequence.begin(), bSequence.end());
        std::vector<std::string>::iterator itb;

        std::sort(ballots.begin(), ballots.end(), &VoteCode::sortBallotVote);

        for (itb = ballots.begin();
             itb != ballots.end();
             itb++)
        {
            if (*itb == ballotDummy) continue;
            checksum += atol((*itb).c_str());
        }
    }

    SafeBuffer buffer(checksum, SIZE_ELEMENT_CODE);
    dataOut.AddData(buffer);
}

void VoteCode::getMD5Checksum(const Vote & vote, SafeBuffer & dataOut)
{
    Glib::ustring message;

    Vote::SSequence sSequence = vote.getSelections();

    std::vector<Smartmatic::SAES::Voting::Vote::Selection> selection(
            sSequence.begin(), sSequence.end());

    std::vector<Smartmatic::SAES::Voting::Vote::Selection>::iterator its;

    std::sort(selection.begin(), selection.end(), &VoteCode::sortSelectionVote);

    std::string contestDummy = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getContestCode();
    std::string ballotDummy = SAESConfigurationManager::Current()->getVoteDummyConfiguration().getBallotOptionCode();

    for (its = selection.begin();
         its != selection.end();
         its++)
    {
        Selection s = (*its);
        std::string contest = s.getContest();

        if (contest == contestDummy) continue;

        Selection::BSequence bSequence = (*its).getBallotOptions();
        std::vector<std::string> ballots(bSequence.begin(), bSequence.end());
        std::vector<std::string>::iterator itb;

        std::sort(ballots.begin(), ballots.end(), &VoteCode::sortBallotVote);

        for (itb = ballots.begin();
             itb != ballots.end();
             itb++)
        {
            if (*itb == ballotDummy) continue;
            message = message.append((*itb).c_str());
        }
    }

    dataOut = Cryptography::MsgDigestUtil::Digest(
            message,
            Cryptography::MsgDigestUtil::DGSTUTIL_MD5);

}

void VoteCode::cryptoCode(SafeBuffer & buffer, SafeBuffer & crc32, SafeBuffer & dataOut)
{
    try
    {

        if (!SAESConfigurationManager::Current()->isUseShortVoteCode())
        {
            buffer.AddData(crc32);
            Encryption::getInstance()->cryptoBufferToBuffer(buffer, dataOut,
                Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY, true);
        }
        else
        {
            Crypto obj;
            obj.init(Crypto::KEY_AES_256, Crypto::MODE_AES_CBC, false);
            obj.cryptoBufferToBuffer(buffer, dataOut, Encryption::getInstance()->getVerificationKey().GetData(), Encryption::getInstance()->getVerificationKey().GetData());
        }

    }
    catch(Smartmatic::System::Exception::CryptoException & ex)
    {
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
    }
    catch(...)
    {
        std::stringstream ss;
        ss  << "FATAL - " << __func__;
        logger->Debug(ss.str());
    }
}

void VoteCode::decryptoCode(std::string composeCode, SafeBuffer & dataOut)
{
    try
    {

        if (!SAESConfigurationManager::Current()->isUseShortVoteCode())
        {
            Encryption::getInstance()->decryptoB64ToBuffer(composeCode, dataOut,
                        Smartmatic::SAES::Security::Encryption::VERIFICATION_KEY, true);
        }
        else
        {
            SafeBuffer data;
            Base64Encoder::ConvertFromBase64(composeCode, data);

            Crypto obj;
            obj.init(Crypto::KEY_AES_256, Crypto::MODE_AES_CBC, false);
            obj.decryptoBufferToBuffer(data, dataOut, Encryption::getInstance()->getVerificationKey().GetData(), Encryption::getInstance()->getVerificationKey().GetData());

        }

    }
    catch(Smartmatic::System::Exception::CryptoException & ex)
    {
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
    }
    catch(...)
    {
        std::stringstream ss;
        ss  << "FATAL - " << __func__;
        logger->Debug(ss.str());
    }
}


void VoteCode::encode( std::string & composeCode )
{
	unsigned int group = SAESConfigurationManager::Current()->getVoteCodeConfig().getCountGroupVoteCode();

	if ( composeCode.length() > group && group > 0 )
	{
		std::string character = SAESConfigurationManager::Current()->getVoteCodeConfig().getCharSeparatorVoteCode();
		std::string code;
		unsigned int parts = composeCode.length() / group - 1;

		for (unsigned int i = 0;i <= parts;i++)
		{
			if (i != 0)
			{
				code.append(character);
			}

			code.append( composeCode.substr(0, group) );
			composeCode.erase(0, group);
		}

		if (composeCode.length() > 0 && code.length() > 0)
		{
			code.append(character);
		}

		code.append(composeCode);
		composeCode = code;
	}
}

void VoteCode::decode( std::string & composeCode )
{
	unsigned int group = SAESConfigurationManager::Current()->getVoteCodeConfig().getCountGroupVoteCode();

	if ( group > 0 )
	{
		std::string find = SAESConfigurationManager::Current()->getVoteCodeConfig().getCharSeparatorVoteCode();
		composeCode = Smartmatic::System::Utils::StringUtils::replaceAll(composeCode, find, "");
	}
}
