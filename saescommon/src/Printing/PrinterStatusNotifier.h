/**
 * @file	PrinterStatusNotifier.h
 *
 * @brief	Declares the printer status notifier class.
 */

#ifndef PRINTERSTATUSNOTIFIER_H_
#define PRINTERSTATUSNOTIFIER_H_

#include <gtkmm.h>
#include "Configuration/s-a-e-s-common-conf-manager.h"

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
class PrinterStatusNotifier
{
public:

	typedef enum PhysichalStateEnum
	{
		PSTATE_UNKNOWN = 0,
		PSTATE_READY = 1,
		PSTATE_OUT_OF_PAPER = 2,
		PSTATE_PROCESSING = 4,
		PSTATE_PAPER_JAM = 8,
		PSTATE_COVER_OPEN = 16,
		PSTATE_OFFLINE = 32,
		PSTATE_REJECTING_JOBS = 64,
		PSTATE_NEAR_END_OF_PAPER = 128,

		/* President machine printer only */

		PSTATE_SUPPLYLOW_WARN = 256,
		PSTATE_OUT_OF_TONER = 512,
		PSTATE_CANCELING = 1024,
		PSTATE_CARTRIDGE_NOT_PRESENT = 4096

	} PhysichalStateEnumType;


	// Life cycle

	/**
	 * @fn	PrinterStatusNotifier::PrinterStatusNotifier();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	PrinterStatusNotifier();

	/**
	 * @fn	virtual PrinterStatusNotifier::~PrinterStatusNotifier();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~PrinterStatusNotifier();


	// Access

	/**
	 * @brief returns comma separated, human readable string value for each state
	 * detected.
	 */
	const Glib::ustring& getStatusMessage (bool useCachedValue = false);


	/**
	 * @brief returns a flagged type containing all detected state bits on,
	 * including warnings and the "processing" state.
	 */
	PhysichalStateEnumType getPrinterState (bool useCachedValue = false);

	const Glib::ustring getStatusMessage (PhysichalStateEnumType state); // TODO: Legacy. remove.
	const Glib::ustring getCurrentStatusMessage ();

	/**
	 * @brief returns a flagged type with all error conditions of the current
	 * state bits on (processing is not considered an error condition). Can
	 * be used as a mask for the state obtained from "getPrinterState" to
	 * extract errors when warnings and "printer ready" state values
	 * are not of interest.
	 */
	int getErrorCondition () const;

	/**
	 * @fn	void PrinterStatusNotifier::setUsePrintBlackResources(bool arg);
	 *
	 * @brief	Sets a use print black resources.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	arg	true to argument.
	 */

	void setExternalStatusTrigger (bool arg);
	static void CheckPrinterState (bool check);
	static void runPrintBlank();

protected:

private:

	static bool CheckCurrentState;

	PhysichalStateEnumType mPhState;	///< State of the ph
	Glib::ustring mStatusMessage;   ///< Message describing the status
	bool externalStatusTrigger;	///< true to use external status trigger

	/**
	 * @fn	void PrinterStatusNotifier::mRefreshStatusMessage(bool skipBlankPage = false);
	 *
	 * @brief	Refresh status message.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	skipBlankPage	true to skip blank page.
	 */

	void mRefreshStatusMessage (bool skipBlankPage = false);
	const Glib::ustring mapStatusMessage (PhysichalStateEnumType state);

	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
};

}

}

}

#endif /* PRINTERSTATUSNOTIFIER_H_ */

