#ifndef FIRCOEFS_HEADER_INCLUDED
#define FIRCOEFS_HEADER_INCLUDED

#include "math.h"
#include "stdlib.h"
#include "stdint.h"

#define PI_USING 3.14159265358979323846
#define SHIFT_OFFSET 1e-16
#define FIR_CREATE_ERR ((uint32_t)(~0x0))
#define FIR_CREATE_SUCCESS ((uint32_t)0)

/*
     
    //矩形窓
    fir_Window = 1.0;
    
    //Vorbis窓
    fir_Window = sin( (PI_USING / 2.0) * sin(PI_USING*windowIndex) * sin(PI_USING*windowIndex) );
    
    //sin窓
    fir_Window = sin(PI * windowIndex);
    
    //Hanning窓
    fir_Window = 0.5 - (0.5 * cos(2 * PI * windowIndex));
    
    //Blackman窓
    fir_Window = 0.42 - (0.5 * cos(2 * PI * windowIndex)) + (0.08 * cos(4 * PI * windowIndex));
    
    //Nuttall窓
    fir_Window = 0.355768 - (0.487396 * cos(2 * PI * windowIndex)) + (0.144232 * cos(4 * PI * windowIndex)) - (0.012604 * cos(6 * PI * windowIndex));
    
    //Blackman‐Harris窓
    fir_Window = 0.35875 - 0.48829 * cos(2 * PI * windowIndex) + 0.14128 * cos(4 * PI * windowIndex) - 0.01168 * cos(6 * PI * windowIndex);

*/

class FIRFilter
{
	private:
		int32_t ctr1; 
		short sampleCount;
		float shiftedCtr1; 
		float windowIndex;
		float fir_hx;
		float* fir_Coef;
		float fir_Window;
		float cutoff_freq;
		float sampling_freq;
		float coef_size;

	public:
		enum _WINDOWTYPEDEF
		{
			Square,
			Vorbis,
			Sine,
			Hanning,
			Blackman,
			Nuttall,
			Blackman_Harris
		};

		FIRFilter()
		{
			ctr1 = 0;
			fir_hx = 0.0;
			fir_Window = 0.0;
			windowIndex = 0.0;
			sampleCount = 0;
			shiftedCtr1 = 0.0;
		}

		uint32_t create(_WINDOWTYPEDEF type, int32_t taps, float fcutoff, float fsample)
		{
			fir_Coef = (float*)calloc(taps, sizeof(float));
			if(fir_Coef == nullptr)
			{
				return FIR_CREATE_ERR;
			}

			cutoff_freq = fcutoff;
			sampling_freq = fsample;
			coef_size = taps;

			for(ctr1 = 0; ctr1 < coef_size; ctr1++)
  			{

				windowIndex = (float)ctr1 / (float)coef_size;
				shiftedCtr1 = (float)ctr1 - ((float)coef_size / 2.0) + SHIFT_OFFSET;

				fir_hx = sinf(2.0*PI_USING*(cutoff_freq/sampling_freq)*shiftedCtr1) / (PI_USING*shiftedCtr1);

				switch (type)
				{
					case Blackman:
						fir_Window = 0.42 - (0.5 * cos(2 * PI * windowIndex)) + (0.08 * cos(4 * PI * windowIndex));
					case Blackman_Harris:
						fir_Window = 0.35875 - 0.48829 * cos(2 * PI * windowIndex) + 0.14128 * cos(4 * PI * windowIndex) - 0.01168 * cos(6 * PI * windowIndex);
					case Hanning:
						fir_Window = 0.5 - (0.5 * cos(2 * PI * windowIndex));
					case Nuttall:
						fir_Window = 0.355768 - (0.487396 * cos(2 * PI * windowIndex)) + (0.144232 * cos(4 * PI * windowIndex)) - (0.012604 * cos(6 * PI * windowIndex));
					case Sine:
						fir_Window = sin(PI * windowIndex);
					case Square:
						fir_Window = 1.0;
					case Vorbis:
						fir_Window = sin( (PI_USING / 2.0) * sin(PI_USING*windowIndex) * sin(PI_USING*windowIndex) );
					default:
						break;
				}

				fir_Coef[ctr1] = fir_hx * fir_Window;
			}

			return FIR_CREATE_SUCCESS;
		}

		uint32_t filter(void* targetData, uint32_t dataSize)
		{

		}		
};

#endif