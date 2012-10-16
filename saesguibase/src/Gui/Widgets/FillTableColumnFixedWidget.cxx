/**
 * @file FillTableColumnFixedWidget.cxx
 * @brief Body class fill table mode widget
 * @date 15/03/2012
 * @author Yadickson Soto
 */

#include "FillTableColumnFixedWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;

FillTableColumnFixedWidget::FillTableColumnFixedWidget(TableCenterWidget * tableWidget)
: FillTableWidget(tableWidget)
{
}

FillTableColumnFixedWidget::~FillTableColumnFixedWidget()
{
}

void FillTableColumnFixedWidget::putPrincipal()
{
	tableWidget->resize(nRow, nCol);

	unsigned int maxRow = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getMaxRows();

	std::list <BallotOptionWidget * >::iterator it;

	for(it = principalList.begin();
		it != principalList.end();
		it++)
	{
        BallotOptionWidget * ballot = (*it);
        ballot->setSize(widgetW, widgetH);

        tableWidget->put(ballot, currentRow, currentCol);

        currentRow++;
        if(currentRow == nRow)
        {
        	currentRow = 0;
            currentCol++;
        }
        else if (currentRow == maxRow)
        {
        	currentRow = 0;
            currentCol++;
        }
	}
}
