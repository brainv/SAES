/**
 * @file Enqueuer.h
 * @brief Header class Enqueuer
 * @date 08/11/2011
 * @author Yadickson Soto
 */

#ifndef _ENQUEUER_H_
#define _ENQUEUER_H_

#include <glibmm.h>
#include <string>
#include <iostream>
#include <Log/ISMTTLog.h>
#include <queue>

namespace Smartmatic
{
	namespace System
	{

			/**
			 * @class Enqueuer
			 * @brief	Enqueuer class. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			template <class TQueueObjectIn>
			class Enqueuer
			{

			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 */
						
				Enqueuer();
				
				/**
				 * @brief	Finaliser.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 */
				virtual ~Enqueuer();

				/**
				 * @brief	Virtual method getter logger
				 * @return	logger
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				virtual Smartmatic::Log::ISMTTLog * getLogger() = 0;

				/**
				 * @brief	Method push new element
				 * @param	saesQueueObject new push template object
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void pushObject(TQueueObjectIn saesQueueObject);

				/**
				 * @brief	Method stop enqueuer process
				 * @param	flushPendingItems clean items in queue
				 * @param	waitForExit wait for exit
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void StopEnqueuerProcess(bool flushPendingItems = true, bool waitForExit = false);

				/**
				 * @brief	Method getter queue size
				 * @return 	queue size
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				int getQueueSize();

				/**
				 * @brief	Method check enqueuer process state
				 * @return	state value
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				bool CheckEnqueuerProcessState();
					
				/**
				 * @brief	Method for start enqueuer process
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void StartEnqueuerProcess();

				/**
				 * @brief	Method for pause enqueuer process
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void pauseProcess();

				/**
				 * @brief	Method for resume enqueuer process
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void resumeProcess();

				/**
				 * @brief	Method for flush process
				 *
				 * @author	Yadickson Soto
				 * @date	23/06/2012
				 *
				 */
				void flush();

				sigc::signal<void> popDispatcher; ///< signal pop dispatcher

			protected:

				Glib::Dispatcher emptyDispatcher; ///< signal empty dispatcher

			protected:
					
				/**
				 * @brief	Virtual method for element process
				 * @param	objectIn object to process
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				virtual void Process(TQueueObjectIn objectIn) = 0 ;

				/**
				 * @brief	Virtual method for discard element
				 * @param	objectIn discard element
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				virtual void DiscardItem(TQueueObjectIn objectIn) = 0;
					
			private:

				long countPushData; ///< count push data for debug
				Glib::Cond data_cond; ///< conditional
				Glib::Mutex data_mutex; ///< mutex for data
				Glib::Mutex queue_mutex; ///< mutes for queue
				Glib::Dispatcher popPrivDispatcher; ///< pop dispatcher
				bool keepRunning; ///< flag for running
				bool isThreadEnabled; ///< flag for thread enable
				bool isThreadSleeping; ///< flag for thread sleep
				bool pause; ///< flag for pause
				std::queue <TQueueObjectIn> saesQueue; ///< queue data

				Glib::Cond syncProcessing_cond; ///< conditional sync processing
				Glib::Mutex syncProcessing_mutex; ///< mutex sync processing

				Glib::Cond exit_cond; ///< conditional exit
				Glib::Mutex exit_mutex; ///< mutex exit

				/**
				 * @brief	Method wait for exit
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void WaitForExit();

				/**
				 * @brief	Method handle dispatch
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void handleDispatch();

				/**
				 * @brief	Method main process
				 *
				 * @author	Yadickson Soto
				 * @date	28/04/2011
				 *
				 */
				void MainProcess();
		};
	}
}

#include "Enqueuer.hpp"

#endif // _ENQUEUER_H_
