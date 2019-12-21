#ifndef RINGBUFFER_HEADER_INCLUDED
#define RINGBUFFER_HEADER_INCLUDED

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define RETTYPE uint8_t
#define RB_CREATE_FAILURE (~((RETTYPE)0x0))
#define RB_CREATE_SUCCESS ((RETTYPE)0x0)
#define RB_FULL (~((RETTYPE)0x0)-(RETTYPE)1)
#define RB_ACCEPTABLE ((RETTYPE)0x1)
#define RB_EMPTY (~((RETTYPE)0x0)-(RETTYPE)2)

typedef uint8_t RB_TYPE;

class ringBuf
{
	private:
		uint32_t tIndex;
		uint32_t bIndex;
		uint32_t wmem;
		uint32_t bufLength;
		RB_TYPE* bufDest;

	public:
		ringBuf()
		{
			tIndex = 0;
			bIndex = 0;
			wmem = 0;
			bufLength = 0;
			bufDest = nullptr;
		}

		void incTop()
		{
			tIndex++;
			tIndex %= bufLength;
		}
		void incTop(uint32_t incval)
		{
			tIndex += incval;
			tIndex %= bufLength;
		}

		void incBottom()
		{
			bIndex++;
			bIndex %= bufLength;
		}
		void incBottom(uint32_t incval)
		{
			bIndex += incval;
			bIndex %= bufLength;
		}
	   
		RETTYPE create(uint32_t length)
		{
			bufLength = length;
			bufDest = (RB_TYPE*)calloc(length, sizeof(RB_TYPE));
			if(bufDest == nullptr)
			{
				return RB_CREATE_FAILURE;
			}
			return RB_CREATE_SUCCESS;
		}
		
		RETTYPE write(RB_TYPE data)
		{
			if(wmem >= bufLength)
			{
				return RB_FULL;
			}
			else
			{
				bufDest[tIndex] = data;
				wmem++;
				incTop();
				return RB_ACCEPTABLE;
			}
		}
		
		RETTYPE read(RB_TYPE* wdest)
		{
			if(wmem == 0)
			{
				return RB_EMPTY;
			}
			else
			{
				*wdest = bufDest[bIndex];
				wmem--;
				incBottom();
				return RB_ACCEPTABLE;
			}
		}
		
		//Fix needed 
		RETTYPE read(RB_TYPE** rbdest, uint32_t readsize = 0, bool manipulateIndex = false)
		{
			if(wmem == 0)
			{   
				return RB_EMPTY;
			}
			if(wmem >= readsize)
			{
				memcpy(*rbdest, bufDest, (sizeof(RB_TYPE) * readsize));
				if(manipulateIndex)
				{
					bIndex += readsize;
					bIndex %= bufLength;
					wmem -= readsize;
				}
				return RB_ACCEPTABLE;
			}
			else
			{
				memcpy(*rbdest, bufDest, (sizeof(RB_TYPE) * wmem));
				if(manipulateIndex)
				{
					bIndex += wmem;
					bIndex %= bufLength;
					wmem = 0;
				}
				return RB_ACCEPTABLE;
			}
		}
};

#endif