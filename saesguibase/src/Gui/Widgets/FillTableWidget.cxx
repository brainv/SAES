/**
 * @file FillTableWidget.cxx
 * @brief Body class fill table mode widget
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#include "FillTableWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Configuration;

FillTableWidget::FillTableWidget(TableCenterWidget * tableWidget)
: Gtk::EventBox()
{
	this->tableWidget = tableWidget;
	this->nRow = 0;
	this->nCol = 0;
	this->widgetW = 0.0;
	this->widgetH = 0.0;
	this->currentRow = 0;
	this->currentCol = 0;
	this->hideStandInLabelIfEmpty = true;

	standInLabel = new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.Substitute"));
	standInLabel->show();
	standInLabel->set_name(SAESGUIConfigurationManager::Current()->GetStandInLabelLabelName());

	standInEventBox = new Gtk::EventBox();
	standInEventBox->show();
	standInEventBox->add(*standInLabel);
	standInEventBox->set_name(SAESGUIConfigurationManager::Current()->GetStandInLabelEventName());

	this->add(*tableWidget);
	this->show();
}

FillTableWidget::~FillTableWidget()
{
	this->remove();

	clear();

	if (tableWidget)
	{
		delete tableWidget;
		tableWidget = NULL;
	}
	if (standInLabel)
	{
		delete standInLabel;
		standInLabel = NULL;
	}
	if (standInEventBox)
	{
		delete standInEventBox;
		standInEventBox = NULL;
	}
}

void FillTableWidget::addPrincipal(BallotOptionWidget * widget)
{
	principalList.push_back(widget);
}

void FillTableWidget::addStandIn(BallotOptionWidget * widget)
{
	standInList.push_back(widget);
}

void FillTableWidget::clear()
{
	std::list <BallotOptionWidget * >::iterator it;

	for (it = principalList.begin();
		 it != principalList.end();
		 it++)
	{
		BallotOptionWidget * widget = (*it);
		delete widget;
		widget = NULL;
	}

	for (it = standInList.begin();
		 it != standInList.end();
		 it++)
	{
		BallotOptionWidget * widget = (*it);
		delete widget;
		widget = NULL;
	}

	principalList.clear();
	standInList.clear();
}

void FillTableWidget::update()
{
	standInLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.Substitute"));
}

std::list <BallotOptionWidget * > & FillTableWidget::getPrincipalList()
{
	return principalList;
}

std::list <BallotOptionWidget * > & FillTableWidget::getStandInList()
{
	return standInList;
}

void FillTableWidget::fill(Contest & contest, int totalW, int totalH)
{
	BallotOptionSelectionConfiguration config = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration();

	nCol = config.getMaxColumns();
	float rowSpacing = config.getBallotsMargin();
	float colSpacing = config.getBallotsMargin();
	float headerHeigth = config.getFrameHeaderHeight();
	float bottomHeigth = config.getFrameBottomHeight();
	int fixBorder = config.getFixBorder();
	bool resizeBallotBox = config.getResizeBallotBox();

	float ballotRelation = 0.0;

	if(config.getUseCustomBallotRelation())
	{
		ballotRelation = config.getBallotRelation();
	}
	else
	{
		Display_info disInfo = contest.getDisplay_info();
		ballotRelation = disInfo.getImage_width_height_relation();
	}

	static float numberW = SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration().getNumberWidth();
	static int candidatesButtonsSpacing = config.getCandidatesButtonsSpacing();

	totalH -= (headerHeigth + bottomHeigth + candidatesButtonsSpacing + 10);
	totalW -= fixBorder;

	//calculate rows of table
	float boxW = totalW / (float)nCol;
	widgetW = boxW - colSpacing * ((nCol - 1) / (float)nCol);
	float imageW = widgetW - numberW;

	widgetH = imageW / ballotRelation;
	float boxH = widgetH + rowSpacing;

	nRow = totalH / boxH;

	if ( nRow > config.getMaxRows())
	{
		nRow = config.getMaxRows();
	}

	unsigned int ballotsToDisplay = principalList.size() + standInList.size() + 1;

	bool useMaxBallotNumber = config.getUseMaxBallotNumberFromContest();

	if(useMaxBallotNumber)
	{
		ballotsToDisplay = MachineOperationManager::getInstance()->getElectoralConfiguration()->getMaxBallotOptionByContestCode(contest.getCode());
		ballotsToDisplay += 1;
	}

	tableWidget->setSpacings(colSpacing, colSpacing);

	if (resizeBallotBox)
	{
		if(nRow * nCol < ballotsToDisplay)
		{
			nRow = ballotsToDisplay / nCol;
			float rest = ballotsToDisplay % nCol;
			nRow = rest > 0.0 ? nRow + 1 : nRow;

			boxH = totalH / (float) nRow;
			widgetH = boxH - rowSpacing;

			imageW = widgetH * ballotRelation;
			widgetW = imageW + numberW;
			boxW = widgetW;
		}

		if(nRow * (nCol-1) < principalList.size())
		{
			nRow = principalList.size() / (nCol-1);
			float rest = principalList.size() % (nCol-1);
			nRow = rest > 0.0 ? nRow + 1 : nRow;

			boxH = totalH / (float) nRow;
			widgetH = boxH - rowSpacing;

			imageW = widgetH * ballotRelation;
			widgetW = imageW + numberW;
			boxW = widgetW;
		}
	}

	currentRow = 0;
	currentCol = 0;

	putPrincipal();
	putStandIn();
}

void FillTableWidget::putStandIn()
{
	std::list <BallotOptionWidget * >::iterator it;

	//calculate first position of the substitute label, then position of stand-in widgets
	if(currentRow > 0 && currentCol == nCol - 1)
	{
		currentRow++;
	}
	else
	{
		currentRow = 0;
	}

	currentCol = nCol - 1;

	//ballot_option substitute
	if(standInList.size() != 0)
	{
		tableWidget->put(standInEventBox, currentRow, currentCol);
		currentRow++;

		for(it = standInList.begin(); it != standInList.end(); it++)
		{
	        BallotOptionWidget * ballot = (*it);
	        ballot->setSize(widgetW, widgetH);

	        tableWidget->put(ballot, currentRow, currentCol);

			currentRow++;
			if(currentRow == nRow)
			{
				break;
			}
		}
	}
	else
	{
		if(!hideStandInLabelIfEmpty)
		{
			tableWidget->put(standInEventBox, currentRow, currentCol);
		}
	}
}
