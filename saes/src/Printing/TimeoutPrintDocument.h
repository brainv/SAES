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

#ifndef _TIMEOUT_PRINT_DOCUMENT_H_
#define _TIMEOUT_PRINT_DOCUMENT_H_
#include "Printing/BasePrintDocument.h"
#include <Voting/ElectoralConfiguration.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @brief	Timeout print document. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class TimeoutPrintDocument : public BasePrintDocument
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param [in,out]	electoralConfiguration	The electoral configuration.
				 * @param	voteCode					  	The vote code.
				 */

				TimeoutPrintDocument (Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Glib::ustring voteCode);
			protected:

				/**
				 * @brief	Print document.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void PrintDoc();

				/**
				 * @brief	Begins a print.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void BeginPrint();

				/**
				 * @brief	Ends a print.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				void EndPrint();
			private:
				Smartmatic::SAES::Voting::ElectoralConfiguration *_electoralConfiguration;  ///< The electoral configuration
				Glib::ustring _voteCode;	///< The vote code
				Smartmatic::SAES::Configuration::ConfigurationTimeout _configurationTimeoutPrinting;	///< The configuration timeout printing
			};
		}
	}
}

#endif // _TIMEOUT_PRINT_DOCUMENT_H_
