/*
 * CryptoTestForm.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#include "CryptoTestForm.h"
#include <Environment/Configurations/resource-path-provider.h>
#include <config.h>

#define UI_FILE_INSTALL "ui/cryptotest.ui"
#define UI_FILE "src/cryptotest.ui"

using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Environment;

CryptoTestForm::CryptoTestForm():  BasicWindow (false,true),
    fixedPBE(NULL),
    fixedSignature(NULL),
    fixedSymmetricCypher(NULL),
	fixedCertificateValidation(NULL),
	fixedCFEncryptor(NULL)
{
  // TODO Auto-generated constructor stub

	set_size_request(800, 768);
	set_default_size(800, 768);
	set_skip_taskbar_hint(false);
	set_skip_pager_hint(false);
	set_decorated(true);

    Glib::RefPtr<Gtk::Builder> builder;

  std::string pathZ = ResourcePathProvider::Current()->GetResourcePath(GETTEXT_PACKAGE, UI_FILE);

  if (pathZ.empty())
  {
	pathZ = ResourcePathProvider::Current()->GetResourcePath(GETTEXT_PACKAGE, UI_FILE_INSTALL);
  }

    try
    {
        builder = Gtk::Builder::create_from_file(pathZ);
    }
    catch (const Glib::FileError & ex)
    {
        std::cerr << ex.what() << std::endl;
        return;
    }


    //exit
    exit.set_label("Exit");
    exit.signal_clicked().connect( sigc::mem_fun(*this,
                 &CryptoTestForm::on_exit_clicked) );
    exit.set_visible(true);


    //title
    title_label.set_text("CRYPTO TEST");
    title_label.set_visible(true);


    hbox.pack_end(exit);
    hbox.pack_start(title_label);
    hbox.set_visible(true);

    setTitle(&hbox);

    //get the widgets
      /*builder->get_widget("fixedPBE",this->fixedPBE);
      builder->get_widget("fixedSignature",this->fixedSignature);
      builder->get_widget("fixedSymmetricCypher",this->fixedSymmetricCypher);
	  builder->get_widget("fixedCertificateValidation",this->fixedCertificateValidation);
	  builder->get_widget("fixedCFEncryptor",this->fixedCFEncryptor);*/


      this->m_Notebook.set_visible(true);

      signTest.SetWindow(this);
	  symmTest.SetWindow(this);
      certTest.SetWindow(this);
      cfencryptor.SetWindow(this);
      rsaTest.SetWindow(this);

    //Add the Notebook pages:
      m_Notebook.append_page(*(pbeTest.GetWidget(builder)), "PBE");
      m_Notebook.append_page(*(signTest.GetWidget(builder)), "Signature");
      m_Notebook.append_page(*(symmTest.GetWidget(builder)), "SymmetricCypher");
	  m_Notebook.append_page(*(certTest.GetWidget(builder)), "CertificateValidation");
	  m_Notebook.append_page(*(cfencryptor.GetWidget(builder)), "CFEncryptor");
	  m_Notebook.append_page(*(rsaTest.GetWidget(builder)), "RSA");
	  m_Notebook.set_size_request(1000,650);

	  this->getClientAreaFrame().set_size_request(1000, 650);
      this->setWidget(&m_Notebook);

}

void CryptoTestForm::on_exit_clicked()
{
	hide();
}

CryptoTestForm::~CryptoTestForm()
{
  // TODO Auto-generated destructor stub
  if(fixedPBE== NULL)
    delete fixedPBE;
  if(fixedSignature)
    delete fixedSignature;
  if(fixedSymmetricCypher)
    delete fixedSymmetricCypher;
  if(fixedCertificateValidation)
    delete fixedCertificateValidation;
  if(fixedCFEncryptor)
	  delete fixedCFEncryptor;
}
