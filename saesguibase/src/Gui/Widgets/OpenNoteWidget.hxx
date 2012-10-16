/**
 * @file OpenNoteWidget.hxx
 * @brief Header class open note widget
 * @date 10/05/2012
 * @author Yadickson Soto
 */

#ifndef OPENNOTEWIDGET_HXX_
#define OPENNOTEWIDGET_HXX_

#include <Widgets/wizard-widget-base.h>
#include <Gui/Widgets/Voting/PBReports/poll-worker-note-widget.h>

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
			namespace Widgets
			{
				/**
				 * @class OpenNoteWidget
				 * @brief Class open note widget
				 * @date 10/05/2012
				 * @author Yadickson Soto
				 */
				class OpenNoteWidget : public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					OpenNoteWidget();
					/**
					 * @brief Class destroy
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~OpenNoteWidget();

				protected:

					/**
					 * @brief virtual method init
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();
					/**
					 * @brief Method get widget name
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					virtual Glib::ustring GetWidgetName();
					/**
					 * @brief method show note
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void showNote();
					/**
					 * @brief method show message
					 * @param text new message
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void showMessage(std::string text);
					/**
					 * @brief method add note
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void addNote();
					/**
					 * @brief method error add note
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void addedTitleEmpty();
					/**
					 * @brief method error add note
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void addedContentEmpty();

				private:

					Gtk::Label * message; ///< message to user
					Gtk::Alignment * align; ///< align
					Smartmatic::SAES::GUI::Widgets::Voting::PBReports::PollWorkerNoteWidget* pollOpenNoteWidget;	///< The poll open note widget
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}
#endif /* OPENNOTEWIDGET_HXX_ */
