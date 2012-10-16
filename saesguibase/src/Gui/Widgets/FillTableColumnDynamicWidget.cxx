/**
 * @file FillTableColumnDynamicWidget.cxx
 * @brief Body class fill table mode widget
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#include "FillTableColumnDynamicWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;

FillTableColumnDynamicWidget::FillTableColumnDynamicWidget(TableCenterWidget * tableWidget)
: FillTableWidget(tableWidget)
{
}

FillTableColumnDynamicWidget::~FillTableColumnDynamicWidget()
{
}

void FillTableColumnDynamicWidget::putPrincipal()
{
	unsigned int size = principalList.size();

	PivotConfig config = SAESGUIConfigurationManager::Current()->getPivotConfig(size);

	unsigned int maxRow = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getMaxRows();
	bool wrap = config.getWrap();

	unsigned int pRow;
	int pivot;

	if (wrap)
	{
		pRow = (size / config.getColumnCount());
		pivot = (size % config.getColumnCount());
	}
	else
	{
		pRow = nRow;
		pivot = 0;
	}

	unsigned int nCol = config.getColumnCount() + (standInList.size() > 0 ? 1: 0);

	tableWidget->resize(nRow, nCol);

	std::list <BallotOptionWidget * >::iterator it;

	for(it = principalList.begin();
		it != principalList.end();
		it++)
	{
        BallotOptionWidget * ballot = (*it);
        ballot->setSize(widgetW, widgetH);

        tableWidget->put(ballot, currentRow, currentCol);

        currentRow++;

        unsigned int add = (pivot > 0 ? 1 : 0);

        if(currentRow == pRow + add)
        {
        	currentRow = 0;
            currentCol++;
            pivot--;
        }
        else if (currentRow == maxRow)
        {
        	currentRow = 0;
            currentCol++;
        }
	}
}
