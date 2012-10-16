/*
 * PrintVote.hxx
 *
 *  Created on: 23/09/2011
 *      Author: soto
 */

#ifndef PRINTVOTE_HXX_
#define PRINTVOTE_HXX_

#include <Voting/Vote/vote-schema.hxx>
#include <System/SafeBuffer.h>
#include <Printing/BasePrintDocument.h>
#include <Log/ISMTTLog.h>

class PrintVote : public Smartmatic::SAES::Printing::BasePrintDocument
{
public:
	PrintVote(Smartmatic::System::SafeBuffer & bufferIn);
	virtual ~PrintVote();
	void PrintDoc();
	void BeginPrint();
	void EndPrint();

private:
	Smartmatic::System::SafeBuffer & buffer;
	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
};

#endif /* PRINTVOTE_HXX_ */
