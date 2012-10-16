/**
 * @file VMWindow.hxx
 * @brief header class vm window
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#ifndef VMWINDOW_HXX_
#define VMWINDOW_HXX_

#include "RunMachineWindow.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Windows
			{
				/**
				 * @class VMWindow
				 * @brief class voting machine window
				 * @date 02/11/2011
				 * @author Yadickson Soto
				 */
				class VMWindow : public RunMachineWindow
				{
				public:
					/**
					 * @brief class constructor
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					VMWindow();
					/**
					 * @brief class destroy
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual ~VMWindow();
					/**
					 * @brief method start
					 * @return true is start success
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					virtual bool start();
					/**
					 * @brief method pause
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					virtual void pause();
					/**
					 * @brief method stop
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					virtual void stop();

				protected:

					/**
					 * @brief method initialize step widget
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void initialize();
					/**
					 * @brief method clear alarm
					 * @date 17/04/2012
					 * @author Yadickson Soto
					 */
					void clearAlarm();
					/**
					 * @brief method alarm box connected
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					void alarmBoxConnected();
					/**
					 * @brief method alarm box disconnected
					 * @date 17/05/2012
					 * @author Yadickson Soto
					 */
					void alarmBoxDisconnected();
					/**
					 * @brief method alarm box not found
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					void alarmBoxNotFound();
					/**
					 * @brief method update
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					void updateMessage();

				private:

					sigc::connection connAlarmButtom; ///< The connection alarm button
					sigc::connection connAlarmConnected; ///< The connection alarm connected
					sigc::connection connAlarmDisconnected; ///< The connection alarm disconnected
					static Smartmatic::Log::ISMTTLog* logger; ///<logger
				};
			}
		}
	}
}

#endif /* VMWINDOW_HXX_ */
