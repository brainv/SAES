/**
 * @file	functionality-initiator.h
 *
 * @brief	Declares the functionality initiator class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FUNCTIONALITY_INITIATOR_H_
#define _FUNCTIONALITY_INITIATOR_H_

#include <Operation/Authenticator/IAuthenticator.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				/**
				 * @brief	Manage the initiator functionality.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class FunctionalityInitiator
				{
					
				public:

					/**
					 * @brief	Registers this object.
					 *
					 * @author	Fsilva
					 * @date	28/04/2011
					 */

					static void Register();

				protected:

				private:

				};
			}
		}
	}
}

#endif // _FUNCTIONALITY_INITIATOR_H_
