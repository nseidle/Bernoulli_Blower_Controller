Bernouli Blower Controller
=========================

The Bernoulli Blower is an interactive exhibit at the [WOW kid's museum](http://www.wowchildrensmuseum.org/) in Lafayette, CO. A large box has a button and a large curved blower facing orthogonal to the ground. Pressing the button causes the blower to turn on and allows kids to send beach balls into the air. Because of differential air pressures around the ball it is held, hovering and spinning in mid air above the outlet of the blower.

![Overall System](https://raw.githubusercontent.com/nseidle/Bernoulli_Blower_Controller/master/images/Overall-System.jpg)

The controller turns on the blower for 45 seconds then turns off. Any presses of the button during that 45 seconds are ignored. This is a very fancy software controlled timed relay. The big arcade button is a leaf switch with an LED that we pulse/breath on/off to try to get kids to press it. The SAMD21 Mini then turns on an AC outlet. You can build your own DC conrolled AC outlet with a solid-state relay (SSR) or you can buy an off the shelf product like power switch tail or IoT Relay.

![Outlet wiring](https://raw.githubusercontent.com/nseidle/Bernoulli_Blower_Controller/master/images/Outlet-Wiring.jpg)

Above you can see the outlet has been clipped on the right side (the small slot is the hot slot) to isolate the two outlets. The outlet shown on the left in the picture above is wired to the SSR and is switchable while the outlet on the right is energized at all times. This allows me to plug a wall adapter into the 'always on' outlet to power the controller and plug the blower into the switched outlet. I had two small wires running from the DC input side. These two wires terminate in a 2-pin JST connector that plugs into the main controller. 

The SSR is switched at 5V through an NPN transistor connected between 5V, SSR, and ground with a 330 base resistor. SAMD21 is only 3.3V and is not quite enough to forward bias the SSR. I used a 2N2222 but any NPN (2N3904) should work.

The direct drive curved AC blower is model # Dayton 5C093C. It uses 8.8 Amps running and pulls over 10 Amps for a few seconds went starting up. The 40A SSR is capable of handling this load and I found that the metal housing makes a very nice heat sink once the SSR is tightly screwed down. The housing and SSR don't even get warm to the touch after multiple start/stops.

I love telephone cable (RJ11) for exhibit building and wiring because:

* It's super cheap (usually free if you ask around)
* Has 4 connectors for I2C or a switch+LED
* The connectors are robust and easily unplugged if needed
* Its sheath give it good protection against rubbing and pinching 

A $5 power strip was the cheapest source for a short 18 gauge pictail. I cut the power cable off at the insert point to the power strip. Then I cut open and spliced the pig tail onto the power leads of the AC motor. This allows me to plug/unplug the motor from the switchable outlet. If I ever need to trouble shoot the system I can plug the motor directly into an outlet or an extension cord and power up the motor to see if it's still working.

The red LED in the big arcade button has a 640 Ohm resistor (I think). I replaced this with a 10 Ohm resistor because it was being powered directly from 3.3V.

Parts List:
-------------------

* [6' 18AWG Pigtail](http://www.homedepot.com/p/HDX-6-ft-16-3-SPT-3-Appliance-Cord-Gray-HD-588-547/100672804) - $7
* [Power Strip with 3' Cord](http://www.homedepot.com/p/Belkin-6-Outlet-Power-Strip-F9P609-03-DP/100654575) (Cheapest way to get 3' a pig tail) - $4
* [Metallic Wall Box - 2.2" Deep](http://www.homedepot.com/p/Steel-City-4-in-30-3-cu-in-Metallic-Square-Box-Case-of-25-521711234EW-25R/202592852) - $3
* [Box Cover](http://www.homedepot.com/p/Steel-City-4-in-Square-Box-Cover-for-Single-Twist-Lock-Receptacle-Case-of-10-RS4-10R/202597334) - $1
* [Outlet](http://www.homedepot.com/p/Leviton-15-Amp-Duplex-Outlet-White-R52-05320-00W/202066670) - $1
* [3/8" Cable Clamp](http://www.homedepot.com/p/3-8-in-Non-Metallic-NM-Twin-Screw-Cable-Clamp-Connectors-5-Pack-20511/100133208) - $1 

* [SparkFun SAMD21 Mini Breakout](https://www.sparkfun.com/products/13664) - $20
* [Micro USB Power Supply](https://www.sparkfun.com/products/12890) - $6
* [SSR](https://www.sparkfun.com/products/13015) - $10
* [2-Pin JST](https://www.sparkfun.com/products/9914) - $1
* [RJ11 Connector](https://www.sparkfun.com/products/132) - $1
* [RJ45 Breakout](https://www.sparkfun.com/products/716) - $1
* [Big Dome Button](https://www.sparkfun.com/products/9181) - $10
* Any NPN Transistor, [2N3904](https://www.sparkfun.com/products/521) will work fine - $0.50
* 7' Telephone Cable (Had some laying around) - $0

Repository Contents
-------------------

* **firmware** - Contains the firmware that runs on the controller

License Information
-------------------
The hardware is released under [CERN Open Hardware License 1.2](http://www.ohwr.org/attachments/2388/cern_ohl_v_1_2.txt).
The code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.