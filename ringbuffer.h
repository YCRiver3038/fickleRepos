#ifndef RINGBUFFER_HEADER_INCLUDED
#define RINGBUFFER_HEADER_INCLUDED

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

typedef uint8_t RB_TYPE;
typedef uint8_t RET_TYPE;
typedef uint16_t INDEX_TYPE;

#define RB_CREATE_FAILURE (~((RET_TYPE)0x0))
#define RB_CREATE_SUCCESS ((RET_TYPE)0x0)
#define RB_FULL (~((RET_TYPE)0x0)-(RET_TYPE)1)
#define RB_ACCEPTABLE ((RET_TYPE)0x1)
#define RB_EMPTY (~((RET_TYPE)0x0)-(RET_TYPE)2)

class ringBuf
{
	private:
		INDEX_TYPE tIndex;
		INDEX_TYPE bIndex;
		INDEX_TYPE wmem;
		INDEX_TYPE bufLength;
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
		void incTop(INDEX_TYPE incval)
		{
			tIndex += incval;
			tIndex %= bufLength;
		}

		void incBottom()
		{
			bIndex++;
			bIndex %= bufLength;
		}
		void incBottom(INDEX_TYPE incval)
		{
			bIndex += incval;
			bIndex %= bufLength;
		}
	   
		RET_TYPE create(INDEX_TYPE length)
		{
			bufLength = length;
			bufDest = (RB_TYPE*)calloc(length, sizeof(RB_TYPE));
			if(bufDest == nullptr)
			{
				return RB_CREATE_FAILURE;
			}
			return RB_CREATE_SUCCESS;
		}
		
		RET_TYPE write(RB_TYPE data)
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
		
		RET_TYPE read(RB_TYPE* wdest)
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
		
		RET_TYPE read(RB_TYPE** rbdest, INDEX_TYPE* topDest, INDEX_TYPE* bottomDest)
		{
			if(wmem == 0)
			{   
				return RB_EMPTY;
			}
			*rbdest = bufDest;
			*topDest = tIndex;
			*bottomDest = bIndex;
			return RB_ACCEPTABLE;
		}
};

#endif