/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * trunk
 * Copyright (C) SmartMatic 2011 <>
 *
 * @file	PrintDocumentClient.h
 *
 * @brief	Declares the print document client class.

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

#ifndef _PRINTDOCUMENTCLIENT_H_
#define _PRINTDOCUMENTCLIENT_H_

#include "Printing/PrintDocumentResult.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class	PrintDocumentClient
			 *
			 * @brief	Print document client. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class PrintDocumentClient
			{
			public:

				PrintDocumentClient(){}

				virtual ~PrintDocumentClient(){}

				/**
				 * @fn	virtual void PrintDocumentClient::onDocumentPrinted (PrintDocumentResult res)
				 *
				 * @brief	Executes the document printed action.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	res	The resource.
				 */

				virtual void onDocumentPrinted (PrintDocumentResult res){}

			protected:

			private:

			};
		}
	}
}

#endif // _PRINTDOCUMENTCLIENT_H_
