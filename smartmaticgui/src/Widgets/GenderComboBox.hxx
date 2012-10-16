/**
 * @file GenderComboBox.hxx
 * @brief Header class gender widget
 * @date 05/06/2012
 * @author Yadickson Soto
 */

#ifndef GENDERCOMBOBOX_HXX_
#define GENDERCOMBOBOX_HXX_

#include "smartmatic-combo-box.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class GenderComboBox
			 * @brief class gender widget
			 * @date 05/06/2012
			 * @author Yadickson Soto
			 */
			class GenderComboBox : public SmartmaticComboBox
			{
			public:
				/**
				 * @brief class constructor
				 * @date 05/06/2012
				 * @author Yadickson Soto
				 */
				GenderComboBox();
				/**
				 * @brief class constructor
				 * @param femaleList female list options
				 * @param maleList male list options
				 * @date 05/06/2012
				 * @author Yadickson Soto
				 */
				GenderComboBox(std::list<std::string> & femaleList, std::list<std::string> & maleList);
				/**
				 * @brief class destroy
				 * @date 05/06/2012
				 * @author Yadickson Soto
				 */
				virtual ~GenderComboBox();
				/**
				 * @brief method getter value
				 * @return value
				 * @date 05/06/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getValue();
				/**
				 * @brief method setter value
				 * @param value value
				 * @date 05/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setValue(std::string value);

				static std::string Female; ///< female
				static std::string Male; ///< male
				static std::string None; ///< none

			protected:

				/**
				 * @brief initialize list
				 * @param femaleList female list options
				 * @param maleList male list options
				 * @date 05/06/2012
				 * @author Yadickson Soto
				 */
				void initialize(std::list<std::string> & femaleList, std::list<std::string> & maleList);

			private:

				std::list<std::string> femaleList; ///< female list options
				std::list<std::string> maleList; ///< male list options
			};
		}
	}
}
#endif /* GENDERCOMBOBOX_HXX_ */
