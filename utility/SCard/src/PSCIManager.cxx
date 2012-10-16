#include <stdio.h>
#include <string.h>

#include <iostream>

#include <PCSC/winscard.h>

#include "PSCIManager.hxx"
#include "ParameterSetImpl.hxx"


PSCIManager::PSCIManager()
{
  LONG returnValue = SCardEstablishContext( SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext );
  if(returnValue != SCARD_S_SUCCESS)   
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
}

PSCIManager::PSCIManager(bool remote)
{
#ifdef SCARD_SCOPE_GLOBAL
  LONG returnValue = SCardEstablishContext( remote?SCARD_SCOPE_GLOBAL:SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext );
#else
  LONG returnValue = SCardEstablishContext( SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext );
#endif
  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
}

PSCIManager::~PSCIManager()
{
  LONG returnValue = SCardReleaseContext( hContext );
  if(returnValue != SCARD_S_SUCCESS)   
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
}

int PSCIManager::establishContext()
{
  LONG returnValue = SCardEstablishContext( SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext );
  if(returnValue != SCARD_S_SUCCESS)   
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
  return returnValue;
}

std::vector<std::string> PSCIManager::getAvailableReaders()
{
  LPSTR mszGroups = NULL;
	DWORD dwReaders;
	LONG returnValue;
	
	returnValue = SCardListReaders( hContext, NULL, NULL, &dwReaders );
  if(returnValue != SCARD_S_SUCCESS)   
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);

	LPSTR mszReaders = (LPSTR)malloc(sizeof(char)*dwReaders);
	
  returnValue = SCardListReaders( hContext, mszGroups, mszReaders, &dwReaders );
  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);

  std::vector<std::string> result = parseReaders(mszReaders);
  delete mszReaders;

	return result;
}

int PSCIManager::connect(ParameterSet * parameters)
{
  LONG returnValue = SCardConnect( 
      hContext, 
      boost::any_cast<LPCSTR>(parameters->getParameter("szReader"). value),
      boost::any_cast<DWORD>(parameters->getParameter("dwShareMode").value),
      boost::any_cast<DWORD>(parameters->getParameter("dwPreferredProtocols").value), 
      boost::any_cast<SCARDHANDLE>(&parameters->getParameter("hCard").value),
      boost::any_cast<DWORD>(&parameters->getParameter("dwActiveProtocol").value) );

  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
  return returnValue;
}

ParameterSet* PSCIManager::getConnectParameters()
{
  ParameterSet * parameters = new ParameterSetImpl();
  parameters->setParameter("szReader", (LPSTR)NULL);
  parameters->setParameter("dwShareMode", (DWORD)SCARD_SHARE_SHARED);
  parameters->setParameter("dwPreferredProtocols", (DWORD)SCARD_PROTOCOL_T1);
  parameters->setParameter("hCard", (SCARDHANDLE)0);
  parameters->setParameter("dwActiveProtocol", (DWORD)0);
  return parameters;
}


int PSCIManager::reconnect(ParameterSet* parameters)
{
  LONG returnValue = SCardReconnect( 
      boost::any_cast<SCARDHANDLE>(parameters->getParameter("hCard").value),
      boost::any_cast<DWORD>(parameters->getParameter("dwShareMode").value),
      boost::any_cast<DWORD>(parameters->getParameter("dwPreferredProtocols").value),
      boost::any_cast<DWORD>(parameters->getParameter("dwInitialization").value),
      boost::any_cast<DWORD>(&parameters->getParameter("dwActiveProtocol").value) );

  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
  return returnValue;
}

ParameterSet* PSCIManager::getReconnectParameters()
{
  ParameterSet* parameters = new ParameterSetImpl();
  parameters->setParameter("hCard", (SCARDHANDLE)0);
  parameters->setParameter("dwShareMode", (DWORD)SCARD_SHARE_SHARED);
  parameters->setParameter("dwPreferredProtocols", (DWORD)SCARD_PROTOCOL_T1);
  parameters->setParameter("dwInitialization", (DWORD)SCARD_LEAVE_CARD);
  parameters->setParameter("dwActiveProtocol", (DWORD)0);
  return parameters;
}

int PSCIManager::disconnect(ParameterSet* parameters)
{
  LONG returnValue = SCardDisconnect( 
    boost::any_cast<SCARDHANDLE>(parameters->getParameter("hCard").value),
    boost::any_cast<DWORD>(parameters->getParameter("dwDisposition").value));

  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
  return returnValue;
}

ParameterSet* PSCIManager::getDisconnectParameters()
{
  ParameterSet* parameters = new ParameterSetImpl();
  parameters->setParameter("hCard", (SCARDHANDLE)0);
  parameters->setParameter("dwDisposition", (DWORD)SCARD_LEAVE_CARD);
  return parameters;
}

int PSCIManager::lock(ParameterSet* parameters)
{
  LONG returnValue = SCardBeginTransaction( 
      boost::any_cast<SCARDHANDLE>(parameters->getParameter("hCard").value));

  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
  return returnValue;
}

ParameterSet* PSCIManager::getLockParameters()
{
  ParameterSet* parameters = new ParameterSetImpl();
  parameters->setParameter("hCard", (SCARDHANDLE)0);
  return parameters;
}

int PSCIManager::unlock(ParameterSet* parameters)
{
  LONG returnValue = SCardEndTransaction( 
    boost::any_cast<SCARDHANDLE>(parameters->getParameter("hCard").value),
    boost::any_cast<DWORD>(parameters->getParameter("dwDisposition").value));
  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);
  return returnValue;
}

ParameterSet* PSCIManager::getUnlockParameters()
{
  ParameterSet* parameters = new ParameterSetImpl();
  parameters->setParameter("hCard", (SCARDHANDLE)0);
  parameters->setParameter("dwDisposition", (DWORD)SCARD_LEAVE_CARD);
  return parameters;
}

int PSCIManager::write(ParameterSet* parameters)
{
  // Setting up the receiving pci
  SCARD_IO_REQUEST * pioRecvPci = new SCARD_IO_REQUEST;

  // Setting up the receiving buffer
  const int KB = 1024;
  DWORD unitSize = KB/2;
  BYTE * pbRecvBuffer = new BYTE[unitSize];
  DWORD recvBufferSize = unitSize;

  LONG returnValue = SCardTransmit( 
    boost::any_cast<SCARDHANDLE>(parameters->getParameter("hCard").value),
    boost::any_cast<LPCSCARD_IO_REQUEST>(parameters->getParameter("pioSendPci").value),
    boost::any_cast<LPCBYTE>(parameters->getParameter("pbSendBuffer").value), 
    boost::any_cast<DWORD>(parameters->getParameter("cbSendLength").value),
    pioRecvPci,
    pbRecvBuffer,
    &recvBufferSize );

  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);

  //Write back to the parameters the returned objects
  parameters->setParameter("pioRecvPci", pioRecvPci);
  parameters->setParameter("pbRecvBuffer", pbRecvBuffer);
  parameters->setParameter("pcbRecvLenght", recvBufferSize);

  return returnValue;
}

ParameterSet* PSCIManager::getWriteParameters()
{
  ParameterSet* parameters = new ParameterSetImpl();
  parameters->setParameter("hCard", (SCARDHANDLE)0);
  parameters->setParameter("pioSendPci", (LPCSCARD_IO_REQUEST)SCARD_PCI_T1);
  parameters->setParameter("pbSendBuffer", (LPCBYTE)NULL);
  parameters->setParameter("cbSendLength", (DWORD)0);
  parameters->setParameter("pioRecvPci", (LPSCARD_IO_REQUEST)NULL);
  parameters->setParameter("pbRecvBuffer", (LPBYTE)NULL);
  parameters->setParameter("pcbRecvLength", (DWORD)0);
  return parameters;
}

int PSCIManager::getStatus(ParameterSet* parameters)
{
  return 0;
}

ParameterSet* PSCIManager::getStatusParameters()
{
  return (ParameterSet*)NULL;
}

int PSCIManager::wait(ParameterSet* parameters)
{
  LPSCARD_READERSTATE rgReaderStates = boost::any_cast<LPSCARD_READERSTATE>(parameters->getParameter("rgReaderStates").value);
  DWORD cReaders = boost::any_cast<DWORD>(parameters->getParameter("cReaders").value);
  //  Reader state initialization
  if(rgReaderStates==NULL && cReaders==0)
  {
    std::vector<std::string> readers = getAvailableReaders();
    rgReaderStates = new SCARD_READERSTATE[readers.size()];
    cReaders = readers.size();
    for(int i=0; i<static_cast<int>(readers.size()); ++i) 
      rgReaderStates[i].szReader = strdup(readers[i].c_str());
  }
  for(int i=0; i<static_cast<int>(cReaders); ++i)
  {
      Parameter currentState = parameters->getParameter("currentState");  
      if(currentState.name != "")
        rgReaderStates[i].dwCurrentState = boost::any_cast<DWORD>(currentState.value);
      else
        rgReaderStates[i].dwCurrentState = SCARD_STATE_UNAWARE;

      Parameter eventState = parameters->getParameter("eventState");  
      if(eventState.name != "")
        rgReaderStates[i].dwEventState = boost::any_cast<DWORD>(eventState.value);
      else
        rgReaderStates[i].dwEventState = SCARD_STATE_CHANGED;
  }

/*DEBUG
  std::cout << "cReaders =" << cReaders << std::endl;
  std::cout << "szReaders =" << rgReaderStates[0].szReader << std::endl;
  std::cout << "timeOut =" << std::hex << boost::any_cast<DWORD>(parameters->getParameter("dwTimeout").value) << std::endl;
  std::cout << "currentState =" << rgReaderStates[0].dwCurrentState << std::endl;
  std::cout << "eventState =" << rgReaderStates[0].dwEventState << std::endl;
*/

  LONG returnValue = SCardGetStatusChange(
    hContext,
    boost::any_cast<DWORD>(parameters->getParameter("dwTimeout").value),
    rgReaderStates,
    cReaders);
    
  if(returnValue != SCARD_S_SUCCESS)    
    throw PSCIException(errorCodes[returnValue], errorCodes.find(returnValue)->first);

  //  Write back the returned status into parameters
  parameters->setParameter("rgReaderStates", (LPSCARD_READERSTATE)rgReaderStates);
  parameters->setParameter("cReaders", (DWORD)cReaders);

  return 0;
}

ParameterSet* PSCIManager::getWaitParameters()
{
  ParameterSet* parameters = new ParameterSetImpl();
  parameters->setParameter("dwTimeout", (DWORD)INFINITE);
  parameters->setParameter("rgReaderStates", (LPSCARD_READERSTATE)NULL);
  parameters->setParameter("cReaders", (DWORD)0);
  return parameters;;
}

int PSCIManager::cancelWait(ParameterSet* parameters)
{
  return 0;
}


ParameterSet* PSCIManager::getCancelWaitParameters()
{
  return (ParameterSet*)NULL;
}

int PSCIManager::setTimeout(int timeout)
{
  return 0;
}

std::string PSCIManager::getErrorMessage(unsigned int errorCode)
{
  return errorCodes[errorCode];
}

std::vector<std::string> PSCIManager::getStatusMessages(unsigned int statusCode)
{
  std::vector<std::string> result;
  if(statusCode == SCARD_STATE_UNAWARE)
  {
    result.push_back(statusCodes[statusCode]);
    return result;
  }
  for(std::map<int, std::string>::iterator iter = statusCodes.begin(); iter != statusCodes.end(); iter++)
  {
    if(statusCode & iter->first)
      result.push_back(iter->second);
  }
  return result;
}

PSCIManager::PSCIException::PSCIException()
{
	errorMsg = "An error with the PSCIManager has ocurred";
}

PSCIManager::PSCIException::~PSCIException() throw() {}

PSCIManager::PSCIException::PSCIException(std::string _errorMsg, int _errorCode) : errorMsg(_errorMsg), errorCode(_errorCode) {}
		
const char * PSCIManager::PSCIException::what() const throw()
{
	char buff[32]; 
	sprintf(buff, "%X", errorCode);
	std::string result = errorMsg + " Exit code: " + std::string(buff);
 	return result.c_str();
}

std::string PSCIManager::PSCIException::getErrorMessage()
{
  return errorMsg;
}
		
std::string PSCIManager::PSCIException::getErrorCodeAsString()
{
  char buff[32]; 
	sprintf(buff, "%X", errorCode);
  return std::string(buff);
}

int PSCIManager::PSCIException::getErrorCode()
{
  return errorCode;
}

std::vector<std::string> PSCIManager::parseReaders(char * mszReaders)
{
  std::vector<std::string> result;
	int idx = 0;
	while(mszReaders[idx]!='\0')
	{
    std::string current;
		for(int i=idx; mszReaders[i]; ++i, ++idx)
			current += mszReaders[i];
		result.push_back(current);
		++idx;
	}
  return result;
}

std::map<int, std::string> PSCIManager::errorCodes = 
  {
    {SCARD_S_SUCCESS, "No error was encountered."},
    {SCARD_F_INTERNAL_ERROR, "An internal consistency check failed."},
    {SCARD_E_CANCELLED, "The action was cancelled by an SCardCancel request."},
    {SCARD_E_INVALID_HANDLE, "The supplied handle was invalid."},
    {SCARD_E_INVALID_PARAMETER, "One or more of the supplied parameters could not be properly interpreted."},
    {SCARD_E_INVALID_TARGET, "Registry startup information is missing or invalid."},
    {SCARD_E_NO_MEMORY, "Not enough memory available to complete this command."},
    {SCARD_F_WAITED_TOO_LONG, "An internal consistency timer has expired."},
    {SCARD_E_INSUFFICIENT_BUFFER, "The data buffer to receive returned data is too small for the returned data."},
    {SCARD_E_UNKNOWN_READER, "The specified reader name is not recognized."},
    {SCARD_E_TIMEOUT, "The user-specified timeout value has expired."},
    {SCARD_E_SHARING_VIOLATION, "The smart card cannot be accessed because of other connections outstanding."},
    {SCARD_E_NO_SMARTCARD, "The operation requires a Smart Card, but no Smart Card is currently in the device."},
    {SCARD_E_UNKNOWN_CARD, "The specified smart card name is not recognized."},
    {SCARD_E_CANT_DISPOSE, "The system could not dispose of the media in the requested manner."},
    {SCARD_E_PROTO_MISMATCH, "The requested protocols are incompatible with the protocol currently in use with the smart card."},
    {SCARD_E_NOT_READY, "The reader or smart card is not ready to accept commands."},
    {SCARD_E_INVALID_VALUE, "One or more of the supplied parameters values could not be properly interpreted."},
    {SCARD_E_SYSTEM_CANCELLED, "The action was cancelled by the system, presumably to log off or shut down."},
    {SCARD_F_COMM_ERROR, "An internal communications error has been detected."},
    {SCARD_F_UNKNOWN_ERROR, "An internal error has been detected, but the source is unknown."},
    {SCARD_E_INVALID_ATR, "An ATR obtained from the registry is not a valid ATR string."},
    {SCARD_E_NOT_TRANSACTED, "An attempt was made to end a non-existent transaction."},
    {SCARD_E_READER_UNAVAILABLE, "The specified reader is not currently available for use."},
    {SCARD_P_SHUTDOWN, "The operation has been aborted to allow the server application to exit."},
    {SCARD_E_PCI_TOO_SMALL, "The PCI Receive buffer was too small."},
    {SCARD_E_READER_UNSUPPORTED, "The reader driver does not meet minimal requirements for support."},
    {SCARD_E_DUPLICATE_READER, "The reader driver did not produce a unique reader name."},
    {SCARD_E_CARD_UNSUPPORTED, "The smart card does not meet minimal requirements for support."},
    {SCARD_E_NO_SERVICE, "The Smart card resource manager is not running."},
    {SCARD_E_SERVICE_STOPPED, "The Smart card resource manager has shut down."},
    {SCARD_E_UNEXPECTED, "An unexpected card error has occurred."},
    {SCARD_E_UNSUPPORTED_FEATURE, "This smart card does not support the requested feature."},
    {SCARD_E_ICC_INSTALLATION, "No primary provider can be found for the smart card."},
    {SCARD_E_ICC_CREATEORDER, "The requested order of object creation is not supported."},
    {SCARD_E_DIR_NOT_FOUND, "The identified directory does not exist in the smart card."},
    {SCARD_E_FILE_NOT_FOUND, "The identified file does not exist in the smart card."},
    {SCARD_E_NO_DIR, "The supplied path does not represent a smart card directory."},
    {SCARD_E_NO_FILE, "The supplied path does not represent a smart card file."},
    {SCARD_E_NO_ACCESS, "Access is denied to this file."},
    {SCARD_E_WRITE_TOO_MANY, "The smart card does not have enough memory to store the information."},
    {SCARD_E_BAD_SEEK, "There was an error trying to set the smart card file object pointer."},
    {SCARD_E_INVALID_CHV, "The supplied PIN is incorrect."},
    {SCARD_E_UNKNOWN_RES_MNG, "An unrecognized error code was returned from a layered component."},
    {SCARD_E_NO_SUCH_CERTIFICATE, "The requested certificate does not exist."},
    {SCARD_E_CERTIFICATE_UNAVAILABLE, "The requested certificate could not be obtained."},
    {SCARD_E_NO_READERS_AVAILABLE, "Cannot find a smart card reader."},
    {SCARD_E_COMM_DATA_LOST, "A communications error with the smart card has been detected. Retry the operation."},
    {SCARD_E_NO_KEY_CONTAINER, "The requested key container does not exist on the smart card."},
    {SCARD_E_SERVER_TOO_BUSY, "The Smart Card Resource Manager is too busy to complete this operation."},
    {SCARD_W_UNSUPPORTED_CARD, "The reader cannot communicate with the card, due to ATR string configuration conflicts."},
    {SCARD_W_UNRESPONSIVE_CARD, "The smart card is not responding to a reset."},
    {SCARD_W_UNPOWERED_CARD, "Power has been removed from the smart card, so that further communication is not possible."},
    {SCARD_W_RESET_CARD, "The smart card has been reset, so any shared state information is invalid."},
    {SCARD_W_REMOVED_CARD, "The smart card has been removed, so further communication is not possible."},
    {SCARD_W_SECURITY_VIOLATION, "Access was denied because of a security violation."},
    {SCARD_W_WRONG_CHV, "The card cannot be accessed because the wrong PIN was presented."},
    {SCARD_W_CHV_BLOCKED, "The card cannot be accessed because the maximum number of PIN entry attempts has been reached."},
    {SCARD_W_EOF, "The end of the smart card file has been reached."},
    {SCARD_W_CANCELLED_BY_USER, "The user pressed \"Cancel\" on a Smart Card Selection Dialog."},
    {SCARD_W_CARD_NOT_AUTHENTICATED, "No PIN was presented to the smart card."}
  };

std::map<int, std::string> PSCIManager::statusCodes = 
  {
    {SCARD_STATE_UNAWARE, "App wants status"},
    {SCARD_STATE_IGNORE, "Ignore this reader"},
    {SCARD_STATE_CHANGED, "State has changed"},
    {SCARD_STATE_UNKNOWN, "Reader unknown"},
    {SCARD_STATE_UNAVAILABLE, "Status unavailable"},
    {SCARD_STATE_EMPTY, "Card removed"},
    {SCARD_STATE_PRESENT, "Card inserted"},
    {SCARD_STATE_ATRMATCH, "ATR matches card"},
    {SCARD_STATE_EXCLUSIVE, "Exclusive Mode"},
    {SCARD_STATE_INUSE, "Shared Mode"},
    {SCARD_STATE_MUTE, "Unresponsive card"},
    {SCARD_STATE_UNPOWERED, "Unpowered card"}
  };

