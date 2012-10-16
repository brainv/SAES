#include "VMStatusWrapper.hxx"

using namespace Smartmatic::SAES::Voting::Status;

VotingMachineStatusWrapper::VotingMachineStatusWrapper(VotingMachineStatus & vmStatus)
{
	 this->status = vmStatus;
}

VotingMachineStatusWrapper::~VotingMachineStatusWrapper()
{
}

VotingMachineStatus & VotingMachineStatusWrapper::getVotingMachineStatus()
{
    return status;
}

void VotingMachineStatusWrapper::setDeviceStatus(::xsd::cxx::tree::sequence< DeviceStatus > sequence)
{
	status.getDevicesStatus().setDeviceStatus(sequence);
}

DevicesStatus &  VotingMachineStatusWrapper::getDevicesStatus()
{
	return status.getDevicesStatus();
}

std::string	& VotingMachineStatusWrapper::getVMFlags()
{
	return status.getVMFlags();
}

bool & VotingMachineStatusWrapper::getFactoryDiagnoseCompleted()
{
	return status.getFactoryDiagnoseCompleted();
}

long long unsigned int & VotingMachineStatusWrapper::getTransmissionAttempts()
{
	return status.getTransmissionAttempts();
}

DeviceStatus & VotingMachineStatusWrapper::getDeviceStatus( std::string Type ) 
{
	for (DevicesStatus::DeviceStatusIterator
		 v (getDevicesStatus().getDeviceStatus().begin ());
		 v != getDevicesStatus().getDeviceStatus().end ();
		 ++v)
	{
	   if ( Type == (*v).getVMType() )
	   {
		  return *v;
	   }
	}
	return *(getDevicesStatus().getDeviceStatus().begin());
}

std::string	& VotingMachineStatusWrapper::getVMDateTime(DeviceStatus & devStatus)
{
	return devStatus.getVMDateTime();
}

std::string	& VotingMachineStatusWrapper::getVMStatus(DeviceStatus & devStatus)
{
	return devStatus.getVMStatus();
}

std::string	& VotingMachineStatusWrapper::getDiagnoseDescription(DeviceStatus & devStatus)
{
	return devStatus.getDiagnoseDescription();
}

