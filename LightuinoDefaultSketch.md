This is some details of the sketch that is shipped with every Lightuino.

# Description #

This sketch does a basic light test (individually turns on each line) and then it runs thru some animations.  It also prints to the serial line so you can see which part of the sketch corresponds to which animation.

You can tell that this sketch is running by looking at the Lightuino's LED right after pressing the reset button.  The LED will first flash a few times, pause and flash a few more times.  This is the boot rom.

Next it will load the sketch.  This sketch will flash the LED 10 times starting rapidly and getting slower and slower.  This is very different than the boot rom which flashes in clusters of equal time pulses. So is easy to tell that the Lightuino sketch is running.

Also, when the Lightuino sketch finishes its sequence (about a minute), it loops back and flashes the LED in this pattern again (but the boot rom LED sequence will NOT run).  This is another way to verify that the default sketch is running.


# Source Location #

http://code.google.com/p/arduino-m5451-current-driver/source/browse/trunk/latest/apps/lightuino_animations/applet/lightuino_animations.cpp

# Serial Output #

<pre>
Lightuino library development test v1.0<br>
Say hi<br>
Start countdown<br>
10<br>
9<br>
8<br>
7<br>
6<br>
5<br>
4<br>
3<br>
2<br>
1<br>
Light Check<br>
0<br>
1<br>
2<br>
3<br>
4<br>
5<br>
6<br>
7<br>
8<br>
9<br>
10<br>
11<br>
12<br>
13<br>
14<br>
15<br>
16<br>
17<br>
18<br>
19<br>
20<br>
21<br>
22<br>
23<br>
24<br>
25<br>
26<br>
27<br>
28<br>
29<br>
30<br>
31<br>
32<br>
33<br>
34<br>
35<br>
36<br>
37<br>
38<br>
39<br>
40<br>
41<br>
42<br>
43<br>
44<br>
45<br>
46<br>
47<br>
48<br>
49<br>
50<br>
51<br>
52<br>
53<br>
54<br>
55<br>
56<br>
57<br>
58<br>
59<br>
60<br>
61<br>
62<br>
63<br>
64<br>
65<br>
66<br>
67<br>
68<br>
69<br>
DoubleRollChaser<br>
Opposite RollChaser<br>
Cross<br>
Ani<br>
Wiper<br>
Sweep<br>
Marquee to 2 centers<br>
DoubleRollChaser with other lit LEDs<br>
Marquee<br>
IntensityRotater<br>
<br>
</pre>
Then it repeats