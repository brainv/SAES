#include "ElectionStatusWrapper.hxx"

using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;

ElectionStatusWrapper::ElectionStatusWrapper(ElectionStatus & elecStatus)
{
	 this->status = elecStatus;
}

ElectionStatusWrapper::~ElectionStatusWrapper()
{
}

ElectionStatus & ElectionStatusWrapper::getElectionStatus ()
{
    return status;
}

ProcessStatus &  ElectionStatusWrapper::getEletionState()
{
	return status.getState();
}

bool ElectionStatusWrapper::getSynchronizeVotes()
{
	return status.getSynchronizeVotes() == NULL ? false : status.getSynchronizeVotes().get();
}

void ElectionStatusWrapper::setSynchronizeVotes(bool value)
{
	return status.setSynchronizeVotes(value);
}

void  ElectionStatusWrapper::setEletionState(ProcessStatus newState)
{
	status.setState(newState);
}

void ElectionStatusWrapper::setElectionConfigurationReportPrinted(bool arg)
{
	status.setElectionConfigurationReportPrinted(arg);
}

std::string & ElectionStatusWrapper::getStringStatus()
{
	return status.getState();
}

std::string & ElectionStatusWrapper::getOpeningCode()
{
	return status.getOpeningCode();
}

void ElectionStatusWrapper::setOpeningCode(std::string & openingCode)
{
	status.setOpeningCode(openingCode);
}

long long unsigned int & ElectionStatusWrapper::getVotersRegisteredInBook()
{
	return status.getVotersRegisteredInBook();
}

std::string & ElectionStatusWrapper::getOperationModeCode()
{
	return status.getOperationModeCode();
}

bool & ElectionStatusWrapper::getElectionConfigurationReportPrinted()
{
	return status.getElectionConfigurationReportPrinted();
}

std::string   ElectionStatusWrapper::getOpenElectionDate()
{
	return status.getOpenElectionDate();
}

std::string   ElectionStatusWrapper::getCloseElectionDate()
{
	return status.getCloseElectionDate();
}

std::string   ElectionStatusWrapper::getCloseVotingDate()
{
	return status.getCloseVotingDate();
}

void	 ElectionStatusWrapper::setOpenElectionDate(std::string openDate)
{

	status.setOpenElectionDate(openDate);
}

void	 ElectionStatusWrapper::setCloseElectionDate(std::string closeElectionDate)
{
	status.setCloseElectionDate(closeElectionDate);
}

void	 ElectionStatusWrapper::setCloseVotingDate(std::string closeVotingDate)
{
	status.setCloseVotingDate(closeVotingDate);
}

void ElectionStatusWrapper::setContingencyCardCreated (bool contCardCreated)
{
	status.setContingencyCardCreated (contCardCreated);
}

bool ElectionStatusWrapper::getContingencyCardCreated ()
{
	return status.getContingencyCardCreated() == NULL ? false : status.getContingencyCardCreated().get();
}
