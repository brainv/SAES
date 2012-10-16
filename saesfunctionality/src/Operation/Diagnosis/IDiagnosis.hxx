/**
 * @file IDiagnosis.hxx
 * @brief Header interface diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#ifndef IDIAGNOSIS_HXX_
#define IDIAGNOSIS_HXX_

#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Voting/operation-status.h>
#include <glibmm.h>

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
			namespace Diagnosis
			{
				/**
				 * @class IDiagnosis
				 * @brief interface diagnosis
				 * @date 20/10/2011
				 * @author Yadickson Soto
				 */
				class IDiagnosis
				{
				public:
					/**
					 * @brief Class constructor
					 * @param type diagnosis type
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					IDiagnosis(Smartmatic::SAES::Voting::OperationStatus::Diagnostic type);
					/**
					 * @brief Class destroy
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					virtual ~IDiagnosis();
					/**
					 * @brief method getter diagnosis type
					 * @return diagnosis type
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					Smartmatic::SAES::Voting::OperationStatus::Diagnostic getType();
					/**
					 * @brief method setter is diagnosis mandatory
					 * @param mandatory mandatory
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					void setMandatory(bool mandatory);
					/**
					 * @brief method getter is diagnosis mandatory
					 * @return true is diagnosis mandatory
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					bool getMandatory();
					/**
					 * @brief method setter message
					 * @param message new message
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					void setMessage(std::string message);
					/**
					 * @brief method getter current message status
					 * @return current message status
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					std::string getMessage();
					/**
					 * @brief method setter message footer
					 * @param messageFooter new message footer
					 * @date 08/05/2012
					 * @author Yadickson Soto
					 */
					void setMessageFooter(std::string messageFooter);
					/**
					 * @brief method getter current message footer
					 * @return current message footer
					 * @date 08/05/2012
					 * @author Yadickson Soto
					 */
					std::string getMessageFooter();
					/**
					 * @brief method setter timeout
					 * @param time timeout
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					void setTime(int time);
					/**
					 * @brief method getter timeout
					 * @return timeout
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					int getTime();
					/**
					 * @brief method setter current status
					 * @param status current status
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					void setStatus(Smartmatic::SAES::Voting::OperationStatus::DiagStatus status);
					/**
					 * @brief method getter current status
					 * @return status
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					Smartmatic::SAES::Voting::OperationStatus::DiagStatus getStatus();
					/**
					 * @brief virtual method update message
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					virtual void updateMessage() = 0;
					/**
					 * @brief virtual method run diagnosis
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					virtual void test() = 0;
					/**
					 * @brief method getter signal end
					 * @return signal end
					 * @date 20/10/2011
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalEnd();

				protected:

					sigc::signal<void> signalEnd; ///< signal end

				private:

					bool mandatory; ///< mandatory
					std::string message; ///< message status
					std::string messageFooter; ///< message footer
					int valueTime; ///< timeout
					Smartmatic::SAES::Voting::OperationStatus::Diagnostic type; ///< type diagnosis
					Smartmatic::SAES::Voting::OperationStatus::DiagStatus status; ///< status
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* IDIAGNOSIS_HXX_ */
