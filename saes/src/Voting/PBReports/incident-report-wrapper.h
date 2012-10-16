/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _INCIDENT_REPORT_WRAPPER_H_
#define _INCIDENT_REPORT_WRAPPER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/incident-report-schema.hxx>
#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

   namespace SAES
   {
      namespace Voting
      {
         namespace PBReports
         {
			/**
			 * @brief	Header class IncidentReportWrapper.
			 *
			 * @author	Marcel Mancini &lt;marcel.mancini@smartmatic.com&gt;
			 * @date	29-03-2011
			 */

			class IncidentReportWrapper
			{
			private:
					IncidentReports* incidentReports;   ///< The incident reports

					/**
					 * @brief	Load the Incident Report
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	xmlFile	The std::string to load.
					 * @return true is load file
					 */

					bool Load(std::string xmlFile)
                    throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);

			public:

					/**
					 * @brief	Class constructor.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					IncidentReportWrapper();

					/**
					 * @brief	Class destroyer.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					~IncidentReportWrapper();					

					/**
					 * @brief	Adds a report. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param [in,out]	report	The report.
					 */

					void AddReport(Report &report);

					/**
					 * @brief	Removes the report described by customCode.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	customCode	The custom code.
					 */

					void RemoveReport(std::string customCode);

					/**
					 * @brief	Modify report.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	report	The report.
					 */

					void ModifyReport(Report report);

					/**
					 * @brief	Gets a report.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @param	customCode	The custom code.
					 *
					 * @return	The report.
					 */

					Report getReport(std::string customCode);

					/**
					 * @brief	Gets the reports.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 * @return	The reports.
					 */

					Reports getReports();

					/**
					 * @brief	Persists.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 *
					 */

					void Persist()
                    throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);

                    /**
                     * @brief	Initialises this object.
                     *
                     * @author	Eduardo.campione
                     * @date	28/04/2011
                     * @return true is load file
                     */

                    bool init ()
                        throw (Smartmatic::System::Exception::CryptoException,
                                 Smartmatic::System::Exception::SignedException,
                                 Smartmatic::System::Exception::XmlException);


                    IncidentReports* getIncidentReports();
					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					void Dispose ();

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
           
		 }
	  }
   }
}

#endif // _INCIDENT_REPORT_WRAPPER_H_
