/**
 * @file StatisticManager.hxx
 * @brief Header class StatisticManager
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

#ifndef _STATISTIC_MANAGER_H_
#define _STATISTIC_MANAGER_H_

#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>
#include <Voting/PBReports/StatisticGroup.hxx>
#include <Voting/PBReports/StatisticWrapper.hxx>
#include <Voting/operation-status.h>
#include "activated-card-statistics-wrapper.h"
#include "assisted-activation-wrapper.h"
#include "vote-statistics.h"

#include <map>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

    namespace SAES
    {
        namespace Voting
        {
            namespace PBReports
            {
                /**
                 * @brief	Header class StatisticManager.
                 *
                 * @author	Yadickson Soto yadickson.soto@smartmatic.com
                 * @date	04-05-2011
                 */

                class StatisticManager
                {
                private:

                    Smartmatic::SAES::Voting::OperationStatus * operationStatus; /**< operation status*/
                    AssistedActivationWrapper * assistedActivationWrapper; /**< assisted activation wrapper*/
                    ActivatedCardStatisticsWrapper * activatedCardStatistics; /**< activated card statistics*/
                    VoteStatisticsWrapper * voteStatisticsWrapper; /**< vote statistics wrapper*/
                    std::list<StatisticGroup*> groupList; /**< list statistic by group*/
                    std::map<std::string, StatisticGroup*> groupMap; /**< map statistic by group*/
                    std::map<std::string, StatisticWrapper*> statisticMap; /**< list all statistic*/
                    std::map<std::string, std::list <std::string> > calculatedMap; /**< list all statistic calculate*/

                    static Smartmatic::Log::ISMTTLog* logger; ///< The logger

                public:

                    /**
                     * @brief	Class constructor.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    StatisticManager();
                    /**
                     * @brief	Class destroyer.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    ~StatisticManager();
                    /**
                     * @brief	Persists.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void persistence()
                        throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);
                    /**
                     * @brief	Initialises this object.
                     * @param   operationStatus operation status
                     * @param   activatedCardStatistics activated card statistics
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     * @return true is load file
                     */
                    bool init(Smartmatic::SAES::Voting::OperationStatus * operationStatus,
                            AssistedActivationWrapper * assistedActivationWrapper,
                            ActivatedCardStatisticsWrapper * activatedCardStatistics,
                            VoteStatisticsWrapper * voteStatisticsWrapper)
                        throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);
                    /**
                     * @brief   Refresh statistics.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void refreshAll();
                    /**
                     * @brief   Refresh calculate statistics.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    05-05-2011
                     */
                    void refreshCalculated();
                    /**
                     * @brief   Refresh app statistics.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void refreshAppStatistic();
                    /**
                     * @brief   Refresh statistics.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void refreshConfigStatistic();
                    /**
                     * @brief Method getter all statistic group
                     * @return  all statistic group
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::list<StatisticGroup*> getStatisticGroup();
                    /**
                     * @brief Method add statistic
                     * @param   statistic new statistic
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void addStatistic(StatisticWrapper* statistic);
                    /**
                     * @brief Method getter statistic by code
                     * @param   code code of statistic
                     * @return  statistic by code
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    StatisticWrapper* getStatisticByCode(std::string code);
                    /**
                     * @brief Method getter all statistic
                     * @return  all statistic
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    std::list<StatisticWrapper*> getAllStatistics();
                    /**
                     * @brief   Dispose all object.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void dispose();
                    /**
                     * @brief   get all statistics.
                     * @return  all statistics.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    Statistics getStatistics();

                private:

                    /**
                     * @brief   load persistent file
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     * @return true is load file
                     */
                    bool load()
                        throw (Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::XmlException);
                    /**
                     * @brief   setter statistics required.
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void setRequired();
                    /**
                     * @brief   get configuration statistic
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void getConfigStatistics();
                    /**
                     * @brief   get application statistic
                     * @author  Yadickson Soto yadickson.soto@smartmatic.com
                     * @date    04-05-2011
                     */
                    void getAppStatistics();
                };
            }
        }
    }
}

#endif // _STATISTIC_MANAGER_H_
