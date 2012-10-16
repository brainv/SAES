/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * ParameterSetImpl.hxx
 * Copyright (C) Daniel Ampuero 2012 <daniel.ampuero@smartmatic.com>
 * 
 * is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ParameterSetImpl is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <map>
#include <string>

#include "Parameters.hxx"
#include "any.hxx"

#ifndef PARAMETERSETIMPL_HXX_
#define PARAMETERSETIMPL_HXX_

class ParameterSetImpl : public Parameters::ParameterSet
{
private:
	/**
	*	Holds the parameter set in a fast access structure
	*/
	std::map<std::string, Parameters::Parameter> parameters;

	/**
	*	Dummy variable for dummy stuffs
	*/
	Parameters::Parameter dummy;

public:
		/**
		* Class default constructor
		*/
		ParameterSetImpl();
	
		/**
		* Copy constructor
		*/
		ParameterSetImpl(const ParameterSetImpl& other);

		/**
		*	Class destructor
		*/
		~ParameterSetImpl();


		/**
		*	Gets a Parameter by its name
		* @param name An string with the parameter name
		*	@return The requested parameter. If no parameter was found with the given name
		*					an empty string should be set on the name of the returning parameter
		*					object.
		*/
		virtual Parameters::Parameter & getParameter(std::string name);

		/**
		*	Sets a parameter value by its name. 
		*	If no parameter is found with the given name, a false value will be returned.
		* @param name Parameter name to be set
		* @param value Value to set on the parameter
		* @return True on success, i.e., the parameter exist; false otherwise
		*/
		virtual bool setParameter(std::string name, boost::any value);

		/**
		*	Sets a parameter by copying
		*	If there is no parameter with the name of the argument parameter, it will be created, 
    * set and false will be returned.
		* @param name Parameter name to be set
		* @param value Value to set on the parameter
		* @return True if the parameter already existed in the set, false otherwise and
    *         it was created
		*/    
    //virtual bool setParameter(Parameters::Parameter& other);

    /**
    * Gets the parameter names from a ParameterSet
    * @return A vector<string> containing the names of the parameters in this
    *         ParameterSet
    */
    virtual std::vector<std::string> getParameterNames();
};

#endif 
