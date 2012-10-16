/**
 * @file FillTableWidget.hxx
 * @brief Header class fill table mode
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#ifndef FILLTABLEWIDGET_HXX_
#define FILLTABLEWIDGET_HXX_

#include <gtkmm.h>
#include <list>
#include <Widgets/TableCenterWidget.hxx>
#include "ballot-option-widget.h"
#include <Voting/Election/election-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class FillTableWidget
				 * @brief Class FillTableWidget
				 * @author Yadickson Soto
				 * @date 15/03/2012
				 */
				class FillTableWidget : public Gtk::EventBox
				{
				public:
					/**
					 * @brief Class constructor
					 * @param fillTableWidget fill mode table widget
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					FillTableWidget(Smartmatic::GUI::Widgets::TableCenterWidget * tableWidget);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					virtual ~FillTableWidget();
					/**
					 * @brief method add principal
					 * @param widget new widget
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					void addPrincipal(BallotOptionWidget * ballotOptionWidget);
					/**
					 * @brief method add stand in
					 * @param ballotOptionWidget new widget
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					void addStandIn(BallotOptionWidget * ballotOptionWidget);
					/**
					 * @brief method fill table
					 * @param contest contest info
					 * @param totalW total width
					 * @param totalH total height
					 * @author Yadickson Soto
					 * @date 16/03/2012
					 */
					void fill(Smartmatic::SAES::Voting::Election::Contest & contest, int totalW, int totalH);
					/**
					 * @brief method fill principal
					 * @author Yadickson Soto
					 * @date 16/03/2012
					 */
					virtual void putPrincipal() = 0;
					/**
					 * @brief method fill stand in
					 * @author Yadickson Soto
					 * @date 16/03/2012
					 */
					virtual void putStandIn();
					/**
					 * @brief method clear
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					void clear();
					/**
					 * @brief method update
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					void update();
					/**
					 * @brief method getter principal list
					 * @return principal list
					 * @author Yadickson Soto
					 * @date 16/03/2012
					 */
					std::list <BallotOptionWidget * > & getPrincipalList();
					/**
					 * @brief method getter stand in list
					 * @return stand in list
					 * @author Yadickson Soto
					 * @date 16/03/2012
					 */
					std::list <BallotOptionWidget * > & getStandInList();

				protected:

					Smartmatic::GUI::Widgets::TableCenterWidget * tableWidget; ///< table widget
					Gtk::Label * standInLabel; ///< label stand in
					Gtk::EventBox * standInEventBox; ///< box stand in

					unsigned int nRow; ///< number row
					unsigned int nCol; ///< number column

					float widgetW; ///< widget width
					float widgetH; //< widget height

					unsigned int currentRow; ///< current row
					unsigned int currentCol; ///< current column

					bool hideStandInLabelIfEmpty; ///< Hide stand in label if empty

					std::list <BallotOptionWidget * > principalList; ///< principal list
					std::list <BallotOptionWidget * > standInList; ///< stand in list
				};
			}
		}
	}
}

#endif /* FillTableWidget_HXX_ */
