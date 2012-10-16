/**
 * @file	guid-class.h
 *
 * @brief	Header file to the guid-class class.
 */



#ifndef _GUID_UTIL_H_
#define _GUID_UTIL_H_

#include <System/Exception/GuIdException.h>
#include <System/SafeBuffer.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace System
	{
		/**
		 * @class	GuidClass
		 *
		 * @brief	Class definition file.
		 *
		 * @author	Freddy Gomez &lt;fgomez@smartmatic.com&gt;
		 * @date	20-02-2011
		 */

		class GuidClass			
		{


			public:

				/**
				 * @brief	Creates a new unique identifier.
				 *
				 * @author	Freddy Gomez 
				 * @date	28/04/2011
				 *
				 * @param	strongest	true to strongest.
				 *
				 * @return	.
				 */

				static GuidClass NewGuid(bool strongest = false);

				/**
				 * @brief	Parses.
				 *
				 * @author	Freddy Gomez 
				 * @date	28/04/2011
				 *
				 * @param [in,out]	stringParam	The string parameter.
				 *
				 * @return	.
				 */

				static GuidClass Parse(std::string stringParam)
					throw (Smartmatic::System::Exception::GuIdException);

				/**
				 * @brief	Convert this object into a string representation.
				 *
				 * @author	Freddy Gomez 
				 * @date	28/04/2011
				 *
				 * @return	A string representation of this object.
				 */

				std::string ToString() const;


				/**
				 * @brief	Encode the GUID binary data as a base64 string.
				 *
				 * @author	Freddy Gomez
				 * @date	07/05/2011
				 *
				 * @return	the string base 64 of the guid data.
				 */

				std::string ToBase64String() const;

				/**
				 * @brief	Converts a sizeOut to the bytes.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else this object as a char*.
				 */

				SafeBuffer toSafeBuffer() const;

				/**
				 * @brief	Default constructor. It fills the guid with nothing
				 *
				 * @author	Freddy Gomez
				 * @date	07/05/2011
				 *
				 */

				GuidClass();

				/**
				 * @brief	Copy constructor.
				 *
				 * @author	Freddy Gomez 
				 * @date	28/04/2011
				 *
				 * @param	guid	Unique identifier.
				 */

				GuidClass(const GuidClass& guid);

				/**
				 * @fn	GuidClass::~GuidClass();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 */

				~GuidClass();

                  /**
                   * @brief	Equality operator.
                   *
                   * @author	Freddy Gomez
                   * @date	28/04/2011
                   *
                   * @param	right	The right.
                   *
                   * @return	true if the parameters are considered equivalent.
                   */

                  bool operator == (const GuidClass& right);                       

                  /**
                   * @brief	Finaliser.
                   *
                   * @author	Freddy Gomez
                   * @date	28/04/2011
                   *
                   * @param	right	The right.
                   *
                   * @return	false if the parameters are considered equivalent.
                   */

                  bool operator != (const GuidClass& right);
			protected:
			private:

               
                unsigned char underlyingUUID[16];  ///< The underlying uuid

				/**
				 * @brief	Constructor.
				 *
				 * @author	Freddy Gomez
				 * @date	28/04/2011
				 *
				 * @param	strongest	true to strongest.
				 */

				GuidClass(bool strongest);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Freddy Gomez
				 * @date	28/04/2011
				 *
				 * @param [in,out]	stringParam	The string parameter.
				 */

				GuidClass(std::string stringParam)
					throw (Smartmatic::System::Exception::GuIdException);



				
				static Smartmatic::Log::ISMTTLog* logger;///< The logger
		};
	}
}
#endif // _GUID_UTIL_H_
