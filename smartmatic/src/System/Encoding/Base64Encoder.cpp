/*
 * Base64Encoder.cpp
 *
 *  Created on: May 5, 2011
 *      Author: fgomez
 */

#include "System/Encoding/Base64Encoder.h"

using namespace Smartmatic::System::Encoding;

Base64Encoder::Base64Encoder() {
	// TODO Auto-generated constructor stub

}

Base64Encoder::~Base64Encoder() {
	// TODO Auto-generated destructor stub
}



Glib::ustring Base64Encoder::ConvertToBase64(const unsigned char * data, int dataLen)
{
    Glib::ustring base64_string;

    if (data != NULL && dataLen > 0)
    {
        gchar* base64_buff = g_base64_encode ((guchar*) data, (gsize)dataLen);
        base64_string.assign(base64_buff);
        g_free(base64_buff);
    }

    return base64_string;
}

Glib::ustring Base64Encoder::ConvertToBase64(const Smartmatic::System::SafeBuffer & buffer)
{
	return ConvertToBase64(buffer.GetData(), buffer.GetSize());
}


Glib::ustring Base64Encoder::ConvertToBase64(Glib::ustring data)
{
	const unsigned char * d = (const unsigned char *)data.c_str();
	int dLen = data.length();
	return ConvertToBase64(d, dLen);
}

void Base64Encoder::ConvertFromBase64(Glib::ustring base64String, Smartmatic::System::SafeBuffer & buffer)
{
	if (TestBase64String(base64String))
	{
	    gsize sizeData = 0;
	    unsigned char * data = (unsigned char *) g_base64_decode ( base64String.c_str(), &sizeData);
	    buffer.AddData(data, sizeData);
	    g_free(data);
	}
}

bool Base64Encoder::TestBase64String(Glib::ustring testString)
{
	guint bufferResultsize = testString.size();
	if(bufferResultsize > 0 && bufferResultsize%4==0)
	{
		gsize sizeData = 0;
		unsigned char * data = (unsigned char *) g_base64_decode ( testString.c_str(), &sizeData);

		if (data !=NULL)
		{
			g_free(data);
		}

		if(sizeData > 0)
		{
			return true;
		}
	}

	return false;
}
