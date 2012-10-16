/**
 * @file PMProgressWidget.cxx
 * @brief Body class president machine progress widget
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#include "PMProgressWidget.hxx"

using namespace Smartmatic::SAES::GUI::Widgets;

PMProgressWidget::PMProgressWidget()
: ProgressWidget()
{

}

PMProgressWidget::~PMProgressWidget()
{

}

void PMProgressWidget::setImage(ProgressImage image)
{
	switch (image)
	{
		case PRINTING:
			ProgressWidget::setImage("ui/printer-mp.gif");
			break;
		case PRINTING_OK:
			ProgressWidget::setImage("ui/printer-ok-mp.img");
			break;
		case PRINTING_ERROR:
			ProgressWidget::setImage("ui/printer-error-mp.img");
			break;
		case SMARTCARD:
			ProgressWidget::setImage("ui/smartcard-mp.gif");
			break;
		case AUTO_DIAGNOSIS_DEVICES:
			ProgressWidget::setImage("ui/auto-diagnosis-devices-mp.gif");
			break;
		default:
			ProgressWidget::setImage(image);
			break;
	}
}
