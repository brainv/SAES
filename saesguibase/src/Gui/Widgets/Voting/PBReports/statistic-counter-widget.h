/**
 * @file	statistic-counter-widget.h
 *
 * @brief	Declares the statistic counter widget class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _STATISTIC_COUNTER_WIDGET_H_
#define _STATISTIC_COUNTER_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/counter-stat-widget.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Voting/PBReports/StatisticWrapper.hxx>
#include <Configuration/label-configuration.h>
#include <Widgets/TableCenterWidget.hxx>

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
					namespace PBReports
					{
						/**
						 * @brief	Statistic counter widget. 
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						class StatisticCounterWidget : public Smartmatic::GUI::Widgets::TableCenterWidget
						{
						public:

							/**
							 * @brief	Constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 *
							 * @param	pivot			The pivot.
							 * @param	rowSpacing  	The row spacing.
							 * @param	colSpacings 	The col spacings.
							 * @param labelConf the label configuration
							 */

							StatisticCounterWidget(std::list<Smartmatic::SAES::Voting::PBReports::StatisticWrapper*> statisticWrapper, bool vertical, int pivot, int rowSpacing, int colSpacings, Smartmatic::GUI::Configuration::LabelConfiguration labelConf);

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							~StatisticCounterWidget();

							/**
							 * @brief	Resets the stats.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void ResetStats();

							/**
							 * @brief	Refresh the values.
							 * @author	Yadickson Soto
							 * @date	01/06/2012
							 */
							void refreshValues();
							/**
							 * @brief	Validate the values.
							 * @return true is validate values
							 * @author	Yadickson Soto
							 * @date	01/06/2012
							 */
							bool validateValues();

							/**
							 * @brief	Persist the values.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							void PersistValues();
												
						protected:
						  
						private:
							std::map<std::string, Smartmatic::GUI::Widgets::CounterStatWidget*> mapWidgets;
							std::list<Smartmatic::SAES::Voting::PBReports::StatisticWrapper*> statisticWrapper;


							void SetStrings();

							std::string strInstallationPackageNumberOfCards;	///< The installation package number of cards
							std::string strInstallationPackageSparePrintingRolls;   ///< The installation package spare printing rolls
							std::string strVoteMachines;	///< The vote machines
							std::string strTotalActivatedCards; ///< The total activated cards
							std::string strTotalActivatedOfficialCards; ///< The total activated official cards
							std::string strTotalActivatedDemoCards; ///< The total activated demo cards
							std::string strTotalSecurityCopyCards;  ///< The total security copy cards
							std::string strTotalBelgianActivatedCards;  ///< The total belgian activated cards
							std::string strTotalEuropeanActivatedCards; ///< The total european activated cards
							std::string strTotalBelgianActivatedOfficialCards;  ///< The total belgian activated official cards
							std::string strTotalEuropeanActivatedOfficialCards; ///< The total european activated official cards
							std::string strTotalBelgianActivatedDemoCards;  ///< The total belgian activated demo cards
							std::string strTotalEuropeanActivateDemoCards;  ///< The total european activate demo cards
							std::string strTotalIssueCards; ///< The total issue cards
							std::string strTotalOfficialVotesReceived;  ///< The total official votes received
							std::string strTotalDemoVotesReceived;  ///< The total demo votes received
							std::string strTotalReadingIssuesVotesReceived; ///< The total reading issues votes received
							std::string strTotalAnnulledVotesByRevelation;  ///< The total annulled votes by revelation
							std::string strTotalProxyVotes; ///< The total proxy votes
							std::string strTotalAnnulledVotes;  ///< The total annulled votes
							std::string strAdditionalHoursToVote;   ///< The additional hours to vote
							std::string strVotersWhichDamagedCards; ///< The voters which damaged cards
							std::string strVotersWhichCouldNotSeeVotes; ///< The voters which could not see votes
						};
					}
				}
			}
		}
	}
}

#endif // _STATISTIC_COUNTER_WIDGET_H_
