import ev3_dc as ev3
import time

with ev3.Color(port=ev3.PORT_1, protocol=ev3.USB) as s:
    print('Performance test ev3-dc')

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
        sum += s.reflected
    print(str(count / 5))

    # test reading unique values from a sensor
    start_time = time.time()
    count = 0
    unique = 0
    prevValue = 0
    while (time.time() - start_time) < 5:
        count += 1
        value = s.reflected
        if value != prevValue:
            prevValue = value
            unique += 1
    print(str(count / 5) + " " + str(unique / 5))

    time.sleep(5)
