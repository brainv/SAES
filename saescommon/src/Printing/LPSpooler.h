/**
 * @file	LPSpooler.h
 *
 * @brief	Declares the pointer to a spooler class.
 */

#ifndef LPSPOOLER_H_
#define LPSPOOLER_H_

#include <string>
#include <queue>
#include <map>
#include <sigc++/sigc++.h>
#include <cups/cups.h>
#include <glibmm/thread.h>

//#include <System/Exception/PrintOperationException.h>


namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
namespace SAES
{

namespace Printing
{
/**
 * @class	LPSpooler
 *
 * @brief	Pointer to a spooler. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class LPSpooler
{

public:

	typedef enum JobStateEnum
	{
		LPSPOOLER_NO_JOBS,          /* No print request has been made so far*/
		LPSPOOLER_SERVER_ERROR,     /* Error communicating with ipp service */
		LPSPOOLER_NO_PRINTER_FOUND, /* No printer was found */
		LPSPOOLER_DEVICE_ERROR,     /* Physical error condition on the printing device*/
		LPSPOOLER_JOB_PENDING,      /* Job is waiting to be printed */
		LPSPOOLER_JOB_HELD,         /* Job is held for printing */
		LPSPOOLER_JOB_PROCESSING,   /* Job is currently printing */
		LPSPOOLER_JOB_STOPPED,      /* Job has been stopped */
		LPSPOOLER_JOB_CANCELED,     /* Job has been canceled */
		LPSPOOLER_JOB_ABORTED,      /* Job has aborted due to error */
		LPSPOOLER_JOB_COMPLETED     /* Job has completed successfully */

	} JobStateEnumType;


	// LIFECYCLE

	/**
	 * @fn	LPSpooler::LPSpooler ();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	LPSpooler ();

	/**
	 * @fn	LPSpooler::LPSpooler(std::string fileToPrint);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	fileToPrint	The file to print.
	 */

	LPSpooler(std::string fileToPrint);

	/**
	 * @fn	LPSpooler::LPSpooler (const LPSpooler& copy);
	 *
	 * @brief	Copy constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	copy	The copy.
	 */

	LPSpooler (const LPSpooler& copy);

	/**
	 * @fn	virtual LPSpooler::~LPSpooler();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~LPSpooler();


	// SIGNALING

	/**
	 * @typedef	sigc::signal<void, JobStateEnumType, Glib::ustring> signal_jobState_t
	 *
	 * @brief	Defines an alias representing the signal job state t. .
	 */

	typedef sigc::signal<void, JobStateEnumType, Glib::ustring> signal_jobState_t;
	signal_jobState_t signalJobStateChanged () { return mSignalJobState; }


	// OPERATORS

	/**
	 * @fn	LPSpooler& LPSpooler::operator=(const LPSpooler& other);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	other	The other.
	 *
	 * @return	A shallow copy of this object.
	 */

	LPSpooler& operator=(const LPSpooler& other);


	// INTERFACE OPERATIONS

	/**
	 * @fn	JobStateEnumType LPSpooler::Print () throw (Smartmatic::System::Exception::PrintOperationException);
	 *
	 * @brief	Submits a job to the named print queue and waits until the end of the print operation
	 * 			in the device is reached monitoring the job state.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	Final status of the operation.
	 *
	 * ### throws	PrintOperationException	on canceling operation failure. Canceling occurs when the
	 * 										hole print operation cannot be completed due to external
	 * 										failure conditions.
	 */

	JobStateEnumType Print (); //throw (Smartmatic::System::Exception::PrintOperationException);

	/**
	 * @fn	JobStateEnumType LPSpooler::PrintChain (std::queue<std::string> filequeue,
	 * 		bool async = false);
	 *
	 * @brief	Submit a sequence of jobs to the named printing queue. In the case the printer queue
	 * 			name is not provided submits to the default printing queue. In both cases connects to
	 * 			the default printing server to make the job request.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	filequeue	The filequeue.
	 * @param	async	 	true to asynchronous.
	 *
	 * @return	.
	 */

	JobStateEnumType PrintChain (std::queue<std::string> filequeue, bool async = false);

	/**
	 * @fn	void LPSpooler::AddOption (const std::string& optionName, const std::string& optionValue);
	 *
	 * @brief	Adds a new option to be passed in subsequent print jobs.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	optionName 	Name of the option.
	 * @param	optionValue	The option value.
	 */

	void AddOption (const std::string& optionName, const std::string& optionValue);

	/**
	 * @fn	void LPSpooler::RemoveOption (const std::string& optionName,
	 * 		const std::string& optionValue);
	 *
	 * @brief	Removes an options which will not be set for subsequent print jobs.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	optionName 	Name of the option.
	 * @param	optionValue	The option value.
	 */

	void RemoveOption (const std::string& optionName, const std::string& optionValue);

	/**
	 * @fn	void LPSpooler::ClearOptions ();
	 *
	 * @brief	Removes all options added so far.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void ClearOptions ();


	// ACCESS

	/**
	 * @fn	void LPSpooler::SetDestName (std::string& destName)
	 *
	 * @brief	Sets a destination name.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	destName	Name of the destination.
	 */

	void SetDestName (std::string& destName)	{ mDestName.assign (destName); }

	/**
	 * @fn	const std::string& LPSpooler::DestName ()
	 *
	 * @brief	Gets the destination name.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	const std::string& DestName () { return mDestName; }

	/**
	 * @fn	void LPSpooler::SetFileName (std::string& fileName)
	 *
	 * @brief	Sets a file name.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	fileName	Filename of the file.
	 */

	void SetFileName (std::string& fileName)	{ mFileName.assign (fileName); }

	/**
	 * @fn	const std::string& LPSpooler::FileName () const
	 *
	 * @brief	Gets the file name.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	const std::string& FileName () const { return mFileName; }

	/**
	 * @fn	long LPSpooler::Id ()
	 *
	 * @brief	Gets the identifier.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	long Id () { return mSpoolerId; }

	/**
	 * @fn	int LPSpooler::JobId ()
	 *
	 * @brief	Gets the job identifier.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	int JobId () { return mJobId; }

	/**
	 * @fn	Glib::ustring LPSpooler::GetSpoolerErrorMessage ( LPSpooler::JobStateEnumType jobState);
	 *
	 * @brief	Translate status enum into a human readable string message.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	jobState	State of the job.
	 *
	 * @return	The spooler error message.
	 */

	Glib::ustring GetSpoolerErrorMessage (
			LPSpooler::JobStateEnumType jobState);

	/**
	 * @fn	const Glib::ustring& LPSpooler::GetSpoolerErrorMessage () const
	 *
	 * @brief	Returns a human readable string representation of the current spooler state.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The spooler error message.
	 */

	const Glib::ustring& GetSpoolerErrorMessage () const { return this->m_StatusMsg; }

	void CancelJobs ();

private:

	long m_StateUnchangedTimeElapsed;   ///< The state unchanged time elapsed
	long mSpoolerId;	///< Identifier for the spooler
	int  mJobId;	///< Identifier for the job

	Glib::ustring m_StatusMsg;  ///< Message describing the status

	std::string mFileName;  ///< Filename of the file
	std::string mDestName;  ///< Name of the destination

	ipp_jstate_t mIppState; ///< State of the ipp
	std::map<std::string, std::string> mJobOptions; ///< Options for controlling the job

	signal_jobState_t mSignalJobState;  ///< State of the signal job


	// Auxiliar

	/**
	 * @fn	JobStateEnumType LPSpooler::mMonitorJobState ();
	 *
	 * @brief	Gets the monitor job state.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	JobStateEnumType mMonitorJobState ();

	/**
	 * @fn	bool LPSpooler::mQueryJobState ();
	 *
	 * @brief	Ms the job state.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool mQueryJobState ();

	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
	
};

}
}
}


#endif /* LPSPOOLER_H_ */
