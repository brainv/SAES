/**
 * @ValidateWidget.hxx
 * @brief Class validate widget
 * @date 04/06/2012
 * @author Yadickson Soto
 */

#ifndef VALIDATEWIDGET_HXX_
#define VALIDATEWIDGET_HXX_

#include <Widgets/smartmatic-entry.h>
#include <Widgets/SmartmaticTextView.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				class ValidateWidget
				{
				protected:
					/**
					 * @brief Class costructor
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					ValidateWidget();
				public:
					/**
					 * @brief Class destroy
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~ValidateWidget();
					/**
					 * @brief Method set properties for validate data
					 * @param idProperties id properties config
					 * @param entry entry data
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					static void setProperties(Smartmatic::SAES::Configuration::IDProperties idProperties, Smartmatic::GUI::Widgets::SmartmaticEntry * entry);
					/**
					 * @brief Method set properties for validate data
					 * @param idProperties id properties config
					 * @param entry entry data
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					static void setProperties(Smartmatic::SAES::Configuration::IDProperties idProperties, Smartmatic::GUI::Widgets::SmartmaticTextView * textView);
					/**
					 * @brief Method validate data
					 * @param idProperties id properties config
					 * @param entry entry data
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					static bool validate(Smartmatic::SAES::Configuration::IDProperties idProperties, Smartmatic::GUI::Widgets::SmartmaticEntry * entry);
					/**
					 * @brief Method validate data
					 * @param idProperties id properties config
					 * @param textBuffer text buffer
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					static bool validate(Smartmatic::SAES::Configuration::IDProperties idProperties, Smartmatic::GUI::Widgets::SmartmaticTextView * textView);
					/**
					 * @brief Method validate data
					 * @param idProperties id properties config
					 * @param text text
					 * @date 28/05/2012
					 * @author Yadickson Soto
					 */
					static bool validate(Smartmatic::SAES::Configuration::IDProperties & idProperties, std::string & text);
				};
			}
		}
	}
}

#endif /* VALIDATEWIDGET_HXX_ */
