/**
 * @file ISmartmaticText.hxx
 * @brief Header class smartmatic text
 * @date 03/06/2012
 * @author Yadickson Soto
 */

#ifndef ISMARTMATICTEXT_HXX_
#define ISMARTMATICTEXT_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class ISmartmaticText
			 * @brief interface smartmatic text
			 * @date 03/06/2012
			 * @author Yadickson Soto
			 */
			class ISmartmaticText
			{
			protected:
				/**
				 * @brief class constructor
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				ISmartmaticText();

			public:

				/**
				 * @brief class destroy
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual ~ISmartmaticText();
				/**
				 * @brief Method setter text
				 * @param text text
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setText(std::string text) = 0;
				/**
				 * @brief Method getter text
				 * @return text
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getText() = 0;
				/**
				 * @brief	Set entry max elements
				 * @param	max max
				 * @author	Yadickson Soto
				 * @date	04/05/2012
				 */
				virtual void setMax(int max);
				/**
				 * @brief	Set entry mask
				 * @param	mask mask
				 * @author	Yadickson Soto
				 * @date	04/05/2012
				 */
				virtual void setMask(std::string mask);
				/**
				 * @brief	Set entry regex
				 * @param	regex regular expresion
				 * @author	Yadickson Soto
				 * @date	03/06/2012
				 */
				virtual void setRegex(std::string regex);
				/**
				 * @brief	Set entry mandatory date
				 * @param	mandatory mandatory date
				 * @author	Yadickson Soto
				 * @date	08/06/2012
				 */
				virtual void setMandatory(bool mandatory);
				/**
				 * @brief method validate
				 * @return true is validate
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual bool validate();
				/**
				 * @brief method set bg error
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setBGError() = 0;
				/**
				 * @brief method set bg normal
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setBGNormal() = 0;

			protected:

				int max; ///< max
				std::string mask; ///< mask
				std::string regex; ///< regex
				bool mandatory; ///< mandatory
			};
		}
	}
}

#endif /* ISMARTMATICTEXT_HXX_ */
