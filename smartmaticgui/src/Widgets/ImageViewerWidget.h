/*
 * ImageViewerWidget.h
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include <gtkmm.h>
#include "Widgets/ImageEventBox.h"
#include "Widgets/smartmatic-button.h"

#ifndef IMAGEVIEWERWIDGET_H_

/**
 * @brief	Gets the imageviewerwidget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define IMAGEVIEWERWIDGET_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ImageViewerWidget : public Gtk::Frame
			{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					ImageViewerWidget();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual ~ImageViewerWidget();

				protected:
					Gtk::VBox vBoxTop;  ///< The v box top
					Gtk::VPaned	vPaned; ///< The v paned
					Gtk::Adjustment * hScroller;	///< The scroller
					Gtk::Adjustment * vScroller;	///< The v scroller
					Gtk::ScrolledWindow* imageScroller; ///< The image scroller
					ImageEventBox imageBox; ///< The image box

					Gtk::Alignment navButtonHBoxAlignment;  ///< The nav button h box alignment

					Gtk::HBox navButtonHBoxAlignmentHBox;   ///< The nav button h box alignment h box
					Gtk::HBox navButtonHBox;	///< The nav button h box
					SmartmaticButton buttonPrevious; ///< The button previous
					SmartmaticButton buttonNext; ///< The button next
					SmartmaticButton buttonZoomIn;   ///< The button zoom in
					SmartmaticButton buttonZoomOut;  ///< The button zoom out
					SmartmaticButton buttonZoom1to1; ///< The first button zoom 1to
					SmartmaticButton buttonRotateAntiClockwise;  ///< The button rotate anti clockwise
					SmartmaticButton buttonRotateClockwise;  ///< The button rotate clockwise

					Gtk::Image iButtonPrevious; ///< The button previous
					Gtk::Image iButtonNext; ///< The button next
					Gtk::Image iButtonZoomIn;   ///< The button zoom in
					Gtk::Image iButtonZoomOut;  ///< The button zoom out
					Gtk::Image iButtonZoom1to1; ///< The first i button zoom 1to
					Gtk::Image iButtonRotateAntiClockwise;  ///< The button rotate anti clockwise
					Gtk::Image iButtonRotateClockwise;  ///< The button rotate clockwise

					double scalefactor; ///< The scalefactor

					/**
					 * @brief	Sets a scalefactor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	scale	The scale.
					 */

					void setScalefactor(double scale);

					/**
					 * @brief	Sets the buttons active.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	active	true to active.
					 */

					virtual void setButtonsActive(bool active);

					/**
					 * @brief	Busies.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param		true to.
					 */

					void busy(bool);
					Gdk::Cursor Hand, Watch;	///< The watch and hand

					/**
					 * @brief	Handles button next signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_next(void);

					/**
					 * @brief	Handles button previous signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_previous(void);

					/**
					 * @brief	Handles button zoom in signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_zoom_in(void);

					/**
					 * @brief	Handles button zoom out signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_zoom_out(void);

					/**
					 * @brief	Handles button zoom 1to 1 signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_zoom_1to1(void);

					/**
					 * @brief	Adjust adjustment on zoom.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	oldscale	The oldscale.
					 */

					virtual void adjust_adjustment_on_zoom(double oldscale);

					/**
					 * @brief	Handles button rotate anticlockwise signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_rotate_anticlockwise(void);

					/**
					 * @brief	Handles button rotate clockwise signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void on_button_rotate_clockwise(void);

					/**
					 * @brief	Adjust adjustment on rotate.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	angle	The angle.
					 * @param	h_old	The old.
					 * @param	v_old	The v old.
					 */

					virtual void adjust_adjustment_on_rotate(int angle,double h_old, double v_old);

					/**
					 * @brief	Executes the drag data received action.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param		The.
					 * @param		The.
					 * @param		The.
					 * @param		The.
					 * @param		The.
					 * @param		The.
					 */

					virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>&, int, int, const Gtk::SelectionData&, guint, guint);
			};
		}
	}
}

#endif /* IMAGEVIEWERWIDGET_H_ */
