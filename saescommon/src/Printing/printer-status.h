/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * MachineApplication
 * Copyright (C) Marcel Cordoví Solés 2010 <marcel.cordovi@smartmatic.com>
 * 
 * @file	printer-status.h
 *
 * @brief	Declares the printer status class.
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

#ifndef _PRINTER_STATUS_H_
#define _PRINTER_STATUS_H_
namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class	PrinterStatus
			 *
			 * @brief	Printer status. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class PrinterStatus
			{
				public:

					/**
					 * @fn	PrinterStatus::PrinterStatus ()
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					PrinterStatus ()
						: online (false)
						, processing (false)
						, paper_present (false)
						, paper_jam (false)
				   {}
		
					bool online;	///< true to online
					bool processing;	///< true to processing
					bool paper_present; ///< true to paper present
					bool paper_jam; ///< true to paper jam

					/**
					 * @fn	bool PrinterStatus::operator== (const PrinterStatus);
					 *
					 * @brief	Equality operator.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	PrinterStatus	The printer status.
					 *
					 * @return	true if the parameters are considered equivalent.
					 */

					bool operator== (const PrinterStatus);

					/**
					 * @fn	bool PrinterStatus::operator!= (const PrinterStatus);
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	PrinterStatus	The printer status.
					 */

					bool operator!= (const PrinterStatus);

			protected:

			private:

			};
		}
	}
}


#endif // _PRINTER_STATUS_H_
