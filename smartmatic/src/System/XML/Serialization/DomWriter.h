/**
 * @file DomWriter.h
 * @brief Header class DomWriter
 * @date 02/03/2011
 * @author freddyg
 */

#ifndef DOMWRITER_H_
#define DOMWRITER_H_

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/framework/XMLFormatter.hpp> // XMLFormatTarget, XMLFormatter

#include <ostream>

namespace Smartmatic {

namespace System {

namespace XML {

namespace Serialization
{
/**
 * @class OutStreamFormatTarget
 * @brief	Out stream format target class. 
 *
 * @author	freddyg
 * @date	28/04/2011
 */

class OutStreamFormatTarget : public XERCES_CPP_NAMESPACE::XMLFormatTarget
{
public:

	/**
	 * @brief	Constructor.
	 *
	 * @author	freddyg
	 * @date	28/04/2011
	 *
	 * @param [in,out]	os	The ostream.
	 */

	OutStreamFormatTarget (std::ostream& os);

public:
	virtual void

	/**
	 * @brief	Constructor.
	 *
	 * @author	freddyg
	 * @date	28/04/2011
	 *
	 * @param	buf			 	The buffer.
	 * @param	size		 	The size.
	 * @param 	format	format
	 */

	writeChars (const XMLByte* const buf,
			const XMLSize_t size,
			XERCES_CPP_NAMESPACE::XMLFormatter* const format);

	/**
	 * @brief	Flushs this object.
	 *
	 * @author	freddyg
	 * @date	28/04/2011
	 */

	virtual void  flush ();

private:

	
	static const std::size_t buf_size_ = 1024; ///< Size of the buffer

	
	char buf_[buf_size_]; ///< The buffer

	
	std::size_t n_; ///< The 

	
	std::ostream& os_; ///< The operating system
};

/**
  * @brief	Dom writer. 
 *
 * @author	freddyg
 * @date	28/04/2011
 */

class DomWriter {
public:

	/**
	 * @brief	Constructor.
	 *
	 * @author	freddyg
	 * @date	28/04/2011
	 *
	 * @param [in,out]	os	The ostream.
	 */

	DomWriter(std::ostream& os);

	/**
	 * @brief	Finaliser.
	 *
	 * @author	freddyg
	 * @date	28/04/2011
	 */

	virtual ~DomWriter();

	/**
	 * @brief	Writes.
	 *
	 * @author	Rafael.gasperi
	 * @date	28/04/2011
	 *
	 * @param [in,out]	doc	If non-null, the XERCES_CPP_NAMESPACE::DOMDocument* to write.
	 */

	void Write(XERCES_CPP_NAMESPACE::DOMDocument* doc);

private:

	
	OutStreamFormatTarget* target; ///< Target 

};

}
}

}

}

#endif /* DOMWRITER_H_ */
