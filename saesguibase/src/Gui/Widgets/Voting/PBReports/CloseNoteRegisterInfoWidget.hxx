/**
 * @file CloseNoteRegisterInfoWidget.hxx
 * @brief Header close note register info widget
 * @date 24/05/2012
 * @author Yadickson Soto
 */

#ifndef CLOSENOTEREGISTERINFOWIDGET_HXX_
#define CLOSENOTEREGISTERINFOWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/RegisterInfoWidget.hxx>
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
						 * @class CloseNoteRegisterInfoWidget
						 * @brief class close note
						 * @data 24/05/2012
						 * @author Yadickson Soto
						 */
						class CloseNoteRegisterInfoWidget : public Smartmatic::GUI::Widgets::RegisterInfoWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @param closeNote close note information
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							CloseNoteRegisterInfoWidget(Smartmatic::SAES::Voting::PBReports::CloseNote & closeNote);
							/**
							 * @brief class destroy
							 * @param closeNote close note
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~CloseNoteRegisterInfoWidget();
							/**
							 * @brief method refresh elements
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							void refresh();
							/**
							 * @brief method getter close note information
							 * @return close note information
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							Smartmatic::SAES::Voting::PBReports::CloseNote & getCloseNote();
							/**
							 * @brief method getter signal clicked
							 * @return signal clicked
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void, CloseNoteRegisterInfoWidget *> getSignalClicked();

						protected:

							/**
							 * @brief method process clicked
							 * @param state signal clicked
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							void clicked(bool state);
							/**
							 * @brief method process clicked
							 * @data 24/05/2012
							 * @author Yadickson Soto
							 */
							void emitClicked();

						private:

							sigc::signal<void, CloseNoteRegisterInfoWidget *> signalClicked; ///< signal clicked info
							Smartmatic::SAES::Voting::PBReports::CloseNote closeNote; ///< close note information
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* CLOSENOTEREGISTERINFOWIDGET_HXX_ */
