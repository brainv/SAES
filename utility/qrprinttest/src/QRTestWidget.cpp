/*
 * QRTestWidget.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: root
 */

#include <pangomm.h>
#include "QRTestWidget.h"



//============================= Life Cycle ===================================//

QRTestWidget::QRTestWidget(bool show_header)
{
	// TestTree

	m_TestTreeModel = Gtk::ListStore::create (m_TestTreeModelColumns);
	m_TestTreeView.set_model (m_TestTreeModel);
	m_TestTreeView.set_headers_visible(show_header);
	m_TestTreeView.set_headers_clickable(false);

	Glib::RefPtr<Gtk::TreeSelection> selection = m_TestTreeView.get_selection ();
//	selection->set_select_function (sigc::mem_fun (*this, &QRTestWidget::selection_callback));

	// Level Combo initialization

	m_TestTreeLevelComboModel = Gtk::ListStore::create (m_TestTreeModelLevelCombo);
	(*m_TestTreeLevelComboModel->append())[m_TestTreeModelLevelCombo.m_level_choices] = "Level L";
	(*m_TestTreeLevelComboModel->append())[m_TestTreeModelLevelCombo.m_level_choices] = "Level M";
	(*m_TestTreeLevelComboModel->append())[m_TestTreeModelLevelCombo.m_level_choices] = "Level Q";
	(*m_TestTreeLevelComboModel->append())[m_TestTreeModelLevelCombo.m_level_choices] = "Level H";


	// Test id

//	m_TestTreeView.append_column ("Test ID", m_TestTreeModelColumns.m_test_id);


	// data size

	Gtk::TreeView::Column* pDataColumn = Gtk::manage (new Gtk::TreeView::Column ("Data Size"));

	Gtk::CellRendererSpin* data_size_spin_renderer = Gtk::manage (new Gtk::CellRendererSpin() );
	Gtk::Adjustment* data_adj = manage (new Gtk::Adjustment (0.0, 0.0, .0, 1.0, 10.0, 100.0));

	data_size_spin_renderer->set_property ("digits", 0);
	data_size_spin_renderer->set_property ("adjustment", data_adj);
	data_size_spin_renderer->set_property ("editable", true);

	data_size_spin_renderer->property_alignment() = Pango::ALIGN_RIGHT;
	data_size_spin_renderer->property_editable () = true;
	data_size_spin_renderer->property_width() = 40;
	data_size_spin_renderer->property_height() = 40;

	data_size_spin_renderer->signal_edited().connect (sigc::mem_fun (*this, &QRTestWidget::on_data_size_edited));

	pDataColumn->pack_start (m_TestTreeModelColumns.m_data_label, false);
	pDataColumn->pack_start (*data_size_spin_renderer, true);
	pDataColumn->add_attribute (data_size_spin_renderer->property_text (), m_TestTreeModelColumns.m_data_size);
	m_TestTreeView.append_column (*pDataColumn);


	// version

	Gtk::TreeView::Column* pVersionColumn = Gtk::manage (new Gtk::TreeView::Column ("Version"));

	Pango::AttrList attr;

	Gtk::CellRendererText* version_text_renderer  = Gtk::manage (new Gtk::CellRendererText() );
	version_text_renderer->property_alignment() = Pango::ALIGN_RIGHT;

	Gtk::CellRendererSpin* version_spin_renderer = Gtk::manage (new Gtk::CellRendererSpin() );
	Gtk::Adjustment* ver_adj = manage (new Gtk::Adjustment (0.0, 0.0, 100.0, 1.0, 10.0, 100.0));

	version_spin_renderer->set_property ("digits", 0);
	version_spin_renderer->set_property ("adjustment", ver_adj);
	version_spin_renderer->set_property ("editable", true);
	version_spin_renderer->set_property ("width", 40);

	version_spin_renderer->signal_edited().connect (sigc::mem_fun (*this, &QRTestWidget::on_version_edited));

//	pVersionColumn->pack_start (m_TestTreeModelColumns.m_version_label, false);
	pVersionColumn->pack_start (*version_text_renderer, false);
	pVersionColumn->add_attribute(version_text_renderer->property_text (), m_TestTreeModelColumns.m_version_label);

	pVersionColumn->pack_start (*version_spin_renderer, true);
	pVersionColumn->add_attribute(version_spin_renderer->property_text (), m_TestTreeModelColumns.m_version);
	m_TestTreeView.append_column (*pVersionColumn);

//	m_TestTreeView.get_column (m_TestTreeView.append_column ("Data Size", *version_spin_renderer) - 1)
//			->add_attribute(version_spin_renderer->property_text (), m_TestTreeModelColumns.m_version);


	// correction level

	Gtk::TreeView::Column* pCorrectionColumn = Gtk::manage (new Gtk::TreeView::Column ("Correction Level"));

	m_ComboRenderer.property_model () = m_TestTreeLevelComboModel;
	m_ComboRenderer.property_has_entry () = false;
	m_ComboRenderer.property_text_column () = 0;
	m_ComboRenderer.property_editable () = true;
	m_ComboRenderer.property_width () = 80;

	m_ComboRenderer.signal_edited().connect (sigc::mem_fun (*this, &QRTestWidget::on_correction_edited));

	pCorrectionColumn->pack_start (m_TestTreeModelColumns.m_level_label, false);
	pCorrectionColumn->pack_start (m_ComboRenderer, true);
	pCorrectionColumn->add_attribute(m_ComboRenderer.property_text (), m_TestTreeModelColumns.m_correction_level);
	m_TestTreeView.append_column (*pCorrectionColumn);


	// Use Image

	Gtk::TreeView::Column* pImageColumn = Gtk::manage (new Gtk::TreeView::Column ("Image Based"));

	Gtk::CellRendererToggle* image_toggle_renderer = Gtk::manage (new Gtk::CellRendererToggle() );
	image_toggle_renderer->property_activatable() = true;
	image_toggle_renderer->property_sensitive() = true;
	image_toggle_renderer->property_width() = 70;

	image_toggle_renderer->signal_toggled().connect (sigc::mem_fun (*this, &QRTestWidget::on_use_image_edited));

	pImageColumn->pack_start(*image_toggle_renderer, true);
	pImageColumn->add_attribute(image_toggle_renderer->property_active() , m_TestTreeModelColumns.m_image_based);
	pImageColumn->add_attribute(image_toggle_renderer->property_visible() , m_TestTreeModelColumns.m_image_option_visible);
	m_TestTreeView.append_column (*pImageColumn);


	// pixel size

	Gtk::TreeView::Column* pPixelColumn = Gtk::manage (new Gtk::TreeView::Column ("Pixel Size"));

	Gtk::CellRendererSpin* pixel_size_spin_renderer = Gtk::manage (new Gtk::CellRendererSpin() );
	Gtk::Adjustment* pix_adj = manage (new Gtk::Adjustment (0.0, 0.0, 100.0, 1.0, 10.0, 100.0));

	pixel_size_spin_renderer->set_property ("digits", 0);
	pixel_size_spin_renderer->set_property ("adjustment", pix_adj);
	pixel_size_spin_renderer->set_property ("editable", true);
	pixel_size_spin_renderer->property_alignment() = Pango::ALIGN_RIGHT;
	pixel_size_spin_renderer->property_width () = 40;

	pixel_size_spin_renderer->signal_edited().connect (sigc::mem_fun (*this, &QRTestWidget::on_pixel_size_edited));

	pPixelColumn->pack_start (m_TestTreeModelColumns.m_pixel_label, false);
	pPixelColumn->pack_start (*pixel_size_spin_renderer, true);
	pPixelColumn->add_attribute(pixel_size_spin_renderer->property_text (), m_TestTreeModelColumns.m_pixel_size);
	pPixelColumn->add_attribute(pixel_size_spin_renderer->property_editable (), m_TestTreeModelColumns.m_image_based);
	pPixelColumn->add_attribute(pixel_size_spin_renderer->property_sensitive (), m_TestTreeModelColumns.m_image_based);
	m_TestTreeView.append_column (*pPixelColumn);


	// Use Background

	Gtk::TreeView::Column* pBgColumn = Gtk::manage (new Gtk::TreeView::Column ("Use Background"));

	Gtk::CellRendererToggle* bg_toggle_renderer = Gtk::manage (new Gtk::CellRendererToggle() );

	bg_toggle_renderer->property_width() = 90;
	bg_toggle_renderer->signal_toggled().connect (sigc::mem_fun (*this, &QRTestWidget::on_use_bkg_edited));

	pBgColumn->pack_start(*bg_toggle_renderer, true);
	pBgColumn->add_attribute(bg_toggle_renderer->property_active() , m_TestTreeModelColumns.m_use_background);
	pBgColumn->add_attribute(bg_toggle_renderer->property_visible() , m_TestTreeModelColumns.m_use_background_visible);
	pBgColumn->add_attribute(bg_toggle_renderer->property_activatable() , m_TestTreeModelColumns.m_image_based);
	pBgColumn->add_attribute(bg_toggle_renderer->property_sensitive() , m_TestTreeModelColumns.m_image_based);
	m_TestTreeView.append_column (*pBgColumn);


	// margin

	Gtk::TreeView::Column* pMarginColumn = Gtk::manage (new Gtk::TreeView::Column ("Margin Size"));

	Gtk::CellRendererSpin* margin_spin_renderer = Gtk::manage (new Gtk::CellRendererSpin() );
	Gtk::Adjustment* mar_adj = manage (new Gtk::Adjustment (0.0, 0.0, 100.0, 1.0, 10.0, 100.0));

	margin_spin_renderer->set_property ("digits", 0);
	margin_spin_renderer->set_property ("adjustment", mar_adj);
	margin_spin_renderer->set_property ("editable", true);
	margin_spin_renderer->set_property ("height", 40);
	margin_spin_renderer->set_property ("width", 40);

	margin_spin_renderer->signal_edited().connect (sigc::mem_fun (*this, &QRTestWidget::on_margin_edited));

	pMarginColumn->pack_start (m_TestTreeModelColumns.m_margin_label, false);
	pMarginColumn->pack_start (*margin_spin_renderer, true);
	pMarginColumn->add_attribute(margin_spin_renderer->property_text (), m_TestTreeModelColumns.m_margin);
	pMarginColumn->add_attribute(margin_spin_renderer->property_editable (), m_TestTreeModelColumns.m_use_background);
	pMarginColumn->add_attribute(margin_spin_renderer->property_sensitive (), m_TestTreeModelColumns.m_use_background);
	m_TestTreeView.append_column (*pMarginColumn);

	// Add Rows

	AddRows ();

	this->add (m_TestTreeView);
	this->show_all_children ();
}

QRTestWidget::~QRTestWidget()
{
	// TODO Auto-generated destructor stub
}


//========================== Public Interface ================================//

QRTestController::QrTestParamsType QRTestWidget::GetParams ()
{
	QRTestController::QrTestParamsType test_params;

	QRTestController::QrParamsRangeType data_range;
	data_range.min = m_Row_1 [m_TestTreeModelColumns.m_data_size];
	data_range.max = m_Row_2 [m_TestTreeModelColumns.m_data_size];
	data_range.step = m_Row_3 [m_TestTreeModelColumns.m_data_size];

	QRTestController::QrParamsRangeType version_range;
	version_range.min = m_Row_1 [m_TestTreeModelColumns.m_version];
	version_range.max = m_Row_2 [m_TestTreeModelColumns.m_version];
	version_range.step = m_Row_3 [m_TestTreeModelColumns.m_version];

	QRTestController::QrParamsRangeType level_range;
	level_range.min = StrLevel2Int (m_Row_1 [m_TestTreeModelColumns.m_correction_level]);
	level_range.max = StrLevel2Int (m_Row_2 [m_TestTreeModelColumns.m_correction_level]);
	level_range.step = 1;

	QRTestController::QrParamsRangeType pixel_range;
	pixel_range.min = m_Row_1 [m_TestTreeModelColumns.m_pixel_size];
	pixel_range.max = m_Row_2 [m_TestTreeModelColumns.m_pixel_size];
	pixel_range.step = m_Row_3 [m_TestTreeModelColumns.m_pixel_size];

	QRTestController::QrParamsRangeType margin_range;
	margin_range.min = m_Row_1 [m_TestTreeModelColumns.m_margin];
	margin_range.max = m_Row_2 [m_TestTreeModelColumns.m_margin];
	margin_range.step = m_Row_3 [m_TestTreeModelColumns.m_margin];

	bool image_based =  m_Row_2 [m_TestTreeModelColumns.m_image_based];
	bool use_bgn =  m_Row_2 [m_TestTreeModelColumns.m_use_background];

	test_params.data_size = data_range;
	test_params.version = version_range;
	test_params.correction_level = level_range;
	test_params.pixel_size = pixel_range;
	test_params.margin_size = margin_range;
	test_params.image_based = image_based;
	test_params.use_background = use_bgn;

	return test_params;
}

int QRTestWidget::StrLevel2Int (const Glib::ustring& levelStr)
{
	if ( levelStr == "Level L" )
		return (int)QRTestController::QRETST_ECLEVEL_L;

	if ( levelStr == "Level M" )
		return (int)QRTestController::QRETST_ECLEVEL_M;

	if ( levelStr == "Level Q" )
		return (int)QRTestController::QRETST_ECLEVEL_Q;

	if ( levelStr == "Level H" )
		return (int)QRTestController::QRETST_ECLEVEL_H;

	return 0;
}


//============================= Auxiliar =====================================//

void QRTestWidget::AddRows ()
{
	m_Row_1 = *(m_TestTreeModel->append ());
	m_Row_2 = *(m_TestTreeModel->append ());
	m_Row_3 = *(m_TestTreeModel->append ());

	m_Row_1 [m_TestTreeModelColumns.m_test_id] = "";
	m_Row_2 [m_TestTreeModelColumns.m_test_id] = "Test"; //TODO: generate ID
	m_Row_3 [m_TestTreeModelColumns.m_test_id] = "";

	m_Row_1 [m_TestTreeModelColumns.m_data_label] = "min";
	m_Row_2 [m_TestTreeModelColumns.m_data_label] = "max";
	m_Row_3 [m_TestTreeModelColumns.m_data_label] = "step";

	m_Row_1 [m_TestTreeModelColumns.m_data_size] = 0;
	m_Row_2 [m_TestTreeModelColumns.m_data_size] = 20;
	m_Row_3 [m_TestTreeModelColumns.m_data_size] = 5;

	m_Row_1 [m_TestTreeModelColumns.m_version_label] = "min";
	m_Row_2 [m_TestTreeModelColumns.m_version_label] = "max";
	m_Row_3 [m_TestTreeModelColumns.m_version_label] = "step";

	m_Row_1 [m_TestTreeModelColumns.m_version] = 10;
	m_Row_2 [m_TestTreeModelColumns.m_version] = 24;
	m_Row_3 [m_TestTreeModelColumns.m_version] = 1;

	m_Row_1 [m_TestTreeModelColumns.m_level_label] = "min";
	m_Row_2 [m_TestTreeModelColumns.m_level_label] = "max";
	m_Row_3 [m_TestTreeModelColumns.m_level_label] = "";

	m_Row_1[m_TestTreeModelColumns.m_correction_level] = "Level L";
	m_Row_2[m_TestTreeModelColumns.m_correction_level] = "Level M";
	m_Row_3[m_TestTreeModelColumns.m_correction_level] = "";

	m_Row_1 [m_TestTreeModelColumns.m_image_option_visible] = false;
	m_Row_2 [m_TestTreeModelColumns.m_image_option_visible] = true;
	m_Row_3 [m_TestTreeModelColumns.m_image_option_visible] = false;
	m_Row_1 [m_TestTreeModelColumns.m_image_based] = false;
	m_Row_2 [m_TestTreeModelColumns.m_image_based] = false;
	m_Row_3 [m_TestTreeModelColumns.m_image_based] = false;

	m_Row_1 [m_TestTreeModelColumns.m_pixel_label] = "min";
	m_Row_2 [m_TestTreeModelColumns.m_pixel_label] = "max";
	m_Row_3 [m_TestTreeModelColumns.m_pixel_label] = "step";

	m_Row_1 [m_TestTreeModelColumns.m_pixel_size] = 2;
	m_Row_2 [m_TestTreeModelColumns.m_pixel_size] = 5;
	m_Row_3 [m_TestTreeModelColumns.m_pixel_size] = 1;

	m_Row_1 [m_TestTreeModelColumns.m_use_background_visible] = false;
	m_Row_2 [m_TestTreeModelColumns.m_use_background_visible] = true;
	m_Row_3 [m_TestTreeModelColumns.m_use_background_visible] = false;
	m_Row_1 [m_TestTreeModelColumns.m_use_background] = false;
	m_Row_2 [m_TestTreeModelColumns.m_use_background] = false;
	m_Row_3 [m_TestTreeModelColumns.m_use_background] = false;

	m_Row_1 [m_TestTreeModelColumns.m_margin_label] = "min";
	m_Row_2 [m_TestTreeModelColumns.m_margin_label] = "max";
	m_Row_3 [m_TestTreeModelColumns.m_margin_label] = "step";

	m_Row_1 [m_TestTreeModelColumns.m_margin] = 1;
	m_Row_2 [m_TestTreeModelColumns.m_margin] = 4;
	m_Row_3 [m_TestTreeModelColumns.m_margin] = 1;
}

bool QRTestWidget::selection_callback (
		  const Glib::RefPtr<Gtk::TreeModel>& model
	    , const Gtk::TreeModel::Path& path
	    , bool value)
{
	return false;
}

//============================= Signal Handling ==============================//

void QRTestWidget::on_data_size_edited (const Glib::ustring& str_path, const Glib::ustring& value)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
        (*row)[m_TestTreeModelColumns.m_data_size] = atoi (value.c_str ());
}

void QRTestWidget::on_version_edited (const Glib::ustring& str_path, const Glib::ustring& value)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
        (*row)[m_TestTreeModelColumns.m_version] = atoi (value.c_str ());
}

void QRTestWidget::on_correction_edited (const Glib::ustring& str_path, const Glib::ustring& value)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
        (*row)[m_TestTreeModelColumns.m_correction_level] = value;
}

void QRTestWidget::on_pixel_size_edited (const Glib::ustring& str_path, const Glib::ustring& value)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
        (*row)[m_TestTreeModelColumns.m_pixel_size] = atoi (value.c_str ());
}

void QRTestWidget::on_margin_edited (const Glib::ustring& str_path, const Glib::ustring& value)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
        (*row)[m_TestTreeModelColumns.m_margin] = atoi (value.c_str ());
}

void QRTestWidget::on_use_image_edited (const Glib::ustring& str_path)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
    {
        (*row)[m_TestTreeModelColumns.m_image_based] = ! (*row)[m_TestTreeModelColumns.m_image_based];

        row--;
        (*row)[m_TestTreeModelColumns.m_image_based] = ! (*row)[m_TestTreeModelColumns.m_image_based];

        row++;
        row++;
        (*row)[m_TestTreeModelColumns.m_image_based] = ! (*row)[m_TestTreeModelColumns.m_image_based];
    }
}

void QRTestWidget::on_use_bkg_edited (const Glib::ustring& str_path)
{
    Gtk::TreePath path(str_path);
    Gtk::TreeModel::iterator row = m_TestTreeModel->get_iter(path);
    if (row)
    {
        (*row)[m_TestTreeModelColumns.m_use_background] = ! (*row)[m_TestTreeModelColumns.m_use_background];

        row--;
        (*row)[m_TestTreeModelColumns.m_use_background] = ! (*row)[m_TestTreeModelColumns.m_use_background];

        row ++;
        row ++;
        (*row)[m_TestTreeModelColumns.m_use_background] = ! (*row)[m_TestTreeModelColumns.m_use_background];
    }

}





