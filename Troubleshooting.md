## My LEDs are smoking or burning out! ##

Are you using a DC "wall-wart" transformer?  Those are **unregulated** power supplies!  The voltage printed on them is the mininum voltage.  Check the voltage with a voltmeter and make sure that it is less than the M5451 maximum of 13 volts!

To solve this problem use a different transformer, feed the power into a voltage regulator chip first, or use a regulated power supply, for example:
http://www.dipmicro.com/store/index.php?act=viewCat&catId=115

Note though that you may have permanently damaged the M5451 chip, you may need to replace it.

## When I turn on all LEDs on multiple M5451 chips, lots of them suddenly turn off ##

Does every LED connected to one (or more) M5451s turn off?  If so, your DC "wall-wart" transformer is not supplying enough current (the rated current is printed on the transformer).  Either don't turn on all the LEDs at once, get a bigger transformer, or use the M5451 "brightness" feature to run them all a bit dimmer.

## My LEDs do not light at all ##
Is power getting to the board?  If you are using power from the Arduino, make sure that the power jumper is closed so that power really is getting to it.  Check that there is 5v on this jumper, and that it is on the IDE cable.

Did you install the LEDs backwards?  Reverse one to find out.

Is the brightness selector jumper in?  If it is missing, the brightness will be 0 (ie. no light).  Try putting it across the center and right pins to eliminate the possibility that the Arduino is turning off the LEDs by using the brightness feature.

See [CCShieldRev1](CCShieldRev1.md) for locations of the brightness jumper, and IDE cable pinout.

## My LEDs blink erratically or do not blink when I tell them to ##
Is the software using the same pins as are selected on the CCBoard?
If so, it is possible that one or more of the solder blobs has a weak or broken connection.  You can check them using a probe by going from the pin that the Arduino plugs into to one of the other pads in the pin-selection area of the CCBoard.