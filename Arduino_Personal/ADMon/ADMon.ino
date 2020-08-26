#define AVG_bits 5
#define AVG_SIZE uint8_t(1<<AVG_bits)
#define CUR_SENS_SLP 2.96f
#define CUR_SENS_OFS 5.7424f

uint8_t AVGCtr = 0;
uint8_t tempctr = 0;
uint16_t printctr = 0;
uint16_t VRaw[AVG_SIZE] = {0};
uint16_t VAvg = 0;
float VAvg_f = 0.0;
float sCur = 0.0;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
}

void loop() {
	// put your main code here, to run repeatedly:
	VRaw[AVGCtr] = analogRead(2);
	while(tempctr < AVG_SIZE)
	{
		VAvg += VRaw[tempctr];
		tempctr++;
	}
	tempctr = 0;
	VAvg >>= AVG_bits;
	AVGCtr = (AVGCtr+1)&(AVG_SIZE-1);
	VAvg_f = (float)VAvg * 0.0048047;
	sCur = (CUR_SENS_SLP*VAvg_f) - CUR_SENS_OFS;
	
	if(printctr == 0)
	{
		Serial.print(sCur);
		Serial.print("\t");
		Serial.print(VAvg_f);
		Serial.print("\r");
	}
	printctr = (printctr+1)&0x1FF;
}
