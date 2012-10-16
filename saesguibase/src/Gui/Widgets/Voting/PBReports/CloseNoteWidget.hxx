/**
 * @file CloseNoteWidget.hxx
 * @brief Header class close note
 * @data 24/05/2012
 * @author Yadickson Soto
 */

#ifndef CLOSENOTEWIDGET_HXX_
#define CLOSENOTEWIDGET_HXX_

#include <Widgets/wizard-widget-base.h>
#include "CloseNoteInfoWidget.hxx"
#include "CloseNoteRegisterWidget.hxx"
#include "CloseNoteRegisterInfoWidget.hxx"
#include <Voting/PBReports/close-election-notes-schema.hxx>

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
					namespace PBReports
					{
						/**
						 * @class CloseNoteWidget
						 * @brief class close note widget
						 * @data 24/05/2012
						 * @author Yadickson Soto
						 */
						class CloseNoteWidget : public Smartmatic::GUI::Widgets::WizardWidgetBase
						{
						public:
							/**
							 * @brief class constructor
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							CloseNoteWidget();
							/**
							 * @brief class destroy
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~CloseNoteWidget();
							/**
							 * @brief method getter signal enabled
							 * @return signal
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalEnabled();
							/**
							 * @brief method getter signal disabled
							 * @return signal
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalDisabled();
							/**
							 * @brief method show next button
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void showNextButton();

						protected:
							/**
							 * @brief virtual method init
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual void dispose();
							/**
							 * @brief method load all info info
							 * @brief showFirstPage show first page
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							void load();
							/**
							 * @brief method add info
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void addInfo();
							/**
							 * @brief method save info
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void saveInfo();
							/**
							 * @brief method cancel info
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void cancelInfo();
							/**
							 * @brief method process signal clicked
							 * @param widget widget
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							void editInfo(CloseNoteRegisterInfoWidget * widget);
							/**
							 * @brief method create close note empty
							 * @param closeNote close note empty
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void createCloseNote(Smartmatic::SAES::Voting::PBReports::CloseNote & closeNote);
							/**
							 * @brief Method getter widget name
							 * @return widget name
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual Glib::ustring GetWidgetName();
							/**
							 * @brief Method next button clicked
							 * @date 24/05/2012
							 * @author Yadickson Soto
							 */
							void nextClicked();

						private:

							sigc::signal<void> signalEnabled; ///< signal enabled
							sigc::signal<void> signalDisabled; ///< signal disabled
							unsigned int minimunNotesToRegister; ///< min notes
							CloseNoteRegisterWidget * closeNoteRegisterWidget; ///< register widget
							CloseNoteInfoWidget * closeNoteInfoWidget; ///< info widget
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDWIDGET_HXX_ */
