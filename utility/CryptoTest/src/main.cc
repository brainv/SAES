/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * cryptotest is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * cryptotest is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm.h>
#include <iostream>
#include <glibmm/timeval.h>

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include "CryptoTestForm.h"
#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xsec/utils/XSECPlatformUtils.hpp>
#include <Environment/Configurations/base-language-controller.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <System/Runtime/ProcessMonitor.h>
#include "config.h"

#include <System/IO/Path.h>

#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/safestack.h>

using namespace Smartmatic::Environment;
using namespace Smartmatic::System::Runtime;

XERCES_CPP_NAMESPACE_USE

void UnblockingWait(int ms);
std::string ReadInputStream();
void ListProcess();


int
main (int argc, char *argv[])
{


  if(!Glib::thread_supported()) Glib::thread_init();

  Gtk::Main kit(argc, argv);


  setlocale (LC_ALL, "");

  BaseLanguageController::LocalizeApplication("en", "US");

  Glib::TimeVal time;
  Glib::ustring dateStr = "1970-01-01T00:00:00.00Z";

  time.assign_from_iso8601(dateStr);

  double timeD = time.as_double();

  std::ios_base::sync_with_stdio(true);

  std::cout << "Time string: " << dateStr << std::endl;
  std::cout << "Time as double: " << timeD << std::endl;



  std::string base = "/home/smartmatic/";

  	Glib::Timer stopWatch;

  	std::cout << "Elapsed: " << stopWatch.elapsed() << std::endl;
  	sleep(1);
  	std::cout << "Elapsed: " << stopWatch.elapsed() << std::endl;
  	usleep(500000);
  	std::cout << "Elapsed: " << stopWatch.elapsed() << std::endl;

  time.assign_current_time();
  dateStr =time.as_iso8601();

  CRYPTO_malloc_init();
    ERR_load_crypto_strings();
    OPENSSL_add_all_algorithms_noconf();
    OPENSSL_config(NULL);

  printf("Starting App: %s\n",dateStr.c_str());




  //UnblockingWait(950);
  //UnblockingWait(3550);

  ListProcess();

  try {
        XMLPlatformUtils::Initialize();
        XSECPlatformUtils::Initialise();
    }
    catch (const XMLException &e) {

        std::cout << "Error during initialization of Xerces" << std::endl;
        std::cout << "Error Message = : "
            << e.getMessage() << std::endl;
    }

  CryptoTestForm form;

  Gtk::Main::run(form);
}

void UnblockingWait(int ms)
{
	Glib::Mutex condMutex;
	Glib::Cond condition;
	condMutex.lock();


	Glib::TimeVal wait_period(0,0);

	int secs = ms/1000;
	int usecs = ms%1000;

	wait_period.add_seconds(secs);
	wait_period.add_milliseconds(usecs);




	Glib::TimeVal abs_time;
	Glib::Timer stopWatch;
	stopWatch.stop();
	stopWatch.reset();
	abs_time.assign_current_time();
	abs_time.add(wait_period);
	stopWatch.start();
	condition.timed_wait(condMutex, abs_time);
	//condition.wait(condMutex);
	//usleep(ms*1000);
	stopWatch.stop();
	condMutex.unlock();

	unsigned long elapseduSecs;
	double elapsedSecs = stopWatch.elapsed(elapseduSecs);

	std::cout << "Elapsed Secs: " <<elapsedSecs<< ". Elapsed uSecs: " << elapseduSecs << std::endl;
}


void ListProcess()
{
	/*std::cout << "STDIN Before System: " << std::endl;
	std::cout << ReadInputStream() << std::endl;

	std::string cmd = "ps -A";
	system(cmd.c_str());
	UnblockingWait(1000);

	std::cout << "STDIN After System: " << std::endl;
	std::cout << ReadInputStream() << std::endl;*/

	/*FILE *in;
	  //extern FILE *popen();
	  char buff[512];

	  /// popen creates a pipe so we can read the output
	     of the program we are invoking
	  if (!(in = popen("ps -A", "r"))) {
	    exit(1);
	  }

	  /// read the output of netstat, one line at a time
	  while (fgets(buff, sizeof(buff), in) != NULL ) {
	    printf("Output: %s", buff);
	  }

	  /// close the pipe
	  pclose(in);
*/

	std::cout<< "Process running: " << ProcessMonitor::CountProcessRunning("eclipse") << std::endl;

}

std::string ReadInputStream()
{
	std::string retVal;
	char buffer[33];
	int read = 0;
	do
	{
		read = std::cin.readsome(buffer, 32);
		retVal.append(buffer, read);
	}while(read > 0);
	return retVal;
}
