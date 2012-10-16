/**
 * @file	VoteCode.hxx
 *
 * @brief	vote code class.
 */

#ifndef _VOTE_CODE_H_
#define _VOTE_CODE_H_

#include <iostream>
#include <Voting/Vote/vote-schema.hxx>
#include <System/SafeBuffer.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Voting
        {
            namespace Vote
            {
                /**
                 * @brief	Vote Code.
                 *
                 * @author  Yadickson Soto yadickson.soto@smartmatic.com
                 * @date    02/06/2011
                 */

                class VoteCode
                {
                protected:

                    /**
                     * @brief	Default constructor.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     */

                    VoteCode();

                public:

                    /**
                     * @brief	Destroy.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     */

                    virtual ~VoteCode();

                    /**
                     * @brief   Method generate compose code.
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The compose vote code (uuid + checksum + sum)
                     */

                    static std::string generateComposeCode(const Vote & vote);

                    /**
                     * @brief   Method get compose code.
                     * @param   uuid code vote
                     * @param   checksum checksum vote
                     * @param   checksum checksum vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The compose vote code (uuid + checksum)
                     */

                    static void getComposeCode(
                            Smartmatic::System::SafeBuffer & uuid,
                            Smartmatic::System::SafeBuffer & checksum,
                            Smartmatic::System::SafeBuffer & crc32,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Method generate checksum vote.
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  checksum of vote
                     */

                    static void generateChecksum(const Vote & vote,
                    		Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Method getter vote code
                     * @param   composeCode code compose of vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The code vote into a safebuffer
                     */

                    static void getVoteCode(
                            std::string composeCode,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Method getter vote code
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The code vote into a safebuffer
                     */

                    static void getVoteCode(
                            const Vote & vote,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Method getter checksum code
                     * @param   composeCode code compose of vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The checksum vote into a safebuffer
                     */

                    static void getChecksum(
                            std::string composeCode,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Method getter crc32
                     * @param   composeCode code compose of vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The crc32 vote into a safebuffer
                     */

                    static void getCRC32(
                            std::string composeCode,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Method getter checksum vote
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  The checksum vote into a safebuffer
                     */

                    static void getChecksum(
                            const Vote & vote,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   validate vote code.
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  true is validate vote code
                     */

                    static bool validateCode(const Vote & vote);

                    /**
                     * @brief   validate code.
                     * @param   code object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  true is validate vote code
                     */

                    static bool validateCode(std::string composeCode);

                    /**
                     * @brief   validate checksum.
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  true is validate checksum
                     */

                    static bool validateChecksum(const Vote & vote);

                    /**
                     * @brief   Carriage return 32 checksum.
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  cr23 checksum vote
                     */

                    static void getCR32Checksum(
                            const Vote & vote,
                            Smartmatic::System::SafeBuffer & dataOut);

                    /**
                     * @brief   Digest checksum.
                     * @param   vote object vote
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  md5 checksum vote
                     */

                    static void getMD5Checksum(
                            const Vote & vote,
                            Smartmatic::System::SafeBuffer & dataOut);

                    static void encode( std::string & composeCode );

                    static void decode( std::string & composeCode );

                private:

                    /**
                     * @brief   Sort selection precedes.
                     *
                     * @param   first   The first selection.
                     * @param   second  The second selection.
                     *
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    02/06/2011
                     *
                     * @return  true if it succeeds, false if it fails.
                     */

                    static bool sortSelectionVote(
                            Selection first,
                            Selection second);

                    static bool sortBallotVote(
                            std::string first,
                            std::string second);

                    static void cryptoCode(
                            Smartmatic::System::SafeBuffer & buffer,
                            Smartmatic::System::SafeBuffer & crc32,
                            Smartmatic::System::SafeBuffer & dataOut);

                    static void decryptoCode(std::string composeCode,
                    		Smartmatic::System::SafeBuffer & dataOut);

                    static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
                };
            }
        }
    }
}

#endif /* _VOTE_CODE_H_ */
