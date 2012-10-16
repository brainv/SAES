/**
 * @file	authenticator-user-rol.h
 *
 * @brief	Declares the authenticator user rol class.
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

#ifndef _AUTHENTICATOR_USER_ROL_H_
#define _AUTHENTICATOR_USER_ROL_H_

#include <iostream>
#include <string.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				/**
				 * @brief	Authenticator user rol. 
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AuthenticatorUserRol
				{
				public:

						/**
						 * @brief	Default constructor.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						AuthenticatorUserRol()
						{
							rol = "";
						}

						std::string rol;	///< The rol to authenticate

				protected:

				private:

				};
			}
		}
	}
}

#endif // _AUTHENTICATOR_USER_ROL_H_
