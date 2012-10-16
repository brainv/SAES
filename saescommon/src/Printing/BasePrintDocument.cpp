/**
 * @file BasePrintDocument.cpp
 * @brief Body class base print document
 * @date 04/03/2011
 * @author Freddy Gomez
 */

#include <iostream>
#include <System/Exception/BaseException.hxx>
#include "Functionalities/time-functionality.h"
#include "Printing/BasePrintDocument.h"
#include "Printing/DocumentOptions.h"
#include "Printing/PrinterStatusNotifier.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"
#include <Log/SMTTLogManager.h>

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

#define POOL(x) mSignalPool.push_back ( (x) ) ///< push signal pool

using namespace Smartmatic::Log;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace std;

ISMTTLog* BasePrintDocument::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.BasePrintDocument",GETTEXT_PACKAGE);

BasePrintDocument::BasePrintDocument(bool forceGTKPrinting)
       : runWholeProcessInSeperatedThread (false)
       , exportDoc (false)
       , res (false, "", PrintDocumentResult::PRINTING_NONE)
{
	currenContentType = Text;
	isRotated = true;
	usingGtkPrinting = true;
	client = NULL;
	
	backendType = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getPrinterBackendType();

	if(backendType == PrinterBackendType::CONFIGURATION_DIRECTPRINTING)
	{
		usingGtkPrinting = false;
	}
	else
	{
		usingGtkPrinting = true;
	}

	if(forceGTKPrinting) 
		usingGtkPrinting = true;
		
//	usingGtkPrinting = false;
	
	m_refPageSetup = Gtk::PageSetup::create();
	m_refSettings = Gtk::PrintSettings::create();
	//contextRetreived= false;
}

BasePrintDocument::~BasePrintDocument()
{
	DisconnectFromSignals ();
	mSignalPool.clear();

	while (!contentTypeQueue.empty())
	{
		contentTypeQueue.pop();
	}

	while (!contentTextQueue.empty())
	{
		contentTextQueue.pop();
	}

	while (!contentImageQueue.empty())
	{
		contentImageQueue.pop();
	}

	while (!contentSepQueue.empty())
	{
		contentSepQueue.pop();
	}

	currentContent.clear();
	currentContentOptions.clear();
	mSignalPool.clear();
}

void BasePrintDocument::setInitialPageSetup(Glib::RefPtr<Gtk::PageSetup> pageSetup)
{
	m_refPageSetup = pageSetup;
}

void BasePrintDocument::setInitialPrintSetings(
		Glib::RefPtr<Gtk::PrintSettings> printSettings)
{
	m_refSettings = printSettings;
}

void BasePrintDocument::PrintPreview (
		  const ::Cairo::RefPtr<Cairo::Context>& graphicCtx
		, Glib::RefPtr<Pango::Context> destPangoContext
		, double renderAreaWidth)
{
  float factor =  (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getScreenPreviewResolutionFactor();

	destPangoContext->set_resolution(factor);

	GraphicContextPrintingBackend gtkBackend (
			  graphicCtx
			, destPangoContext
			, renderAreaWidth);

	RenderDocument (gtkBackend);
}

void BasePrintDocument::CalculatePreviewDimensions (
		::Cairo::RefPtr<Cairo::Context> cr
		, Glib::RefPtr<Pango::Context>  pg
		, double areaWidth)
{
    float factor =  (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getScreenPreviewResolutionFactor();

	pg->set_resolution(factor);

	GraphicContextPrintingBackend gtkBackend (cr, pg, areaWidth);

	mDocumentHeight = RenderDocument (gtkBackend);
	mDocumentWidth = areaWidth;
}


//TODO: use a exception to signal failure
void BasePrintDocument::Print()
{
	bool skipPrint = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getSkipPrint();

	if(!skipPrint)
		innerPrintThreadBody();
	else
	{
		sleep(4);
		res.setResult(true,"Printing Simulation", PrintDocumentResult::PRINTING_COMPLETED);

		if(client != NULL)
			client->onDocumentPrinted(res);
	}
}

void BasePrintDocument::innerPrintThreadBody()
{
	BeginPrint();
	try
	{
		if(usingGtkPrinting)
		{
			PrintWithGTK();
		}
		else
		{
			PrintDoc ();
			PrintDirect();
		}
	}
	catch(BaseException& baseEx)
	{
		res.wasSuccess = false;
		res.printerStatusDetail = baseEx.getMessage();
		res.printingResult = PrintDocumentResult::PRINTING_UNEXPECTED_ERROR;
	}
	catch(std::exception& exc)
	{
		res.wasSuccess = false;
		res.printerStatusDetail = exc.what();
		res.printingResult = PrintDocumentResult::PRINTING_UNEXPECTED_ERROR;
	}

	EndPrint();
}

/**
 * Starts a text based print operation.
 */
void BasePrintDocument::PrintDirect()
{
	//create the current file
	directBackEnd.Init();

	while(!this->contentTypeQueue.empty())
	{
		DocumentContentType contentType =this->contentTypeQueue.front();
		this->contentTypeQueue.pop();

		if(contentType == Break)
			continue;
		if(contentType == Image && !this->contentImageQueue.empty())
		{
			ImageContent img = this->contentImageQueue.front();
			this->contentImageQueue.pop();
			directBackEnd.DrawImage(img.getImage());
		}
		else if ( contentType == QRCode && !(this->contentQRCodeQeue.empty()) )
		{
			QRCodeContent qrc = this->contentQRCodeQeue.front();
			directBackEnd.DrawQRCode (qrc);
			this->contentQRCodeQeue.pop();
		}
		else if (contentType == Text && !this->contentTextQueue.empty())
		{
			TextContent txt = this->contentTextQueue.front();
			this->contentTextQueue.pop();

			directBackEnd.DrawString(txt.getContent(), txt.getContentOptions());
		}
	}

	directBackEnd.End();
	res = directBackEnd.getPrintResult ();

	if(client != NULL)
		client->onDocumentPrinted(directBackEnd.getPrintResult());
	
}


void BasePrintDocument::PrintWithGTK()
{
	GTKPrintingThreadBody ();
}

void BasePrintDocument::GTKPrintingThreadBody ()
{
	currentPrintOperation = Gtk::PrintOperation::create ();
	currentPrintOperation->set_export_filename ("/tmp/print_custom_test.pdf");

	currentPrintOperation->set_n_pages (1);
	currentPrintOperation->set_allow_async (true);
	currentPrintOperation->set_track_print_status (true);

	ConnectToSignals(currentPrintOperation);

	prev_status = Gtk::PRINT_STATUS_INITIAL;

	PrinterStatusNotifier::CheckPrinterState (true);

	aborted_by_thread = false;
	p_monitor = Glib::Thread::create (sigc::mem_fun (*this, &BasePrintDocument::OnPrinterMonitorThreadBody), true);

	try
	{
		if(exportDoc)
			currentPrintOperation->run (Gtk::PRINT_OPERATION_ACTION_EXPORT);
		else
			currentPrintOperation->run (Gtk::PRINT_OPERATION_ACTION_PRINT);
	}
	catch (const Gtk::PrintError& ex)
	{
		res.setResult(false, ex.what (), PrintDocumentResult::PRINTING_SERVER_ERROR);

		if(client != NULL)
			client->onDocumentPrinted(res);
	}
}

void BasePrintDocument::ConnectToSignals(const Glib::RefPtr<Gtk::PrintOperation>& operation)
{
	POOL (operation->signal_begin_print ().connect (sigc::mem_fun(*this
			, &BasePrintDocument::OnBeginPrint), true));

	POOL (operation->signal_draw_page ().connect (sigc::mem_fun(*this
			, &BasePrintDocument::OnDrawPage), true));

	POOL (operation->signal_request_page_setup ().connect (sigc::mem_fun(*this
			, &BasePrintDocument::OnRequestPageSetup), true));

	POOL (operation->signal_done ().connect (sigc::mem_fun(*this
			, &BasePrintDocument::OnDone), true));

	POOL (operation->signal_status_changed ().connect (sigc::bind(sigc::mem_fun(*this
			, &BasePrintDocument::OnStatusChanged), operation )));
}

void BasePrintDocument::DisconnectFromSignals()
{
	for (list<sigc::connection>::iterator it = mSignalPool.begin ()
			; it != mSignalPool.end ()
			; it++)
	{
		it->disconnect();
	}
}



//============================ SIGNAL HANDLERS ===============================//

void BasePrintDocument::OnSetupPrintOperation(Glib::RefPtr<Gtk::PrintOperation>& operation)
{
}

void BasePrintDocument::OnBeginPrint(const Glib::RefPtr<Gtk::PrintContext>& context)
{
	Glib::RefPtr<Gtk::PageSetup> page_setup = context->get_page_setup ();

	GraphicContextPrintingBackend gtkBackEnd (
			  context->get_cairo_context ()
			, context->create_pango_context ()
			, context->get_width ()
			, context->get_height () - page_setup->get_bottom_margin (Gtk::UNIT_PIXEL) - 15
			);

	m_GraphicBackend = gtkBackEnd;

	PreRenderDocument ();
	int num_pages = m_GraphicBackend.GetNumPages();
	currentPrintOperation->set_n_pages (num_pages);
}

void BasePrintDocument::OnRequestPageSetup(const Glib::RefPtr<Gtk::PrintContext>& context,int page_no, const Glib::RefPtr<Gtk::PageSetup>& setup)
{

}

void BasePrintDocument::OnDrawPage(
		  const Glib::RefPtr<Gtk::PrintContext>& context
		, int page_nr)
{
	Cairo::RefPtr<Cairo::Context> ctx = context->get_cairo_context ();
	m_GraphicBackend.RenderPage (ctx);
}

void BasePrintDocument::OnDone(Gtk::PrintOperationResult result)
{
	switch (result)
	{
	case Gtk::PRINT_OPERATION_RESULT_ERROR:

		res.setResult(false, "Error sending print job to spooler", PrintDocumentResult::PRINTING_INTERNAL_ERROR);

		if(client != NULL)
			client->onDocumentPrinted(res);

		break;

	case Gtk::PRINT_OPERATION_RESULT_APPLY:

		break;

	case Gtk::PRINT_OPERATION_RESULT_CANCEL:

		res.setResult(false, "Print operation canceled", PrintDocumentResult::PRINTING_CANCELED);

		if(client != NULL)
			client->onDocumentPrinted(res);

		break;

	case Gtk::PRINT_OPERATION_RESULT_IN_PROGRESS:

		break;
	}
}

/**
 * Monitors the print job after spooling. Ends after the document has been
 * printed.
 */
void BasePrintDocument::OnStatusChanged(const Glib::RefPtr<Gtk::PrintOperation>& operation)
{
	PrinterStatusNotifier notifier;
	PrinterStatusNotifier::PhysichalStateEnumType state;
	LPSpooler spooler;

	bool success = false;
	Glib::ustring res_msg;
	PrintDocumentResult::PrintingResultEnumType result;

	Gtk::PrintStatus op_status = operation->get_status();

	switch (op_status)
	{
	case Gtk::PRINT_STATUS_INITIAL:
		logger->Debug("Initial");
		break;
	case Gtk::PRINT_STATUS_PREPARING:
		logger->Debug("Preparing");
		res.setResult(false, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationPreparing"), PrintDocumentResult::PRINTING_PREPARING);
		break;
	case Gtk::PRINT_STATUS_GENERATING_DATA:
		logger->Debug("Generating");
		res.setResult(false, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationGenerating"), PrintDocumentResult::PRINTING_GENERATING_DATA);
		break;
	case Gtk::PRINT_STATUS_SENDING_DATA:
		logger->Debug("Sending");
		res.setResult(false, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationSending"), PrintDocumentResult::PRINTING_SENDING_DATA);
		break;
	case Gtk::PRINT_STATUS_PENDING:
		logger->Debug("Pending");
		res.setResult(false, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationPending"), PrintDocumentResult::PRINTING_PENDING);

		if  ( prev_status == Gtk::PRINT_STATUS_PRINTING )
		{
			LPSpooler spooler;
			spooler.CancelJobs();
		}

		break;
	case Gtk::PRINT_STATUS_PENDING_ISSUE:
		logger->Debug("Pending Issue");
		res.setResult(false, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationPendingIssue"), PrintDocumentResult::PRINTING_PENDING);
		break;
	case Gtk::PRINT_STATUS_PRINTING:
		logger->Debug("Printing");
		prev_status = Gtk::PRINT_STATUS_PRINTING;
		res.setResult(false, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationPrinting"), PrintDocumentResult::PRINTING_PROCESSING);
		break;
	case Gtk::PRINT_STATUS_FINISHED:

		logger->Debug("Finished");

		state = notifier.getPrinterState();

		if ( state & notifier.getErrorCondition() )
			res.setResult(false, notifier.getCurrentStatusMessage (), PrintDocumentResult::PRINTING_COMPLETED);
		else
			res.setResult(true, _("Smartmatic.SAES.Printing.BasePrintDocument.PrintOperationCompleted"), PrintDocumentResult::PRINTING_COMPLETED);


		PrinterStatusNotifier::CheckPrinterState (true);

		if (p_monitor)
			p_monitor->join ();

		if(client != NULL)
			client->onDocumentPrinted(res);

		break;

	case Gtk::PRINT_STATUS_FINISHED_ABORTED:

		logger->Debug("Aborted");

		res.getResult (success, res_msg, result);

		if  ( ! aborted_by_thread )
		{
			res.setResult (
					false
					, _("Smartmatic.SAES.Printing.BasePrintDocument.AbortedBySystem")
					, PrintDocumentResult::PRINTING_JOB_ABORTED_BY_SYSTEM );
		}

		PrinterStatusNotifier::CheckPrinterState (false);

		if (p_monitor)
			p_monitor->join ();

		if(client != NULL)
			client->onDocumentPrinted(res);

		break;
	}
}

void BasePrintDocument::OnPrinterMonitorThreadBody ()
{
	PrinterStatusNotifier notifier;
	PrinterStatusNotifier::PhysichalStateEnumType state;

	bool success = false;
	Glib::ustring res_msg;
	PrintDocumentResult::PrintingResultEnumType result;
	int timeout = SAESCommonConfigurationManager::Current ()->getStatusMonitorTimeOut ();

	while ( true )
	{
		res.getResult (success, res_msg, result);

		if ( result == PrintDocumentResult::PRINTING_COMPLETED )
		{
			logger->Debug( " MONITOR OPERATION COMPLETED " );
			break;
		}
		else if ( result == PrintDocumentResult::PRINTING_ABORTED
		     || result == PrintDocumentResult::PRINTING_JOB_ABORTED_BY_SYSTEM )
		{
			logger->Debug( " MONITOR ERROR OPERATION HAS BEEN ABORTED " );
			break;
		}

		state = notifier.getPrinterState();

		if (    (state & notifier.getErrorCondition()) &&
			(   result == PrintDocumentResult::PRINTING_PROCESSING
		     || result == PrintDocumentResult::PRINTING_PENDING ) )
		{
			// At this point the PrintOperation cannot be canceled so we use the LPSpooler instead

			logger->Debug( " MONITOR ERROR CONDITION " );

			aborted_by_thread = true;
			res.setResult (false, notifier.getCurrentStatusMessage(), PrintDocumentResult::PRINTING_ABORTED);

			if ( SAESCommonConfigurationManager::Current ()->getStatusMonitorCancel () )
			{
				LPSpooler spooler;
				spooler.CancelJobs();
				PrinterStatusNotifier::CheckPrinterState (false);
			}

			break;
		}
		else
		{
			logger->Debug( " MONITOR NOT COMPLETED NO ERROR CONDITION " );
		}

		usleep (1000 * timeout);
	}
}



//=============================== AUXILIARS ==================================//

void BasePrintDocument::PreRenderDocument ()
{
	try
	{
		PrintDoc ();
	}
	catch(std::exception& ex)
	{
		res.setResult(false, "Error creating logical document:", PrintDocumentResult::PRINTING_INTERNAL_ERROR);

		DisconnectFromSignals();

		if(client != NULL)
			client->onDocumentPrinted(res);
	}

	logger->Debug("Start PreRenderDocument");

	m_GraphicBackend.Init();

	while(!this->contentTypeQueue.empty())
	{
		DocumentContentType content_type = this->contentTypeQueue.front();
		this->contentTypeQueue.pop();

		if( content_type == Image && !(this->contentImageQueue.empty()))
		{
			ImageContent img = this->contentImageQueue.front();
			this->contentImageQueue.pop();

			m_GraphicBackend.PreDrawImage(img);
		}
		else if (content_type == QRCode && !(this->contentQRCodeQeue.empty()))
		{
			QRCodeContent qrc = this->contentQRCodeQeue.front();
			this->contentQRCodeQeue.pop();

			m_GraphicBackend.PreDrawQRCode (qrc);
		}
		else if (content_type == Text && !(this->contentTextQueue.empty()))
		{
			TextContent txt = this->contentTextQueue.front();
			this->contentTextQueue.pop();

			m_GraphicBackend.PreDrawString(txt.getContent(), txt.getContentOptions());
		}
		else if (content_type == LineSep && !(this->contentSepQueue.empty()))
		{
			SeparatorContent line = this->contentSepQueue.front();
			contentSepQueue.pop();

			m_GraphicBackend.PreDrawSeparator (line);
		}
		else if (content_type == Break)
		{
			m_GraphicBackend.PreJumpInlineImage ();
		}
		else if (content_type == SingleColumnRequest)
		{
			m_GraphicBackend.PreSetSingleColumn ();
		}
		else if (content_type == TwoColumnRequest)
		{
			m_GraphicBackend.PreSetDoubleColumn ();
		}
		else
		{
			logger->Debug("Content type unsupported");
		}
	}

	logger->Debug("Start PreRenderDocument");

	m_GraphicBackend.End();
}

double BasePrintDocument::RenderDocument (GraphicContextPrintingBackend & gtkBackEnd)
{
	try
	{
		PrintDoc ();
	}
	catch(std::exception& ex)
	{
		res.setResult(false, "Error creating logical document:", PrintDocumentResult::PRINTING_INTERNAL_ERROR);

		DisconnectFromSignals();

		if(client != NULL)
			client->onDocumentPrinted(res);

		return 0;
	}

	gtkBackEnd.Init();

	while(!this->contentTypeQueue.empty())
	{
		DocumentContentType content_type = this->contentTypeQueue.front();
		this->contentTypeQueue.pop();

		if( content_type == Image && !(this->contentImageQueue.empty()))
		{
			ImageContent img = this->contentImageQueue.front();
			this->contentImageQueue.pop();

			gtkBackEnd.DrawImage(img);
		}
		else if (content_type == QRCode && !(this->contentQRCodeQeue.empty()))
		{
			QRCodeContent qrc = this->contentQRCodeQeue.front();
			this->contentQRCodeQeue.pop();

			m_GraphicBackend.DrawQRCode (qrc);
		}
		else if (content_type == Text && !(this->contentTextQueue.empty()))
		{
			TextContent txt = this->contentTextQueue.front();
			this->contentTextQueue.pop();

			gtkBackEnd.DrawString(txt.getContent(), txt.getContentOptions());
		}
		else if (content_type == LineSep && !(this->contentSepQueue.empty()))
		{
			SeparatorContent line = this->contentSepQueue.front();
			contentSepQueue.pop();

			gtkBackEnd.DrawLine (line);
		}
		else if (content_type == Break)
		{
			continue;
		}
		else
		{
			logger->Debug("Content type unsupported");
		}
	}

	gtkBackEnd.End();

	return gtkBackEnd.Height ();
}

void BasePrintDocument::CommitCurrentTextBlock()
{
	if(currenContentType != Image /*&& currenContentType != QRCode */&& this->currentContent.size() > 0 && this->currentContentOptions.size() > 0)
	{
		TextContent txtContent(currentContent, currentContentOptions);
		this->contentTypeQueue.push(currenContentType);
		this->contentTextQueue.push(txtContent);
		this->currentContent.clear();
	}
}

//TODO: Add parameters to the methods
void BasePrintDocument::UpdateContentType()
{
	if(isRotated)
	{
		if(currentContentOptions.size() >1)
		{
			currenContentType = Text;//RotatedTextColumns;
		}
		else
		{
			currenContentType = Text;//RotatedText;
		}
	}
	else
	{
		if(currentContentOptions.size() >1)
		{
			currenContentType = Text;
		}
		else
		{
			currenContentType = Text;//TextColumns;
		}
	}
}

void BasePrintDocument::Indent(gint levelsToIndent)
{
	CommitCurrentTextBlock();

	//New text block
	if(currentContentOptions.size() >0)
	{
		currentContent.clear(); //initialize the list of text
		std::_List_iterator<DocumentTextOptions> opIte = currentContentOptions.begin();
		while(opIte != currentContentOptions.end())
		{
			opIte->Indent(levelsToIndent);
			opIte++;
		}
		UpdateContentType();
	}
}

void BasePrintDocument::UnIndent(gint levelsToUnIndent )
{
	CommitCurrentTextBlock();
	//New text block
	if(currentContentOptions.size() >0)
	{
		currentContent.clear(); //initialize the list of text
		std::_List_iterator<DocumentTextOptions> opIte = currentContentOptions.begin();
		while(opIte != currentContentOptions.end())
		{
			opIte->UnIndent(levelsToUnIndent);
			opIte++;
		}
		UpdateContentType();
	}
}

void BasePrintDocument::Rotate()
{
	isRotated = !isRotated;
	CommitCurrentTextBlock();
	UpdateContentType();
}

void BasePrintDocument::NewLine()
{
	currentContent.push_back("\n");
}

void BasePrintDocument::SetSingleColumnLayout ()
{
	this->contentTypeQueue.push(SingleColumnRequest);
}

void BasePrintDocument::SetDoubleColumnLayout ()
{
	this->contentTypeQueue.push(TwoColumnRequest);
}

void BasePrintDocument::DrawLine (double lenght, DocumentImageAlignmet alignment)
{
	CommitCurrentTextBlock();

	SeparatorContent line (lenght, alignment);

	this->contentSepQueue.push(line);
	this->contentTypeQueue.push(LineSep);
	UpdateContentType();
}

void BasePrintDocument::NewTextBlock(DocumentTextOptions& textOptions)
{
	CommitCurrentTextBlock();
	currentContentOptions.clear();
	currentContentOptions.push_back(textOptions);
	UpdateContentType();
}

void BasePrintDocument::NewTextColunmsBlock(std::list<DocumentTextOptions>& textOptionList)
{
	CommitCurrentTextBlock();
	currentContentOptions.clear();
	std::_List_const_iterator<DocumentTextOptions> iteratorOptions = textOptionList.begin();
	while(iteratorOptions != textOptionList.end())
	{
		currentContentOptions.push_back(*iteratorOptions++);
	}
	UpdateContentType();
}

void BasePrintDocument::ChangeFont(DocumentFontSize newFont)
{
	CommitCurrentTextBlock();
	if(currentContentOptions.size() >0)
	{
		currentContent.clear(); //initialize the list of text
		std::_List_iterator<DocumentTextOptions> opIte = currentContentOptions.begin();

		while(opIte != currentContentOptions.end())
		{
			opIte->setFontSize(newFont);
			opIte++;
		}

		UpdateContentType();
	}
	UpdateContentType();
}

void BasePrintDocument::DrawString(const Glib::ustring&  text,	bool addDocBreak )
{
	currentContent.push_back(text);

	if(addDocBreak)
	{
		CommitCurrentTextBlock();
		this->contentTypeQueue.push(Break);
		UpdateContentType();
	}
}

void BasePrintDocument::DrawStrings(std::list<Glib::ustring> & text, bool addDocBreak )
{
	std::_List_iterator<Glib::ustring> opIte = text.begin();
	while(opIte != text.end())
	{
		currentContent.push_back(*opIte++);
	}
	if(addDocBreak)
	{
		CommitCurrentTextBlock();
		this->contentTypeQueue.push(Break);
		UpdateContentType();
	}
}

void BasePrintDocument::AddBreak()
{
	CommitCurrentTextBlock();
	this->contentTypeQueue.push(Break);
	UpdateContentType ();
}

void BasePrintDocument::DrawImage(
		  Glib::RefPtr<Gdk::Pixbuf> image
		, DocumentImageAlignmet imgAligment
		, DocumentImageLayout imgLayout
		, CellBorderType imageBorder
		, int leftPadding
		, int rightPadding
		, int topPadding
		, int bottomPadding
		)
{
	CommitCurrentTextBlock();

	ImageContent imgContent(image, imgAligment, imgLayout, imageBorder
			               , leftPadding, rightPadding, topPadding, bottomPadding);

	this->contentImageQueue.push(imgContent);
	this->contentTypeQueue.push(Image);
	UpdateContentType();
}

void BasePrintDocument::DrawQRCode (QRCodeContent& qr_content)
{
	CommitCurrentTextBlock ();
	this->contentQRCodeQeue.push (qr_content);
	this->contentTypeQueue.push (QRCode);
	UpdateContentType();
}

void BasePrintDocument::DrawQRCode (
		  const Smartmatic::System::SafeBuffer& data
		, gint pixelSize
		, gint margin
		, QRecLevel level
		, gint symbolVersion

		, Glib::RefPtr<Gdk::Pixbuf> backgroundImage
		, DocumentImageAlignmet imgAligment
		, DocumentImageLayout imgLayout
		, CellBorderType imageBorder
		, int leftPadding
		, int rightPadding
		, int topPadding
		, int bottomPadding
		, Smartmatic::Graphics::Image::PixbufComposer::ComposePosition position)
{
	CommitCurrentTextBlock ();

	QRCodeContent qr_code (data, pixelSize, margin, level, symbolVersion
			, backgroundImage
			, imgAligment
			, imgLayout
			, imageBorder
			, leftPadding
			, rightPadding
			, topPadding
			, bottomPadding
			, position);

	this->contentQRCodeQeue.push (qr_code);
	this->contentTypeQueue.push (QRCode);
	UpdateContentType();
}

void BasePrintDocument::setClient(PrintDocumentClient * client)
{
	this->client = client;
}

PrinterBackendType BasePrintDocument::getBackendType()
{
	return backendType;
}
