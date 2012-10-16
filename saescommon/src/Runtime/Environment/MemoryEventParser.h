/*
 * MemoryEventParser.h
 *
 *  Created on: May 18, 2011
 *      Author: Freddy Gomez
 */

#ifndef MEMORYEVENTPARSER_H_
#define MEMORYEVENTPARSER_H_

#include <string>
#include <vector>
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
                 * @class	MemoryEventParser
                 *
                 * @brief	Memory Event Parser.
                 *
                 * @author	Freddy.Gomez
                 * @date	18/05/2011
                 */
                class MemoryEventParser
                {
                public:

                    enum MemoryEventType
                    {
                         NO_MEMORY_CHANGE
                        ,MEMORY_INSERTED
                        ,MEMORY_REMOVED
                    };

                    /**
                     * @fn	MemoryEventParser::MemoryEventParser();
                     *
                     * @brief	Default constructor.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    MemoryEventParser();

                    /**
                     * @fn	MemoryEventParser::~MemoryEventParser();
                     *
                     * @brief	Default constructor.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     */
                    virtual ~MemoryEventParser();

                    /**
                     * @fn	MemoryEventParser::Load();
                     *
                     * @brief	Load the file and update the fields of the class.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     *
                     */
                    void Load(std::string filePath);

                    std::vector<MemoryInfo> & getUmountedMemories();

                    /**
                     * @fn	MemoryEventParser::getMountedMemories();
                     *
                     * @brief	Get the list of memory mounted in the system
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     * @return a vector of MemoryInfo
                     */
                    std::vector<MemoryInfo> & getMountedMemories();

                    /**
                     * @fn	MemoryEventParser::getLastDetection();
                     *
                     * @brief	Get the Memory Info of the last event.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     *
                     */
                    MemoryInfo getLastDetection();

                    /**
                     * @fn	MemoryEventParser::LastEvent();
                     *
                     * @brief	Get the last event detected.
                     *
                     * @author	Freddy.Gomez
                     * @date	18/05/2011
                     *
                     */
                    MemoryEventType LastEvent();

                private:

                    MemoryInfo lastMemoryInfo;
                    MemoryEventType eventType;
                    std::vector<MemoryInfo> mountedMemories;
                    std::vector<MemoryInfo> umountedMemories;
                };
            }
        }
    }
}

#endif /* MEMORYEVENTPARSER_H_ */
