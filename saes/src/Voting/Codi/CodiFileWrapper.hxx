/**
 * @file CodiFileWrapper.hxx
 * @brief Header codi file wrapper
 * @date 23/02/2012
 * @author Yadickson Soto
 */

#ifndef CODIFILEWRAPPER_HXX_
#define CODIFILEWRAPPER_HXX_

#include <Voting/ElectoralConfiguration.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <System/Exception/CodiException.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <Voting/Vote/StationTallyWrapper.hxx>
#include <System/SafeBuffer.h>
#include <Configuration/SaesConfiguration-schema.hxx>

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
				class CodiFile;
				/**
				 * @class CodiFileWrapper
				 * @brief Class codi file wrapper
				 * @date 23/02/2012
				 * @author Yadickson Soto
				 */
				class CodiFileWrapper
				{
				public:

					/**
					 * @brief Class constructor
					 * @date 23/02/2012
					 * @author Yadickson Soto
					 */
					CodiFileWrapper();

					/**
					 * @brief Class destroy
					 * @date 23/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~CodiFileWrapper();

					/**
					 * @brief Method init class
					 * @param electoralConfiguration electoral configuration
					 * @param directories saes directories
					 * @date 17/02/2012
					 * @author Yadickson Soto
					 */
					void init(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
							Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories);

					/**
					 * @brief Method update class
					 * @date 15/03/2012
					 * @author Yadickson Soto
					 */
					void update();

					/**
					 * @brief	Method persist codi files
					 * @param stationTally station tally info
					 * @author	Yadickson Soto
					 * @date	17/02/2012
					 */
					void persistCodiFiles(Smartmatic::SAES::Voting::Vote::StationTallyWrapper * stationTally)
						throw (Smartmatic::System::Exception::CryptoException,
								Smartmatic::System::Exception::SignedException,
								Smartmatic::System::Exception::XmlException,
								Smartmatic::System::Exception::CodiException);

					/**
					 * @brief	Method validate files
					 * @return true is validate files
					 * @author	Yadickson Soto
					 * @date	17/02/2012
					 */
					bool validate();

					/**
					 * @brief	Method delete codi files
					 * @author	Yadickson Soto
					 * @date	17/02/2012
					 */
					void deleteFiles();

					/**
					 * @brief method getter codi machine
					 * @return codi machine
					 * @date 14/03/2012
					 * @author Yadickson Soto
					 */
					std::string getCodiMachine();

					/**
					 * @brief method getter custom nis code
					 * @return custom nis code
					 * @date 14/03/2012
					 * @author Yadickson Soto
					 */
					std::string getCustomniscode();

					/**
					 * @brief method getter codi voting type
					 * @return codi voting type
					 * @date 14/03/2012
					 * @author Yadickson Soto
					 */
					std::string getCodiVotingType();

				private:

					/**
					 * @brief method persistence codi file
					 * @param codi registers
					 * @author Yadickson Soto
					 * @date 24/02/2012
					 */
					void persistence(CodiFile * codi)
						throw (Smartmatic::System::Exception::CodiException);

					/**
					 * @brief method fill register G in buffer
					 * @param buffer buffer
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					void fillRegisterG(Smartmatic::System::SafeBuffer & buffer)
						throw (Smartmatic::System::Exception::CodiException);

					/**
					 * @brief method fill register S in buffer
					 * @param buffer buffer
					 * @param regS codi register S
					 * @author Yadickson Soto
					 * @date 25/02/2012
					 */
					void fillRegisterS(Smartmatic::System::SafeBuffer & buffer, CodiRegister_S & regS)
						throw (Smartmatic::System::Exception::CodiException);

					/**
					 * @brief method fill register L in buffer
					 * @param buffer buffer
					 * @param regL codi register L
					 * @author Yadickson Soto
					 * @date 25/02/2012
					 */
					void fillRegisterL(Smartmatic::System::SafeBuffer & buffer, CodiRegister_L & regL)
						throw (Smartmatic::System::Exception::CodiException);

					/**
					 * @brief method fill register C in buffer
					 * @param buffer buffer
					 * @param regC codi register C
					 * @author Yadickson Soto
					 * @date 25/02/2012
					 */
					void fillRegisterC(Smartmatic::System::SafeBuffer & buffer, CodiRegister_C & regC)
						throw (Smartmatic::System::Exception::CodiException);

					/**
					 * @brief method fill register H in buffer
					 * @param buffer buffer
					 * @param currentSize current size
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					void fillRegisterH(Smartmatic::System::SafeBuffer & buffer)
						throw (Smartmatic::System::Exception::CodiException);

					/**
					 * @brief method fill register T in buffer
					 * @param buffer buffer
					 * @author Yadickson Soto
					 * @date 27/02/2012
					 */
					void fillRegisterT(Smartmatic::System::SafeBuffer & buffer)
						throw (Smartmatic::System::Exception::CodiException);

					std::string separator; ///< separator resource name for register C
					std::string currentDate; ///< current date (dd/mm/yyyy)
					std::string currentTime; ///< current time (hh:mm:ss)
					std::string currentRegion; ///< current region name
					std::string currentFile; ///< current codi file
					std::string customniscode; ///< custom NIS code
					std::string codiMachine; ///< codi machine
					std::string codiVotingType; ///< cody voting tipe

					Smartmatic::SAES::Configuration::RegisterCodiConfig registerS; ///< register config
					Smartmatic::SAES::Configuration::RegisterCodiConfig registerL; ///< register config
					Smartmatic::SAES::Configuration::RegisterCodiConfig registerC; ///< register config

					unsigned long currentSize; ///< current size
					Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; ///< electoral configuration
					Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories; ///< saes directories
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}
#endif /* CODIFILEWRAPPER_HXX_ */
