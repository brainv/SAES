/**
 * @file StringUtils.hxx
 * @brief Header class string utils
 */

#ifndef __STRING_UTILS__
#define __STRING_UTILS__

#include <iostream>
#include <list>
#include <vector>
#include <System/SafeBuffer.h>

namespace Smartmatic
{
    namespace System
    {
        namespace Utils
        {
            /**
             * @class StringUtils
             * @brief Class utils for string manager
             * @author Yadickson Soto yadickson.soto@smartmatic.com
             * @date 13-05-2011
             */
            class StringUtils
            {
            protected:
                /**
                 * @brief Class constructor
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                StringUtils();

            public:
                /**
                 * @brief Method remove first element found
                 * @param input string orig
                 * @param find string find
                 * @return string result
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                static std::string remove(std::string input, std::string find);
                /**
                 * @brief Method remove all element found
                 * @param input string orig
                 * @param find string find
                 * @return string result
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                static std::string removeAll(std::string input, std::string find);
                /**
                 * @brief Method replace first element found
                 * @param input string orig
                 * @param find string find
                 * @param dest element to replace
                 * @return string result
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                static std::string replace(std::string input, std::string find, std::string dest);
                /**
                 * @brief Method replace all element found
                 * @param input string orig
                 * @param find string find
                 * @param dest element to replace
                 * @return string result
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                static std::string replaceAll(std::string input, std::string find, std::string dest);
                /**
                 * @brief Method split string
                 * @param input string orig
                 * @param find string find
                 * @return all element of split
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                static std::list <std::string> split(const std::string & input, const std::string & find);
                /**
                 * @brief Method split string
                 * @param input string orig
                 * @param find string find
                 * @param vector result element of split
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 13-05-2011
                 */
                static void split(const std::string & input, const std::string & find, std::vector <std::string> & vector);
                /**
				 * @brief Method conver array hex to string
				 * @param input array
				 * @param prefix string prefix
				 * @param separator string separator
				 * @return string result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 18-08-2011
				 */
                static std::string arrayHexToString(
                		const std::vector <unsigned char> & input,
                		std::string prefix = "",
                		std::string separator = "");
                /**
				 * @brief Method conver string to array hex
				 * @param input array
				 * @param output vector result
				 * @param prefix string prefix
				 * @param separator string separator
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 18-08-2011
				 */
                static void stringToArrayHex(
                		std::string input,
                		std::vector <unsigned char> & output,
                		std::string prefix = "",
                		std::string separator = "");
                /**
				 * @brief Method conver array hex to string
				 * @param input array
				 * @param prefix string prefix
				 * @param separator string separator
				 * @return string result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 18-08-2011
				 */
                static std::string bufferHexToString(
                		const Smartmatic::System::SafeBuffer & input,
                		std::string prefix = "",
                		std::string separator = "");
                /**
				 * @brief Method conver string to array hex
				 * @param input array
				 * @param output buffer result
				 * @param prefix string prefix
				 * @param separator string separator
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 18-08-2011
				 */
                static void stringToBufferHex(
                		std::string input,
                		Smartmatic::System::SafeBuffer & output,
                		std::string prefix = "",
                		std::string separator = "");

                /**
				 * @brief Method is found character in string
				 * @param text input string
				 * @param character character to find
				 * @return result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 04-05-2012
				 */
                static bool isFound(std::string text, char character);
                /**
				 * @brief Method use regex for match
				 * @param reg input string
				 * @param text text to match
				 * @return result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 04-05-2012
				 */
                static bool regex(std::string reg, std::string text);

                /**
				 * @brief Method trim to string
				 * @param str input string
				 * @return result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 18-08-2011
				 */
                static std::string trim(std::string str);

                /**
				 * @brief Method string to integer
				 * @param str input string
				 * @return result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 03-05-2012
				 */
                static int stringToInt(std::string str);

                /**
				 * @brief Method string to long
				 * @param str input string
				 * @return result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 04-05-2012
				 */
                static long stringToLong(std::string str);

                /**
				 * @brief Method integer to string
				 * @param value input value
				 * @return result
				 * @author Yadickson Soto yadickson.soto@smartmatic.com
				 * @date 03-05-2012
				 */
                static std::string intToString(int value);
            };
        }
    }
}

#endif
