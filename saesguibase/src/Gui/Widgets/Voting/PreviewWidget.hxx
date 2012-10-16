/**
 * @file PreviewWidget.hxx
 * @brief Body class preview
 * @date 13/04/2012
 * @author Yadickson Soto
 */

#ifndef PREVIEWWIDGET_HXX_
#define PREVIEWWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include <Voting/Vote/vote-schema.hxx>
#include "VotePreviewWidget.hxx"
#include "TimeOutPreviewWidget.hxx"
#include "language-selection-widget.h"

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
					 * @class PreviewWidget
					 * @brief Class preview widget
					 * @date 13/04/2012
					 * @author Yadickson Soto
					 */
					class PreviewWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:
						/**
						 * @brief Class constructor
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						PreviewWidget();
						/**
						 * @brief Class destroy
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~PreviewWidget();
						/**
						 * @brief Method preview
						 * @param vote to preview
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						void preview(Smartmatic::SAES::Voting::Vote::Vote & vote);
						/**
						 * @brief Method preview error
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						void error();

					protected:

						/**
						 * @brief Method selection language
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void selectionLanguage();
						/**
						 * @brief Method selection language vote
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void setLanguageVote();
						/**
						 * @brief Method selection language install
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void setLanguageInstall();
						/**
						 * @brief Method selection language elector
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void setLanguageElector();
						/**
						 * @brief Method back widget
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void back();
						/**
						 * @brief Method view vote
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void viewVote();
						/**
						 * @brief Method set timeout
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						void setTimeout();
						/**
						 * @brief Method release timeout
						 * @param time time
						 * @date 05/10/2011
						 * @author Yadickson Soto
						 */
						bool releaseTimeout(int time);
						/**
						 * @brief Method release timeout close
						 * @param time time
						 * @date 24/05/2012
						 * @author Yadickson Soto
						 */
						bool releaseTimeoutClose(int time);

					private:

						bool view; ///< flag view vote
						bool language; ///< flag selection language
						sigc::connection connTimeout; /// < The connection timeout preview
						sigc::connection connTimeoutClose; /// < The connection timeout close preview
						Smartmatic::SAES::Voting::Vote::Vote vote; ///< vote to preview
						VotePreviewWidget * votePreviewWidget; ///< vote preview widget
						TimeOutPreviewWidget * timeOutPreviewWidget; ///< timeout preview widget
						LanguageSelectionWidget * languageWidget; ///< language widget
						static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
					};
				}
			}
		}
	}
}

#endif /* PREVIEWWIDGET_HXX_ */
