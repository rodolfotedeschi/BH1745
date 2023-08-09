# BH1745 Color Sensor Driver

This driver is for BH1745 color sensor, and is based on [Adafruit's Unified Sensor Library](https://github.com/adafruit/Adafruit_Sensor).

This is the basic usage (you can also find an example sketch in the repository):
```
BH1745 colorSensor;
colorSensor.begin();

// ...

sensors_event_t colorEvent;
colorSensor.getColorEvent(&colorEvent);

sensors_event_t lightEvent;
colorSensor.getLightEvent(&lightEvent);
```

## About this driver ##

This driver was written as an exercise, it can serve as a baseline to work with this sensor but it's neither tested nor complete.

These are a few suggestions on how to improve the drive, if you plan to use it:
- measurement time should be configured depending on desired reading frequency
- gain should be automatically adjusted to provide best accuracy and avoid saturation
- color components should probably be compensated based on material and channel sensitivity
- take absolute light readings (lx) with a gran of salt (or two), especially if you want to compare it with other sensors