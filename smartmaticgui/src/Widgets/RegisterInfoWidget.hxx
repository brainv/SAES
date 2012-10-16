/**
 * @file RegisterInfoWidget.hxx
 * @brief Header class register info widget
 * @date 19/05/2012
 * @author Yadickson Soto
 */

#ifndef REGISTERINFOWIDGET_HXX_
#define REGISTERINFOWIDGET_HXX_

#include <gtkmm.h>
#include <Configuration/label-configuration.h>
#include "TableWidget.hxx"

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
			 * @class RegisterInfoWidget
			 * @brief class register info view
			 * @date 19/05/2012
			 * @author Yadickson Soto
			 */
			class RegisterInfoWidget : public Gtk::EventBox
			{
			public:
				/**
				 * @brief class constructor
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				RegisterInfoWidget();
				/**
				 * @brief class destroy
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				virtual ~RegisterInfoWidget();
				/**
				 * @brief method add header info
				 * @param title title
				 * @param content content
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void addHeader(std::string title, std::string content);
				/**
				 * @brief method add center info
				 * @param title title
				 * @param content content
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void addCenter(std::string title, std::string content);
				/**
				 * @brief method add bottom info
				 * @param title title
				 * @param content content
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void addBottom(std::string title, std::string content);
				/**
				 * @brief method add center info
				 * @param message message
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void putCenterMessage(std::string message);
				/**
				 * @brief method add wrap info
				 * @param message message
				 * @date 25/05/2012
				 * @author Yadickson Soto
				 */
				void putWrapMessage(std::string message);
				/**
				 * @brief method clear all info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void clearAll();
				/**
				 * @brief method clear header info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void clearHeader();
				/**
				 * @brief method clear center info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void clearCenter();
				/**
				 * @brief method clear bottom info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void clearBottom();
				/**
				 * @brief method show header info
				 * @param show show
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void showHeader(bool show = true);
				/**
				 * @brief method show center info
				 * @param show show
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void showCenter(bool show = true);
				/**
				 * @brief method show bottom info
				 * @param show show
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void showBottom(bool show = true);
				/**
				 * @brief method hide header info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void hideHeader();
				/**
				 * @brief method hide center info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void hideCenter();
				/**
				 * @brief method hide bottom info
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void hideBottom();
				/**
				 * @brief Method setter header config
				 * @param labelConf label configuration
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void setHeaderConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);
				/**
				 * @brief Method setter center config
				 * @param labelConf label configuration
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void setCenterConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);
				/**
				 * @brief Method setter bottom config
				 * @param labelConf label configuration
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				void setBottomConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);
				/**
				 * @brief Method getter signal click
				 * @return signal click
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				sigc::signal<void, bool> getSignalClick();

			protected:

				/**
				 * @brief Method getter signal click
				 * @param event event click
				 * @return true is success
				 * @date 19/05/2012
				 * @author Yadickson Soto
				 */
				bool clicked(GdkEventButton* event);

			private:

				Gtk::Frame * mainFrame; ///< main frame
				Gtk::EventBox * mainEventbox; ///< main event box
				Gtk::VBox * mainVBox; ///< main vbox
				Gtk::Frame * headerFrame; ///< header frame
				Gtk::EventBox * headerEventbox; ///< header evenbox
				Gtk::Label * headerLabel; ///< header label
				Gtk::Frame * centerFrame; ///< center frame
				Gtk::EventBox * centerEventbox; ///< center evenbox
				Gtk::Frame * bottomFrame; ///< bottom frame
				Gtk::EventBox * bottomEventbox; ///< bottom evenbox
				Gtk::Label * bottomLabel; ///< bottom label

				Gtk::Label * centerLabel; ///< center label
				Smartmatic::GUI::Widgets::TableWidget * table; ///< center table

				bool flagInfo; ///< flag info
				sigc::signal<void, bool> signal; ///< signal clicked
				static Smartmatic::Log::ISMTTLog* logger;   ///< logger
			};
		}
	}
}

#endif /* REGISTERINFOWIDGET_HXX_ */
