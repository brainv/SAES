/**
 * @file Enqueuer.hpp
 * @brief Header template class Enqueuer
 * @date 08/11/2011
 * @author Yadickson Soto
 */

#ifndef ENQUEUER_HPP_
#define ENQUEUER_HPP_

namespace Smartmatic
{
namespace System
{

template <class TQueueObjectIn>
Enqueuer<TQueueObjectIn>::Enqueuer()
{
	pause = false;
	countPushData = 0;
	keepRunning = true;
	isThreadEnabled = false;
	isThreadSleeping = true;
	popPrivDispatcher.connect(sigc::mem_fun(*this, &Enqueuer::handleDispatch));
}

template <class TQueueObjectIn>
Enqueuer<TQueueObjectIn>::~Enqueuer()
{
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::pushObject(TQueueObjectIn saesQueueObject)
{
	{
		std::stringstream ss;
		ss << "Fase # 4 : Push data - count data : " << ++countPushData;
		getLogger()->Debug(ss.str());
	}

	if (keepRunning)
	{
		Glib::Mutex::Lock lock (queue_mutex);
		saesQueue.push(saesQueueObject);

		{
			std::stringstream ss;
			ss << "Fase # 4 : Push data - size queue : " << saesQueue.size();
			getLogger()->Debug(ss.str());
		}

		if (!pause)
		{
			data_cond.signal();
		}
	}
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::StopEnqueuerProcess(bool flushPendingItems, bool waitForExit)
{
	keepRunning = false;

	if(flushPendingItems)
	{
		flush();
	}

	if(isThreadEnabled == true)
	{
		bool wasSleeping = isThreadSleeping;
		data_cond.signal();

		if(waitForExit)
		{
			if(wasSleeping && flushPendingItems == true)
			{
				//A wait here may lock the execution
				WaitForExit();
			}
		}
	}

	countPushData = 0;
}

template <class TQueueObjectIn>
int Enqueuer<TQueueObjectIn>::getQueueSize()
{
	return saesQueue.size();
}

template <class TQueueObjectIn>
bool Enqueuer<TQueueObjectIn>::CheckEnqueuerProcessState()
{
	return isThreadEnabled;
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::StartEnqueuerProcess()
{
	resumeProcess();

	if (!isThreadEnabled)
	{
		keepRunning = true;
		Glib::Thread::create(sigc::mem_fun(*this, &Enqueuer::MainProcess), false);
	}
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::pauseProcess()
{
	pause = true;
	getLogger()->Debug("Pause signal enqueuer");
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::resumeProcess()
{
	pause = false;

	if (!saesQueue.empty())
	{
		data_cond.signal();
	}

	getLogger()->Debug("Resume signal enqueuer");
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::WaitForExit()
{
	getLogger()->Debug("Before wait for thread exit");
	exit_cond.wait(exit_mutex);
	getLogger()->Debug("After wait for thread exit");
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::flush()
{
	getLogger()->Debug("flush queue");

	Glib::Mutex::Lock lock (queue_mutex);
	while (!saesQueue.empty())
	{
		TQueueObjectIn inObject = saesQueue.front();
		saesQueue.pop();
		DiscardItem(inObject);
	}
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::handleDispatch()
{
	getLogger()->Debug("handling signal before mutex");
	Glib::Mutex::Lock lock (syncProcessing_mutex);
	getLogger()->Debug("handling signal after mutex");
	popDispatcher();
	getLogger()->Debug("handling signal after notify");
	syncProcessing_cond.signal();
	getLogger()->Debug("thread unlocked");
}

template <class TQueueObjectIn>
void Enqueuer<TQueueObjectIn>::MainProcess()
{
	Glib::TimeVal wait_period(1,0);
	Glib::TimeVal abs_time;
	isThreadEnabled = true;
	getLogger()->Debug("Starting enqueuer thread");

	while(keepRunning)
	{
		abs_time.assign_current_time();
		abs_time.add(wait_period);

		isThreadSleeping = true;
		data_cond.timed_wait(data_mutex,abs_time);
		isThreadSleeping = false;

		while (!saesQueue.empty() && !pause)
		{
			{
				std::stringstream ss;
				ss << "Fase # 4 : Process data - count data : " << ++countPushData << " - size queue : " << saesQueue.size();
				getLogger()->Debug(ss.str());
			}

			TQueueObjectIn inObject;
			{
				Glib::Mutex::Lock lock (queue_mutex);
				inObject = saesQueue.front();
				saesQueue.pop();
			}

			if(keepRunning == false)
			{
				DiscardItem(inObject);
				break;
			}

			Process(inObject);
			getLogger()->Debug("Fase # 4 : Before signal internal dispatcher");
			popPrivDispatcher();
			//wait for the signal to be processed
			getLogger()->Debug("Fase # 4 : Before wait for processing");
			syncProcessing_cond.wait(syncProcessing_mutex);
			getLogger()->Debug("Fase # 4 : thread running again");

		}

		if (pause) continue;

		//TODO: convert it to a synchronous processing
		emptyDispatcher();

	}
	//signal the thread is exiting
	getLogger()->Debug("Before thread exit signaling");
	exit_cond.signal();
	isThreadEnabled = false;
	getLogger()->Debug("After thread exit signaling");

	countPushData = 0;
}

}
}

#endif /* ENQUEUER_HPP_ */
