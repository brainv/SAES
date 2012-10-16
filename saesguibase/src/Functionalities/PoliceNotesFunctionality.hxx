/**
 * @file PoliceNotesFunctionality.hxx
 * @brief Header class police notes functionality
 * @date 25/05/2012
 * @author Yadickson Soto
 */

#ifndef POLICENOTESFUNCTIONALITY_HXX_
#define POLICENOTESFUNCTIONALITY_HXX_

#include <gtkmm.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Gui/Widgets/Voting/PBReports/PoliceNoteWidget.hxx>

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
				 * @class PoliceNotesFunctionality
				 * @brief Class police notes functionality
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				class PoliceNotesFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
				private:
					/**
					 * @brief Class constructor
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					PoliceNotesFunctionality();

					static PoliceNotesFunctionality * instance; ///< instance of class
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
					Smartmatic::SAES::GUI::Widgets::Voting::PBReports::PoliceNoteWidget * policeNotesWidget; ///< police notes

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
					static PoliceNotesFunctionality * getInstance();
					/**
					 * @brief Class destroy
					 * @date 18/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~PoliceNotesFunctionality();
				};
			}
		}
	}
}
#endif /* VOTINGFORDISABLEDFUNCTIONALITY_HXX_ */
