# Toshiba TCD1703C sample code for Arduino UNO

This code generates signals to run a [Toshiba TCD1703C CCD sensor.](http://pdf.datasheetcatalog.com/datasheet/toshiba/1971.pdf)

It provides the sensor with two ~440KHz clock signals (PHI1, PHI2) and SH, RS and CP pulses. To free up Arduino ports, PHI2 can be generated by inverting PHI1 and CP from delaying RS in hardware.

The clock frequencies generated are lower than the typical 1MHz suggested in the datasheet which may cause the sensor to saturate. To get readable results, cover the sensor to reduce the amount of light entering it.
