/**
 * @file BallotOptionTableWidget.hxx
 * @brief Header class ballot option table widget
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#ifndef BALLOTOPTIONTABLEWIDGET_HXX_
#define BALLOTOPTIONTABLEWIDGET_HXX_

#include <gtkmm.h>
#include <Voting/Election/election-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class FillTableWidget;
				class BallotOptionWidget;

				/**
				 * @class BallotOptionTableWidget
				 * @brief Class BallotOptionTableWidget
				 * @author Yadickson Soto
				 * @date 15/03/2012
				 */
				class BallotOptionTableWidget : public Gtk::Frame
				{
				public:
					/**
					 * @brief Class constructor
					 * @param fillTableWidget fill mode table widget
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					BallotOptionTableWidget(FillTableWidget * fillTableWidget);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto
					 * @date 15/03/2012
					 */
					virtual ~BallotOptionTableWidget();
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
					FillTableWidget * fillTableWidget; ///< fill table mode widget
				};
			}
		}
	}
}

#endif /* BALLOTOPTIONTABLEWIDGET_HXX_ */
