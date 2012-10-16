/**
 * @file VotePreviewWidget.hxx
 * @brief Body class vote preview widget
 * @date 05/10/2011
 * @author Yadickson Soto
 */

#ifndef VOTEPREVIEWWIDGET_HXX_
#define VOTEPREVIEWWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>
#include <Printing/PrintPreviewWidget.h>
#include <Printing/VotePrintDocument.h>
#include <Gui/Widgets/party-contest-viewer-widget.h>
#include <Gui/Widgets/Voting/language-selection-widget.h>
#include <Widgets/StepWidget.hxx>

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
				namespace Voting
				{
					/**
					 * @class VotePreviewWidget
					 * @brief Class vote preview widget
					 * @date 05/10/2011
					 * @author Yadickson Soto
					 */
					class VotePreviewWidget: public Smartmatic::GUI::Widgets::StepWidget
					{
						public:
							/**
							 * @brief Class constructor
							 * @date 05/10/2011
							 * @author Yadickson Soto
							 */
							VotePreviewWidget();
							/**
							 * @brief Class destroy
							 * @date 05/10/2011
							 * @author Yadickson Soto
							 */
							virtual ~VotePreviewWidget();
							/**
							 * @brief Method preview
							 * @param vote to preview
							 * @date 05/10/2011
							 * @author Yadickson Soto
							 */
							void preview(Smartmatic::SAES::Voting::Vote::Vote & vote);
							/**
							 * @brief Method preview error
							 * @date 05/10/2011
							 * @author Yadickson Soto
							 */
							void error();
							/**
							 * @brief Method getter signal back clicked
							 * @return signal
							 * @date 05/10/2011
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getBackClicked();

						protected:
							/**
							 * @brief Method clear element
							 * @date 05/10/2011
							 * @author Yadickson Soto
							 */
							void clear();

						private:

							Gtk::Label * labelMessage;   ///< Message describing the label
							Gtk::VBox * vboxMagnify; ///< The vbox magnify
							Gtk::ScrolledWindow * scrolledMagnify;  ///< The scrolled magnify
							Gtk::Viewport * viewMagnify;   ///< The view magnify
							Smartmatic::GUI::Widgets::SmartmaticButton* buttonBack; ///< button back preview

							Smartmatic::SAES::Printing::PrintPreviewWidget* printWidgetMagnify; ///< The print widget magnify
							Smartmatic::SAES::GUI::Widgets::PartyContestViewerWidget* partyViewerWidget;	///< The party viewer widget
							Smartmatic::SAES::Printing::VotePrintDocument* docMagnify;  ///< The document magnify

							static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
					};
				}
			}
		}
	}
}

#endif /* VOTEPREVIEWWIDGET_HXX_ */
