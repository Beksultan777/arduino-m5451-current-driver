#include "lightuinoPwm.h"
#include "inttypes.h"
#include <wiring.h>
#include <avr/interrupt.h>

//#define SAFEMODE

FlickerBrightness::~FlickerBrightness() {StopAutoLoop();}

void FlickerBrightness::shift(int amt) 
    { 
    offset+=amt; 
    if (offset>=M5451_NUMOUTS) offset -=Lightuino_NUMOUTS; 
    else if (offset<0) offset +=Lightuino_NUMOUTS; 
    }


ChangeBrightness::ChangeBrightness(FlickerBrightness& thebrd,void (*doneCallback)(ChangeBrightness& me, int led)):brd(thebrd)
{
  doneCall = doneCallback;
  for (int i=0;i<Lightuino_NUMOUTS;i++)
    {
      change[i] = 0;
      count[i]  = 0;
      destination[i] = 0;
      bresenham[i] = 0;
    }
}

void ChangeBrightness::set(uint8_t led, uint8_t intensity, int transitionDuration)
{
  if (led<Lightuino_NUMOUTS)
  {
    if (transitionDuration<1) transitionDuration=1;  // Fix up impossible values
    count[led] = transitionDuration;
    destination[led] = intensity;
    change[led] = ((long int) intensity) - ((long int) brd.brightness[led]);
  }
}

void ChangeBrightness::loop(void)
{
  unsigned char j;
  for (j=0;j<Lightuino_NUMOUTS;j++)
  {
    if (destination[j] != brd.brightness[j]) // This led is changing
    {
      bresenham[j] += change[j];
      /* Note that if change could be > count then this should be a while loop */
      while ((bresenham[j]<0)&& (brd.brightness[j] != destination[j]))
        { bresenham[j]+=count[j]; brd.brightness[j]--;}
      while ((bresenham[j]>=count[j])&& (brd.brightness[j] != destination[j])) { bresenham[j]-=count[j]; brd.brightness[j]++;}

      if ((brd.brightness[j]==destination[j])&&doneCall)
      {
        bresenham[j]=0;
        (*doneCall)(*this,j);
      }
    }
  }

  brd.loop();
}

//#define CLK (1<<7)
//#define LFT (1<<6)
//#define RGT (1<<5)


prog_uchar bitRevTable[] PROGMEM = { 
  0,16,8,24,4,20,12,28,2,18,10,26,6,22,14,30,1,17,9,25,5,21,13,29,3,19,11,27,7,23,15,31 };

static unsigned long reverseframe(unsigned int x) {
 unsigned int h = 0;
 unsigned char i = 0;

 for(h = i = 0; i < 13; i++) {
  h = (h << 1) + (x & 1); 
  x >>= 1; 
 }

 return h;
}

FlickerBrightness::FlickerBrightness(LightuinoSink& mybrd):brd(mybrd)
{
  for (int i=0;i<Lightuino_NUMOUTS;i++)
  {
    brightness[i] = 0;
    //bresenham[i]  = 0;
  }
  
  //iteration = 0;
  offset = Lightuino_NUMOUTS-1;
  minBrightness = 11;
  next = 0;
}

#ifdef SAFEMODE

unsigned int frame=0;
void FlickerBrightness::loop(void)
{
  char i=Lightuino_NUMOUTS-1;
  char pos;
  unsigned long int a[3] = {0,0,0};
  uint8_t lvl=false;
  int* bri = &brightness[offset];
  
  frame++;
  if (frame>=Lightuino_MAX_BRIGHTNESS) frame=0;
  unsigned int rframe = reverseframe(frame);
  
  while (i>=0)
    {
      register int temp = *bri;
            
      if (bri==brightness) bri=&brightness[Lightuino_NUMOUTS-1];
      else bri--;
      // This provides support for saturating arithemetic in the brightness, AND enforces the minimum brightness
      if (temp>=Lightuino_MAX_BRIGHTNESS) temp = Lightuino_MAX_BRIGHTNESS-1;
      //if (temp>minBrightness)
        {
          lvl = (rframe<temp);
        }
       // else lvl = false;
      
      if (i<32) a[0] = (a[0]<<1)|lvl;
      else if (i<64) a[1] = (a[1]<<1)|lvl;
      else a[2] = (a[2]<<1)|lvl;
      i--;
    }
  //iteration++;
  //if (iteration > Lightuino_MAX_BRIGHTNESS) iteration = 0;  
  
  brd.set(a);
}

#else

#define CDELAY(x) call(x)
#define PREPDELAY(x) call(x)
//delayMicroseconds(x);
#define DELAYTIME 1
#define PDELAYTIME 4

//#define CHK() { if (rframe < *bri) {datain=LFT;} else datain=0; if (rframe < *bri2) {datain |=RGT;}; bri--; bri2--;    }
//#define WRI() { PORTD = regVal; CDELAY(DELAYTIME); PORTD = regVal | datain; CDELAY(DELAYTIME); PORTD |= CLK; CDELAY(DELAYTIME); }

#define DoOne() { PORTD = regVal; temp = *bri2; if ((temp>minBrightness)&&(rframe < temp)) {datain=LFT;} else datain=0; temp=*bri; if ((temp>minBrightness)&&(rframe < temp)) {datain |=RGT;}; CDELAY(DELAYTIME); PORTD = regVal | datain;  CDELAY(DELAYTIME); bri++; PORTD |= CLK; rframe -= Lightuino_MAX_BRIGHTNESS/(Lightuino_NUMOUTS); rframe&=Lightuino_MAX_BRIGHTNESS-1; CDELAY(DELAYTIME); bri2++; }

//rframe -= Lightuino_MAX_BRIGHTNESS/(Lightuino_NUMOUTS/2); rframe&=Lightuino_MAX_BRIGHTNESS-1;

static void call(unsigned char loop)
{
  for(unsigned char i=0;i<loop;i++)
    {
    asm("nop");
    }
}

unsigned int frame=0;
void FlickerBrightness::loop(void)
{
  cli();
  //char i=Lightuino_NUMOUTS;
  //char pos;
  register unsigned char CLK = 1 << brd.clockPin;
  register unsigned char LFT = 1 << brd.serDataPin[0];
  register unsigned char RGT = 1 << brd.serDataPin[1];
  register int temp;
  unsigned char datain=0;
  //register int* bri = &brightness[Lightuino_NUMOUTS-1];
  //register int* bri2 = &brightness[(Lightuino_NUMOUTS/2)-1];
  register int* bri = &brightness[(Lightuino_NUMOUTS/2)];
  register int* bri2 = &brightness[0];
  
  frame++;
  if (frame>=Lightuino_MAX_BRIGHTNESS) frame=0;
  unsigned int rframe = reverseframe(frame);

  // Write the initial "start" signal
  PORTD &= ~(CLK | LFT | RGT);  // all low
  uint8_t regVal  = PORTD;      // remember all the other bits in the register
  PREPDELAY(PDELAYTIME);
  PORTD = regVal | CLK;         // toggle clock
  PREPDELAY(PDELAYTIME);
  PORTD = regVal & (~CLK);
  PREPDELAY(PDELAYTIME);
  PORTD = regVal | LFT | RGT;   // raise the data line on all the chips
  PREPDELAY(PDELAYTIME);
  PORTD = regVal | CLK;         // toggle clock
  PREPDELAY(PDELAYTIME);
  PORTD = regVal & (~CLK);
  PREPDELAY(PDELAYTIME);
  
  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();
      
  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();

  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();

  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();

  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();

  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();
     
  DoOne();
  DoOne();
  DoOne();
  DoOne();
  DoOne();
  sei();
}
#endif

// Code from: http://www.uchobby.com/index.php/2007/11/24/arduino-interrupts/
// Setup Timer2.
//Configures the ATMegay168 8-Bit Timer2 to generate an interrupt at the specified frequency.
//Returns the time load value which must be loaded into TCNT2 inside your ISR routine.
//See the example usage below.
#define TIMER_CLOCK_FREQ (F_CPU/128.0) //2MHz for /8 prescale from 16MHz
FlickerBrightness* gleds= 0;
unsigned int timerLatency;
unsigned char timerLoadValue;

#define TOGGLE_IO 13

ISR(TIMER2_OVF_vect) {
  FlickerBrightness* tmp = gleds;
  //Toggle the IO pin to the other state.
  //digitalWrite(TOGGLE_IO,!digitalRead(TOGGLE_IO));
  while (tmp) { tmp->loop(); tmp=tmp->next; }  
  
  //Capture the current timer value. This is how much error we have
  //due to interrupt latency and the work in this function
  timerLatency=TCNT2;

  //Reload the timer and correct for latency.  
  TCNT2=timerLatency+timerLoadValue; 
}

void StartTimer2(float timeoutFrequency)
{
  //Calculate the timer load value
  timerLoadValue=(int)((257.0-(TIMER_CLOCK_FREQ/timeoutFrequency))+0.5); //the 0.5 is for rounding;
  //The 257 really should be 256 but I get better results with 257, dont know why.

  //Timer2 Settings: Timer Prescaler /8, mode 0
  //Timmer clock = 16MHz/8 = 2Mhz or 0.5us
  //The /8 prescale gives us a good range to work with so we just hard code this for now.
  TCCR2A = 0;
  TCCR2B = 1<<CS22 | 0<<CS21 | 1<<CS20; 

  //Timer2 Overflow Interrupt Enable   
  TIMSK2 = 1<<TOIE2;

  //load the timer for its first cycle
  TCNT2=timerLoadValue; 
}

unsigned char StopTimer2()
{
    TCCR2B = 0;  // Stop the timer/counter 
}

void FlickerBrightness::StartAutoLoop(int rate)
{
  gleds = this;
  StartTimer2(rate);
}

void FlickerBrightness::StopAutoLoop(void)
{
  if (gleds == this)
    {
    gleds = 0;
    StopTimer2();
    }
}

