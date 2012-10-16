/*
 * QRTestWidget.h
 *
 *  Created on: Jul 19, 2011
 *      Author: root
 */

#ifndef QRTESTWIDGET_H_
#define QRTESTWIDGET_H_

#include <gtkmm.h>
#include "QRTestController.h"

class QRTestWidget : public Gtk::Frame
{
public:

	QRTestWidget(bool show_header);

	virtual ~QRTestWidget();


	/* Public interface */

	QRTestController::QrTestParamsType GetParams ();


	/* Column Models */


	class TestTreeModelLevelCombo : public Gtk::TreeModel::ColumnRecord
	{
	public:

		TestTreeModelLevelCombo ()
		{
			add (m_level_choices);
		}

		Gtk::TreeModelColumn<Glib::ustring> m_level_choices;
	};

	class TestTreeModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:

		TestTreeModelColumns ()
		{
			add (m_test_id);
			add (m_data_label);
			add (m_data_size);
			add (m_version_label);
			add (m_version);
			add (m_level_label);
			add (m_correction_level);
			add (m_image_option_visible);
			add (m_image_based);
			add (m_pixel_label);
			add (m_pixel_size);
			add (m_use_background_visible);
			add (m_use_background);
			add (m_margin_label);
			add (m_margin);
			add (m_progress);
		}

		Gtk::TreeModelColumn<Glib::ustring> m_test_id;

		Gtk::TreeModelColumn<Glib::ustring> m_data_label;
		Gtk::TreeModelColumn<int> m_data_size;

		Gtk::TreeModelColumn<Glib::ustring> m_version_label;
		Gtk::TreeModelColumn<int> m_version;

		Gtk::TreeModelColumn<Glib::ustring> m_level_label;
		Gtk::TreeModelColumn<Glib::ustring> m_correction_level;

		Gtk::TreeModelColumn<bool> m_image_option_visible;
		Gtk::TreeModelColumn<bool> m_image_based;

		Gtk::TreeModelColumn<Glib::ustring> m_pixel_label;
		Gtk::TreeModelColumn<int> m_pixel_size;

		Gtk::TreeModelColumn<bool> m_use_background_visible;
		Gtk::TreeModelColumn<bool> m_use_background;

		Gtk::TreeModelColumn<Glib::ustring> m_margin_label;
		Gtk::TreeModelColumn<int> m_margin;

		Gtk::TreeModelColumn<int> m_progress;
	};

private:

	/* Signal handling */

	void on_data_size_edited (const Glib::ustring& path, const Glib::ustring& value);
	void on_version_edited (const Glib::ustring& path, const Glib::ustring& value);
	void on_correction_edited (const Glib::ustring& path, const Glib::ustring& value);
	void on_pixel_size_edited (const Glib::ustring& path, const Glib::ustring& value);
	void on_margin_edited (const Glib::ustring& path, const Glib::ustring& value);

	void on_use_image_edited (const Glib::ustring& path);
	void on_use_bkg_edited (const Glib::ustring& path);


	// Rows

	Gtk::TreeModel::Row m_Row_1;
	Gtk::TreeModel::Row m_Row_2;
	Gtk::TreeModel::Row m_Row_3;

	// Combo box for correction level values

	Glib::RefPtr<Gtk::ListStore> m_TestTreeLevelComboModel;
	TestTreeModelLevelCombo m_TestTreeModelLevelCombo;
	Gtk::CellRendererCombo m_ComboRenderer;

	// List of all other parameters

	Glib::RefPtr<Gtk::ListStore> m_TestTreeModel;
	TestTreeModelColumns m_TestTreeModelColumns;
	Gtk::TreeView m_TestTreeView;


	/* Auxiliar methods */

	void AddRows ();
	int StrLevel2Int (const Glib::ustring& levelStr);

	bool selection_callback (
			  const Glib::RefPtr<Gtk::TreeModel>& model
		    , const Gtk::TreeModel::Path& path
		    , bool value);
};

#endif /* QRTESTWIDGET_H_ */
