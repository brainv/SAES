/**
 * @file	IPrintingBackend.h
 *
 * @brief	Declares the IPrintingBackend interface.
 */

#ifndef IPRINTINGBACKEND_H_
#define IPRINTINGBACKEND_H_

#include "Printing/DocumentOptions.h"


namespace Smartmatic
{

namespace SAES
{

namespace Printing
{
/**
 * @class	IPrintingBackend
 *
 * @brief	Printing backend. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class IPrintingBackend
{
public:

	/**
	 * @fn	IPrintingBackend::IPrintingBackend();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	IPrintingBackend();

	/**
	 * @fn	virtual IPrintingBackend::~IPrintingBackend();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~IPrintingBackend();

	/**
	 * @fn	virtual void IPrintingBackend::Init() = 0;
	 *
	 * @brief	Initialises this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void Init() = 0;

	/**
	 * @fn	virtual void IPrintingBackend::End() = 0;
	 *
	 * @brief	Ends this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void End() = 0;
	//TODO: Add parameters to the methods
	//void Indent(gint levelsToIndent =1);
	//void UnIndent(gint levelsToUnIndent =1);
	//void Rotate();

	/**
	 * @fn	virtual void IPrintingBackend::DrawString(std::list<Glib::ustring>& textContent,
	 * 		std::list<DocumentTextOptions>& textContentOptionList) = 0;
	 *
	 * @brief	Draw string.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	textContent			 	The text content.
	 * @param [in,out]	textContentOptionList	List of text content options.
	 */

	virtual void DrawString(std::list<Glib::ustring>& textContent,std::list<DocumentTextOptions>& textContentOptionList) = 0;

	/**
	 * @fn	virtual void IPrintingBackend::DrawImage(Glib::RefPtr<Gdk::Pixbuf> image) = 0;
	 *
	 * @brief	Draw image.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	image	The image.
	 */

	virtual void DrawImage(Glib::RefPtr<Gdk::Pixbuf> image) = 0;

};

}

}

}

#endif /* IPRINTINGBACKEND_H_ */
