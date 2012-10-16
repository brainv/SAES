/**
 * @file DomWriter.cpp
 * @brief Body class DomWriter
 * @date 02/03/2011
 * @author freddyg
 */

#include "DomWriter.h"

#include <xercesc/util/XMLUniDefs.hpp> //characters definitions
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <cstring> // std::memcpy


XERCES_CPP_NAMESPACE_USE

namespace Smartmatic {

namespace System {

namespace XML {

namespace Serialization
{

OutStreamFormatTarget::OutStreamFormatTarget (std::ostream& os)
: XMLFormatTarget(), n_ (0), os_ (os)
{
}


void
OutStreamFormatTarget::writeChars (const XMLByte* const buf,
		const XMLSize_t size,
		XERCES_CPP_NAMESPACE::XMLFormatter* const format)
{
	// Ignore the write request if there was a stream failure and the
	// stream is not using exceptions.
	//
	if (os_.fail ())
		return;

	// Flush the buffer if the block is too large or if we don't have
	// any space left.
	//
	if ((size >= buf_size_ / 8 || n_ + size > buf_size_) && n_ != 0)
	{
		os_.write (buf_, static_cast<std::streamsize> (n_));
		n_ = 0;

		if (os_.fail ())
			return;
	}

	if (size < buf_size_ / 8)
	{
		std::memcpy (buf_ + n_, reinterpret_cast<const char*> (buf), size);
		n_ += size;
	}
	else
		os_.write (reinterpret_cast<const char*> (buf),
				static_cast<std::streamsize> (size));
}


void
OutStreamFormatTarget::flush ()
{
	// Ignore the flush request if there was a stream failure
	// and the stream is not using exceptions.
	//
	if (!os_.fail ())
	{
		if (n_ != 0)
		{
			os_.write (buf_, static_cast<std::streamsize> (n_));
			n_ = 0;

			if (os_.fail ())
				return;
		}

		os_.flush ();
	}
}





DomWriter::DomWriter(std::ostream& os)
{
	// TODO Auto-generated constructor stub
	target = new OutStreamFormatTarget(os);
}

DomWriter::~DomWriter()
{
	// TODO Auto-generated destructor stub
	if(target)
		delete(target);
}

void DomWriter::Write(XERCES_CPP_NAMESPACE::DOMDocument* doc)
{
	// get a serializer, an instance of DOMLSSerializer
	XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
	DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
	DOMLSSerializer   *theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
	DOMLSOutput       *theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput();

	XMLCh* encoding = XMLString::transcode( "UTF-8");
	theOutputDesc->setEncoding(encoding);
	XMLString::release(&encoding);

	//Serializer configurations. To be adjusted later. Now using default values

	DOMConfiguration* serializerConfig=theSerializer->getDomConfig();

	//TODO: set an error handler to report failures
	//serializerConfig->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

	// set feature if the serializer supports the feature/mode
	if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTSplitCdataSections, true))
		serializerConfig->setParameter(XMLUni::fgDOMWRTSplitCdataSections, true);

	if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true))
		serializerConfig->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);

	if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, false))
		serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, false);

	if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTBOM, false))
		serializerConfig->setParameter(XMLUni::fgDOMWRTBOM, false);


    theOutputDesc->setByteStream(target);

    theSerializer->write(doc, theOutputDesc);

    theOutputDesc->release();
    theSerializer->release();

}

}
}
}
}
