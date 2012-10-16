/**
 * @file	BasePrintDocument.h
 *
 * @brief	Declares the base print document class.
 */

#ifndef BASEPRINTDOCUMENT_H_
#define BASEPRINTDOCUMENT_H_


#include <queue>
#include <qrencode.h>
#include <gtkmm.h>
#include <gdkmm.h>

#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include "Printing/DocumentOptions.h"
#include "Printing/DirectPrintingBackend.h"
#include "Printing/GraphicContextPrintingBackend.h"
#include "Printing/PrintDocumentResult.h"
#include "Printing/PrintDocumentClient.h"
#include <set>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
namespace SAES
{
namespace Printing
{
/**
 * @class	BasePrintDocument
 *
 * @brief	Base print document. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class BasePrintDocument
{
public:

	/**
	 * @fn	BasePrintDocument::BasePrintDocument(bool forceGTKPrinting = false);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	forceGTKPrinting	true to force gtk printing.
	 */

	BasePrintDocument(bool forceGTKPrinting = false);

	/**
	 * @fn	virtual BasePrintDocument::~BasePrintDocument();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~BasePrintDocument();

	/**
	 * @fn	void BasePrintDocument::setInitialPageSetup(Glib::RefPtr<Gtk::PageSetup> m_refPageSetup);
	 *
	 * @brief	Sets an initial page setup.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	m_refPageSetup	The reference page setup.
	 */

	void setInitialPageSetup(Glib::RefPtr<Gtk::PageSetup> m_refPageSetup);

	/**
	 * @fn	void BasePrintDocument::setInitialPrintSetings(Glib::RefPtr<Gtk::PrintSettings> m_refSettings);
	 *
	 * @brief	Sets an initial print setings.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	m_refSettings	The reference settings.
	 */

	void setInitialPrintSetings(Glib::RefPtr<Gtk::PrintSettings> m_refSettings);

	/**
	 * @fn	void BasePrintDocument::Print();
	 *
	 * @brief	Prints this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void Print();

//	void PrintPreview (Glib::RefPtr<Gtk::Widget> previewWidget);

	/**
	 * @fn	void BasePrintDocument::PrintPreview ( const Cairo::RefPtr<Cairo::Context>& graphicCtx ,
	 * 		Glib::RefPtr<Pango::Context> destPangoContext , double renderAreaWidth);
	 *
	 * @brief	Print preview.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	graphicCtx			Context for the graphic.
	 * @param	destPangoContext	Context for the destination pango.
	 * @param	renderAreaWidth 	Width of the render area.
	 */

	void PrintPreview (
			  const ::Cairo::RefPtr<Cairo::Context>& graphicCtx
			, Glib::RefPtr<Pango::Context> destPangoContext
			, double renderAreaWidth);

	/**
	 * @fn	void BasePrintDocument::CalculatePreviewDimensions ( Cairo::RefPtr<Cairo::Context> cr ,
	 * 		Glib::RefPtr<Pango::Context> pg , double areaWidth );
	 *
	 * @brief	Calculates the preview dimensions.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	cr		 	The carriage return.
	 * @param	pg		 	The page.
	 * @param	areaWidth	Width of the area.
	 */

	void CalculatePreviewDimensions (
			::Cairo::RefPtr<Cairo::Context> cr
			, Glib::RefPtr<Pango::Context>  pg
			, double areaWidth
			);

	/**
	 * @fn	double BasePrintDocument::GetWidth ()
	 *
	 * @brief	Gets the width.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The width.
	 */

	double GetWidth () {return mDocumentWidth;}

	/**
	 * @fn	double BasePrintDocument::GetHeight ()
	 *
	 * @brief	Gets the height.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The height.
	 */

	double GetHeight () {return mDocumentHeight;}

	/**
	 * @fn	void BasePrintDocument::setClient(PrintDocumentClient * client);
	 *
	 * @brief	set the client of the print document.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	client	If non-null, the client.
	 */

	void setClient (PrintDocumentClient * client);

	/**
	 * @fn	PrintDocumentResult BasePrintDocument::getDocumentResult ()
	 *
	 * @brief	Gets the document result.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The document result.
	 */

	PrintDocumentResult getDocumentResult () { return this->res; }

	void PreRenderDocument ();

protected:

	/**
	 * @fn	virtual void BasePrintDocument::PrintDoc()=0;
	 *
	 * @brief	Print document.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void PrintDoc()=0;

	/**
	 * @fn	virtual void BasePrintDocument::BeginPrint()=0;
	 *
	 * @brief	Begins a print.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void BeginPrint()=0;

	/**
	 * @fn	virtual void BasePrintDocument::EndPrint()=0;
	 *
	 * @brief	Ends a print.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void EndPrint()=0;

	/**
	 * @fn	void BasePrintDocument::NewTextBlock(DocumentTextOptions& textOptions);
	 *
	 * @brief	Creates a new text block.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	textOptions	Options for controlling the text.
	 */

	void NewTextBlock(DocumentTextOptions& textOptions);

	/**
	 * @fn	void BasePrintDocument::NewTextColunmsBlock(std::list<DocumentTextOptions>& textOptionList);
	 *
	 * @brief	Creates a new text colunms block.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	textOptionList	List of text options.
	 */

	void NewTextColunmsBlock(std::list<DocumentTextOptions>& textOptionList);

	/**
	 * @fn	void BasePrintDocument::ChangeFont(DocumentFontSize newFont);
	 *
	 * @brief	Change font.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	newFont	The new font.
	 */

	void ChangeFont(DocumentFontSize newFont);

	/**
	 * @fn	void BasePrintDocument::Indent(gint levelsToIndent =1);
	 *
	 * @brief	Indents.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	levelsToIndent	The levels to indent.
	 */

	void Indent(gint levelsToIndent =1);

	/**
	 * @fn	void BasePrintDocument::UnIndent(gint levelsToUnIndent =1);
	 *
	 * @brief	Un indent.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	levelsToUnIndent	The levels to un indent.
	 */

	void UnIndent(gint levelsToUnIndent =1);

	/**
	 * @fn	void BasePrintDocument::Rotate();
	 *
	 * @brief	Rotates this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void Rotate();

	/**
	 * @fn	void BasePrintDocument::DrawString(const Glib::ustring& text, bool addDocBreak = true);
	 *
	 * @brief	Draw string.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	text	   	The text.
	 * @param	addDocBreak	true to add document break.
	 */

	void DrawString(const Glib::ustring& text, bool addDocBreak = true);

	/**
	 * @fn	void BasePrintDocument::DrawStrings(std::list<Glib::ustring>& text,
	 * 		bool addDocBreak = true);
	 *
	 * @brief	Draw strings.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	text	The text.
	 * @param	addDocBreak 	true to add document break.
	 */

	void DrawStrings(std::list<Glib::ustring>&  text, bool addDocBreak = true);

	void AddBreak();

	/**
	 * @fn	void BasePrintDocument::DrawImage( Glib::RefPtr<Gdk::Pixbuf> image ,
	 * 		Smartmatic::SAES::Printing::DocumentImageAlignmet imgAligment ,
	 * 		Smartmatic::SAES::Printing::DocumentImageLayout imgLayout = Exclusive ,
	 * 		CellBorderType imageBorder = Border_None , int leftPadding = 0 , int rightPadding = 0 ,
	 * 		int topPadding = 0 , int bottomPadding = 0);
	 *
	 * @brief	Draw image.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	image		 	The image.
	 * @param	imgAligment  	The image aligment.
	 * @param	imgLayout	 	The image layout.
	 * @param	imageBorder  	The image border.
	 * @param	leftPadding  	The left padding.
	 * @param	rightPadding 	The right padding.
	 * @param	topPadding   	The top padding.
	 * @param	bottomPadding	The bottom padding.
	 */

	void DrawImage(
			  Glib::RefPtr<Gdk::Pixbuf> image
			, Smartmatic::SAES::Printing::DocumentImageAlignmet imgAligment
			, Smartmatic::SAES::Printing::DocumentImageLayout imgLayout = Exclusive
			, CellBorderType imageBorder = Border_None
			, int leftPadding = 0
			, int rightPadding = 0
			, int topPadding = 0
			, int bottomPadding = 0);

	void DrawQRCode (QRCodeContent& qr_content);

	void DrawQRCode (
			  const Smartmatic::System::SafeBuffer& data
			, gint pixelSize
			, gint margin
			, QRecLevel level
			, gint symbolVersion
			// Image content
			, Glib::RefPtr<Gdk::Pixbuf> backgroundImage
			, DocumentImageAlignmet imgAligment = Left
			, DocumentImageLayout imgLayout = Exclusive
			, CellBorderType imageBorder = Border_None
			, int leftPadding = 0
			, int rightPadding = 0
			, int topPadding = 0
			, int bottomPadding = 0
			, Smartmatic::Graphics::Image::PixbufComposer::ComposePosition position = Smartmatic::Graphics::Image::PixbufComposer::MIDDLE_CENTER
			);

	void SetSingleColumnLayout ();

	void SetDoubleColumnLayout ();

	/**
	 * @fn	void BasePrintDocument::NewLine();
	 *
	 * @brief	Creates a new line.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void NewLine();

	/**
	 * @fn	void BasePrintDocument::DrawLine (double lenght, DocumentImageAlignmet alignment);
	 *
	 * @brief	Draw line.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	lenght   	The lenght.
	 * @param	alignment	The alignment.
	 */

	void DrawLine (double lenght, DocumentImageAlignmet alignment);

	/**
	 * @fn	virtual void BasePrintDocument::OnSetupPrintOperation(Glib::RefPtr<Gtk::PrintOperation>& operation);
	 *
	 * @brief	Executes the setup print operation action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	operation	The operation.
	 */

	virtual void OnSetupPrintOperation(Glib::RefPtr<Gtk::PrintOperation>& operation);

	/**
	 * @fn	virtual void BasePrintDocument::OnBeginPrint(const Glib::RefPtr<Gtk::PrintContext>& context);
	 *
	 * @brief	Executes the begin print action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	context	The context.
	 */

	virtual void OnBeginPrint(const Glib::RefPtr<Gtk::PrintContext>& context);

	/**
	 * @fn	virtual void BasePrintDocument::OnDrawPage(const Glib::RefPtr<Gtk::PrintContext>& context ,
	 * 		int page_nr);
	 *
	 * @brief	Executes the draw page action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	context	The context.
	 * @param	page_nr	The page nr.
	 */

	virtual void OnDrawPage(const Glib::RefPtr<Gtk::PrintContext>& context , int page_nr);

	/**
	 * @fn	virtual void BasePrintDocument::OnDone(Gtk::PrintOperationResult result);
	 *
	 * @brief	Executes the done action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	result	The result.
	 */

	virtual void OnDone(Gtk::PrintOperationResult result);

	/**
	 * @fn	virtual void BasePrintDocument::OnStatusChanged(const Glib::RefPtr<Gtk::PrintOperation>& operation);
	 *
	 * @brief	Executes the status changed action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	operation	The operation.
	 */

	virtual void OnStatusChanged(const Glib::RefPtr<Gtk::PrintOperation>& operation);

	/**
	 * @fn	virtual void BasePrintDocument::OnRequestPageSetup(const Glib::RefPtr<Gtk::PrintContext>& context,
	 * 		int page_no, const Glib::RefPtr<Gtk::PageSetup>& setup);
	 *
	 * @brief	Executes the request page setup action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	context	The context.
	 * @param	page_no	The page no.
	 * @param	setup  	The setup.
	 */

	virtual void OnRequestPageSetup(const Glib::RefPtr<Gtk::PrintContext>& context,int page_no, const Glib::RefPtr<Gtk::PageSetup>& setup);

	bool OnPrintOperationTimeout ();

	/**
	 * @fn	virtual void BasePrintDocument::ConnectToSignals(const Glib::RefPtr<Gtk::PrintOperation>& operation);
	 *
	 * @brief	Connects to signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	operation	The operation.
	 */

	virtual void ConnectToSignals(const Glib::RefPtr<Gtk::PrintOperation>& operation);

	/**
	 * @fn	void BasePrintDocument::DisconnectFromSignals();
	 *
	 * @brief	Disconnects from signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void DisconnectFromSignals();
	void OnPrinterMonitorThreadBody ();

	Smartmatic::SAES::Common::Configuration::PrinterBackendType getBackendType();

private:

	enum DocumentContentType
	{
		Text,
		RotatedText,
		TextColumns,
		RotatedTextColumns,
		Image,
		Break,
		LineSep,
		TwoColumnRequest,
		SingleColumnRequest,
		QRCode
	};

	// Document Content Representation

	std::queue<DocumentContentType> contentTypeQueue;   ///< Queue of content types
	std::queue<TextContent> contentTextQueue;   ///< Queue of content texts
	std::queue<ImageContent> contentImageQueue; ///< Queue of content images
	std::queue<SeparatorContent> contentSepQueue;   ///< Queue of content separators
	std::queue<QRCodeContent> contentQRCodeQeue;

	std::list<Glib::ustring> currentContent;	///< The current content
	std::list<DocumentTextOptions> currentContentOptions;   ///< Options for controlling the current content
	DocumentContentType currenContentType;  ///< Type of the curren content

	// Printing management

	Glib::RefPtr<Gtk::PrintOperation> currentPrintOperation;	///< The current print operation
	Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;	///< The reference page setup
	Glib::RefPtr<Gtk::PrintSettings> m_refSettings; ///< The reference settings

	bool aborted_by_thread;

	std::list<sigc::connection> mSignalPool;	///< The signal pool
	std::list<sigc::connection> mTimeoutPool;	///< The signal pool

	Glib::Mutex m_PrintOpMutex;
	Glib::Cond m_JobSentCond;
	Glib::Cond m_MonitorFinishedCond;
	static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

	// Document build and formatting operations

	/**
	 * @fn	void BasePrintDocument::SplitIntoPages ();
	 *
	 * @brief	Split document content into pages
	 *
	 * @param [in,out]	gtkBackEnd	The gtk back end.
	 */
	void SplitIntoPages ();

	/**
	 * @fn	double BasePrintDocument::RenderDocument (GraphicContextPrintingBackend & gtkBackEnd);
	 *
	 * @brief	Renders the document described by gtkBackEnd.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	gtkBackEnd	The gtk back end.
	 *
	 * @return	.
	 */

	double RenderDocument (GraphicContextPrintingBackend & gtkBackEnd);

	/**
	 * @fn	void BasePrintDocument::CommitCurrentTextBlock();
	 *
	 * @brief	Commit current text block.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void CommitCurrentTextBlock();

	/**
	 * @fn	void BasePrintDocument::UpdateContentType();
	 *
	 * @brief	Updates the content type.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void UpdateContentType();

	/**
	 * @fn	void BasePrintDocument::innerPrintThreadBody();
	 *
	 * @brief	Inner print thread body.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void innerPrintThreadBody();

	/**
	 * @fn	void BasePrintDocument::PrintWithGTK();
	 *
	 * @brief	Print with gtk.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void PrintWithGTK();

	/**
	 * @fn	void BasePrintDocument::PrintDirect();
	 *
	 * @brief	Print direct.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void PrintDirect();

	/**
	 * @fn	void BasePrintDocument::GTKPrintingThreadBody ();
	 *
	 * @brief	Gtk printing thread body.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void GTKPrintingThreadBody ();

	gint isRotated; ///< The is rotated
	bool usingGtkPrinting;  ///< true to using gtk printing
	bool runWholeProcessInSeperatedThread;  ///< true to run whole process in seperated thread
	bool exportDoc; ///< true to export document
	bool mIsPrinterOpComplete;
	//bool contextRetreived;
	PrintDocumentResult res;	///< The resource

	GraphicContextPrintingBackend m_GraphicBackend;

	Glib::Thread* p_monitor;

	// Dimensions

	double mDocumentWidth;  ///< Width of the document
	double mDocumentHeight; ///< Height of the document

	DirectPrintingBackend directBackEnd;	///< The direct back end
	PrintDocumentClient *client;	///< The client

	Gtk::PrintStatus prev_status;
	Smartmatic::SAES::Common::Configuration::PrinterBackendType backendType;
	//int mNumPages;
};
}
}
}
#endif /* BASEPRINTDOCUMENT_H_ */
