/**
 * @file ProgressWidget.hxx
 * @brief Header class progress widget
 * @date 18/10/2011
 * @author Yadickson Soto
 */

#ifndef PROGRESSWIDGET_HXX_
#define PROGRESSWIDGET_HXX_

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
				/**
				 * @class PMProgressWidget
				 * @brief Class president machine progress widget
				 * @date 18/10/2011
				 * @author Yadickson Soto
				 * @see ProgressWidget
				 */
				class ProgressWidget : public Gtk::EventBox
				{
				public:

					/**
					 * @enum ProgressImage
					 * @brief Any type image
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					enum ProgressImage
					{
						 NONE ///< none image
						,NOT_FOUND ///< image not found
						,PROGRESS ///< progress image
						,PRINTING ///< printing image
						,PRINTING_OK ///< printing status ok
						,PRINTING_ERROR ///< printing status error
						,SMARTCARD ///< smartcard image
						,AUTO_DIAGNOSIS_DEVICES ///< image auto diagnosis devices
					};

					/**
					 * @brief Class constructor
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					ProgressWidget();
					/**
					 * @brief Class destroy
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					virtual ~ProgressWidget();
					/**
					 * @brief Method dispose widget
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void dispose();

					/**
					 * @brief Virtual method setter image relative path to project
					 * @param image image relative path to project
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					virtual void setImage(std::string image);
					/**
					 * @brief Virtual method setter image type
					 * @param image image type
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					virtual void setImage(ProgressImage image);
					/**
					 * @brief Virtual method setter image pixbuff
					 * @param image image pixbuff
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					virtual void setImage(Glib::RefPtr<Gdk::Pixbuf> pixbuff);
					/**
					 * @brief Method setter title text
					 * @param text new title text
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void setTitle(std::string text);
					/**
					 * @brief Method setter bottom text
					 * @param text new bottom text
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void setText(std::string text);
					/**
					 * @brief Method setter footer text
					 * @param text new footer text
					 * @date 03/05/2012
					 * @author Yadickson Soto
					 */
					void setFooter(std::string text);
					/**
					 * @brief Method setter title text config
					 * @param labelConf label configuration
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void setTitleConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);
					/**
					 * @brief Method setter bottom text config
					 * @param labelConf label configuration
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void setTextConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);
					/**
					 * @brief Method setter footer text config
					 * @param labelConf label configuration
					 * @date 03/05/2012
					 * @author Yadickson Soto
					 */
					void setFooterConfig(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);
					/**
					 * @brief Method hide title
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void hideTitle();
					/**
					 * @brief Method show title
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void showTitle();
					/**
					 * @brief Method hide image
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void hideImage();
					/**
					 * @brief Method show image
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void showImage();
					/**
					 * @brief Method hide bottom text
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void hideText();
					/**
					 * @brief Method show bottom text
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void showText();
					/**
					 * @brief Method hide footer text
					 * @date 03/05/2012
					 * @author Yadickson Soto
					 */
					void hideFooter();
					/**
					 * @brief Method show footer text
					 * @date 03/05/2012
					 * @author Yadickson Soto
					 */
					void showFooter();

				private:

					/**
					 * @brief Method initialize widget
					 * @date 18/10/2011
					 * @author Yadickson Soto
					 */
					void initialize();

					Gtk::EventBox * mainFrame; ///< principal frame
					Gtk::VBox * mainVBox; ///< principal container
					Gtk::Image * progressImage; ///< center image
					Gtk::Label * progressTitle; ///< top text
					Gtk::Label * progressLabel; ///< bottom text
					Gtk::Label * progressFooter; ///< footer text

					static Smartmatic::Log::ISMTTLog* logger;   ///< logger
				};
			}
		}
	}
}

#endif /* PROGRESSWIDGET_HXX_ */
