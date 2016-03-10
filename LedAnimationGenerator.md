# Introduction #

This page lets you create small LED animations in a simple format and then convert them into C code for use in your sketch.  The following format is used:
```
<time to show this frame>: <* = ON, or _ = OFF>[, <space> ignored]
```
For example:
```
5000: *_ _*
1000: __ __
```

Defines a 2 frame animation, the first frame is shown for 5 seconds, the second for 1 second.  The first frame has 4 leds (for the purpose of this example), ON OFF OFF ON, the second frame also defined 4 leds, all of them OFF.

## Complete example ##

The following example pairs LEDs in groups of 7 and starts with them all on.  Then it turns them off starting in the middle and going out.
```
500: *******,*******,*******,*******,******* *******,*******,*******,*******,*******
400: ***_***,***_***,***_***,***_***,***_*** ***_***,***_***,***_***,***_***,***_***
300: **___**,**___**,**___**,**___**,**___** **___**,**___**,**___**,**___**,**___** 
200: *_____*,*_____*,*_____*,*_____*,*_____* *_____*,*_____*,*_____*,*_____*,*_____*
100: _______,_______,_______,_______,_______ _______,_______,_______,_______,_______ 
```

When this code is pasted in the gadget below, the generated code is:
```
prog_uchar leds[] PROGMEM = {255,255,255,255,255,255,255,255,63,239,223,191,126,253,251,247,239,55,199,143,30,60,120,241,227,199,35,131,6,12,24,48,96,193,131,1,0,0,0,0,0,0,0,0,0 };
prog_uint16_t delays[] PROGMEM = {500,400,300,200,100 };
int numFrames = 5;
```

Do not pay attention to what all the numbers are.  The point is that 3 variables are created, "leds", "delays", and "numFrames".  Paste this code into your sketch.

Next, you use the generate code like this:

```
void loop()
{
  // Create the Shield object... if you don't know what this is
  // you need to back up and learn how to use the Shield to turn on basic LEDs
  // before working on animations.
  CCShield out(myClockPin,mySerDataPin,mySerDataPin2, myBrightnessPin);

  // Create the animation object
  LedAnimation la(out, leds,delays,numFrames);

  // Optionally tell it to show the animation in reverse, or in forward-then-back (windshield wiper) mode.
  //la.setBackForth();
  //la.setReverse();
  
  for (int i=0;i<numFrames*10;i++)  // NumFrames*10 will make it go thru the animation 10 times.
    la.next();  // Show the next frame in the animation
  }
```

**Of course you can have more than one animation in a single sketch, you simply need to change the variable names!**

## Here is the Code Generator! ##
&lt;wiki:gadget url="http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ledani.xml" height="400" width="800" border="5" /&gt;