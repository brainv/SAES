/**
 * @file ButtonsWidget.hxx
 * @brief Header class buttons widget
 * @date 17/05/2012
 * @author Yadickson Soto
 */

#ifndef BUTTONSWIDGET_HXX_
#define BUTTONSWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @class ButtonsWidget
			 * @brief Class ButtonsWidget
			 * @author Yadickson Soto
			 * @date 17/05/2012
			 */
			class ButtonsWidget : public Gtk::EventBox
			{
			public:
				/**
				 * @brief Class constructor
				 * @param expand expand all button
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				ButtonsWidget(bool expand = true);
				/**
				 * @brief Class constructor
				 * @param cobject the cobject
				 * @param refBuilder The reference builder.
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				ButtonsWidget(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder=Gtk::Builder::create());
				/**
				 * @brief Class destroy
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				virtual ~ButtonsWidget();
				/**
				 * @brief method initialize class
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				virtual void initialize();
				/**
				 * @brief method dispose class
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				virtual void dispose();
				/**
				 * @brief method getter signal clear button clicked
				 * @return signal clicked
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				Glib::SignalProxy0< void > getSignalClearButtonClicked();
				/**
				 * @brief method getter signal accept button clicked
				 * @return signal clicked
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				Glib::SignalProxy0< void > getSignalAcceptButtonClicked();
				/**
				 * @brief method getter signal back button clicked
				 * @return signal clicked
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				Glib::SignalProxy0< void > getSignalBackButtonClicked();
				/**
				 * @brief method getter signal null button clicked
				 * @return signal clicked
				 * @author Yadickson Soto
				 * @date 13/03/2012
				 */
				Glib::SignalProxy0< void > getSignalNullButtonClicked();
				/**
				 * @brief method set spacing
				 * @param spacing spacing
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				void setSpacing(int spacing);
				/**
				 * @brief method set font button size
				 * @param size font button size
				 * @author Yadickson Soto
				 * @date 17/05/2012
				 */
				void modifyFontSize(int size);
				/**
				 * @brief method show button
				 * @param showClear flag show clear button
				 * @param showAccept flag show accept button
				 * @param showBack flag show back button
				 * @param showNull flag show null button
				 * @author Yadickson Soto
				 * @date 12/03/2012
				 */
				virtual void showButton(bool showClear, bool showAccept, bool showBack, bool showNull = false);
				/**
				 * @brief method setter text clear button
				 * @param text new text button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setTextClearButton(std::string text);
				/**
				 * @brief method setter text accept button
				 * @param text new text button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setTextAcceptButton(std::string text);
				/**
				 * @brief method setter text back button
				 * @param text new text button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setTextBackButton(std::string text);
				/**
				 * @brief method setter text null button
				 * @param text new text button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setTextNullButton(std::string text);
				/**
				 * @brief method setter size clear button
				 * @param width new width button
				 * @param height new width button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setSizeClearButton(int width, int height);
				/**
				 * @brief method setter size accept button
				 * @param width new width button
				 * @param height new width button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setSizeAcceptButton(int width, int height);
				/**
				 * @brief method setter size back button
				 * @param width new width button
				 * @param height new width button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setSizeBackButton(int width, int height);
				/**
				 * @brief method setter size null button
				 * @param width new width button
				 * @param height new width button
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				virtual void setSizeNullButton(int width, int height);
				/**
				 * @brief method change mode buttons accept and cancel
				 * @author Yadickson Soto
				 * @date 21/05/2012
				 */
				void changeButtom();

			private:

				Gtk::EventBox * eventbox; ///< The main frame
				Gtk::HBox * mainHbox; ///< The main hbox
				static Smartmatic::Log::ISMTTLog* logger;   ///< logger

			protected:

				bool expand; ///< expand
				Smartmatic::GUI::Widgets::SmartmaticButton * clearButton; ///< The clear button
				Smartmatic::GUI::Widgets::SmartmaticButton * acceptButton; ///< The accept button
				Smartmatic::GUI::Widgets::SmartmaticButton * backButton; ///< The back button
				Smartmatic::GUI::Widgets::SmartmaticButton * nullButton; ///< The null button
			};
		}
	}
}

#endif /* BUTTONSWIDGET_HXX_ */
