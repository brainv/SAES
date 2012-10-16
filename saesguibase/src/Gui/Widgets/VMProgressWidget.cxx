/*
 * VMProgressWidget.cxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#include "VMProgressWidget.hxx"

using namespace Smartmatic::SAES::GUI::Widgets;

VMProgressWidget::VMProgressWidget()
: ProgressWidget()
{

}

VMProgressWidget::~VMProgressWidget()
{

}

void VMProgressWidget::setImage(ProgressImage image)
{
	switch (image)
	{
		case PRINTING:
			ProgressWidget::setImage("ui/printer.img");
			break;
		case PRINTING_OK:
			ProgressWidget::setImage("ui/printer-ok.img");
			break;
		case PRINTING_ERROR:
			ProgressWidget::setImage("ui/printer-error.img");
			break;
		case SMARTCARD:
			ProgressWidget::setImage("ui/smartcard.gif");
			break;
		case AUTO_DIAGNOSIS_DEVICES:
			ProgressWidget::setImage("ui/auto-diagnosis-devices-mv.gif");
			break;
		default:
			ProgressWidget::setImage(image);
			break;
	}
}
