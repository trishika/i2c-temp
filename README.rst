Description
===========

i2c-temp is made to communicate with the `TMP102 <https://www.sparkfun.com/products/9418>`_ temperature sensor breakout.
It used i2c to communicate with the sensor.
Kudos to `agilart <http://www.agilart.com/blog/tmp102-raspberry-pi>`_
and `donalmorrissey <http://donalmorrissey.blogspot.co.uk/2012/09/raspberry-pi-i2c-tutorial.html>`_.

Usage
=====

TMP102
------

Here is the connect map you should use to connect the TMP102 to the i2c bus :

+-------------------+----------+-------------------------------------+
| Raspberry Pi GPIO |  TMP102  | Description                         |
+===================+==========+=====================================+
| Pin1/3V3          |    V+    | Power                               |
+-------------------+----------+-------------------------------------+
| Pin6/Ground       |   GND    | Ground                              |
+-------------------+----------+-------------------------------------+
| Pin3/SDA          |   SDA    | I2C Data                            |
+-------------------+----------+-------------------------------------+
| Pin5/SCL          |   SCL    | I2C Clock                           |
+-------------------+----------+-------------------------------------+
| 3V3 or Ground     |   ADA0   | I2C address selector : 0x49 or 0x48 |
+-------------------+----------+-------------------------------------+

If ADA0 is connected to GND, I2C address would be 0x48.
If it is connected to VCC. I2C address would be 0x49.


I2C
---

You firsly need to enable the I2C driver by removing it from the blacklist.
From the file `sudo vi /etc/modprobe.d/raspi-blacklist.conf`, comment with a **#** the line (you'll need to reboot after that):

	blacklist i2c-bcm2708

Then load the module that allow control of the I2C bus from userspace with :

	# modprobe i2c-dev

You can use `i2c-tools` (most probably available through your package manager) to check the i2c bus is working correctly.
After installing those tool you be able to use i2cdetect (If you did nothing to change right on i2c dev node you'll probably need to be root to do that)::

	# i2cdetect -y 0
	    0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
	00:          -- -- -- -- -- -- -- -- -- -- -- -- --
	10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
	20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
	30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
	40: -- -- -- -- -- -- -- -- 48 -- -- -- -- -- -- --
	50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
	60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
	70: -- -- -- -- -- -- -- --

Depending how you connected your TMP102 it will be available on 48 or/and 49 I2C bus address.

Copying
=======

Copyright (C) 2013, Aurélien Chabot <aurelien@chabot.fr>

Licensed under **GPLv3**.

See COPYING file.
