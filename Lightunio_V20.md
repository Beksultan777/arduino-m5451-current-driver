**The Lightuino board is a standalone Arduino-compatible (ATMEGA 328p) or a shield (daughtercard)**.  <br>

The purpose of the board is to expand the number of outputs available to the Arduino user and to provide outputs optimised for driving LEDs, optocouplers, relays, etc.  Instead of providing additional digital logic, the Lightuino offers 70 constant current outputs that can provide up to approximately 20 milliAmps of current per output.<br>
<br>
<br>This is different then digital logic chips.  Digital logic provide a constant voltage; i.e. when the pin is "high" you will see 5 volts (say) if a meter is placed across the pin and ground.  When a constant current output pin is "on" it will vary the voltage as necessary to drive a specific current out of the pin.  This means (for example) that an LED can be placed directly between V+ and the pin (the pin sinks the current) without using an additional resistor.  In fact, using a constant current driver is better than using a resistor for LEDs because the constant current driver will compensate for variations in the LEDs, for LED aging, and finally be safe if the LED fails by shorting.<br>
<br>
<h1>Uses</h1>

<ul><li>Light up model railroad houses, streetlights, etc<br>
</li><li>RGB mood lighting<br>
</li><li>LED coffee tables</li></ul>

<h1>Orientation</h1>
For all locations described on this page, please hold the board in front of you so that the M5451 chips are on the top surface and the power jack is farthest from your body (and the silkscreen is right-side up).  We will call the side the power jack is on the top.<br>
<br>
IDE cable pin numbers on both cables start from the bottom right (it is marked "1") and go to pin 40.  All location descriptions refer to the LEFT IDE cable.  To find the pin on the RIGHT side, just "flip" the top and bottom pins -- <b>Note: its nice to use a meter to be sure!</b>

<img src='http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/Lightuino20_fully_pop_isometric_annotated.png' />

<h1>Configuration</h1>

<h2>Jumpers</h2>
There are several jumpers on the board:<br>
<br>
<ul><li>SRC5V: If this jumper shorts the top and middle (as shown) 5V power (CPU power) comes from the DC jack.  If the jumper shorts the middle and bottom, then 5V comes from the FTDI cable.  If the jumper is removed, power must be supplied via the Arduino pin.<br>
</li><li>VPASS: This 5 pin header provides several functions.<br>
<ul><li>If this jumper shorts the left 2 pins (as shown), then power is shared between this board AND and Arduino Header's Vin pin.  This allows you to use a single wall-wart for multiple stacked boards.<br>
</li><li>If a jumper shorts pins 3 and 4 (from the left) then the GND signal is carried out to the IDE cables, pin 40 (top of the board the bottom pin).<br>
</li><li>Pin 5 (farthest to the right) is provided for you to send a custom signal or voltage out the IDE cables.  This voltage will be on IDE cable pin 36 (third from the top of the board, bottom pin).<br>
</li></ul></li><li>JBRI: If the jumper shorts the bottom and middle pin, overall brightness is controlled solely by the trim pots (as shown).  If the jumper shorts the top and middle pin, overall brightness can be software controlled by a PWM pin.  If the jumper is off, no LEDs will light!</li></ul>



<h2>Headers</h2>

<ul><li>ICSP: The ICSP header is used to program the boot image, just like on an Arduino.  Pin 1 is on the bottom right.</li></ul>

<ul><li>FTDI: Sketches are programmed via an FTDI cable, connected to these pins.  The BLACK FTDI wire should be on the LEFT the GREEN on the right (as marked on the board).  You may purchase an FTDI cable here (among other places): <a href='http://www.adafruit.com/index.php?main_page=product_info&products_id=70'>http://www.adafruit.com/index.php?main_page=product_info&amp;products_id=70</a></li></ul>

<h2>Potentiometers (VSEL and VTRIM)</h2>

<ul><li>VSEL: This potentiometer controls the voltage level expressed on the VCC pin (37, or top pin, 2nd from the top of the board) of the IDE cables.  The voltage can range from 0 to whatever your DC wall wart is providing (up to a max of about 20 volts).</li></ul>

<ul><li>VTRIM: These 2 potentiometers adjust the brightness (i.e. current) output on the left and right IDE cables respectively.  Generally they are used to match the sides so that the exact same intensities are generated.  However you can set them differently to generate different intensities per side.  Note that you may also use the provided library to implement software PWM to individually control brightness.</li></ul>


<h2>VDIV footprint</h2>

If you need to implement a voltage divider connected to your analog pins, these resistor footprints do the trick.  They bridge 5V and the analog pins.  Also just above each analog pin is a footprint for a set of ground connections, for easy connection of the variable half of the voltage divider.<br>
<br>
<h2>PINSEL</h2>

The pin select footprint lets you choose which digital IOs control the LEDs.  The top footprint holes correspond to the left side data pin, the clock pin, the right side data pin, and the brightness pin (as marked).  The bottom footprint holes correspond to digital IOs 0 through 13 moving from left to right.<br>
<br>
To use the M5451 chips, you must solder wires between a hole on the lower bank to a hole in the upper bank (if it is not already done). <b>Make sure your wire does not short against a via on the board!</b>

If you do not care which pins, then I recommend you use pin 3 to the "clock", pin 4 to the "left", pin 5 to the "right", and finally pin 10 to "bright".  You will need to enter this information into your sketch so it knows what pins to use.<br>
<br>
<h1>RESET</h1>

The reset button is located on the top as shown.  Please click the reset button EXACTLY when the Arduino IDE prints the "sketch size..." log.  It is very easy to press the button too early or late, which will cause the sketch to not be uploaded!<br>
<br>
<h1>LEDS</h1>

<ul><li>The rightmost LED indicates 5v power (CPU power).<br>
</li><li>The leftmost LED is the pin 13 LED used in a lot of sketches like the "blink" sketch.  It will also flicker rapidly when a sketch is being downloaded.</li></ul>

<h1>IDE cable pinout</h1>

The left and right IDE cable pinouts are exactly the same on the circuit board.  But since the header does a right angle turn to leave the board on the side, a pin on the top of the left side is on the bottom on the right, and vice versa.<br>
<br>
For example, pin 40 (the GND pin) on the circuitboard is on the upper left corner.  On the left side then corresponds to the top row, bottom pin.  On the right side this is the top row, top pin.<br>
<br>
<ul><li>Pin 40 GND Pin:  This pin is ground IF the appropriate VPASS jumper is closed.  Otherwise it is unused.<br>
</li><li>Pin 39 Vin Pin:  This is the raw voltage coming from the wall wart.  Only use this pin if you are using too much power for the voltage regulator to handle.<br>
</li><li>Pin 38 5V Pin: This pin provides 5 volts.  Use this pin to drive logic.<br>
</li><li>Pin 37 VSEL Pin: This pin provides whatever voltage is selected via the VSEL variable resistor.  If in doubt, use THIS pin to drive your LEDs, etc.<br>
</li><li>Pin 36 ANY Pin: This pin can be used for anything; it is exposed on the rightmost pin of the VPASS header (on the board "IDEVSEL S1" is silkscreened next to it).<br>
</li><li>Pin 35 - Pin 1: These are the individually controllable constant current sink pins.  Connect your load from one of the voltage pins described above to one of these pins.</li></ul>

In code,<br>
<pre><code>// A nice little PIN identifier sketch.  It assigns the extreme 4 pins (2 on each side)<br>
// different values.  Hook a multimeter up in series with an LED and measure the current<br>
// flowing through when the LED is connected to each pin.  You will see different currents<br>
// on each pin.  <br>
<br>
// You can use the same technique to find pins in the middle of the connector!<br>
<br>
CCShield board(myClockPin,mySerDataPin,mySerDataPin2, myBrightnessPin);   <br>
FlickerBrightness leds(board);<br>
<br>
void loop() <br>
  {<br>
  board.flags = Lightuino_FASTSET;<br>
  <br>
  while (1)<br>
  {<br>
  leds.brightness[0] = 32;      // This is the near side top pin on the LEFT connector<br>
  leds.brightness[34] = 64;     // This is 2-from-the-far side top pin on the LEFT connector<br>
  leds.brightness[35] = 127;    // This is the near side bottom pin on the RIGHT IDE connector  <br>
  leds.brightness[69] = 255;    // This is 2-from-the-far side bottom pin on the RIGHT IDE connector<br>
  for (int i=0;i&lt;10;i++) leds.loop();<br>
  //delay(100);<br>
  }<br>
}<br>
<br>
</code></pre>
<b>Note, sometimes the IDE cable will reverse what is bottom and top, so while the code comments are accurate for your connector they may not be accurate for the output of the IDE cable.  Just experiment!</b>

<h1>Miscellaneous</h1>


<h2>Brightness</h2>

Note that the M5451 chip can dissipate 1 Watt at 25 Celsius, so you must work within this limit.  For example let's say that you are putting 5V across the circuit, and the LEDs use 3V.  This means that 2V will be dissipated in the chip (5 minus 3).  At 10mA current, this is 20mW per line (power = volts*amps) or 20*35 LEDs = 700mW total dissipated in the chip.  So you are ok.  But if you used 20mA current, you would have 1.4Watts when all the LEDs are lit.  Not so good.<br>
<br>
However, there is more than one way to fix the problem. First, you can change the VSEL pot to adjust the input voltage.  Second, if only half of the LEDs are simultaneously on (maybe your application blinks them), then you are back to 700mW so are ok.  But of course this means a bug in your program might cause all the LEDs to turn on and the chip to burn out...  Or maybe you could install a heat sink onto the M5451 chip and do some testing to ensure you don't start a fire :-).<br>
<br>
<h1>CPU Components Only</h1>

<img src='http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/Lightuino20_CPU_only.jpg' />

<h1>Board Layout</h1>

<img src='http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/Lightuino20_circuitboard.png' />