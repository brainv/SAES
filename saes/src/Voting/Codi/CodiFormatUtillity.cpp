/*
 * CodiFormatUtillity.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: Marcel Cordoví
 */

#include "CodiFormatUtillity.h"
#include <iostream>

using namespace Smartmatic::SAES::Voting::Codi;



/******************************************************************************/
/******************************* Life cycle ***********************************/
/******************************************************************************/


CodiFormatUtility::CodiFormatUtility()
{
	// TODO Auto-generated constructor stub
}

CodiFormatUtility::~CodiFormatUtility()
{
	// TODO Auto-generated destructor stub
}


/******************************************************************************/
/**************************** public interface ********************************/
/******************************************************************************/

long CodiFormatUtility::CodiCheckSum (std::vector<unsigned long> countArray)
{
	long lni = 0;

	while (lni < (int) countArray.size () )
	{
		if (lni == 0)
		{
			// leave first value unmodified
			// countArray[lni] = countArray[lni];
		}
		else if (countArray[lni] == 0L)
		{
			countArray[lni] = (countArray[(lni - 1)] + 9L);
		}
		else
		{
			countArray[lni] = ((countArray[(lni - 1)] * countArray[lni] + 1L) % 99991L);
		}

		lni++;
	}

	return countArray[(lni - 1)];
}



///////////////////////////////////////////////////////////////////////////////
// Checksum algorithm Java implementation provided as reference
///////////////////////////////////////////////////////////////////////////////

/*
public  String calculateChecksum(String[] csarray)
    {
        long[] ci = new long[csarray.length];
        for (int i = 0; i < csarray.length; ++i) {
            try {
                ci[i] = Long.parseLong(csarray[i]);
            } catch (NumberFormatException e) {
                ci[i] = 0L;
            }

        }

        int lni = 0;
        while (lni < csarray.length)
        {
            if (lni == 0) {
                ci[lni] = ci[lni];
            }
            else if (ci[lni] == 0L)
            {
                ci[lni] = (ci[(lni - 1)] + 9L);
            }
            else
            {
                ci[lni] = ((ci[(lni - 1)] * ci[lni] + 1L) % 99991L);
            }

            ++lni;
        }

        return Long.toString(ci[(lni - 1)]);
    }
*/

