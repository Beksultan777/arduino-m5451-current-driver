# Intro #

This page is a discussion about driving LED matrices with the M5451 chipset.

## Definitions ##

An LED matrix is a grid of LEDs connected so all LEDs on a ROW share a common anode and all LEDs on a column share a common cathode.  You can learn more about them and see a schematic here: http://www.acm.uiuc.edu/sigarch/tutorials/ledarray/

# The Problem #

So essentially to drive a LED matrix, you need a bunch of current sinks on one side (let's say the columns) and a current source on the other (let's say the rows).

The current sinks are easy!  They can be the CCShield/M5451 outputs.

The current sources are a bit tricky.  We essentially need to convert the CCShield "sink" into a current source.  Parts go by the name of high-side driver, PNP darlington, etc.

Note that the current source needs to be able to drive every LED on a row, so that could be quite a bit of power.  For example, since the CCShield has 70 "switches", you could run a 62x8 matrix.  This would make a pretty nice scrolling marquee.  And of course CCShield is stackable...

The simplest way to visualize this is to think of each CCShield line as a switch, and the current source switch as a PNP transistor.  The CCShield line is connected to the base of the transistor, so when it is "open" current can't flow thru the base; so it can't flow thru the transistor, i.e. it is "off".  When the CCShield is "closed", current can flow through the base so the transistor is "on".

However using individual transistors is **SO** 1960s!  It would be quite nice to find an IC!  I'm still digging around for the perfect part to drive the high side & I've basically come to the conclusion that it doesn't exist. :-)  It is ironic, the available parts are essentially TOO complicated; they expect TTL logic, not a CCShield line.

Here are the possibilities:

1. Micrel2981
http://www.futureelectronics.com/en/technologies/semiconductors/analog/drivers/motor-drivers/Pages/8432775-MIC2981-82YN.aspx

This drives 8 IOs but the problem is that it takes as input digital logic and is active high.  Now, you can easily interface a CCShield output to this part, but it requires one resistor per line.  Basically, put the resistor from VCC to the input on this chip.  And connect that same input to a CCShield line.  Now when the CCShield IO is OFF the input line is high so the IO here turns ON.  And when the CCShield is ON, it is drawn to ground and so the IO turns off (so its actually inverted, but that is easily corrected in software).  This is basically resistor-transistor logic or RTL.

The problem with this approach is it still requires one resistor per CCShield line.

2. MPQ2907
http://www.futureelectronics.com/en/Technologies/Product.aspx?ProductID=MPQ2907CENTRALSEMI8920217

Here is a chip with 4 PNP transistors in it.  So the advantage is just that its one chip instead of 4...but actually its 2 more solder pads than just using transistors because there are 2 unused pins.

**SO** 1970s! :-)


3. An bunch of PNP darlingtons:
http://www.fairchildsemi.com/ds/TI%2FTIP126.pdf

I've come circle and like the solution of just using individual transistors best.  The reason why I like it is because the footprint TO-220 is very standardized, so if you need to put 3 or even 5 amp transistors in to make a really long array you can do so, whereas if you use the Micrel2981 or MPQ2907 you are stuck with exactly that part.

Note though that this costs about twice as much as solution 1, but at $4 instead of $2+ for 8 rows its not going to break the bank :-) (I'm assuming that the resistors are essentially free, but there is the extra time it takes to solder more pads to think about -- and solution #1 has a few more pads).
