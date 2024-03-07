#include <iostream> 
#include "ev3.h"

int main() { 
	InitEV3();

	Ev3ColorSensor s(S1);
	Lcd::clean();
	Lcd::printf(1, "Performance Test evcpp\n");

	// test idling
	int start_time = Ev3::getCurrentTime();
	int count = 0;
	while (count < 10000000)
	{
		count++;
	}
	int end_time = Ev3::getCurrentTime();
	if (end_time != start_time) {
		Lcd::printf(1, "%f\n", ((float)count * 1000) / (end_time - start_time));
	} else {
		Lcd::printf(1, "0\n");
	}
	
	// test reading a sensor
	start_time = Ev3::getCurrentTime();
	count = 0;
	int sum;
	while (Ev3::getCurrentTime() - start_time < 5000)
	{
		count++;
		sum += s.getRawValue();
	}
	Lcd::printf(1, "%d\n", count / 5 + sum * 0); // use sum to prevent compiler optimizations

	// test reading unique values from a sensor
	start_time = Ev3::getCurrentTime();
	count = 0;
	int unique = 0;
	int prevValue = 0;
	while (Ev3::getCurrentTime() - start_time < 5000)
	{
		count += 1;
		int value = s.getRawValue();
		if (value != prevValue) {
			unique++;
			prevValue = value;
		}
	}
	Lcd::printf(1, "%d %d\n", count / 5, unique / 5);

	Wait(5000);

	FreeEV3();
	return 0;
}
