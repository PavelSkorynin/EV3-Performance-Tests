#include "ev3api.h"
#include "app.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) < (y) ? (y) : (x))

int32_t default_menu_font_width;
int32_t default_menu_font_height;

#define TEXT_SIZE 128
char text[TEXT_SIZE];

SYSTIM TimerMS() {
    SYSTIM tim;
    get_tim(&tim);
    return tim;
}

inline void lcd_clear() {
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
}

void lcd_print(const char *s, int x, int y) {
	// Get font information
	int32_t fontw, fonth;
	ev3_font_get_size(MENU_FONT, &fontw, &fonth);

	ev3_lcd_draw_string(s, 0, default_menu_font_height + y * (fonth + 2));
}

void testIdling(int lineNumber) {
    int count = 0;
    SYSTIM startTime = TimerMS();
    while (count < 1000000000) {
        count++;
    }
    SYSTIM duration = TimerMS() - startTime;
    snprintf(text, TEXT_SIZE, "Idling: %ld", duration);
    lcd_print(text, 0, lineNumber);
}

void testSensorReading(int lineNumber) {
    SYSTIM start_time = TimerMS();
    int count = 0;
    int sum = 0;
    while (TimerMS() - start_time < 5000) {
        sum += ev3_color_sensor_get_reflect(EV3_PORT_1);
        count++;
    }
    snprintf(text, TEXT_SIZE, "Sensor read: %d", count / 5);
    lcd_print(text, 0, lineNumber);
}

void testUniqueSensorReading(int lineNumber) {
    SYSTIM start_time = TimerMS();
    int unique = 0;
    int prevValue = 0;
    while (TimerMS() - start_time < 5000) {
        int value = ev3_color_sensor_get_reflect(EV3_PORT_1);
        if (prevValue != value) {
            prevValue = value;
            unique++;
        }
    }
    snprintf(text, TEXT_SIZE, "Sensor uniq: %d", unique / 5);
    lcd_print(text, 0, lineNumber);
}

void testEncoderReadingBC(int lineNumber) {
    ev3_motor_set_power(EV3_PORT_B, 100);
    ev3_motor_set_power(EV3_PORT_C, 100);
    tslp_tsk(1000);
    SYSTIM start_time = TimerMS();
    int uniqueB = 0;
    int prevValueB = 0;
    int uniqueC = 0;
    int prevValueC = 0;
    while (TimerMS() - start_time < 5000) {
        int valueB = ev3_motor_get_counts(EV3_PORT_B);
        if (prevValueB != valueB) {
            prevValueB = valueB;
            uniqueB++;
        }
        int valueC = ev3_motor_get_counts(EV3_PORT_C);
        if (prevValueC != valueC) {
            prevValueC = valueC;
            uniqueC++;
        }
    }
    ev3_motor_stop(EV3_PORT_B, true);
    ev3_motor_stop(EV3_PORT_C, true);
    snprintf(text, TEXT_SIZE, "BC uniq: %d %d", uniqueB / 5, uniqueC / 5);
    lcd_print(text, 0, lineNumber);
}

void testPController4_2(int lineNumber) {
    ev3_motor_config(EV3_PORT_B, LARGE_MOTOR);
    ev3_motor_config(EV3_PORT_C, LARGE_MOTOR);
    ev3_sensor_config(EV3_PORT_1, COLOR_SENSOR);
    ev3_sensor_config(EV3_PORT_2, COLOR_SENSOR);
    ev3_sensor_config(EV3_PORT_3, COLOR_SENSOR);
    ev3_sensor_config(EV3_PORT_4, COLOR_SENSOR);
    ev3_motor_set_power(EV3_PORT_B, 100);
    ev3_motor_set_power(EV3_PORT_C, 100);
    lcd_print("Config...", 0, lineNumber);
    tslp_tsk(5000);
    lcd_print("Testing...", 0, lineNumber);
    SYSTIM start_time = TimerMS();
    int uniqueEncoder[4] = {0, 0, 0, 0};
    int uniqueSensor[4] = {0, 0, 0, 0};
    int prevEncoder[4] = {0, 0, 0, 0};
    int prevSensor[4] = {0, 0, 0, 0};
    int count = 0;
    int value = 0;
    while (TimerMS() - start_time < 5000) {
        for (int i = 1; i < 3; ++i) {
            value = ev3_motor_get_counts(EV3_PORT_A + i);
            if (prevEncoder[i] != value) {
                prevEncoder[i] = value;
                uniqueEncoder[i]++;
            }
        }
        for (int i = 0; i < 4; ++i) {
            value = ev3_color_sensor_get_reflect(EV3_PORT_1 + i);
            if (prevSensor[i] != value) {
                prevSensor[i] = value;
                uniqueSensor[i]++;
            }
        }

        int delta = (prevSensor[0] * 2 + prevSensor[1] - prevSensor[2] - prevSensor[3] * 2) / 6;
        int powerB = min(100 + delta, 100);
        int powerC = min(100 - delta, 100);

        ev3_motor_set_power(EV3_PORT_B, powerB);
        ev3_motor_set_power(EV3_PORT_C, powerC);

        count++;
    }
    ev3_motor_stop(EV3_PORT_B, true);
    ev3_motor_stop(EV3_PORT_C, true);
    snprintf(text, TEXT_SIZE, "P-cont: %d %d %d", count / 5, uniqueEncoder[1] / 5, uniqueEncoder[2] / 5);
    lcd_print(text, 0, lineNumber++);
    snprintf(text, TEXT_SIZE, "%d %d %d %d", uniqueSensor[0] / 5, uniqueSensor[1] / 5, uniqueSensor[2] / 5, uniqueSensor[3] / 5);
    lcd_print(text, 0, lineNumber);
}

void main_task(intptr_t unused) {
	ev3_lcd_set_font(MENU_FONT);
   	// ev3_sensor_config(EV3_PORT_1, COLOR_SENSOR);
    // lcd_print("Configuring Sensor...", 0, 0);

   	// tslp_tsk(5000);

   	lcd_clear();
    int lineNumber = 0;
    lcd_print("EV3RT Performance Test", 0, lineNumber++);

//    testIdling(lineNumber++);
//    testSensorReading(lineNumber++);
//    testUniqueSensorReading(lineNumber++);
//    testEncoderReadingBC(lineNumber++);
    testPController4_2(lineNumber++);
}
