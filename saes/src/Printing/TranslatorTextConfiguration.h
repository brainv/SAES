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

#ifndef _TRANSLATORTEXTCONFIGURATION_H_
#define _TRANSLATORTEXTCONFIGURATION_H_
#include "Printing/DocumentOptions.h"
#include "Configuration/s-a-e-s-conf-manager.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @brief	Translate the text configuration. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class TranslatorTextConfiguration
			{
			public:

				/**
				 * @brief	Text configuration to document text options.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	textConfiguration	The text configuration.
				 *
				 * @return	.
				 */

				static DocumentTextOptions TextConfigurationToDocumentTextOptions(Smartmatic::SAES::Configuration::TextConfiguration textConfiguration);
			protected:

			private:

			};
		}
	}
}

#endif // _TRANSLATORTEXTCONFIGURATION_H_
