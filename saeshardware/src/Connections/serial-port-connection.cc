/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * commandstructure
 * Copyright (C)  2010 <>
 * 
 * commandstructure is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * commandstructure is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "serial-port-connection.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/File.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::HW::Connections;
using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;

ISMTTLog* SerialPortConnection::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.HW.Connections.SerialPortConnection",GETTEXT_PACKAGE);

SerialPortConnection::SerialPortConnection(bool connectSignal)
{
	fd=0;
	baud = 9600;
	parity = Parity::PARITY_8N1;
	dataBits = 8;
	dev = "/dev/ttyS0";
	keepPeeking = false;
	this->connectSignal = connectSignal;
};

SerialPortConnection::~SerialPortConnection()
{

}

SerialPortConnection::SerialPortConnection(int baudI,Parity::ParityEnum parityI,int dataBitsI,string devI,bool enableCTS, bool connectSignal)
{
	fd=0;
	baud = baudI;
	parity = parityI;
	dataBits = dataBitsI;
	dev = devI;
	enableCTSRTS = enableCTS;
	keepPeeking = false;
	this->connectSignal = connectSignal;
};

void SerialPortConnection::FlushReadBuffer()
{
	readBuffer.clear();
}

void SerialPortConnection::peekEvent(std::vector<unsigned char> & data)
{
	//readBuffer.clear(); //Clear after read
	readBuffer.insert(readBuffer.end(),data.begin(),data.end());

}
	
int SerialPortConnection::Send(std::vector<unsigned char> data) 
{
	Glib::Mutex::Lock lock(mutexFileDescriptor);

	int len = data.size();

	if(fd != -1)
	{
		int n = write(fd, &data[0], len);
		if (n < 0) 
		{
			logger->Debug("ERROR - Serial port connection, write failed");
			return 0;
		}
		return 1;
	}

	logger->Debug("ERROR - Serial port connection, port not open");
	return 0;
}
	
bool SerialPortConnection::Initialize()
{
	if(fd > 0) {
		struct termios options;
		// Get the current options for the port...
		tcgetattr(fd, &options);

		// Enable the receiver and set local mode...
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		//set the port to manage data as raw input
        options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
        options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
       
		// Turn off hardware flow control
		options.c_cflag &= ~CRTSCTS;

		// Set the baud rates...
		switch (baud) {
			case 4800:
				cfsetispeed(&options, B4800);
				cfsetospeed(&options, B4800);
				break;
			case 9600:	
				cfsetispeed(&options, B9600); 
				cfsetospeed(&options, B9600); 		
				break;
			case 38400:	
				cfsetispeed(&options, B38400); 
				cfsetospeed(&options, B38400); 				
				break;
			case 57600:	
				cfsetispeed(&options, B57600); 
				cfsetospeed(&options, B57600); 				
				break;
			case 115200:	
				cfsetispeed(&options, B115200); 
				cfsetospeed(&options, B115200); 				
				break;
			default:	
				cfsetispeed(&options, B9600); 
				cfsetospeed(&options, B9600); 				
				break;
		}

		// Set options for proper port settings 
		//	ie. 8 Data bits, No parity, 1 stop bit
		options.c_cflag |= (CLOCAL | CREAD);
	
		switch (parity) {
			case Parity::PARITY_7E1:
				// Parity, odd, 1 stop bit (7E1)
				options.c_cflag |= PARENB;
				options.c_cflag &= ~PARODD;
				options.c_cflag &= ~CSTOPB;
				break;
			case Parity::PARITY_8N1:
				// No parity, 1 stop bit (8N1)
				options.c_cflag |= CS8;
				break;
			default:
				// No parity, 1 stop bit (8N1)
				options.c_cflag |= CS8;
				break;
		}			

		// Set number of data bits.  Default is 8.
		switch (dataBits) {
			case 7:		
				options.c_cflag |= CS7; 
				break;
			case 8:		
				options.c_cflag |= CS8; 
				break;
			default:	
				options.c_cflag |= CS8; 
				break;
		}
		//FLOW CONTROL!!!!!!!!!!!!!!!
		if(enableCTSRTS)
		{
			options.c_cflag |= CRTSCTS;
		}
		//**************************		
		tcsetattr(fd, TCSANOW, &options); //MAKE CHANGES NOW		
		return true;
	}

	logger->Debug("ERROR - Serial port connection, port not open");
	return false;
}

bool SerialPortConnection::presentDevice()
{
	return File::canOpenFile(dev);
}

bool SerialPortConnection::Open()
{
	mutexFileDescriptor.lock();

	if(fd<=0 && presentDevice())
	{
		std::stringstream ss;
		ss << "Fase # 1 : Open serial port - Internal signal " << (connectSignal ? "connect" : "disconnect");
		logger->Debug(ss.str());

		char *devChar = (char*)dev.c_str();

		fd = open(devChar, O_RDWR | O_NOCTTY | O_NDELAY);		

		if (fd > 0)
		{
			fcntl(fd, F_SETFL, FNDELAY);
			Initialize();
			usleep(200000);
			tcflush(fd, TCIOFLUSH); /* flush the buffer */
			mutexFileDescriptor.unlock();
			StartPeeking ();

			if (connectSignal)
			{
				connPeek.disconnect();
				connPeek = signal_detected.connect(sigc::mem_fun(*this, &SerialPortConnection::peekEvent));
			}

			return true;
		}
	}

	mutexFileDescriptor.unlock();
	return false;
}

int SerialPortConnection::StartPeeking()
{
	if (!keepPeeking)
	{
		Glib::Mutex::Lock lock(mutexNewThread);

		if(!Glib::thread_supported()) Glib::thread_init();
		keepPeeking = true;
		Glib::Thread::create(sigc::mem_fun(*this, &SerialPortConnection::waitForInput), false);
	}

    return 0;
}

void SerialPortConnection::waitForInput()
{
	Glib::Mutex::Lock lock(mutexNewThread);

	logger->Debug("Start SerialPortConnection wait for input");

    int    maxfd;     /* maximum file desciptor used */    	
    maxfd = fd+1;  /* maximum bit entry (fd) to test */  

	FD_ZERO(&readfs);
	std::vector<unsigned char> commandAnswer;
	unsigned char sResult[5000];
	
	struct timeval timeout;
	timeout.tv_sec  = 1;
    timeout.tv_usec = 0;

	/* block until input becomes available */
	while(keepPeeking)
	{
		{
			Glib::Mutex::Lock lock(mutexFileDescriptor);
			FD_SET(fd, &readfs);  /* set testing for source 1 */
		}
		usleep(300000);

	    int n = select(maxfd, &readfs, NULL, NULL, &timeout);
	    commandAnswer.clear();

		if (n != 0 && FD_ISSET(fd,&readfs))
		{
			int nBytesRead;

			do
			{
				usleep(250000);

				{
					Glib::Mutex::Lock lock(mutexFileDescriptor);

					if(fd>0)
					{
						nBytesRead = read(fd, sResult, 5000);

						if (nBytesRead > 0)
						{
							commandAnswer.assign (sResult,sResult + nBytesRead);
						}
					}
					else
					{
						nBytesRead = 0;
					}
				}
			}
			while(nBytesRead > 0);

			if(commandAnswer.size() > 0)
			{
			    signal_detected.emit(commandAnswer);
			}
			else
			{
				break;
			}
		}
	}

	logger->Debug("End SerialPortConnection wait for input");
}  
	
void SerialPortConnection::Dispose()
{
}
	
std::vector<unsigned char> SerialPortConnection::Read()
{		
	//unsigned char sResult[5000];
	std::vector<unsigned char> buffer;
	buffer.clear();
	if(fd != -1)
	{
		buffer.assign(readBuffer.begin(),readBuffer.end());
		readBuffer.clear();
	}
	else
	{
		logger->Debug("ERROR - Serial port connection, read port");
	}

	return buffer;
}
	
int SerialPortConnection::Close()
{
	keepPeeking = false;

	Glib::Mutex::Lock lock(mutexFileDescriptor);

	FlushReadBuffer();

	if(fd>0)
	{
		logger->Debug("Fase # 1 : Close serial port");
		connPeek.disconnect();
		close(fd);
		FD_CLR(fd,&readfs);
		FD_ZERO(&readfs);
		fd = 0;
		return 1;
	}

	return 0;
}






