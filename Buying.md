# Buying Hardware #

## MM5451YN ##
The M5451 chip is available either as a 40 pin DIP package (breadboardable) or as a surface mount package.  The part is no longer produced by ST Microelectronics in DIP format so that confuses the issue, but Micrel has it under the MM5451YN name.  I sourced mine from Future Electronics:

http://www.futureelectronics.com/en/Technologies/Product.aspx?ProductID=MM5451YNMICRELSEMICONDUCTOR5939202

Future electronic also carries surface mount versions

You can buy ST Microelectronics surface mount parts from Mouser:

http://mouser.com/Search/ProductDetail.aspx?qs=gr8Zi5OG3Mi5UnW0nBYFJA%3d%3d

Digikey
http://parts.digikey.com/1/parts/488039-ic-driver-display-led-40dip-mm5451yn.html


## CCShield ##

I had 10 prototypes built which are a few more than I need so drop me an email or add a comment here (with your obfuscated email address) if you would like one.  Unfortunately, due to the low volume production, it cost me about $10 a board for the circuit boards.  Each Micrel part is $3.67, so when you add in the IDE connectors and so forth, I'm breaking even at about $19.99 not even counting the labor of soldering it all together.  It would be cheaper if there is enough interest to do higher volume.

Some things to know about the prototype:

  * The boards can either use power from the Arduino, or use their own power via a 2.1mm jack (or the board's jack can even power the Arduino).  A jumper selects whether the board's power is connected to the Arduino's Vin or is isolated.  If you turn on all 70 LEDs at top brightness you will exceed the available power from USB, so you do need to use a wall wart.
  * The M5451 has a maximum voltage of 13.2 volts.  If you exceed this, LEDs start smoking and your M5451s burn out!  Standard wall-wart transformers are "unregulated" which means that although a value like "12v" may be printed on it, it might ACTUALLY be producing 20v (yes, I learned this from painful experience).  Many boards, like the arduino, have a voltage regulator on them that brings the voltage down to an exact 5v value.  However my boards do not have a regulator because the M5451 is capable of handling a wide voltage range (about 4 to 13 volts) and adding a regulator wastes efficiency (although if I did it again, I'd provide the option selectable via a jumper).
> But this means that you must TEST the wall-wart's actual voltage before using it.  I find that wall-wart transformers from 5 to 9 volts generally actually produce less then 13.2v.
  * You can select which pins the board should use by shorting certain surface mount pads.  Unfortunately, doing so with a radio shack soldering iron is actually very difficult, since they are so small (this is the main thing I would change if I did it again).
> So I would prefer to select the pins before sending the boards, to make sure that it is done right. I recommend not using pin 0 and 1 since those are the Arduino serial ports.  Let me recommend pins 3 (clock),4,5 (data), and 11 for brightness (must be a PWM port).
> Finally, there are currently 2 implementations of the "set" function in my library.  The first is totally generic (uses digitalWrite) and the second is really fast...but this second implementation only works if the clock pin is between 0 and 7 (its not systemic, I just haven't tested clock in the upper pins), so hopefully you're ok with it between 0 and 7.
  * CCShield boards are stackable, so you can drive hundreds of outputs by stacking a few of them.  To do this, you'd want to have different pins for each board of course (although theoretically you could use the same clock pin and modify my library).  Also, its pretty tight to get the IDE cables in between the boards when stacked (some IDE cables are smaller than others), so I'd recommend putting a spacer like [http://www.adafruit.com/index.php?main\_page=product\_info&cPath=17&products\_id=85](these.md).

  * Some really old IDE cables have one pin blocked so you can't put the cable in backwards (just look at the ends of the cable, you'll see that one hole is missing).  I am using all 40 pins so you need to get IDE cables with all 40 holes