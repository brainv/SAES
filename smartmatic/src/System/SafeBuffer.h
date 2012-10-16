/**
 * @file	SafeBuffer.h
 *
 * @brief	Header file to the safe buffer class.
 */

#ifndef SAFEBUFFER_H_
#define SAFEBUFFER_H_


#include <string.h>
#include <iostream>

namespace Smartmatic{

  namespace System {

    /**
     * @class SafeBuffer
     * @brief	Buffer for safe class. 
     *
     * @author	freddyg
     * @date	28/04/2011
     */

    class SafeBuffer
    {

    public:

      /**
       * @brief	Default constructor.
       *
       * @author	freddyg
       * @date	28/04/2011
       */

      SafeBuffer();

      /**
       * @brief Constructor.
       *
       * @author Yadickson Soto yadickson.soto@smartmatic.com
       * @date  02/06/2011
       *
       * @param data string to convert
       */

      SafeBuffer (std::string & data);

      /**
       * @brief Constructor.
       *
       * @author Yadickson Soto yadickson.soto@smartmatic.com
       * @date  02/06/2011
       *
       * @param data long data to convert
       * @param resultSize result size to buffer
       */

      SafeBuffer (long & data, int resultSize);

      /**
       * @brief	Constructor.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @param [in,out]	digestBuffer	If non-null, buffer for digest data.
       * @param	bufSize						Size of the buffer.
       * @param	copy						true to copy.
       */

      SafeBuffer (unsigned char* digestBuffer, size_t bufSize, bool copy = true);

      /**
       * @brief	Copy constructor.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @param	buff	The buffer.
       */

      SafeBuffer (const SafeBuffer& buff);

      /**
       * @brief	Finaliser.
       *
       * @author	freddyg
       * @date	28/04/2011
       */

      virtual ~SafeBuffer();

      /**
       * @brief	Assignment operator.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @param	sk	The sk.
       *
       * @return	A shallow copy of this object.
       */

      SafeBuffer& operator=(const SafeBuffer& sk);

      /**
       * @brief	Method compare buffer
       * @param rhs buffer
       * @return true is equals
       * @author	Yadickson Soto
       * @date	24/02/2012
       */
      bool operator== ( const SafeBuffer& rhs );

      /**
       * @brief	Method compare buffer
       * @param rhs buffer
       * @return false is equals
       * @author	Yadickson Soto
       * @date	24/02/2012
       */
      bool operator!= ( const SafeBuffer& rhs );

      /**
       * @brief	Gets a data.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @param [in,out]	destBuf	If non-null, buffer for destination data.
       * @param [in,out]	destLen	Length of the destination.
       */

      void GetData (unsigned char** destBuf, size_t& destLen) const;

      /**
       * @brief	Adds a data to 'moreDataSize'.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @param	moreData		Data to add.
       * @param	moreDataSize	Size of the data to add.
       */

      void AddData (const unsigned char* moreData, size_t moreDataSize);

      /**
       * @brief Adds a buffer data.
       *
       * @author    Yadickson Soto yadickson.soto@smartmatic.com
       * @date  02/06/2011
       *
       * @param moreData        Data to add.
       */

      void AddData (const SafeBuffer & moreData);

      /**
       * @brief Adds a buffer data.
       *
       * @author    Yadickson Soto yadickson.soto@smartmatic.com
       * @date  24/02/2012
       *
       * @param moreData        Data to add.
       */

      void AddData (const std::string & moreData);

      /**
       * @brief	Method insert back data in buffer
       * @param data new data
       * @author	Yadickson Soto
       * @date	24/02/2012
       */
      void push_back(unsigned char data);

      /**
       * @brief	Gets the data.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @return	null if it fails, else the data.
       */

      const unsigned char* GetData () const { 
		  return mp_Buff; }

      /**
       * @brief	Gets the size.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @return	The size of the Buffer.
       */

      size_t GetSize () const { return m_BufferSize; }

      /**
       * @brief	Gets the base 64 data.
       *
       * @author	freddyg
       * @date	28/04/2011
       *
       * @return	The date in format Base 64.
       */
      std::string GetBase64Data () const;

      /**
       * @brief	Method clear buffer
       *
       * @author	Yadickson Soto
       * @date	28/04/2011
       */
      void Clear ();

      /**
       * @brief	Method insert data in buffer
       * @param index	index to insert data
       * @param	moreData		Data to insert.
       * @param	moreDataSize	Size of the data to insert.
       * @author	Yadickson Soto
       * @date	24/02/2012
       */
      void insertData (unsigned long index, const unsigned char* moreData, size_t moreDataSize);

      /**
       * @brief	Method insert data in buffer
       * @param index	index to insert data
       * @param	moreData		Data to insert.
       * @author	Yadickson Soto
       * @date	24/02/2012
       */
      void insertData (unsigned long index, const SafeBuffer & moreData);

      /**
       * @brief	Method insert data in buffer
       * @param index	index to insert data
       * @param	moreData		Data to insert.
       * @author	Yadickson Soto
       * @date	24/02/2012
       */
      void insertData (unsigned long index, const std::string & moreData);

      /**
       * @brief	Method find data in buffer
       * @param index	index to begin find data
       * @param	moreData		Data to find.
       * @param	moreDataSize	Size data to find.
       * @param postResult 		Post found moreData
       * @return true is found
       * @author	Yadickson Soto
       * @date	25/02/2012
       */
      bool findData (unsigned long index, const unsigned char* moreData, size_t moreDataSize, unsigned long & postResult);

      /**
       * @brief	Method find data in buffer
       * @param index	index to begin find data
       * @param	moreData		Data to find.
       * @param postResult 		Post found moreData
       * @return true is found
       * @author	Yadickson Soto
       * @date	25/02/2012
       */
      bool findData (unsigned long index, const SafeBuffer & moreData, unsigned long & postResult);

      /**
       * @brief	Method find data in buffer
       * @param index	index to begin find data
       * @param	moreData		Data to find.
       * @param postResult 		Post found moreData
       * @return true is found
       * @author	Yadickson Soto
       * @date	25/02/2012
       */
      bool findData (unsigned long index, const std::string & moreData, unsigned long & postResult);

      /**
       * @brief	Method remove data in buffer
       * @param index	index to begin find data
       * @param	size size remove
       * @author	Yadickson Soto
       * @date	25/02/2012
       */
      void removeData (unsigned long index, size_t size);

    protected:


    private:
      
     
      unsigned char* mp_Buff;  ///< The buffer

     
      size_t m_BufferSize;  ///< Size of the buffer
    };
  }
}
#endif /* SAFEBUFFER_H_ */
