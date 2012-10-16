/*
 * MasterMemoryParser.h
 *
 *  Created on: May 18, 2011
 *      Author: Freddy Gomez
 */

#ifndef MASTERMEMORYPARSER_H_
#define MASTERMEMORYPARSER_H_

#include <string>
#include "Runtime/Environment/MemoryInfo.h"

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {

                /**
                 * @class	MasterMemoryParser
                 *
                 * @brief	Master memory parser. The boot memory.
                 *
                 * @author	Freddy.Gomez
                 * @date	18/05/2011
                 */

                class MasterMemoryParser
                {
                public:
                    /**
                     * @fn	MasterMemoryParser::MasterMemoryParser();
                     *
                     * @brief	Default constructor.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    MasterMemoryParser();
                    /**
                     * @fn	MasterMemoryParser::~MasterMemoryParser();
                     *
                     * @brief	Destructor.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    virtual ~MasterMemoryParser();

                    /**
                     * @fn	MemoryPathController::Load();
                     *
                     * @brief	Load the file and update the fields of the class.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     *
                     */
                    bool Load(std::string filePath);

                    /**
                     * @fn	MemoryPathController::getMemoryInfo();
                     *
                     * @brief	Get the info of the device of the boot memory.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     *
                     * @return the path of the device.
                     */
                    MemoryInfo getMemoryInfo();

                private:
                    MemoryInfo memoryInfo; ///< memory info
                };
            }
        }
    }
}
#endif /* MASTERMEMORYPARSER_H_ */
