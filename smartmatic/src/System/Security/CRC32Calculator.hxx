/**
 * @file CRC32Calculator.hxx
 * @brief Header class for CRC32Calculator
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#ifndef __CRC32_CALCULATOR__H__
#define __CRC32_CALCULATOR__H__

#include <System/SafeBuffer.h>

namespace Smartmatic
{
    namespace System
    {
        namespace Security
        {
            /**
             * @class CRC32Calculator
             * @brief Class utility for calculate CRC32
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date 05-06-2011
             */
            class CRC32Calculator
            {
            protected:

                /**
                 * @brief Class constructor
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 05-06-2011
                 */
                CRC32Calculator();

            public:

                /**
                 * @brief Class destroy
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 05-06-2011
                 */
                ~CRC32Calculator();

                /**
                 * @brief method getter crc32 of buffer
                 * @param buffer buffer calculate crc32
                 * @param dataOut crc32 calculator result
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 05-06-2011
                 */
                static void getCRC32(
                        Smartmatic::System::SafeBuffer & buffer,
                        Smartmatic::System::SafeBuffer & dataOut);

            };
        }
    }
}

#endif /*__CRC32_CALCULATOR__H__*/
