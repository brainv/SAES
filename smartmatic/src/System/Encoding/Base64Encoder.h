/*
 * Base64Encoder.h
 *
 *  Created on: May 5, 2011
 *      Author: fgomez
 */

#ifndef BASE64ENCODER_H_
#define BASE64ENCODER_H_

#include <glibmm.h>
#include "System/SafeBuffer.h"

namespace Smartmatic
{
namespace System
{
namespace Encoding
{
/**
	 * @class	Base64Encoder
	 *
	 * @brief	Class definition file.
	 *
	 * @author	Freddy Gomez &lt;fgomez@smartmatic.com&gt;
	 * @date	05-05-2011
	 */
class Base64Encoder {
public:
	/**
	 * @brief	Default Constructor
	 *
	 * @author	Freddy Gomez
	 * @date	05-05-2011
	 *
	 *
	 */
	Base64Encoder();
	/**
		 * @brief	Class destructor.
		 *
		 * @author	Freddy Gomez
		 * @date	04/05/2011
		 *
		 *
		 */
	virtual ~Base64Encoder();
	/**
	 * @brief	Encode a byte array in a base 64 string.
	 *
	 * @author	Freddy Gomez
	 * @date	05/05/2011
	 *
	 * @param [in]	data	pointer to the byte array.
	 * @param [in]	dataLen	Lenght of the byte array.
	 * @return	the string base 64 which represent the buffer.
	 *
	 */
	static Glib::ustring ConvertToBase64(const unsigned char * data, int dataLen);
	/**
	 * @brief	Encode a byte array in a base 64 string.
	 *
	 * @author	Yadickson Soto
	 * @date	05/05/2011
	 *
	 * @param [in]	buffer
	 * @return	the string base 64 which represent the buffer.
	 *
	 */
	static Glib::ustring ConvertToBase64(const Smartmatic::System::SafeBuffer & buffer);

	/**
	 * @brief	Encode a string in a base 64 string.
	 *
	 * @author	Yadickson Soto yadickson.soto@smartmatic.com
	 * @date	18/07/2011
	 *
	 * @param 	data string to convert
	 * @return	the string base 64 which represent the data.
	 *
	 */
	static Glib::ustring ConvertToBase64(Glib::ustring data);
	/**
	 * @brief	Decode a base 64 string .
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	base64String	a base 64 strign to decode.
	 * @return	A SafeBuffer with the decoded data.
	 *
	 */
	static void ConvertFromBase64(Glib::ustring base64String, Smartmatic::System::SafeBuffer & buffer);
	/**
	 * @brief	This method run the process specified in the command line using the popen/pclose function.
	 *
	 * @author	Freddy Gomez
	 * @date	04/05/2011
	 *
	 * @param [in]	testString	A string to test.
	 * @return	true whether the string is in base 64 format.
	 *
	 */
	static bool TestBase64String(Glib::ustring testString);

};

}
}
}
#endif /* BASE64ENCODER_H_ */
