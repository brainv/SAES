/*
 * PrintDocumentResult.cpp
 *
 *  Created on: Mar 19, 2011
 *      Author: marcel
 */

#include <iostream>
#include "PrintDocumentResult.h"

using namespace std;
using namespace Smartmatic::SAES::Printing;

PrintDocumentResult::PrintDocumentResult()
{
	wasSuccess = false;
}

PrintDocumentResult::~PrintDocumentResult()
{

}

PrintDocumentResult::PrintDocumentResult(bool success, Glib::ustring printer_status, PrintDocumentResult::PrintingResultEnum printResult)
{
	wasSuccess = success;
	printerStatusDetail = printer_status;
	printingResult = printResult;
}

void PrintDocumentResult::setResult(bool wasOk, Glib::ustring printerStatus, PrintDocumentResult::PrintingResultEnum printResult )
{
	this->wasSuccess = wasOk;	
	this->printerStatusDetail.assign (printerStatus);
	this->printingResult = printResult;
}

void PrintDocumentResult::getResult(bool& wasOk,
		Glib::ustring& printStatus, PrintDocumentResult::PrintingResultEnum& printResult )
{
	wasOk = this->wasSuccess;
	printStatus.assign ("-");
	printStatus = this->printerStatusDetail;
	printResult = this->printingResult;
}

PrintDocumentResult::PrintingResultEnum PrintDocumentResult::getResult(bool& wasOk, Glib::ustring& printStatus )
{
	wasOk= this->wasSuccess;
	printStatus.assign ("-");
	printStatus = this->printerStatusDetail;
	return this->printingResult;
}

bool PrintDocumentResult::getSuccess()
{
	return wasSuccess;
}

Glib::ustring PrintDocumentResult::getPrinterStatusDetail()
{
	return printerStatusDetail;
}

PrintDocumentResult::PrintingResultEnumType PrintDocumentResult::getPrintingResult()
{
	return printingResult;
}
