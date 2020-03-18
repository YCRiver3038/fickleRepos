#include "SD1COMM.h"
#include "../../ringbuffer.h"
#include "stdint.h"

void setup() {
	// put your setup code here, to run once:

	/*todo:*/
	SD1Device SD1Target1;
	SD1Tone usrTone;
	uint8_t gtRet = 0;

	SD1Target1.init();
	gtRet = usrTone.getToneMemory(15);

	if(gtRet != TMEM_ALLOC_ERR)
	{
		//usrTone.setToneParams(0, N_OP1, PN_BO, 0);
	}
	else
	{
		return;
	}
}

void loop() {
	// put your main code here, to run repeatedly:

}
