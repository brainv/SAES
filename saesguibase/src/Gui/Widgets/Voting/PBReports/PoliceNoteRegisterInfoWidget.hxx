/**
 * @file PoliceNoteRegisterInfoWidget.hxx
 * @brief Header police note register info widget
 * @date 25/05/2012
 * @author Yadickson Soto
 */

#ifndef POLICENOTEREGISTERINFOWIDGET_HXX_
#define POLICENOTEREGISTERINFOWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/RegisterInfoWidget.hxx>
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
						 * @class PoliceNoteRegisterInfoWidget
						 * @brief class police note
						 * @data 25/05/2012
						 * @author Yadickson Soto
						 */
						class PoliceNoteRegisterInfoWidget : public Smartmatic::GUI::Widgets::RegisterInfoWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @param policeNote police note information
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							PoliceNoteRegisterInfoWidget(Smartmatic::SAES::Voting::PBReports::PoliceNote & policeNote);
							/**
							 * @brief class destroy
							 * @param policeNote police note
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~PoliceNoteRegisterInfoWidget();
							/**
							 * @brief method refresh elements
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							void refresh();
							/**
							 * @brief method getter police note information
							 * @return police note information
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							Smartmatic::SAES::Voting::PBReports::PoliceNote & getPoliceNote();
							/**
							 * @brief method getter signal clicked
							 * @return signal clicked
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void, PoliceNoteRegisterInfoWidget *> getSignalClicked();

						protected:

							/**
							 * @brief method process clicked
							 * @param state signal clicked
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							void clicked(bool state);
							/**
							 * @brief method process clicked
							 * @data 25/05/2012
							 * @author Yadickson Soto
							 */
							void emitClicked();

						private:

							sigc::signal<void, PoliceNoteRegisterInfoWidget *> signalClicked; ///< signal clicked info
							Smartmatic::SAES::Voting::PBReports::PoliceNote policeNote; ///< police note information
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* POLICENOTEREGISTERINFOWIDGET_HXX_ */
