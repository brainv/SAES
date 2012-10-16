/*
 * MemoryInfo.h
 *
 *  Created on: May 18, 2011
 *      Author: feddy
 */

#ifndef _MEMORYINFO_H_
#define _MEMORYINFO_H_

#include <iostream>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Runtime
        {
            namespace Environment
            {
                class MemoryInfo
                {
                public:
                    MemoryInfo();

                    /**
                     * @brief Class constructor
                     * @param info line info
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 19/05/2011
                     */
                    MemoryInfo(std::string info);
                    virtual ~MemoryInfo();

                    std::string getDevice();
                    std::string getPath();
                    std::string getSerial();

                    bool isRemove();
                    bool isAdd();
                    bool isMount();

                    void setDevice(std::string devName);
                    void setPath(std::string mountPath);
                    void setSerial(std::string serialNumber);

                    /**
                     * @brief Method setter is mount device
                     * @param mount new flag mount device
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 19/05/2011
                     */
                    void setMount(bool mount);

                    /**
                     * @brief Overloading operator =
                     * @param orig class orig
                     * @return setter all field
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 19/05/2011
                     */
                    //const MemoryInfo & operator= (const MemoryInfo &orig) const;

                private:
                    std::string device;
                    std::string path;
                    std::string serial;
                    bool mount; ///< flag mount device
                    bool remove;
                    bool add;
                };
            }
        }
    }
}
#endif /* _MEMORYINFO_H_ */
