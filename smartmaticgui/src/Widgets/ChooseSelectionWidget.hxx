/**
 * @file ChooseSelectionWidget.hxx
 * @brief Header class choose selection widget
 * @date 12/04/2012
 * @author Yadickson Soto
 */

#ifndef CHOOSESELECTIONWIDGET_HXX_
#define CHOOSESELECTIONWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/choose-dialog-info.h>
#include <Widgets/choose-dialog-widget.h>
#include <Widgets/choose-dialog-button-info.h>
#include <Widgets/confirmation-dialog-widget.h>
#include <Widgets/StepWidget.hxx>
#include <Configuration/label-configuration.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class ChooseSelectionWidget
			 * @brief class choose selection widget
			 * @date 12/04/2012
			 * @author Yadickson Soto
			 */
			class ChooseSelectionWidget: public StepWidget
			{
			public:
				/**
				 * @brief class constructor
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				ChooseSelectionWidget();
				/**
				 * @brief class constructor
				 * @param title title
				 * @param confirmation confirmation widget
				 * @param choices choice buttons
				 * @param showBack show confirmation or back
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				ChooseSelectionWidget(std::string title, std::vector <ChooseDialogButtonInfo*> & choices, ConfirmationDialogWidget * confirmation = NULL, bool showBack = false);
				/**
				 * @brief class constructor
				 * @param info info frame
				 * @param confirmation confirmation widget
				 * @param showBack show confirmation or back
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				ChooseSelectionWidget(ChooseDialogInfo * info, ConfirmationDialogWidget * confirmation = NULL, bool showBack = false);
				/**
				 * @brief class destroy
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				virtual ~ChooseSelectionWidget();
				/**
				 * @brief method setter label configuration
				 * @param headerConf header conf
				 * @param footerConf footer conf
				 * @date 13/04/2012
				 * @author Yadickson Soto
				 */
				void setLabelConfig(Smartmatic::GUI::Configuration::LabelConfiguration headerConf, Smartmatic::GUI::Configuration::LabelConfiguration footerConf);
				/**
				 * @brief method setter label confirmation configuration
				 * @param headerConf header conf
				 * @param footerConf footer conf
				 * @date 13/04/2012
				 * @author Yadickson Soto
				 */
				void setLabelConfirmationConfig(Smartmatic::GUI::Configuration::LabelConfiguration headerConf, Smartmatic::GUI::Configuration::LabelConfiguration footerConf);
				/**
				 * @brief virtual method stop
				 * @date 08/03/2012
				 * @author Yadickson Soto
				 */
				virtual void dispose();

			protected:

				/**
				 * @brief method setter choose buttons
				 * @param title title
				 * @param choices choice buttons
				 * @param confirmation confirmation widget
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				void setChooseButtons(std::string title, std::vector <ChooseDialogButtonInfo*> & choices, ConfirmationDialogWidget * confirmation = NULL);
				/**
				 * @brief method setter show confirmation or back
				 * @param showBack show confirmation or back
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				void setShowBack(bool showBack);
				/**
				 * @brief method setter choose info
				 * @param info info frame
				 * @param confirmation confirmation widget
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				void setChooseInfo(ChooseDialogInfo * info, ConfirmationDialogWidget * confirmation = NULL);
				/**
				 * @brief method signal option selected
				 * @param choose option selected
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				virtual void onSelected(ChooseDialogButtonInfo* choose) = 0;
				/**
				 * @brief method signal option pre selected
				 * @param choose option selected
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				virtual void onPreSelected(ChooseDialogButtonInfo* choose);
				/**
				 * @brief method signal option pre selected back
				 * @date 12/04/2012
				 * @author Yadickson Soto
				 */
				virtual void onPreSelectedBack();
				/**
				 * @brief method setter internal size
				 * @param width width
				 * @param height height
				 * @date 17/04/2012
				 * @author Yadickson Soto
				 */
				void setInternalSizeWidget(int width, int height);

			protected:

				Gtk::EventBox * mainFrame; ///< main frame
				ChooseDialogWidget * chooseDialogWidget; ///< choose dialog widget
				Gtk::Alignment * alignFrame;  ///< align frame

			private:

				std::vector <ChooseDialogButtonInfo*> choices; ///< choose buttons
				bool showBack; ///< flag confirmation or back
			};
		}
	}
}

#endif /* CHOOSESELECTIONWIDGET_HXX_ */
