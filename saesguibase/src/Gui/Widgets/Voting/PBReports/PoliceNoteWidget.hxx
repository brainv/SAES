/**
 * @file PoliceNoteWidget.hxx
 * @brief Header class police note
 * @data 25/05/2012
 * @author Yadickson Soto
 */

#ifndef POLICENOTEWIDGET_HXX_
#define POLICENOTEWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include "PoliceNoteInfoWidget.hxx"
#include "PoliceNoteRegisterWidget.hxx"
#include "PoliceNoteRegisterInfoWidget.hxx"
#include <Voting/PBReports/police-notes-schema.hxx>

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
						 * @class PoliceNoteWidget
						 * @brief class police note widget
						 * @data 25/05/2012
						 * @author Yadickson Soto
						 */
						class PoliceNoteWidget : public Smartmatic::GUI::Widgets::StepWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							PoliceNoteWidget();
							/**
							 * @brief class destroy
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~PoliceNoteWidget();
							/**
							 * @brief method getter signal enabled
							 * @return signal
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalEnabled();
							/**
							 * @brief method getter signal disabled
							 * @return signal
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalDisabled();
							/**
							 * @brief method show next button
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void showNextButton();

						protected:
							/**
							 * @brief virtual method init
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 25/05/2012
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
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void addInfo();
							/**
							 * @brief method save info
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void saveInfo();
							/**
							 * @brief method cancel info
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void cancelInfo();
							/**
							 * @brief method process signal clicked
							 * @param widget widget
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							void editInfo(PoliceNoteRegisterInfoWidget * widget);
							/**
							 * @brief method create police note empty
							 * @param policeNote police note empty
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							void createPoliceNote(Smartmatic::SAES::Voting::PBReports::PoliceNote & policeNote);
							/**
							 * @brief Method getter widget name
							 * @return widget name
							 * @date 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual Glib::ustring GetWidgetName();

						private:

							sigc::signal<void> signalEnabled; ///< signal enabled
							sigc::signal<void> signalDisabled; ///< signal disabled
							PoliceNoteRegisterWidget * policeNoteRegisterWidget; ///< register widget
							PoliceNoteInfoWidget * policeNoteInfoWidget; ///< info widget
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDWIDGET_HXX_ */
