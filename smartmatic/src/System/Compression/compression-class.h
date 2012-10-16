/**
 * @file	compression-class.h
 *
 * @brief	Header file to the compression class class.
 */

#ifndef _COMPRESION_CLASS_H_
#define _COMPRESION_CLASS_H_

#include <zlib.h>
#include <glib.h>
#include <System/SafeBuffer.h>
#include <list>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

    namespace System
    {
        namespace Compression
        {
            /**
             * @class CompressionClass
             * @brief	Compression class.
             *
             * @author	Rafael.gasperi
             * @date	28/04/2011
             */

            class CompressionClass
            {
            private:

                /**
                 * @brief   Inflates.
                 *
                 * @author  Rafael.gasperi
                 * @date    28/04/2011
                 *
                 * @param   data                The data.
                 * @param   size                The size.
                 * @param [in,out]  dest        If non-null, destination for the.
                 * @param [in,out]  outputSize  Size of the output.
                 * @param avail availability data
                 * @return  status.
                 */

                static gint Inflate(const gpointer data, gint size,
                        gpointer* dest, gint& outputSize, int & avail);

                /**
                 * @brief	Deflates.
                 *
                 * @author	Rafael.gasperi
                 * @date	28/04/2011
                 *
                 * @param	data			  	The data.
                 * @param	size			  	The size.
                 * @param [in,out]	dest	  	If non-null, destination for the.
                 * @param [in,out]	outputSize	Size of the output.
                 * @param	level			  	The level.
                 *
                 * @return  status.
                 */

                static gint Deflate(const gpointer data, gint size,
                        gpointer* dest, gint& outputSize,
                        gint level = Z_DEFAULT_COMPRESSION);

            public:

                /**
                 * @brief   Inflate data.
                 *
                 * @author  Yadickson Soto yadickson.soto@smartmatic.com
                 * @date    03/06/2011
                 *
                 * @param   dataIn              The data.
                 * @param dataOut The result
                 * @return  status.
                 */

                static gint Inflate(
                        Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut);

                /**
                 * @brief   Inflate data.
                 *
                 * @author  Yadickson Soto yadickson.soto@smartmatic.com
                 * @date    03/06/2011
                 *
                 * @param   dataIn              The data.
                 * @param 	listDataOut		the data out
                 * @return  status.
                 */
                static gint Inflate(
                        Smartmatic::System::SafeBuffer & dataIn,
                        std::list <Smartmatic::System::SafeBuffer *> & listDataOut);

                /**
                 * @brief   Deflate data.
                 *
                 * @author  Yadickson Soto yadickson.soto@smartmatic.com
                 * @date    03/06/2011
                 *
                 * @param   dataIn              The data.
                 * @param	dataOut				The result
                 * @param   level               The level.
                 *
                 * @return  status.
                 */

                static gint Deflate(
                		Smartmatic::System::SafeBuffer & dataIn,
                		Smartmatic::System::SafeBuffer & dataOut,
						gint level = Z_DEFAULT_COMPRESSION);

            protected:

                /**
                 * @brief method view log status
                 * @param value value status to string
                 * @author  Yadickson Soto yadickson.soto@smartmatic.com
                 * @date    03/06/2011
                 */
                static void viewText(gint value);

            private:

				static Smartmatic::Log::ISMTTLog* logger;/**<logger*/

            };
        }
    }
}
#endif // _COMPRESION_CLASS_H_
