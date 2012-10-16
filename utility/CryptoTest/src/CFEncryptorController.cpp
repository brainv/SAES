/*
 * CFEncryptorController.cpp
 *
 *  Created on: Apr 21, 2011
 *      Author: fgomez
 */

#include "CFEncryptorController.h"
#include <iostream>

CFEncryptorController::CFEncryptorController():
fixedContainer(NULL),
window(NULL),
checkbuttonSign(NULL),
checkbuttonEncryptFiles(NULL),
checkbuttonProtectSecretKey(NULL),

entryInputDir(NULL),
entryOutPutDir(NULL),
entrySingP12(NULL),
entryProtectionKey(NULL),

buttonSelectinputDir(NULL),
buttonSelectOutDi(NULL),
buttonSelectCer(NULL),
buttonRun(NULL),
textviewLog(NULL)
{
	// TODO Auto-generated constructor stub
	encryptorClass.finished.connect(sigc::mem_fun(this, &CFEncryptorController::on_encryption_finished));
	//encryptorClass.updateMessage.connect(sigc::mem_fun(this, &CFEncryptorController::on_encryption_update));

	encryptorClass.updateMessage.connect(sigc::bind(sigc::mem_fun(this, &CFEncryptorController::on_encryption_update), &encryptorClass));

}

CFEncryptorController::~CFEncryptorController() {
	// TODO Auto-generated destructor stub
	if(fixedContainer)
		delete(fixedContainer);

	if(checkbuttonSign)
		delete(checkbuttonSign);
	if(checkbuttonEncryptFiles)
		delete(checkbuttonEncryptFiles);
	if(checkbuttonProtectSecretKey)
		delete(checkbuttonProtectSecretKey);

	if(entryInputDir)
		delete(entryInputDir);
	if(entryOutPutDir)
		delete(entryOutPutDir);
	if(entrySingP12)
		delete(entrySingP12);
	if(entryProtectionKey)
		delete(entryProtectionKey);

	if(buttonSelectinputDir)
		delete(buttonSelectinputDir);
	if(buttonSelectOutDi)
		delete(buttonSelectOutDi);
	if(buttonSelectCer)
		delete(buttonSelectCer);
	if(buttonRun)
		delete(buttonRun);

	if(textviewLog)
		delete textviewLog;
}
void CFEncryptorController::SetWindow(Gtk::Window* parentWindow)
{
	this->window = parentWindow;
}

void CFEncryptorController::on_encryption_update(CFEncryptor * cfe)
{
	if(cfe != NULL)
	{
		std::list<Glib::ustring> newMsgs;
		cfe->FillWithMessages(newMsgs);

		std::list<Glib::ustring>::iterator it = newMsgs.begin();

		while(it != newMsgs.end())
		{
			RegisterMessage(*it++);
		}
	}
}

void CFEncryptorController::RegisterMessage(Glib::ustring& line)
{
	textviewLog->get_buffer()->insert_at_cursor(line);
	textviewLog->get_buffer()->insert_at_cursor("\n");
}

Gtk::Fixed* CFEncryptorController::GetWidget( Glib::RefPtr<Gtk::Builder> builder)
{
	  builder->get_widget("fixedCFEncryptor",this->fixedContainer);

	 //checks
	builder->get_widget("checkbuttonSign",this->checkbuttonSign);
	builder->get_widget("checkbuttonEncryptFiles",this->checkbuttonEncryptFiles);
	builder->get_widget("checkbuttonProtectSecretKey",this->checkbuttonProtectSecretKey);

	//entries
	builder->get_widget("entryInputDir",this->entryInputDir);
	builder->get_widget("entryOutPutDir",this->entryOutPutDir);
	builder->get_widget("entrySingP12",this->entrySingP12);
	builder->get_widget("entryProtectionKey",this->entryProtectionKey);

	//buttons
	builder->get_widget("buttonSelectinputDir",this->buttonSelectinputDir);
	builder->get_widget("buttonSelectOutDi",this->buttonSelectOutDi);
	builder->get_widget("buttonSelectCer",this->buttonSelectCer);
	builder->get_widget("buttonRun",this->buttonRun);

	//text view
	builder->get_widget("textviewLog",this->textviewLog);

	Gtk::WrapMode wrapMode =Gtk::WRAP_WORD;
	this->textviewLog->set_wrap_mode(wrapMode);

	this->buttonSelectinputDir->signal_clicked().connect( sigc::mem_fun(*this,
	      &CFEncryptorController::on_inputbuton_clicked) );
	this->buttonSelectOutDi->signal_clicked().connect( sigc::mem_fun(*this,
	      &CFEncryptorController::on_outputbutton_clicked) );
	this->buttonSelectCer->signal_clicked().connect( sigc::mem_fun(*this,
	      &CFEncryptorController::on_cert_clicked) );
	this->buttonRun->signal_clicked().connect( sigc::mem_fun(*this,
	      &CFEncryptorController::on_runbutton_clicked) );

	entryInputDir->set_text("");
	entryOutPutDir->set_text("");
	entryProtectionKey->set_text("");
	entrySingP12->set_text("");

	return fixedContainer;
}

void CFEncryptorController::on_inputbuton_clicked()
{
	Gtk::FileChooserDialog dialog("SELECT THE FOLDER TO ENCRYPT",
	        Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	    dialog.set_transient_for(*window);


	    //Add response buttons the the dialog:
	    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	    dialog.add_button("Select", Gtk::RESPONSE_OK);

	    int result = dialog.run();

	    //Handle the response:
	    switch(result)
	    {
	    case(Gtk::RESPONSE_OK):
	                    {

	      Glib::ustring folder = dialog.get_filename();
	      this->entryInputDir->set_text(folder);
	      break;
	                    }
	    case(Gtk::RESPONSE_CANCEL):
	                    {
	      std::cout << "Action Canceled\n" << std::endl;
	      break;
	                    }
	    default:
	      {
	        std::cout << "Unexpected button clicked." << std::endl;
	        break;
	      }
	    }
}

void CFEncryptorController::on_outputbutton_clicked()
{
	Gtk::FileChooserDialog dialog("SELECT THE OUTPUT FOLDER",
	        Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	    dialog.set_transient_for(*window);


	    //Add response buttons the the dialog:
	    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	    dialog.add_button("Select", Gtk::RESPONSE_OK);

	    int result = dialog.run();

	    //Handle the response:
	    switch(result)
	    {
	    case(Gtk::RESPONSE_OK):
	                    {

	      Glib::ustring folder = dialog.get_filename();
	      this->entryOutPutDir->set_text(folder);
	      break;
	                    }
	    case(Gtk::RESPONSE_CANCEL):
	                    {
	      std::cout << "Action Canceled\n" << std::endl;
	      break;
	                    }
	    default:
	      {
	        std::cout << "Unexpected button clicked." << std::endl;
	        break;
	      }
	    }
}

void CFEncryptorController::on_cert_clicked()
{
	Gtk::FileChooserDialog dialog("SELECT THE SIGNING CERTIFICATE",
			Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*window);

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	//Add filters, so that only certain file types can be selected:

	Gtk::FileFilter filter_p12;
	filter_p12.set_name("PKCS#12 files");
	filter_p12.add_mime_type("application/x-pkcs12");
	dialog.add_filter(filter_p12);

	Gtk::FileFilter filter_any;
	filter_any.set_name("Any files");
	filter_any.add_pattern("*");
	dialog.add_filter(filter_any);

	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	switch(result)
	{
	case(Gtk::RESPONSE_OK):
	                    	{
		Glib::ustring filename = dialog.get_filename();
		this->entrySingP12->set_text(filename);
		break;
	                    	}
	case(Gtk::RESPONSE_CANCEL):
	                    	{
		std::cout << "Cancel clicked." << std::endl;
		break;
	                    	}
	default:
	{
		std::cout << "Unexpected button clicked." << std::endl;
		break;
	}
	}
}

void CFEncryptorController::on_encryption_finished()
{
	this->buttonRun->set_sensitive(true);
}

void CFEncryptorController::on_runbutton_clicked()
{


	this->buttonRun->set_sensitive(false);
	encryptorClass.SetEncryptFiles(checkbuttonEncryptFiles->get_active());
	encryptorClass.SetProtectSecretKey(checkbuttonProtectSecretKey->get_active());
	Glib::ustring input = entryInputDir->get_text();
	Glib::ustring output = entryOutPutDir->get_text();

	if(checkbuttonSign->get_active())
	{
		Glib::ustring path = entrySingP12->get_text();
		Glib::ustring pass = entryProtectionKey->get_text();
		encryptorClass.SetSigningCertificate(path,  pass);
	}
	else
	{
		encryptorClass.ExcludeFileSigning();
	}

	//set input dir
	encryptorClass.SetNewInputPath(input);
	//set output dir
	encryptorClass.SetNewOutputPath(output);

	encryptorClass.Run(true);
}
