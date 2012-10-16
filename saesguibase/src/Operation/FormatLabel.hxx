/**
 * @file FormatLabel.hxx
 * @brief Header class format label text
 * @date 11/04/2012
 * @author Yadickson Soto
 */

#ifndef FORMATLABEL_HXX_
#define FORMATLABEL_HXX_

#include <string>
#include <glibmm.h>
#include <Voting/Election/election-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Operation
			{
				/**
				 * @class FormatLabel
				 * @brief class format label text
				 * @date 11/04/2012
				 * @author Yadickson Soto
				 */
				class FormatLabel
				{
				protected:
					/**
					 * @brief class constructor
					 * @date 11/04/2012
					 * @author Yadickson Soto
					 */
					FormatLabel();

				public:
					/**
					 * @brief class destroy
					 * @date 11/04/2012
					 * @author Yadickson Soto
					 */
					virtual ~FormatLabel();
					/**
					 * @brief method format text multi language
					 * @param text text to format
					 * @return text format
					 * @date 11/04/2012
					 * @author Yadickson Soto
					 */
					static std::string format(std::string text);
					/**
					 * @brief method check compose string
					 * @param stringToCheck check and result text
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					static void checkComposeString(std::string & stringToCheck);

					static Glib::ustring contestText(Smartmatic::SAES::Voting::Election::Contest & contest, Glib::ustring & format);

				};
			}
		}
	}
}

#endif /* FORMATLABEL_HXX_ */
