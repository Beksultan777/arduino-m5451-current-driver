# Required materials #

  * You should have an Arduino or variant.

  * You should have a few M5451 chips.

  * A solderless connector board.

  * Solderless connector jumper wires.

  * A bunch of LEDs

  * A voltmeter

# Setup #

  1. Insert your M5451 into the breadboard
  1. Connect your breadboard power rail to Vin on the Arduino
  1. Connect your breadboard ground rail to GND on the Arduino

  1. Count the pins on your M5451 starting with 1 on the upper left, and going down the left side.  Then switch over to the bottom right side and count up.  So pin 40 is on the upper right.

# Connections #

  1. Connect a 1K ohm RESISTOR between 5V and M5451 pin 19. Pin 19 is brightness control -- the current going through the LEDs will be proportional to the current going into pin 19.
  1. Optionally, connect a capacitor between M5451 pin 19 to ground.  This cap is optional on a breadboard since its just there to stop ringing (flickering).
  1. M5451 pin 1 (upper left) should be connected to the ground rail
  1. M5451 pin 20 (lower left) should be connected to 5V.
  1. M5451 pins 21 (lower right) and 22 are clock and data.  They should be connected to digital IOs on the Arduino.  You can use any digital pin, but since pins 0,1, and 2 are "special", I recommend using pins 3 and 4.
  1. If you have a M5450 chip (verses a 5451) pin 23 is NOT output enable so it should be LOW.  Connect it to ground ONLY if you have a M5450 chip.
  1. Finally hook up a bunch of LEDs (its nice to try more than one in case something is wrong with one of them, the pin, etc).  The LEDs "plus" side (anode) should be connected to the power rail and the minus side (cathode) to each pin on the 5451. The M5451 spec is a little unclear because it calls each LED pin an "output" pin.  But that does not mean current flows out!  "Output" in that context just means the "effect" or "result" of the chip is on these pins. So conventional current must flow IN to the M5451 chip.