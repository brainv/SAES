/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * SCard.hxx
 * Copyright (C) Daniel Ampuero 2012 <daniel.ampuero@smartmatic.com>
 * 
 * is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SCard is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <vector>
#include <string>

#include "Parameters.hxx"

#ifndef SCARDWRAPPER_HXX_
#define SCARDWRAPPER_HXX_

namespace SCard
{
	/**
	* @autor Daniel Ampuero
	*	Virtual interface for interact with a Smart Card reader. Is not
	*	considered for being used in production code, but to be used in
	* stress tests, altough it is designed for highly generic use.
	*
	*	Using a virtual interface will provide, as a good collateral
	*	effect, the possibility to use Mocking objects in unit tests
	*	involving an Smart Card reader. I would be highly desirable to
	* achieve standarization of this pattern in order to provide
	* flexibility on future releases.
	*/
	class SCardManager
	{
	/**
	*	Public interface
	*/
	public:
		/**
		*	Creates a new SCardManager instance. Context initialization
		*	should be done here. 
		* As this is an pure virtual class (interface), no constructor 
		*	is needed. 
		*/
		//SCardManager() = 0;
	
		/**
		*	Destroy a SCardManager instance. Context release should be
		* done here.
		*/
		virtual ~SCardManager() {};
	
		/**
		*	Establish a new context
		*/
		virtual int establishContext() = 0;

		/**
		*	Returns the available card readers
		*	@return A vector<string> with the name of the available card
		*					readers plugged into the system.
		*/
		virtual std::vector<std::string> getAvailableReaders() = 0;

		/**
		*	Connects to an smart card reader
		*	@param parameter Parameter list as a ParameterSet object
		* @return Connection return value (it depends on the smart card reader driver)
		*/
		virtual int connect(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke connect function
		* @return A ParameterSet with the set of parameters needed to invoke connect
		*/
		virtual Parameters::ParameterSet* getConnectParameters() = 0;

		/**
		*	Reconects an smart card reader
		* @param parameter Parameter list as a ParameterSet object
		* @return Reconnection return value (it depends on the smart card reader driver)
		*/
		virtual int reconnect(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke reconnect function
		* @return A ParameterSet with the set of parameters needed to invoke reconnect
		*/
		virtual Parameters::ParameterSet* getReconnectParameters() = 0;

		/**
		*	Disconects an smart card reader
		* @param parameter Parameter list as a ParameterSet object
		* @return Disconnection return value (it depends on the smart card reader driver)
		*/
		virtual int disconnect(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke disconnect function
		* @return A ParameterSet with the set of parameters needed to invoke disconnect
		*/
		virtual Parameters::ParameterSet* getDisconnectParameters() = 0;

		/**
		*	Locks an smart card reader for exclusive use
		* On failure, this function will no
		* @param parameter Parameter list as a ParameterSet object
		* @return Lock return value (it depends on the smart card reader driver)
		*/
		virtual int lock(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke lock function
		* @return A ParameterSet with the set of parameters needed to invoke lock
		*/
		virtual Parameters::ParameterSet* getLockParameters() = 0;

		/**
		*	Release a lock on an smart card reader
		* @param parameter Parameter list as a ParameterSet object
		* @return Unlock return value (it depends on the smart card reader driver)
		*/
		virtual int unlock(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke unlock function
		* @return A ParameterSet with the set of parameters needed to invoke unlock
		*/
		virtual Parameters::ParameterSet* getUnlockParameters() = 0;

		/**
		*	Writes an smart card
		* @param parameter Parameter list as a ParameterSet object
		* @return Write return value (it depends on the smart card reader driver)
		*/
		virtual int write(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke write function
		* @return A ParameterSet with the set of parameters needed to invoke write
		*/
		virtual Parameters::ParameterSet* getWriteParameters() = 0;

		/**
		*	Gets the current status of the card readers managed by this manager
		*	@param parameter Parameter list as a ParameterSet object
		* @return Status retrieval return value (it depends on the smart card reader driver)
		*/
		virtual int getStatus(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke getStatus function
		*	NOTE: Function name should be getGetStatusParameters() but it sounds redundant
		* 			so it was changed to getStatusParameters()
		* @return A ParameterSet with the set of parameters needed to invoke reconnect
		*/
		virtual Parameters::ParameterSet* getStatusParameters() = 0;

		/**
		*	Waits for an status change of the card readers managed by this manager
		*	@param parameter Parameter list as a ParameterSet object
		* @return Wait return value (it depends on the smart card reader driver)
		*/
		virtual int wait(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke wait function
		* @return A ParameterSet with the set of parameters needed to invoke wait
		*/
		virtual Parameters::ParameterSet* getWaitParameters() = 0;

		/**
		*	Cancel all pending waits for an status change of the card readers managed by this manager
		*	@param parameter Parameter list as a ParameterSet object
		* @return Wait cancel operation return value (it depends on the smart card reader driver)
		*/
		virtual int cancelWait(Parameters::ParameterSet* parameters) = 0;

		/**
		*	Gets the neccesary parameters to invoke cancelWait function
		* @return A ParameterSet with the set of parameters needed to invoke cancelWait
		*/
		virtual Parameters::ParameterSet* getCancelWaitParameters() = 0;

		/**
		*	Sets the time out
		*	@param timeout
		* @return Timeout setting return value (it depends on the smart card reader driver)
		*/
		virtual int setTimeout(int timeout) = 0;

		/**
		*	Returns a human readable error message associated with an error code
		*/
		virtual std::string getErrorMessage(unsigned int errorCode) = 0;

	};
};
#endif /* SCARDWRAPPER_HXX_ */
