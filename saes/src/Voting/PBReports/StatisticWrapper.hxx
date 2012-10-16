/**
 * @file StatisticWrapper.hxx
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

#ifndef _STATISTIC_WRAPPER_H_
#define _STATISTIC_WRAPPER_H_

#include <Voting/PBReports/statistics-schema.hxx>
#include <Configuration/SaesConfiguration-schema.hxx>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Voting
        {
            namespace PBReports
            {
                /**
                 * @brief	Header class StatisticWrapper.
                 *
                 * @author	Yadickson Soto yadickson.soto@gmail.com
                 * @date	04/05/2011
                 */
                class StatisticWrapper: public StatisticType
                {
                private:

                    bool edit; ///< Flag edit element
                    bool calculated; ///< Flag calculated element
                    bool required; ///< Flag required element
                    unsigned int max; ///< max elements
                    std::string mask; ///< mask elements
                    std::string regex; ///< regex element
                    bool mandatory; ///< mandatory
                    int width; ///< width
                    int height; ///< height
                    Smartmatic::SAES::Configuration::StatisticElementType type; ///< type

                public:

                    /**
                     * @brief   Class constructor.
                     *
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    04/05/2011
                     */
                    StatisticWrapper();
                    /**
                     * @brief	Class constructor.
                     *
                     * @param   statistic
                     * @author	Yadickson Soto yadickson.soto@gmail.com
                     * @date	04/05/2011
                     */
                    StatisticWrapper(StatisticType & statistic);
                    /**
                     * @brief	Class destroyer.
                     *
                     * @author	Yadickson Soto yadickson.soto@gmail.com
                     * @date	04/05/2011
                     */
                    virtual ~StatisticWrapper();
                    /**
                     * @brief   Method setter edit flag
                     * @param   edit new value
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    04/05/2011
                     */
                    void setEdit(bool edit);
                    /**
                     * @brief   Method getter edit flag
                     * @return  true is edit
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    04/05/2011
                     */
                    bool isEdit();
                    /**
                     * @brief   Method setter calculated flag
                     * @param   calculated new value
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    05/05/2011
                     */
                    void setCalculated(bool calculated);
                    /**
                     * @brief   Method getter calculated flag
                     * @return  true is calculated
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    05/05/2011
                     */
                    bool isCalculated();
                    /**
                     * @brief   Method setter required flag
                     * @param   required new value
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    05/05/2011
                     */
                    void setRequired(bool required);
                    /**
                     * @brief   Method getter required flag
                     * @return  true is required
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    05/05/2011
                     */
                    bool isRequired();
                    /**
                     * @brief   Method getter name
                     * @return  name
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    05/05/2011
                     */
                    std::string getName();
                    /**
                     * @brief   Method getter description
                     * @return  description
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    05/05/2012
                     */
                    std::string getDescription();
                    /**
                     * @brief   Method getter max element
                     * @return  max element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    14/05/2012
                     */
                    unsigned int getMax();
                    /**
                     * @brief   Method setter max element
                     * @param  	max max elements
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    14/05/2012
                     */
                    void setMax(unsigned int max);
                    /**
                     * @brief   Method getter mask element
                     * @return  mask element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    25/05/2012
                     */
                    std::string getMask();
                    /**
                     * @brief   Method setter mask element
                     * @param  	mask mask elements
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    25/05/2012
                     */
                    void setMask(std::string mask);
                    /**
                     * @brief   Method getter regex element
                     * @return  regex element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    25/05/2012
                     */
                    std::string getRegex();
                    /**
                     * @brief   Method setter regex element
                     * @param  	regex regex elements
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    25/05/2012
                     */
                    void setRegex(std::string regex);
                    /**
                     * @brief   Method getter width element
                     * @return  width element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    31/05/2012
                     */
                    int getWidth();
                    /**
                     * @brief   Method getter height element
                     * @return  height element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    31/05/2012
                     */
                    int getHeight();
                    /**
                     * @brief   Method setter size element
                     * @param	width width element
                     * @param  	height height element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    31/05/2012
                     */
                    void setSize(int width, int height);
                    /**
                     * @brief   Method getter type element
                     * @return  type element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    25/05/2012
                     */
                    Smartmatic::SAES::Configuration::StatisticElementType getType();
                    /**
                     * @brief   Method setter type element
                     * @param  	type type element
                     * @author  Yadickson Soto yadickson.soto@gmail.com
                     * @date    25/05/2012
                     */
                    void setType(Smartmatic::SAES::Configuration::StatisticElementType type);
    				/**
    				 * @brief	Set mandatory date
    				 * @param	mandatory mandatory date
    				 * @author	Yadickson Soto
    				 * @date	08/06/2012
    				 */
    				void setMandatory(bool mandatory);
    				/**
    				 * @brief	Set mandatory date
    				 * @return true is mandatory
    				 * @author	Yadickson Soto
    				 * @date	08/06/2012
    				 */
    				bool isMandatory();
                };
            }
        }
    }
}

#endif // _STATISTICS_WRAPPER_H_
