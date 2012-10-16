/**
 * @file AlarmMessage.hxx
 * @brief Header class alarm message text
 * @date 12/04/2012
 * @author Yadickson Soto
 */

#ifndef ALARMMESSAGE_HXX_
#define ALARMMESSAGE_HXX_

#include <string>
#include <Operation/Alarm/AlarmController.hxx>

namespace Smartmatic
{
	namespace
	{
		class Log;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				/**
				 * @class AlarmMessage
				 * @brief class alarm message text
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				class AlarmMessage
				{
				protected:
					/**
					 * @brief class constructor
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					AlarmMessage();

				public:
					/**
					 * @brief class destroy
					 * @date 12/04/2012
					 * @author Yadickson Soto
					 */
					virtual ~AlarmMessage();
					/**
					 * @brief method format alarm type to text
					 * @param alarmType alarm type
					 * @param optionalText optional text
					 * @date 11/04/2012
					 * @author Yadickson Soto
					 */
					static void alarm(Smartmatic::SAES::Functionality::Configuration::AlarmEnum alarmType, std::string optionalText = "");

				private:

					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
				};
			}
		}
	}
}

#endif /* ALARMMESSAGE_HXX_ */
