/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * MachineApplication
 * Copyright (C) Marcel Cordoví Solés 2010 <marcel.cordovi@smartmatic.com>
 * 
 * @file	printer-client.h
 *
 * @brief	Declares the printer client class.
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PRINTER_CLIENT_H_
#define _PRINTER_CLIENT_H_

#include <gtkmm.h>
#include "printer-status.h"



/*
 * Abstract.
 * Interface.
 * Implement in order to get printer services.
 */

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class	PrinterClient
			 *
			 * @brief	Printer client. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class PrinterClient
			{
			public:

				PrinterClient();

				virtual ~PrinterClient();

				/**
				 * @fn	virtual void PrinterClient::job_event_callback (int job_id, int error_code) = 0;
				 *
				 * @brief	Callback, called when the job event.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	job_id	  	Identifier for the job.
				 * @param	error_code	The error code.
				 */

				virtual void job_event_callback (int job_id, int error_code) = 0;

				/**
				 * @fn	virtual void PrinterClient::on_ticket_printed (Gtk::PrintOperationResult result);
				 *
				 * @brief	Handles ticket printed signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	result	The result.
				 */

				virtual void on_ticket_printed (Gtk::PrintOperationResult result);

				/**
				 * @fn	virtual void PrinterClient::on_job_finished ( const Glib::RefPtr<Gtk::PrintOperation>& operation);
				 *
				 * @brief	Handles job finished signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	operation	The operation.
				 */

				virtual void on_job_finished (
					const Glib::RefPtr<Gtk::PrintOperation>& operation);

				/**
				 * @fn	virtual void PrinterClient::on_status_reported (PrinterStatus *status);
				 *
				 * @brief	Handles status reported signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param [in,out]	status	If non-null, the status.
				 */

				virtual void on_status_reported (PrinterStatus *status);

			protected:

			private:

			};
		}
	}
}

#endif // _PRINTER_CLIENT_H_
