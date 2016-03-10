# Orientation #
For all locations described on this page, please hold the in front of you so that the M5451 chips are on the top surface and the power jack is nearest to your body.  We will call the side the power jack is on the bottom.

![http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/CCShield_isometric_view_parts_defined.jpg](http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/CCShield_isometric_view_parts_defined.jpg)
# Jumpers #

There are 2 jumpers on the board.

## Power ##
The Power jumper has just 2 pins.  If it is closed, Vin power is shared between the CCShield and the Arduino.  Vin is **NOT** 5 volts, it is whatever is coming in from the power jack.

## Brightness Selection ##
The brightness selection jumper has 3 pins.  If the jumper shorts the right pin (farthest from the IDE connector) and the middle pin, brightness is set by the value of the resistor and the value of Vin.  If the jumper is shorting the middle and the left pin, brightness is selected by the one of the Arduino digital IOs (whichever is selected by the solder blob on the back of the board) and the resistor value.  If the jumper is off, no LEDs will light!

# IDE cable pinout #

The left and right IDE cable pinouts are rotated 180 degrees.  This is so both IDE cables fan out AWAY from the board when plugged in.

Each cable has 35 connections for LEDs, 4 power wires, and 1 ground wire. Generally you want to connect the LED from one of the power wires to one of the 35 connections.  You can connect lots of LEDs to the same power wire, which is why only 4 are provided.

The ground wire is **NOT** needed for normal uses like lighting LEDs.  Its only there in case you are interfacing to other chips, etc.  In fact accidently connecting an LED directly from one of the power lines to the ground line will burn the LED out so it is recommended that you mark the ground line specially by coloring it on the IDE cable with a pen.

## Left cable ##

**The UPPER LEFT pin (topmost wire on the cable) is GROUND.**DO NOT USE FOR LED APPLICATIONS

**The BOTTOM RIGHT pin (lowest wire on the cable) is Vin POWER.**

**There are 3 other Power pins spaced more-or-less evenly through the cable.**

**The LEDs count from the bottom of the cable (ie. writing the lowest bit (1) into the set function will activate the bottom left pin.**

![http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ccshield_left_ide_pinout.jpg](http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ccshield_left_ide_pinout.jpg)
**In this pinout, WHITE is GROUND and RED is power**

## Right cable ##

The right cable is the exact 180 degree rotation of the left (so that the IDE cable heads away from the board):

**The UPPER LEFT pin (topmost wire on the cable) is Vin POWER.**

**The BOTTOM RIGHT pin (lowest wire on the cable) is GROUND.**DO NOT USE FOR LED APPLICATIONS

**The LEDs count from the top of the cable (ie. writing the lowest bit (a 1) into the set function will activate the upper right pin.  Writing 0x2 will activate the left pin on the second row, a 0x4 the right pin second row, and so on.  If you want to make sure you have the pins correct, just turn one on using the "set" function.  Then set you multimeter to measure current -- around 50mA.  Next put the + probe on the end of the power jack and start touching pins with the - probe, but of course MAKE SURE YOU DONT TOUCH THE ONE GROUND PIN (well its not so bad, worst case just burn out your wall wart, but most likely the wall wart is internally protected against overdriving).**

**Whether the right cable start at bit 0 or at bit 35 (and so the left starts at 0) depends on which data line they connect to and how the CCShield class is initialized.  If its backwards, just switch the 2 "data" line numbers in the CCShield constructor!**

![http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ccshield_right_ide_pinout.jpg](http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ccshield_right_ide_pinout.jpg)
**In this pinout, WHITE is GROUND and RED is power**

# Miscellaneous #


## Brightness ##

There is a 2.2KOhm resistor on the board that selects the max current flowing through each LED to about 15mA.  You can change the LED brightness by changing this resistor higher to dim the LED and lower to brighten it.

Note that the M5451 chip can dissipate 1 Watt at 25 Celsius, so you must work within this limit.  For example let's say that you are putting 5V across the circuit, and the LEDs use 3V.  This means that 2V will be dissipated in the chip (5 minus 3).  At 10mA current, this is 20mW per line (power = volts\*amps) or 20\*35 LEDs = 700mW total dissipated in the chip.  So you are ok.  But if you used 20mA current, you would have 1.4Watts when all the LEDs are lit.  Not so good.

However, there is more than one way to fix the problem. First, if only half of the LEDs are simultaneously on (maybe your application blinks them), then you are back to 700mW so are ok.  Or maybe you could install a heat sink onto the M5451 chip and do some testing to ensure you don't start a fire :-).

# Board Layout #

![http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ccshield_board.jpg](http://arduino-m5451-current-driver.googlecode.com/svn/trunk/latest/wiki/ccshield_board.jpg)