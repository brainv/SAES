/**
 * @file SafeBuffer.cpp
 * @brief Body class safe buffer
 * @date 11/04/2011
 * @author Freddy Gomez
 */

#include "System/SafeBuffer.h"
#include "System/Encoding/Base64Encoder.h"
#include <string.h>
#include <cstring>

using namespace Smartmatic::System;
using namespace Smartmatic::System::Encoding;

SafeBuffer& SafeBuffer::operator=(const SafeBuffer& dbuf)
{
    if (this != &dbuf )
    {
            this->m_BufferSize = dbuf.m_BufferSize;

            if(this->mp_Buff)
            {
                g_free(mp_Buff);
                mp_Buff = NULL;
            }

            this->mp_Buff = static_cast<unsigned char*> (
                            g_malloc (dbuf.m_BufferSize * sizeof (unsigned char)));

            memcpy (this->mp_Buff, dbuf.mp_Buff, dbuf.m_BufferSize);
    }

    return *this;
}

bool SafeBuffer::operator== ( const SafeBuffer& rhs )
{
	bool validate = false;

	if (this->m_BufferSize == rhs.m_BufferSize)
	{
		validate = memcmp((const char *)this->mp_Buff, (const char *)rhs.mp_Buff, rhs.m_BufferSize) == 0;
	}

	return validate;
}

bool SafeBuffer::operator!= ( const SafeBuffer& rhs )
{
	bool validate = false;

	if (this->m_BufferSize == rhs.m_BufferSize)
	{
		validate = memcmp((const char *)this->mp_Buff, (const char *)rhs.mp_Buff, rhs.m_BufferSize) != 0;
	}

	return validate;
}

SafeBuffer::SafeBuffer()
{
    mp_Buff = NULL;
    m_BufferSize = 0;
}

SafeBuffer::~SafeBuffer()
{
    if (mp_Buff != NULL && m_BufferSize > 0)
    {
        memset (mp_Buff, 0, m_BufferSize);
    }

    if(mp_Buff != NULL && m_BufferSize > 0)
    {
        g_free(mp_Buff);
    }

    mp_Buff = NULL;
}

SafeBuffer::SafeBuffer (std::string & data)
{
    mp_Buff = NULL;
    m_BufferSize = 0;

    if (data.length() > 0)
    {
    	m_BufferSize = data.length();
		mp_Buff = (unsigned char*)g_malloc (m_BufferSize * sizeof (unsigned char));
		memcpy (mp_Buff, data.c_str(), m_BufferSize);
    }
}

SafeBuffer::SafeBuffer (long & data, int resultSize)
{
    mp_Buff = NULL;
    m_BufferSize = 0;

    mp_Buff = (unsigned char*)g_malloc (resultSize);
    memset(mp_Buff, 0, resultSize);

    char * d = (char*)&data;
    int sizeL = sizeof(data) / sizeof(char);

    memcpy(mp_Buff, d, sizeL);
    m_BufferSize = resultSize;
}

SafeBuffer::SafeBuffer (unsigned char* buffer, size_t bufSize, bool copy)
{
  mp_Buff = NULL;
  m_BufferSize = 0;

  if(buffer != NULL && bufSize > 0)
  {
      mp_Buff = (unsigned char*)g_malloc (bufSize * sizeof (unsigned char));
      memcpy (mp_Buff, buffer, bufSize);
  }

  m_BufferSize = bufSize;
}


SafeBuffer::SafeBuffer (const SafeBuffer& other)
{
    mp_Buff = NULL;
    m_BufferSize = 0;

    if ( other.m_BufferSize > 0 && other.mp_Buff != NULL)
    {
        this->m_BufferSize = other.m_BufferSize;
        this->mp_Buff = (unsigned char*)g_malloc (m_BufferSize * sizeof (unsigned char));
        memcpy (this->mp_Buff, other.mp_Buff, m_BufferSize);
    }
}

void SafeBuffer::GetData (unsigned char** destBuf, size_t& destLen) const
{
    if (m_BufferSize > 0)
    {
        *destBuf = static_cast<unsigned char*> (
                        g_malloc (m_BufferSize * sizeof (unsigned char)));

        memcpy (destBuf, mp_Buff, m_BufferSize);
    }

    destLen = m_BufferSize;
}

void SafeBuffer::AddData (const unsigned char* moreData, size_t moreDataSize)
{
  if (moreDataSize > 0 && moreData != NULL)
  {
      unsigned char* tmp = (unsigned char*)g_malloc (moreDataSize +m_BufferSize);

      if(mp_Buff && m_BufferSize > 0)
      {
          memcpy (tmp, mp_Buff, m_BufferSize);
      }

      memcpy (tmp+m_BufferSize, moreData, moreDataSize);

      if(mp_Buff)
      {
        g_free ( mp_Buff);
      }

       mp_Buff = tmp;
       m_BufferSize += moreDataSize;
  }
}

void SafeBuffer::AddData (const SafeBuffer & moreData)
{
    AddData(moreData.GetData(), moreData.GetSize());
}

void SafeBuffer::AddData (const std::string & moreData)
{
    AddData((const unsigned char *)moreData.c_str(), moreData.size());
}

void SafeBuffer::push_back(unsigned char data)
{
	unsigned char* tmp = (unsigned char*)g_realloc (mp_Buff, m_BufferSize + 1);

	if (tmp != NULL)
	{
		mp_Buff = tmp;
		mp_Buff[m_BufferSize] = data;
		m_BufferSize++;
	}
}

std::string SafeBuffer::GetBase64Data () const
{
	return Base64Encoder::ConvertToBase64(*this);
}

void SafeBuffer::Clear ()
{
	if (mp_Buff != NULL)
		memset (mp_Buff, 0, m_BufferSize);

	if(mp_Buff)
		g_free(mp_Buff);

    mp_Buff = NULL;
    m_BufferSize = 0;
}

void SafeBuffer::insertData (unsigned long index, const unsigned char* moreData, size_t moreDataSize)
{
  index = (index > m_BufferSize ? m_BufferSize : index);

  if (moreDataSize > 0 && moreData != NULL && index <= m_BufferSize)
  {
      unsigned char* tmp = (unsigned char*)g_malloc (moreDataSize +m_BufferSize);

      if(mp_Buff && m_BufferSize > 0)
      {
          memcpy (tmp, mp_Buff, index);
      }

      memcpy (tmp+index, moreData, moreDataSize);

      if(mp_Buff && m_BufferSize > 0)
      {
          memcpy (tmp+index+moreDataSize, mp_Buff+index, m_BufferSize - index);
      }

      if(mp_Buff)
      {
        g_free ( mp_Buff);
      }

       mp_Buff = tmp;
       m_BufferSize += moreDataSize;
  }
}

void SafeBuffer::insertData (unsigned long index, const SafeBuffer & moreData)
{
	insertData(index, moreData.GetData(), moreData.GetSize());
}

void SafeBuffer::insertData (unsigned long index, const std::string & moreData)
{
	insertData(index, (const unsigned char*)moreData.c_str(), moreData.size());
}

bool SafeBuffer::findData (unsigned long index, const unsigned char* moreData, size_t moreDataSize, unsigned long & postResult)
{
	bool find = false;
	postResult = 0;

	if (mp_Buff && m_BufferSize > 0 && moreData && moreDataSize > 0 && index < m_BufferSize )
	{
		do
		{
			unsigned char * pch = (unsigned char*) memchr (mp_Buff + index + postResult, moreData[0], m_BufferSize - index - postResult);

			if (pch && postResult < m_BufferSize)
			{
				postResult = pch - mp_Buff;

				if ( memcmp ( pch, moreData, moreDataSize ) == 0)
				{
					find = true;
					break;
				}
				else
				{
					postResult++;
				}
			}
			else
			{
				postResult = 0;
				break;
			}

		}while(!find);
	}

	return find;
}

bool SafeBuffer::findData (unsigned long index, const SafeBuffer & moreData, unsigned long & postResult)
{
	return findData(index, moreData.GetData(), moreData.GetSize(), postResult);
}

bool SafeBuffer::findData (unsigned long index, const std::string & moreData, unsigned long & postResult)
{
	return findData(index, (const unsigned char*)moreData.c_str(), moreData.size(), postResult);
}

void SafeBuffer::removeData (unsigned long index, size_t size)
{
  if (size > 0)
  {
	  index = (index > m_BufferSize ? m_BufferSize : index);
	  size = ((index + size) > m_BufferSize ? m_BufferSize - index: size);

	  if (mp_Buff && m_BufferSize > 0 && index < m_BufferSize)
	  {
		  unsigned char* tmp = (unsigned char*)g_malloc (m_BufferSize - size);

		  memcpy (tmp, mp_Buff, index);
		  memcpy (tmp+index, mp_Buff + index + size, m_BufferSize - index - size);

		  g_free (mp_Buff);

		  mp_Buff = tmp;
		  m_BufferSize -= size;
	  }
  }
}
