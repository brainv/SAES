/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * PSCIManager.hxx
 * Copyright (C) Daniel Ampuero 2012 <daniel.ampuero@smartmatic.com>
 * 
 * PSCIManager is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * PSCIManager is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <map>
#include <exception>

#include <PCSC/winscard.h>

#include "SCard.hxx"
#include "Parameters.hxx"

using namespace Parameters;

/**
* @autor Daniel Ampuero
*	This is an implementation of the SCard interface using MUSCLE PC/SC.
* Parameter names can be found in "MUSCLE PC/SC Lite API Toolkit API
* Reference Documentation" at 
*	http://www.linuxnet.com/documentation/files/pcsc-lite-0.7.3.pdf
*
*	Altough some data types are refered as pointers in the API description,
*	here are not described as pointers when they are OUT parameters of a
*	function. This is because every parameter has to be indeed a reference
* in memory when it is an OUT parameter.
*/
class PSCIManager : public SCard::SCardManager
{
public:
	/**
	*	Class constructor
	* Context initialization is done here. It relies on local machine 
	*	connection with the Smart Card reader. If a remote machine connection
	* is needed, use the parametric class constructor.
	*/
	PSCIManager();

	/**
	*	Class constructor with parameters
	* Context initialization is done here with a boolean flag indicating if the
	* connection is done with a local service or a remote service.
	*/
	PSCIManager(bool remote);

	/**
	*	Class destructor
	* Context release is done here.
	*/
	~PSCIManager();

	/**
	*	Establish a new context
	*/
	int establishContext();

	/**
	*	Returns the available card readers
	*	@return A vector<string> with the name of the available card
	*					readers plugged into the system.
	*/
	std::vector<std::string> getAvailableReaders();

	/**
	*	Connects to an smart card reader
	*	@param parameter Parameter list as a ParameterSet object
	* @return Connection return value (it depends on the smart card reader driver)
	*/
	int connect(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke connect function.
	* Parameters returned :
	*		Name									Data Type				Type	Description, available values and default value.
	*	
	*		szReader							LPCSTR					IN		Reader name to connect. (can be cast from a char *)
	*																								(default NULL)
	*		dwShareMode						DWORD						IN 		Mode of connection type: exclusive or shared. 
	*																								Available options: [SCARD_SHARE_SHARED, SCARD_SHARE_EXCLUSIVE] 
	*																								(default SCARD_SHARE_SHARED)
	*		dwPreferredProtocols	DWORD						IN  	Desired protocol use.
	*																								Available options: [SCARD_PROTOCOL_T0, SCARD_PROTOCOL_T1, SCARD_PROTOCOL_RAW]
	*																								(default SCARD_PROTOCOL_T1)
	*		hCard									SCARDHANDLE			OUT		Handle to this connection.
	*																								(default 0)
	* 	dwActiveProtocol			DWORD						OUT		Established protocol to this connection
	*																								(default 0)
	* @return A ParameterSet with the set of parameters needed to invoke connect
	*/
	ParameterSet* getConnectParameters();

	/**
	*	Reconects an smart card reader
	* @param parameter Parameter list as a ParameterSet object
	* @return Reconnection return value (it depends on the smart card reader driver)
	*/
	int reconnect(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke reconnect function.
	* Parameters returned :
	*		Name									Data Type				Type	Description, available values and default value.
	*	
	*		hCard									SCARDHANDLE			IN		Handle to a previous call to connect
	*																								(default NULL)
	*		dwShareMode						DWORD						IN 		Mode of connection type: exclusive or shared. 
	*																								Available options: [SCARD_SHARE_SHARED, SCARD_SHARE_EXCLUSIVE] 
	*																								(default SCARD_SHARE_SHARED)
	*		dwPreferredProtocols	DWORD						IN  	Desired protocol use.
	*																								Available options: [SCARD_PROTOCOL_T0, SCARD_PROTOCOL_T1, SCARD_PROTOCOL_RAW]
	*																								(default SCARD_PROTOCOL_T1)
	*		dwInitialization			DWORD						IN 		Desired action taken on the card reader.
	*																								Available options: [SCARD_LEAVE_CARD, SCARD_RESET_CARD, SCARD_UNPOWER_CARD, SCARD_EJECT_CARD]
	*																								(default SCARD_LEAVE_CARD)
	*		dwActiveProtocol			DWORD						OUT		Established protocol to this connection
	*																								(default 0)
	* @return A ParameterSet with the set of parameters needed to invoke reconnect
	*/
	ParameterSet* getReconnectParameters();

	/**
	*	Disconects an smart card reader
	* @param parameter Parameter list as a ParameterSet object
	* @return Disconnection return value (it depends on the smart card reader driver)
	*/
	int disconnect(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke disconnect function.
	* Parameters returned :
	*		Name									Data Type				Type	Description, available values and default value.
	*	
	*		hCard 								SCARDHANDLE			IN		Connection made from SCardConnect.
	*																								(default 0)
	*		dwInitialization			DWORD						IN		Desired action taken on the card reader.
	*																								Available options: [SCARD_LEAVE_CARD, SCARD_RESET_CARD, SCARD_UNPOWER_CARD, SCARD_EJECT_CARD]
	*																								(default SCARD_LEAVE_CARD)
	* @return A ParameterSet with the set of parameters needed to invoke disconnect
	*/
	ParameterSet* getDisconnectParameters();

	/**
	*	Locks an smart card reader for exclusive use
	* On failure, this function will no
	* @param parameter Parameter list as a ParameterSet object
	* @return Lock return value (it depends on the smart card reader driver)
	*/
	int lock(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke lock function.
	* Parameters returned :
	*		Name									Data Type				Type	Description, available values and default value.
	*	
	*		hCard									SCARDHANDLE			IN		Connection made from SCardConnect
	*																								(default 0)
	* @return A ParameterSet with the set of parameters needed to invoke lock
	*/
	ParameterSet* getLockParameters();

	/**
	*	Release a lock on an smart card reader
	* @param parameter Parameter list as a ParameterSet object
	* @return Unlock return value (it depends on the smart card reader driver)
	*/
	int unlock(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke unlock function
	* Parameters returned :
	*		Name									Data Type				Type	Description, available values and default value.
	*	
	*		hCard									SCARDHANDLE			IN		Connection made from SCardConnect.
	*																								(default 0)
	*		dwInitialization			DWORD						IN		Desired action taken on the card reader.
	*																								Available options: [SCARD_LEAVE_CARD, SCARD_RESET_CARD, SCARD_UNPOWER_CARD, SCARD_EJECT_CARD]
	*																								(default SCARD_LEAVE_CARD)
	* @return A ParameterSet with the set of parameters needed to invoke unlock
	*/
	ParameterSet* getUnlockParameters();

	/**
	*	Writes an smart card
	* @param parameter Parameter list as a ParameterSet object
	* @return Write return value (it depends on the smart card reader driver)
	*/
	int write(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke write function
	*	Parameters returned:
	*		Name									Data Type				Type		Description, available values and default value.
	*	
	*		hCard									SCARDHANDLE			IN			Connection made from SCardConnect.
	*																									(default 0)
	*		pioSendPci				LPCSCARD_IO_REQUEST	INOUT		Structure of protocol information.
	*																									Available options: [SCARD_PCI_T0, SCARD_PCI_T1]
	*																									(default SCARD_PCI_T1)
	*		pbSendBuffer					LPCBYTE					IN			APDU to send to the card.
	*																									(default 0)
	*		cbSendLength					DWORD						IN			Length of the APDU.
	*																									(default 0)
	*		pioRecvPci				LPSCARD_IO_REQUEST	IN			Structure of protocol information. (NULL) possible.
	*																									(default NULL)
	*		pbRecvBuffer					LPBYTE					OUT			Response from the card.
	*																									(default NULL)
	*		pcbRecvLength					DWORD						INOUT		Length of the response.
	*																									(default 0)
	* @return A ParameterSet with the set of parameters needed to invoke write
	*/
	ParameterSet* getWriteParameters();

	/**
	*	Gets the current status of the card readers managed by this manager
	*	@param parameter Parameter list as a ParameterSet object
	* @return Status retrieval return value (it depends on the smart card reader driver)
	*/
	int getStatus(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke getStatus function
	*	NOTE: Function name should be getGetStatusParameters() but it sounds redundant
	* 			so it was changed to getStatusParameters()
	* @return A ParameterSet with the set of parameters needed to invoke reconnect
	*/
	ParameterSet* getStatusParameters();

	/**
	*	Waits for an status change of the card readers managed by this manager
	*
	*	If a rgReaderStates null pointer is passed in the ParameterSet, it will be
	* filled with all the available card readers (as they are returned in the 
	*	getAvailableReaders function). Otherwise, the parameter will be used.
	*	The current card state and the spected card state SHOULD be indicated. To do
	* so, include in the ParameterSet the following entries:
	*			Entry								Available values
	*
	*			currentState				[SCARD_STATE_UNAWARE, SCARD_STATE_IGNORE, SCARD_STATE_UNAVAILABLE, SCARD_STATE_EMPTY, SCARD_STATE_PRESENT, SCARD_STATE_ATRMATCH,
	*													 SCARD_STATE_EXCLUSIVE, SCARD_STATE_INUSE, SCARD_STATE_MUTE]
	*			eventState					[SCARD_STATE_IGNORE, SCARD_STATE_CHANGED, SCARD_STATE_UNKNOWN, SCARD_STATE_UNAVAILABLE, SCARD_STATE_EMPTY, SCARD_STATE_PRESENT,
	*													 SCARD_STATE_ATRMATCH, SCARD_STATE_EXCLUSIVE, SCARD_STATE_INUSE, SCARD_STATE_MUTE]
	*	If no current state is specified, SCARD_STATE_UNAWARE will be used and the
	* call will return inmediatly (no matter the blocking time set) with the current
	*	state of the card reader.
	*
	*	NOTE: For detailed information about the meaning of each value, see MUSCLE PC/SC Lite.
	*
	*	@param parameter Parameter list as a ParameterSet object
	* @return Wait return value (it depends on the smart card reader driver)
	*/
	int wait(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke wait function
	*	Parameters returned:
	*		Name									Data Type				Type		Description, available values and default value.
	*
	*		dwTimeout							DWORD						IN			Maximum block waiting time for status change.
	*																									Available options: [INFINITE] and any DWORD in the range (0, INFINITE)
	*																									(default INFINITE)
	*		rgReaderStates		LPSCARD_READERSTATE	INOUT		Structures of readers with current states.
	*																									(default NULL)
	*		cReaders							DWORD						IN			Number of structures.
	*																									(default 0)
	* @return A ParameterSet with the set of parameters needed to invoke wait
	*/
	ParameterSet* getWaitParameters();

	/**
	*	Cancel all pending waits for an status change of the card readers managed by this manager
	*	@param parameter Parameter list as a ParameterSet object
	* @return Wait cancel operation return value (it depends on the smart card reader driver)
	*/
	int cancelWait(ParameterSet* parameters);

	/**
	*	Gets the neccesary parameters to invoke cancelWait function
	* @return A ParameterSet with the set of parameters needed to invoke cancelWait
	*/
	ParameterSet* getCancelWaitParameters();

	/**
	*	Sets the time out
	*	@param timeout
	* @return Timeout setting return value (it depends on the smart card reader driver)
	*/
	int setTimeout(int timeout);

	/**
	*	Returns a human readable error message associated with an error code
	*/
	virtual std::string getErrorMessage(unsigned int errorCode);

	/**
	*	Returns a human readable list of status messages associated with an status code
	*/
	virtual std::vector<std::string> getStatusMessages(unsigned int statusCode);

	class PSCIException : public std::exception
  {
	private:
		/**
		*	Human readable error message
		*/
		std::string errorMsg;
		/**
		*	Original error code
		*/
		int errorCode;
  public:
		/**
		*	Default class constructor
		*/
		PSCIException();

		/**
		*	Parametric class constructor
		* @param errorMsg A human readable error message
		* @param errorCode Original error code
		*/
		PSCIException(std::string errorMsg, int errorCode);
		
		/**
		*	Dumb destructor for making compiler happy
		*/
		~PSCIException() throw();

		/**
		*	Gets the error code with the following format:
		*		<human readable message> with code <original error code>
		* @return A char pointer with the message
		*/
  	virtual const char * what() const throw();

		/**
		*	Gets the human readable error message contained in this exception
		*/
		std::string getErrorMessage();
		
		/**
		*	Gets the error code contained in this exception
		*/
		std::string getErrorCodeAsString();

		/**
		*	Gets the error code contained in this exception
		*/
		int getErrorCode();
  };

private:
	
	/**
	*	Internal variable to store the smart card reader context
	*/
	SCARDCONTEXT hContext;

	/**
	*	Map that associates error codes with a human readable message
	* Don't mess with it!
	*/
	static std::map<int, std::string> errorCodes;

	/**
	*	Map that associates status codes with a human readable message
	* Don't mess with it!
	*/
	static std::map<int, std::string> statusCodes;

	/**
	* Parse the list of readers returned by the PSCI driver into
	* a vector<string>
	*/
	std::vector<std::string> parseReaders(char * mszReaders);

};
