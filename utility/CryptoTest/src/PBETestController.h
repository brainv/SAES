/*
 * PBETestController.h
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#ifndef PBETESTCONTROLLER_H_
#define PBETESTCONTROLLER_H_

#include <gtkmm.h>
#include <System/Security/Cryptography/DigestAlgorithmLookup.h>


 class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_name); }

    Gtk::TreeModelColumn<int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  };



class PBETestController
{
public:
  PBETestController();
  virtual
  ~PBETestController();

   Gtk::Fixed* GetWidget( Glib::RefPtr<Gtk::Builder> builder);

private:

   void on_compute_clicked();

   Smartmatic::System::Security::Cryptography::DigestAlgType GetDigestType();

   Glib::ustring GetDigestName();

   Gtk::Fixed* fixedContainer;
   Gtk::RadioButton* hmacAlgorithm;

   Gtk::RadioButton* digestMD5;
   Gtk::RadioButton* digestSHA1;
   Gtk::RadioButton* digestSHA256;
   Gtk::RadioButton* digestSHA512;

   Gtk::ComboBox* digest;

   ModelColumns m_Columns;
   Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

   Gtk::Entry*  phrase;
   Gtk::Entry*  keySize;
   Gtk::Entry*  iterations;
   Gtk::Entry*  salt;


   Gtk::Button* compute;
   Gtk::TextView* outPut;

};

#endif /* PBETESTCONTROLLER_H_ */
