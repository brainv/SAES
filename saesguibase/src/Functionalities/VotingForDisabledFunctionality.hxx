/**
 * @file VotingForDisabledFunctionality.hxx
 * @brief Header class voting for disabled functionality
 * @date 18/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGFORDISABLEDFUNCTIONALITY_HXX_
#define VOTINGFORDISABLEDFUNCTIONALITY_HXX_

#include <gtkmm.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Gui/Widgets/Voting/PBReports/VotingForDisabledWidget.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				/**
				 * @class VotingForDisabledFunctionality
				 * @brief Class voting for disabled functionality
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				class VotingForDisabledFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
				private:
					/**
					 * @brief Class constructor
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					VotingForDisabledFunctionality();

					static VotingForDisabledFunctionality * instance; ///< instance of class
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
					Smartmatic::SAES::GUI::Widgets::Voting::PBReports::VotingForDisabledWidget * votingForDisabledWidget; ///< voting for disabled

				protected:

					/**
					 * @brief	Gets the window title.
					 * @return	The window title.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					std::string GetWindowTitle();
					/**
					 * @brief	Gets the menu option type.
					 * @return	The menu option type.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();
					/**
					 * @brief	Gets the frame.
					 * @return	null if it fails, else the frame.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					Gtk::Widget * GetFrame();
					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					void Dispose();
					/**
					 * @brief	Initializes this object.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					void Initialize();
					/**
					 * @brief	Gets the logger.
					 * @return	null if it fails, else the logger.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					Smartmatic::Log::ISMTTLog* getLogger();
					/**
					 * @brief	Gets the start log message.
					 * @return	The start log message.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					Glib::ustring getStartLogMessage();
					/**
					 * @brief	Gets the finish log message.
					 * @return	The finish log message.
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					Glib::ustring getFinishLogMessage();
					/**
					 * @brief method delete all element
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();
					/**
					 * @brief method block functionality
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					virtual void block();
					/**
					 * @brief method partial functionality
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					virtual void partial();
					/**
					 * @brief method resume functionality
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					virtual void resume();

				public:
					/**
					 * @brief Method getter instance
					 * @return instance of class
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					static VotingForDisabledFunctionality * getInstance();
					/**
					 * @brief Class destroy
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~VotingForDisabledFunctionality();
				};
			}
		}
	}
}
#endif /* VOTINGFORDISABLEDFUNCTIONALITY_HXX_ */
