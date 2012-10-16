/**
 * @file StatisticGroup.hxx
 * @brief Header class StatisticGroup
 */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _STATISTIC_GROUP_H_
#define _STATISTIC_GROUP_H_

#include <iostream>
#include <list>
#include <Voting/PBReports/StatisticWrapper.hxx>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Voting
        {
            namespace PBReports
            {
                /**
                 * @brief	Header class StatisticGroup.
                 *
                 * @author	Yadickson Soto yadickson.soto@smartmatic.com
                 * @date	04-05-2011
                 */
                class StatisticGroup
                {
                private:

                    bool state; /**< state*/
                    bool vertical; ///< vertical filling
                    unsigned int pivot; ///< pivot filling
                    std::string nameKey; /**< name*/
                    std::string editInfoKey; /**< edit info*/
                    std::string blockerInfoKey; /**< edit info*/
                    std::list<StatisticWrapper*> list; /**< statistic list*/

                public:

                    /**
                     * @brief	Class constructor.
                     *
                     * @author	Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    StatisticGroup();
                    /**
                     * @brief	Class destroyer.
                     *
                     * @author	Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    ~StatisticGroup();
                    /**
                     * @brief Method add statistic
                     *
                     * @param statistic set new statistic
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void addStatistic(StatisticWrapper * statistic);
                    /**
                     * @brief Method setter name key
                     *
                     * @param nameKey name key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::string getName();
                    /**
                     * @brief Method setter name key
                     *
                     * @param nameKey name key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void setNameKey(std::string nameKey);
                    /**
                     * @brief Method getter name key
                     *
                     * @return name key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::string getNameKey();
                    /**
                     * @brief Method setter edit info key
                     *
                     * @param editInfoKey edit info key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void setEditInfoKey(std::string editInfoKey);
                    /**
                     * @brief Method getter edit info key
                     *
                     * @return edit info key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::string getEditInfoKey();
                    /**
                     * @brief Method setter blocker info key
                     *
                     * @param blockerInfoKey blocker info key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void setBlockerInfoKey(std::string blockerInfoKey);
                    /**
                     * @brief Method getter blocker info key
                     *
                     * @return blocker info key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::string getBlockerInfoKey();
                    /**
                     * @brief Method setter state
                     *
                     * @param state new state
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    08-05-2011
                     */
                    void setState(bool state);
                    /**
                     * @brief Method getter state
                     *
                     * @return state
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    08-05-2011
                     */
                    bool getState();
                    /**
                     * @brief Method setter vertical filling
                     *
                     * @param vertical vertical filling
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    21-05-2012
                     */
                    void setVerticalFilling(bool vertical);
                    /**
                     * @brief Method getter vertical filling
                     *
                     * @return true is vertical filling
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    21-05-2012
                     */
                    bool isVerticalFilling();
                    /**
                     * @brief Method getter edit or blocker info key
                     *
                     * @return edit or blocker info key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    08-05-2011
                     */
                    std::string getInfoKey();
                    /**
                     * @brief Method getter edit or blocker info key
                     *
                     * @return edit or blocker info key
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    08-05-2011
                     */
                    std::string getInfo();
                    /**
                     * @brief Method setter pivot filling
                     *
                     * @param pivot pivot filling
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    30-05-2012
                     */
                    void setPivot(unsigned int pivot);
                    /**
                     * @brief Method getter pivot filling
                     *
                     * @return pivot filling
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    30-05-2012
                     */
                    unsigned int getPivot();
                    /**
                     * @brief Method getter all statistic
                     *
                     * @return  all statistic
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::list<StatisticWrapper*> getStatistics();
                };
            }
        }
    }
}

#endif // _STATISTIC_MANAGER_H_
