/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SMARTCARDREMOVEDPRINTDOCUMENT_H_
#define _SMARTCARDREMOVEDPRINTDOCUMENT_H_

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
			 * @brief	Smartcard removed print document. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class SmartcardRemovedPrintDocument : public BasePrintDocument
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
				 * @param	timesRemoved				  	The times removed.
				 */

				SmartcardRemovedPrintDocument(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration, Glib::ustring voteCode, int timesRemoved);
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
				Smartmatic::SAES::Voting::ElectoralConfiguration *electoralConfiguration;   ///< The electoral configuration
				Glib::ustring voteCode;
				int timesRemoved;   ///< The times removed
				Smartmatic::SAES::Configuration::ConfigurationSmartcardRemoved configurationSmartcardRemovedPrinting;   ///< The configuration smartcard removed printing

			};
		}
	}
}

#endif // _SMARTCARDREMOVEDPRINTDOCUMENT_H_
