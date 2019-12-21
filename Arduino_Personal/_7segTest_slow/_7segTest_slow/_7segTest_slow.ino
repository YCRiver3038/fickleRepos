#define mSecCycle 125
#define SRCLR_wait 1000
#define SEGMENTS 7
#define SREG_BITS 8
#define CHARS 16
#define CHARS_COUNTUP SREG_BITS*1

int SRCLK = 2;
int SER = 7;
int SRCLR = 3;
int OE = 4;
int counter1 = 0;
int counter3 = 0;
int counter4 = 0;
int c1ClrTime = 18;
int SERHighTiming = c1ClrTime / 2;
int onLED[CHARS][SEGMENTS] = {
                              {0, 1, 1, 1, 1, 1, 1},/*G,F,E,D,C,B,A*//*0*/
                              {0, 0, 0, 0, 1, 1, 0},/*1*/
                              {1, 0, 1, 1, 0, 1, 1},/*2*/
                              {1, 0, 0, 1, 1, 1, 1},/*3*/
                              {1, 1, 0, 0, 1, 1, 0},/*4*/
                              {1, 1, 0, 1, 1, 0, 1},/*5*/
                              {1, 1, 1, 1, 1, 0, 1},/*6*/
                              {0, 1, 0, 0, 1, 1, 1},/*7*/
                              {1, 1, 1, 1, 1, 1, 1},/*8*/
                              {1, 1, 0, 1, 1, 1, 1},/*9*/
                              {1, 1, 1, 0, 1, 1, 1},/*A*/
                              {1, 1, 1, 1, 1, 0, 0},/*b*/
                              {0, 1, 1, 1, 0, 0, 1},/*C*/
                              {1, 0, 1, 1, 1, 1, 0},/*d*/
                              {1, 1, 1, 1, 0, 0, 1},/*E*/
                              {1, 1, 1, 0, 0, 0, 1} /*F*/
                            };
int counter2 = 0;
bool isInit = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(SRCLK, OUTPUT);
  pinMode(SER, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(SRCLR, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!isInit)
  {
    counter3 = 0;
    counter4 = 0;
    digitalWrite(OE, HIGH);
    digitalWrite(SER, LOW);
    digitalWrite(SRCLR, LOW);
    delay(200);
    isInit = true;
    digitalWrite(SRCLR, HIGH);
    counter2 = 0;
  }

  if( (counter3 %= CHARS_COUNTUP) == 0)
  {
    counter4++;
    counter4 %= CHARS;
  }
    
  if( onLED[counter4][counter2] == 0 )
  {
    digitalWrite(SER, LOW);
  }
  else
  {
    digitalWrite(SER, HIGH);
  }
  counter2++;
  
  if ( counter2 > SEGMENTS )
  {
    digitalWrite(OE, LOW);
    delay(SRCLR_wait);
    digitalWrite(SER, LOW);
    digitalWrite(SRCLR, LOW);
    delay(mSecCycle);
    digitalWrite(SRCLR, HIGH);
    counter2 = 0;
  }

  delay(mSecCycle);
  digitalWrite(SRCLK, HIGH);
  delay(mSecCycle);
  digitalWrite(SRCLK, LOW);
  digitalWrite(OE, HIGH);
  counter3++;
}
