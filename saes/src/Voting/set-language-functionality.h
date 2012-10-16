/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmatic
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmatic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmatic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SET_LANGUAGE_FUNCTIONALITY_H_
#define _SET_LANGUAGE_FUNCTIONALITY_H_

#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Voting
		{
			/**
			 * @brief	Set language functionality. 
			 *
			 * @author	Eduardo.campione
			 * @date	28/04/2011
			 */

			class SetLanguageFunctionality
			{
			public:

                /**
                 * @brief	Gets the current language code.
                 *
                 * @author	Eduardo.campione
                 * @date	28/04/2011
                 *
                 * @return	The current language code.
                 */

                static std::string getCurrentLanguageCode ();

				/**
				 * @brief	Sets a new voting language.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	codeLanguage	The code language.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				static bool SetNewVotingLanguage(std::string codeLanguage);

                /**
                 * @brief	Gets a current language country.
                 *
                 * @author	Eduardo.campione
                 * @date	28/04/2011
                 *
                 * @param [in,out]	language	The language.
                 * @param [in,out]	country 	The country.
                 */

                static void getCurrentLanguageCountry (std::string & language, std::string & country);

				/**
				 * @brief	Sets a new voting language by language country.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 *
				 * @param	language	The language.
				 * @param	country 	The country.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				static bool setNewVotingLanguageByLanguageCountry(std::string language, std::string country);
			protected:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				SetLanguageFunctionality();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Eduardo.campione
				 * @date	28/04/2011
				 */

				~SetLanguageFunctionality();

			private:
				

			};
		}
	}
}

#endif // _SET_LANGUAGE_FUNCTIONALITY_H_
