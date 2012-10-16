/**
 * @file ResultWidget.hxx
 * @brief Body class result widget
 * @date 18/07/2012
 * @author Yadickson Soto
 */

#ifndef RESULTWIDGET_HXX_
#define RESULTWIDGET_HXX_

#include <gtkmm.h>
#include <Configuration/label-configuration.h>

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
				class ResultWidget : public Gtk::EventBox
				{
				public:
					ResultWidget();
					virtual ~ResultWidget();

					void setText(std::string text, bool center = true);
					void setStatus(bool status);

					std::string getText();
					bool getStatus();

					struct Result
					{
						bool status;
						std::string message;
					};

					void addResult(Result & result);
					void setResult(std::list <Result> & list);
					std::list <Result> & getResult();

					/**
					 * @brief Method getter signal click
					 * @return signal click
					 * @date 19/05/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void, ResultWidget * > getSignalClick();

					void setLabelConfig(Smartmatic::GUI::Configuration::LabelConfiguration & labelConf);

				protected:
					void initialize();
					void dispose();

					/**
					 * @brief Method getter signal click
					 * @param event event click
					 * @return true is success
					 * @date 19/05/2012
					 * @author Yadickson Soto
					 */
					bool clicked(GdkEventButton* event);

				private:
					Gtk::Frame * mainFrame;
					Gtk::Label * label;
					Gtk::Image * image;
					bool status; ///< global status
					std::list <Result> list; ///< list message
					sigc::signal<void, ResultWidget * > signal; ///< signal clicked
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* RESULTWIDGET_HXX_ */
