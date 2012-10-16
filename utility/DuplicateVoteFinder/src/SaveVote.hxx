/*
 * SaveVote.hxx
 *
 *  Created on: 23/09/2011
 *      Author: soto
 */

#ifndef SAVEVOTE_HXX_
#define SAVEVOTE_HXX_

#include <System/SafeBuffer.h>

class SaveVote
{
private:
	SaveVote();
public:
	virtual ~SaveVote();

	static bool open(std::string & file, Smartmatic::System::SafeBuffer & bufferOut);
	static bool save(std::string & file, Smartmatic::System::SafeBuffer & bufferIn);
};

#endif /* SAVEVOTE_HXX_ */
