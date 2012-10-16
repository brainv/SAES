/**
 * @file	vote-statistics-widget.h
 *
 * @brief	Declares the vote statistics widget class.
 */

#ifndef _VOTE_STATISTICS_WIDGET_H_
#define _VOTE_STATISTICS_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/counter-stat-widget.h>
#include <Voting/PBReports/vote-statistics.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Voting/VotingDevice/voting-devices-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					/**
					 * @brief	Vote statistics widget. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					class VoteStatisticsWidget : public Gtk::Table
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param [in,out]	voteStats	If non-null, the vote stats.
						 * @param [in,out]	cadefs   	The cadefs.
						 */

						VoteStatisticsWidget(Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper* voteStats,
								Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definitions& cadefs,
								Smartmatic::SAES::Configuration::CountConfiguration & totalCountType,
								Smartmatic::SAES::Configuration::CountConfiguration & officialCountType);

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~VoteStatisticsWidget();

						/**
						 * @brief	Refresh stats.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void RefreshStats();

						/**
						 * @brief	Sets a sensitive.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	setSensitive	true to set sensitive.
						 */

						void SetSensitive(bool setSensitive = true);

					protected:

						/**
						 * @brief	Initializes this object.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void Initialize();

						std::string getValue(Smartmatic::SAES::Configuration::CountConfiguration::CountTypeSequence & seq);

					private:

						Gtk::Label* labelTitle;
						Gtk::EventBox* eventTitle;

						std::vector<std::string> vmCA;  ///< The virtual memory ca
						std::vector<std::string> pmCA;  ///< The pm ca
						std::vector<Gtk::Label*> vecLabels; ///< The vector labels

						Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper* voteStats; ///< The vote stats

						Smartmatic::GUI::Widgets::CounterStatWidget* totalVoteCounter;  ///< The total vote counter
						Smartmatic::GUI::Widgets::CounterStatWidget* officialVoteCounter;  ///< The official vote counter
						Smartmatic::GUI::Widgets::CounterStatWidget* duplicateVoteCounter;  ///< The duplicate vote counter

						std::map<std::string, Smartmatic::GUI::Widgets::CounterStatWidget*> vmMap;  ///< The virtual memory map
						std::map<std::string, Smartmatic::GUI::Widgets::CounterStatWidget*> pmMap;  ///< The pm map

						bool showVM;	///< true to show, false to hide the virtual memory
						Smartmatic::SAES::Configuration::CountConfiguration totalCountType;
						Smartmatic::SAES::Configuration::CountConfiguration officialCountType;
					};
				}
			}
		}
	}
}

#endif // _VOTE_STATISTICS_WIDGET_H_
