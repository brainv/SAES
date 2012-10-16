/**
 * @file CheckImageFile.hxx
 * @brief Header class check image file
 * @date 29/06/2012
 * @author Yadickson Soto
 */

#ifndef __CHECKIMAGEFILE_HXX__
#define __CHECKIMAGEFILE_HXX__

#include <iostream>

namespace Smartmatic
{
    namespace Graphics
    {
        namespace Image
        {
            /**
             * @class CheckImageFile
             * @brief class check image file
             * @date 29/06/2012
             * @author Yadickson Soto
             */
            class CheckImageFile
            {
            private:
                /**
                 * @brief class constructor
                 * @date 29/06/2012
                 * @author Yadickson Soto
                 */
                CheckImageFile();

            public:
                /**
                 * @brief class destroy
                 * @date 29/06/2012
                 * @author Yadickson Soto
                 */
                virtual ~CheckImageFile();
                /**
                 * @brief methos check image file
                 * @param file file name
                 * @return true is check success
                 * @date 29/06/2012
                 * @author Yadickson Soto
                 */
                static bool check(std::string file);
            };
        }
    }
}

#endif
