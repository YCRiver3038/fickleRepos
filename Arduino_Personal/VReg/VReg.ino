#define P_AD_CHG_CURRENT_HOT 3
#define P_AD_CHG_CURRENT_COLD 0
#define P_AD_SRC_VOL 1
#define P_PWM 10
#define V_SRC_RATIO 0.20833f
#define V_CHG_CUR_HOT_RATIO 0.20833f
#define V_CHG_CUR_COLD_RATIO 0.20833f
#define V_CHG_RATIO 0.5f
#define SEQ_DISP 30
#define SEQ_SUB_DISP 15
#define CHG_CUR_RESET 10

/*
 * CC：青LED
 * CV：緑LED
 * Float：白LED
 */

#define BAT_VOLT_LIM_FLOAT 12.1f
#define GAIN_BAT_VOLT 5.0f
#define GAIN_PRENOW_VOLT 5.0f
#define GAIN_DIFFSUM_VOLT 0.1f

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

bool isFloatChg = false;
bool isWaiting = false;
bool isStarted = false;

float thrVoltage = 0.0;
float batVoltDiff = 0.0;
float vdifPre = 0.0;
float vdifNow = 0.0;
int vdifPNCtr = 0;
float diffSum = 0.0;
float difVDif = 0;

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
    if(isFloatChg)
    {
      Serial.print("Float");
    }
    Serial.print("\n");

    if( (ctrSub % SEQ_SUB_DISP) == 0 )
    {
      Serial.print("\nSRC\tBAT\tDUT%\tCCH\tCCC\tCUR\tVDIF\tSTAT\n");
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
  /*
  Carrier Freq:
  0x01:15686.275Hz
  0x02:1960.58Hz
  0x03:245.10Hz
  0x04:61.275Hz
  0x05:15.32Hz  
  */
  pinMode(9, OUTPUT);
  Serial.begin(38400);
  Serial.print("\nSRC\tBAT\tDUT%\tCCH\tCCC\tCUR\tVDIF\tSTAT\n");
  ctrDisp = 0;
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
  
  if( batVoltage > 15.0 || ((chgCurrent == 0) && (srcVoltage == 0)) )
  {
    chgDuty = 0;
    diffSum = 0.0;
    isWaiting = true;
    isFloatChg = false;
    isStarted = false;
  }
  else
  {
    isWaiting = false;
    if(!isStarted)
    {
      isFloatChg = true;
      isStarted = true;
    }
  }
  
  if(!isWaiting)
  {
    if(isFloatChg)
    {
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

      if(abs(batVoltDiff) > (BAT_VOLT_LIM_FLOAT * 0.005))
      {
        dutyControl((int)thrVoltage);
      }          
    }
  }
  else
  {
    isWaiting = true;
    isFloatChg = false;
  }
}
