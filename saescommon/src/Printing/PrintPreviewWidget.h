/**
 *
 * @file	PrintPreviewWidget.h
 *
 * @brief	Declares the print preview widget class.
 * 
 */

#ifndef PRINTPREVIEWWIDGET_H_
#define PRINTPREVIEWWIDGET_H_

#include <gtkmm.h>
#include <gdkmm.h>
#include <cairomm/surface.h>
#include "Printing/BasePrintDocument.h"

namespace Smartmatic
{
namespace SAES
{
namespace Printing
{

class PrintPreviewWidget: public Gtk::Widget
{
public:


	// Lifecycle

	/**
	 * @fn	PrintPreviewWidget::PrintPreviewWidget ();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	PrintPreviewWidget ();

	/**
	 * @fn	PrintPreviewWidget::PrintPreviewWidget(BasePrintDocument* doc);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	doc	If non-null, the document.
	 */

	PrintPreviewWidget(BasePrintDocument* doc);

	/**
	 * @fn	virtual PrintPreviewWidget::~PrintPreviewWidget();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~PrintPreviewWidget();


	// Access

	/**
	 * @fn	void PrintPreviewWidget::SetDocument (BasePrintDocument* newDoc);
	 *
	 * @brief	Sets a document.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	newDoc	If non-null, the new document.
	 */

	void SetDocument (BasePrintDocument* newDoc);


protected:

	//Overrides:

	/**
	 * @fn	virtual void PrintPreviewWidget::on_size_request(Gtk::Requisition* requisition);
	 *
	 * @brief	Handles size request signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	requisition	If non-null, the requisition.
	 */

	virtual void on_size_request(Gtk::Requisition* requisition);

	/**
	 * @fn	virtual void PrintPreviewWidget::on_size_allocate(Gtk::Allocation& allocation);
	 *
	 * @brief	Handles size allocate signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	allocation	The allocation.
	 */

	virtual void on_size_allocate(Gtk::Allocation& allocation);

	/**
	 * @fn	virtual void PrintPreviewWidget::on_map();
	 *
	 * @brief	Handles map signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void on_map();

	/**
	 * @fn	virtual void PrintPreviewWidget::on_unmap();
	 *
	 * @brief	Handles unmap signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void on_unmap();

	/**
	 * @fn	virtual void PrintPreviewWidget::on_realize();
	 *
	 * @brief	Handles realize signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void on_realize();

	/**
	 * @fn	virtual void PrintPreviewWidget::on_unrealize();
	 *
	 * @brief	Handles unrealize signals.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void on_unrealize();

	/**
	 * @fn	virtual bool PrintPreviewWidget::on_expose_event(GdkEventExpose* event);
	 *
	 * @brief	Raises the expose event.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	event	If non-null, the event.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	virtual bool on_expose_event(GdkEventExpose* event);

private:

	Glib::RefPtr<Gdk::Window> mrGdkWindow;  ///< The mr gdk window
	Cairo::RefPtr<Cairo::ImageSurface> mrDocSurface;	///< The mr document surface

	bool release; ///< release widget
	BasePrintDocument* mrDoc;   ///< The mr document

	double mDocWidth;   ///< Width of the document
	double mDocHeight;  ///< Height of the document
};

}
}
}

#endif /* PRINTPREVIEWWIDGET_H_ */
