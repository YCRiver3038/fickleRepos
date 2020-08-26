#define BAT_CAPACITY_mAh 4200
#define P_AD_CHG_CURRENT_HOT 3
#define P_AD_CHG_CURRENT_COLD 0
#define P_AD_SRC_VOL 1
#define P_PWM 9
#define V_SRC_RATIO 0.20833f
#define V_CHG_CUR_HOT_RATIO 0.20833f
#define V_CHG_CUR_COLD_RATIO 0.20833f
#define V_CHG_RATIO 0.5f
#define SEQ_DISP 30
#define SEQ_SUB_DISP 15
#define CHG_CUR_RESET 10
#define BULK_CHARGE_EXIT_COUNT 3000L
#define BULK_CHARGE_EXIT_RATIO 0.30f

//CC：青LED
//CV：緑LED
//Float：白LED

#define BAT_VOLT_LIM_BULK 14.5f
#define BAT_VOLT_LIM_FLOAT 13.85f
#define GAIN_BAT_VOLT 4.0f
#define GAIN_PRENOW_VOLT 100.0f
#define GAIN_DIFFSUM_VOLT 0.008f

#define CHG_CUR_LIM_BULK (BAT_CAPACITY_mAh * 0.12)
#define GAIN_CHG_CUR 0.1f
#define GAIN_PRENOW_CUR 0.4f
#define GAIN_DIFFSUM_CUR 0.0002f

int ctrDisp = 0;
int ctrSub = 0;
int chgDuty = 0;
int chgCtr = 0;

float srcVoltage = 0.0;
float dutyPercent = 0.0;
float chgCurHot = 0.0;
float chgCurCold = 0.0;
float chgCurrent = 0.0;
float chgCurrentT = 0.0;
float batVoltage = 0.0;
float batVoltageT = 0.0;

bool isBulkChg = false;
bool isFloatChg = false;
bool isWaiting = false;
bool isStarted = false;
bool isConstCur = false;
bool isConstV = false;

float thrVoltage = 0.0;
float batVoltDiff = 0.0;
float vdifPre = 0.0;
float vdifNow = 0.0;
int vdifPNCtr = 0;
float diffSum = 0.0;
float difVDif = 0;

float thrCurrent = 0.0;
float chgCurDiff = 0.0;
float cdifPre = 0.0;
float cdifNow = 0.0;
int cdifPNCtr = 0;
float diffSumCur = 0.0;
float difCurDif = 0.0;
float diffSumB = 0.0;
float difVDifB = 0;
long bChgEndCount = 0;

void serialPrintInfo()
{
		Serial.print(srcVoltage);
		Serial.print("\t");
		Serial.print(batVoltage);
		Serial.print("\t");
		Serial.print(dutyPercent);
		Serial.print("\t");
		Serial.print(chgCurHot);
		Serial.print("\t");
		Serial.print(chgCurCold);
		Serial.print("\t");
		Serial.print(chgCurrent);
		Serial.print("\t");
		Serial.print(batVoltDiff);
		Serial.print("\t");
		if(isWaiting)
		{
			Serial.print("Waiting");
		}
		if(isConstCur)
		{
			Serial.print("CC");
		}
		if(isConstV)
		{
			Serial.print("CV");
		}
		if(isFloatChg)
		{
			Serial.print("Float");
		}
		Serial.print("\t");
		Serial.print(bChgEndCount);
		Serial.print("\n");

		if( (ctrSub % SEQ_SUB_DISP) == 0 )
		{
			Serial.print("\nSRC\tBAT\tDUT%\tCCH\tCCC\tCUR\tVDIF\tSTAT\tEXC\n");
		}
		ctrSub++;
		ctrSub %= SEQ_SUB_DISP;
		return;
}

void dutyControl(int control)
{
	chgDuty += control;
	if(chgDuty <= 0)
	{
		chgDuty = 0;
	}
	if(chgDuty >= 255)
	{
		chgDuty = 255;
	}
	chgDuty %= 256;
	analogWrite(P_PWM, chgDuty);
	return;
}

void setup() {
	// put your setup code here, to run once:
	TCCR1B = (TCCR1B & 0b11111000) | 0x01;

//  Carrier Freq:
//  0x01:15686.275Hz
//  0x02:1960.58Hz
//  0x03:245.10Hz
//  0x04:61.275Hz
//  0x05:15.32Hz  

	pinMode(9, OUTPUT);
	Serial.begin(38400);
	Serial.print("\nSRC\tBAT\tDUT%\tCCH\tCCC\tCUR\tVDIF\tSTAT\tEXC\n");
	ctrDisp = 0;
	isBulkChg = true;
}

void loop() {
	// put your main code here, to run repeatedly:
	
	chgCtr = 0;
	batVoltage = 0;
	chgCurrent = 0;
	while(chgCtr < CHG_CUR_RESET)
	{
		chgCtr++;
		
		chgCurHot = ((float)analogRead(P_AD_CHG_CURRENT_HOT)*0.004883f);
		chgCurCold = ((float)analogRead(P_AD_CHG_CURRENT_COLD)*0.004883f);
		chgCurrentT = (chgCurHot - chgCurCold)*1000*2;
		chgCurrent += chgCurrentT;
			
		srcVoltage = ((float)analogRead(P_AD_SRC_VOL)*0.004883f) / V_SRC_RATIO;
		batVoltage += srcVoltage;
	}
	chgCurrent /= (float)chgCtr;
	batVoltage /= (float)chgCtr;
	
	dutyPercent = ((float)chgDuty/255.0)*100;

	if( (ctrDisp % SEQ_DISP) == 0)
	{
		serialPrintInfo();
	}
	ctrDisp %= SEQ_DISP;
	ctrDisp++;
	
	if( batVoltage > 15.0 )
	{
		chgDuty = 0;
		diffSumB = 0.0;
		diffSum = 0.0;
		isWaiting = true;
		isBulkChg = false;
		isConstCur = false;
		isConstV = false;
		isFloatChg = false;
		isStarted = false;
	}
	else
	{
		isWaiting = false;
		if(!isStarted)
		{
			isBulkChg = true;
			isConstCur = true;
			isConstV = false;
			isFloatChg = false;
			isStarted = true;
		}
	}
	
	if(!isWaiting)
	{
		if(isBulkChg)
		{
			isFloatChg = false;      
			
			if(isConstCur)
			{
				isConstV = false;
				isConstCur = true;
				chgCurDiff = (CHG_CUR_LIM_BULK - chgCurrent) / CHG_CUR_LIM_BULK;
				thrCurrent = chgCurDiff * GAIN_CHG_CUR;            
				diffSumCur += chgCurDiff / CHG_CUR_LIM_BULK;
				thrCurrent += diffSumCur * GAIN_DIFFSUM_CUR;
				
				if(cdifPNCtr % 2 == 0)
				{
					cdifPre = chgCurDiff;
				}
				else
				{
					cdifNow = chgCurDiff;
					difCurDif = (cdifNow - cdifPre) / CHG_CUR_LIM_BULK;
					thrCurrent += difCurDif * GAIN_PRENOW_CUR;
				}
				cdifPNCtr++;
				cdifPNCtr %= 2; 

				thrCurrent *= 255.0;

				dutyControl((int)thrCurrent);
				if(batVoltage > BAT_VOLT_LIM_BULK)
				{
					isConstV = true;
				}     
			}      
			if(isConstV)
			{
				isConstCur = false;
				isConstV = true;
				batVoltDiff = BAT_VOLT_LIM_BULK - batVoltage;      
				thrVoltage = batVoltDiff * GAIN_BAT_VOLT;            
				diffSumB += batVoltDiff;
				thrVoltage += diffSum * GAIN_DIFFSUM_VOLT;
				
				if(vdifPNCtr % 2 == 0)
				{
					vdifPre = batVoltDiff;
				}
				else
				{
					vdifNow = batVoltDiff;
					difVDif = (vdifNow - vdifPre);
					thrVoltage += difVDif * GAIN_PRENOW_VOLT;
				}
				vdifPNCtr++;
				vdifPNCtr %= 2;      
				dutyControl((int)thrVoltage);
				if(chgCurrent > (CHG_CUR_LIM_BULK + 80.0))
				{
					isConstCur = true;
				}     
			}
			
			if( (batVoltage >= (BAT_VOLT_LIM_BULK-0.2)) && (chgCurrent < (CHG_CUR_LIM_BULK * BULK_CHARGE_EXIT_RATIO)) )
			{
				bChgEndCount++;
				if(bChgEndCount > BULK_CHARGE_EXIT_COUNT)
				{
					bChgEndCount = 0;
					diffSum = 0.0;
					isFloatChg = true;
					isBulkChg = false;
				}
			}
			else
			{
				isFloatChg = false;
				bChgEndCount = 0;
			}
		}
		else if(isFloatChg)
		{
			diffSumB = 0.0;
			isBulkChg = false;
			isConstV = false;
			isConstCur = false;
			batVoltDiff = BAT_VOLT_LIM_FLOAT - batVoltage;
			
			thrVoltage = batVoltDiff * GAIN_BAT_VOLT;
						
			diffSum += batVoltDiff;
			thrVoltage += diffSum * GAIN_DIFFSUM_VOLT;
			
			if(vdifPNCtr % 2 == 0)
			{
				vdifPre = batVoltDiff;
			}
			else
			{
				vdifNow = batVoltDiff;
				difVDif = (vdifNow - vdifPre);
				thrVoltage += difVDif * GAIN_PRENOW_VOLT;
			}
			vdifPNCtr++;
			vdifPNCtr %= 2;
			
			dutyControl((int)thrVoltage);
			if(chgCurrent > 250.0)
			{
				isFloatChg = false;
				isBulkChg = true;
				isConstCur = true;
				isConstV = false;   
				diffSumB = 0.0;
			}
		}
	}
	else
	{
		isWaiting = true;
		isBulkChg = false;
		isFloatChg = false;
	}
}
