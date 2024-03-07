#!/usr/bin/env python3

import os
import time

# from ev3dev2.motor import LargeMotor
from ev3dev2.sensor import Sensor

os.system('setfont Lat15-Terminus12x6')

s = Sensor(address='in1', driver_name='lego-ev3-color')
s.mode = 'REF-RAW'

print('Performance test')

# test idling
start_time = time.time()
count = 0
while count < 100000:
    count += 1
end_time = time.time()
print(str(100000 / (end_time - start_time)))

# test reading a sensor
start_time = time.time()
count = 0
sum = 0
while (time.time() - start_time) < 5:
    count += 1
    sum += s.value()
end_time = time.time()
print(str(count / 5))

# test reading unique values from a sensor
start_time = time.time()
count = 0
unique = 0
prevValue = 0
while (time.time() - start_time) < 5:
    count += 1
    value = s.value()
    if value != prevValue:
        prevValue = value
        unique += 1
end_time = time.time()
print(str(count / 5) + " " + str(unique / 5))

time.sleep(5)

