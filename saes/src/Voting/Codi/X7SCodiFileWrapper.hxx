/**
 * @file X7SCodiFileWrapper.hxx
 * @brief Header class x7s codi file
 * @date 01/03/2012
 * @author Yadickson Soto
 */

#ifndef X7SCODIFILEWRAPPER_HXX_
#define X7SCODIFILEWRAPPER_HXX_

#include <Voting/ElectoralConfiguration.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <System/Exception/CodiException.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <Voting/Codi/x7s-codi-file-schema.hxx>

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
				/**
				 * @class X7SCodiFileWrapper
				 * @brief Class x7s codi file
				 * @date 01/03/2012
				 * @author Yadickson Soto
				 */
				class X7SCodiFileWrapper
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 01/03/2012
					 * @author Yadickson Soto
					 */
					X7SCodiFileWrapper();
					/**
					 * @brief Class destroy
					 * @date 01/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~X7SCodiFileWrapper();

					/**
					 * @brief Method init class
					 * @param electoralConfiguration electoral configuration
					 * @param directories saes directories
					 * @date 02/03/2012
					 * @author Yadickson Soto
					 */
					void init(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration,
							Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories);

					/**
					 * @brief	Method persist x7s codi files
					 * @param codiFile codi file name
					 * @param codiX7SFile codi x7s file
					 * @param pvformFile pv form file
					 * @author	Yadickson Soto
					 * @date 02/03/2012
					 */
					void persistX7SCodiFile(std::string & codiFile, std::string & codiX7SFile, std::string & pvformFile)
						throw (Smartmatic::System::Exception::CryptoException,
								Smartmatic::System::Exception::SignedException,
								Smartmatic::System::Exception::XmlException,
								Smartmatic::System::Exception::CodiException);

					/**
					 * @brief	Method persist x7s codi files
					 * @param 	x7sCodi object x7s Codi
					 * @param 	outString output string result
					 * @author	Yadickson Soto
					 * @date 	02/03/2012
					 */
					void x7sCodiToString(const X7SCodiFile & x7sCodi, std::string& outString)
						throw (Smartmatic::System::Exception::XmlException);

				private:

					Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; ///< electoral configuration
					Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories; ///< saes directories
					bool addPV; ///< flag add pv report
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* X7SCODIFILEWRAPPER_HXX_ */
