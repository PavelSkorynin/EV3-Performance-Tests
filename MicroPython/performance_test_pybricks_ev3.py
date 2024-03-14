#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (ColorSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile


# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.


# Create your objects here.
ev3 = EV3Brick()
timer = StopWatch()
s = ColorSensor(Port.S1)

ev3.screen.print('Performance test MicroPython')
print("Performance test MicroPython")

# test idling
timer.resume()
timer.reset()
count = 0
while count < 100000:
    count += 1
duration = timer.time()
ev3.screen.print(str(count * 1000 / duration))
print("test1:" + str(count * 1000 / duration))

# test reading a sensor
timer.reset()
count = 0
sum = 0
while timer.time() < 5000:
    count += 1
    sum += s.reflection()
ev3.screen.print(str(int(count / 5)))
print("test2:"+str(int(count / 5)))


# test reading unique values from a sensor
timer.reset()
count = 0
unique = 0
prevValue = 0
while timer.time() < 5000:
    count += 1
    value = s.reflection()
    if value != prevValue:
        prevValue = value
        unique += 1
ev3.screen.print(str(int(count / 5)) + " " + str(int(unique / 5)))
print("test3: "+ str(int(count / 5)) + " " + str(int(unique / 5)))

wait(5000)
