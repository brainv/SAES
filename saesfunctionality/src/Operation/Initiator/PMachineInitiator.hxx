/**
 * @file	PMachineInitiator.hxx
 * @brief	presidnt machine initiator class.
 */

#ifndef _PMACHINE_INITIATOR_H_
#define _PMACHINE_INITIATOR_H_


#include <Printing/InstallationPrintDocument.h>
#include "Printing/PrintDocumentClient.h"
#include "Printing/PrintDocumentResult.h"
#include "Log/ISMTTLog.h"
#include "IMachineInitiator.hxx"

namespace Smartmatic
{
    namespace SAES 
    {
        namespace Operation
        {
		namespace Initiator
		{
		    /**
		     * @brief	class for president machine initiator.
		     * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
		     * @date	03-03-2011
		     */

		    class PMachineInitiator: public IMachineInitiator, Smartmatic::SAES::Printing::PrintDocumentClient
		    {
		        
		    public:

		    	/**
		    	 * @brief	Constructor.
                 * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date    03-03-2011
		    	 */

		    	PMachineInitiator ();

		    	/**
		    	 * @brief	Finaliser.
                 * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date    03-03-2011
		    	 */

		    	virtual ~PMachineInitiator ();

		        /**
		         * @brief	Method to start machine initiator.
                 * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date    03-03-2011
		         */

		        virtual void start();

		        /**
		         * @brief	Method to dispose machine initiator.
                 * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date    03-03-2011
		         */

		        virtual void dispose();
                /**
                 * @brief Method for check data from media
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 25/05/2011
                 * @return true is check success
                 */
                bool checkData();

                /**
                 * @brief Method for check data from media
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 25/05/2011
                 * @return true is check success
                 */
                bool runFirstTime();

                /**
                 * @brief Method for check data from media
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 25/05/2011
                 * @return true is check success
                 */
                bool runNormalMode();

                /**
                 * @brief Method for check data from media
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 25/05/2011
                 * @return true is check success
                 */
                bool runRecoveryMode(bool copyDomToFlash);

                /**
                 * @brief Method for check data from media in replace machine
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 14/07/2011
                 * @return true is check success
                 */
                bool runReplaceMachineMode();

                /**
                 * @brief Method for check basic data
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 14/07/2011
                 * @return true is check success
                 */
                bool checkBasicConfig();

                virtual int getSuccessMessageTime();

		    private:

		        Smartmatic::SAES::Printing::InstallationPrintDocument*  m_InstallationPrintDocument;	///< The installation print document

		        /**
		         * @brief	Method for run machine initiator.
                 * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date    03-03-2011
		         */

		        void run();

		        /**
		         * @brief	method to check the configuration load.
                 * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date    03-03-2011
		         * @return	true if chack succeeds, false if it fails.
		         */

		        bool CheckConfigurationLoad();

                /**
                 * @brief	Gets the print report.
                 * @return	true if it succeeds, false if it fails.
                 */

                bool printReport();

                bool runNormal; ///< emit signal start application
                int stepTime;
                RunModeType runMode;

				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				/**
				 * @brief	Executessignal_detected.emit(status,true); when the document is printed.
				 * @param	res	The resource.
				 */

				void onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res);

				void endLoad();
		    };
            }
        }
    }
}

#endif // _PMACHINE_INITIATOR_H_
