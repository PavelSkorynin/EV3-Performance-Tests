#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import ColorSensor, Motor
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile


# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.


# Create your objects here.
ev3 = EV3Brick()
timer = StopWatch()
s1 = ColorSensor(Port.S1)

ev3.screen.print('MicroPython performance test')
print("MicroPython performance test")

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
    sum += s1.reflection()
ev3.screen.print(str(int(count / 5)))
print("test2:"+str(int(count / 5)))


# test reading unique values from a sensor
timer.reset()
count = 0
unique = 0
prevValue = 0
while timer.time() < 5000:
    count += 1
    value = s1.reflection()
    if value != prevValue:
        prevValue = value
        unique += 1
results = str(int(count / 5)) + " " + str(int(unique / 5))
ev3.screen.print(results)
print("test3: " + results)

# test P-controller: read 4 color sensors and update power of two motors
motorB = Motor(Port.B)
motorC = Motor(Port.C)
s2 = ColorSensor(Port.S2)
s3 = ColorSensor(Port.S3)
s4 = ColorSensor(Port.S4)
motorB.dc(100)
motorC.dc(100)
wait(1000)
timer.reset()
count = 0
uniqueB = 0
uniqueC = 0
prevValueB = 0
prevValueC = 0
while timer.time() < 5000:
    count += 1
    value1 = s1.reflection()
    value2 = s2.reflection()
    value3 = s3.reflection()
    value4 = s4.reflection()
    valueB = motorB.angle()
    valueC = motorC.angle()
    delta = (value1 * 2 + value2 - value3 - value4 * 2) / 6

    motorB.dc(max(100 + delta, 100))
    motorC.dc(max(100 - delta, 100))

    if valueB != prevValueB:
        prevValueB = valueB
        uniqueB += 1
    if valueC != prevValueC:
        prevValueC = valueC
        uniqueC += 1

results = str(int(count / 5)) + " " + str(int(uniqueB / 5)) + " " + str(int(uniqueC / 5))
ev3.screen.print(results)
print("test3: " + results)

wait(10000)
