/*
 * QrTestMainWindow.h
 *
 *  Created on: Jul 14, 2011
 *      Author: root
 */

#ifndef QRTESTMAINWINDOW_H_
#define QRTESTMAINWINDOW_H_


#include <gtkmm.h>
#include "QRTestWidget.h"
#include "QRTestController.h"


class QrTestMainWindow : public Gtk::Window
{
public:

	QrTestMainWindow ();

	virtual ~QrTestMainWindow ();


private:

	/* Logic */

	int m_TestCount;
	Glib::RefPtr<QRTestController> m_AppController;
	std::list<QRTestWidget* > m_TestParams;


	/* Widgets */

	Glib::RefPtr<Gtk::Builder> m_Builder;

	// Containers

	Gtk::Frame* m_MainFrame;
	Gtk::ScrolledWindow* m_TestScrolledwindow;
	Gtk::Notebook m_MainNotebook;
	Gtk::VBox* m_TestsBox;

	Gtk::Fixed m_FixedContainer;


	// Buttons

	Gtk::Button* m_ExecuteButton;
	Gtk::Button* m_AddTestButton;


	/* Event Handling  */

	void on_addTestButton_clicked ();
	void on_executeButton_clicked ();

	/* Auxiliar  */

	void InitWidgets ();
	void AddTest ();

};

#endif /* QRTESTMAINWINDOW_H_ */
