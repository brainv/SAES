/*
 * GpCommandException.h
 *
 *  Created on: Oct 1, 2011
 *      Author: root
 */

#ifndef GPCOMMANDEXCEPTION_H_
#define GPCOMMANDEXCEPTION_H_

#include <exception>
#include <string>

class GpCommandException: public std::exception
{

public:

	GpCommandException(std::string message);
	virtual ~GpCommandException() throw ();

	const char* what () const throw () { return this->mMessage.c_str (); }

private:

	std::string mMessage;

};

#endif /* GPCOMMANDEXCEPTION_H_ */
