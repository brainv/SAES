/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * Parameters.hxx
 * Copyright (C) Daniel Ampuero 2012 <daniel.ampuero@smartmatic.com>
 * 
 * PSCIManager is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Parameters is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <vector>

#include "any.hxx"

#ifndef PARAMETERS_HXX_
#define PARAMETERS_HXX_

namespace Parameters
{
  /**
	*	Generic class to provide generic parameter management.
  * It use boost::any as data type.
	*/
	class Parameter
	{
	public:
		/**
		*	Name given to this parameter
		*/
		std::string name;

		/**
		*	Actual value of this parameter
		*/
		boost::any value;
	
		/**
		*	Class default constructor
		*/
		Parameter() {}

		/**
		*	Class constructor with parameters
		*/
		Parameter(std::string _name, boost::any _value) : name(_name), value(_value) {}

    /**
    * Class copy constructor
    */
		Parameter(const Parameter& other) : name(other.name), value(other.value) {}

		/**
		*	Class destructor
		* Any pointer should be release before calling the class
		* destructor since this class is not aware about pointer
		* using.
		*/
		~Parameter() {}

	};

	/**
	*	Work around to abstract parameters in a single object.
	* Each manager implementation should inherints from this class and
	* declare its own parameters.
	* 
	*	In order to provide flexibility, two functions will be
	* provided: getParameter(parameterName) and setParameter(parameterName, value).
	*/
	class ParameterSet
	{
	public:
		/**
		* Class constructor
		*/
		//ParameterSet() {};
	
		/**
		*	Class destructor
		*/
		virtual ~ParameterSet() {};

		/**
		*	Gets a Parameter by its name
		* @param name An string with the parameter name
		*	@return The requested parameter. If no parameter was found with the given name
		*					an empty string should be set on the name of the returning parameter
		*					object.
		*/
		virtual Parameter& getParameter(std::string name) = 0;

		/**
		*	Sets a parameter value by its name. 
		*	If there is no parameter with the given name, it will be created, set and false
    * will be returned.
		* @param name Parameter name to be set
		* @param value Value to set on the parameter
		* @return True if the parameter already existed in the set, false otherwise and
    *         it was created
		*/
		virtual bool setParameter(std::string name, boost::any value) = 0;

		/**
		*	Sets a parameter by copying
		*	If there is no parameter with the name of the argument parameter, it will be created, 
    * set and false will be returned.
		* @param name Parameter name to be set
		* @param value Value to set on the parameter
		* @return True if the parameter already existed in the set, false otherwise and
    *         it was created
		*/    
    //virtual bool setParameter(Parameter& other) = 0;

    /**
    * Gets the parameter names from a ParameterSet
    * @return A vector<string> containing the names of the parameters in this
    *         ParameterSet
    */
    virtual std::vector<std::string> getParameterNames() = 0;
	};
};
#endif //PARAMETER_HXX_
