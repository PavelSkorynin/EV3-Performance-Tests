#include "ev3api.h"
#include "app.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int32_t default_menu_font_width;
int32_t default_menu_font_height;

SYSTIM TimerMS() {
    SYSTIM tim;
    get_tim(&tim);
    return tim;
}

static void lcd_clear() {
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
}

static void lcd_print(const char *s, int x, int y) {
    // Get font information
    int32_t fontw, fonth;
    ev3_font_get_size(MENU_FONT, &fontw, &fonth);

    ev3_lcd_draw_string(s, 0, default_menu_font_height + y * (fonth + 2));
}


void main_task(intptr_t unused) {
    ev3_lcd_set_font(MENU_FONT);
    ev3_sensor_config(EV3_PORT_1, COLOR_SENSOR);
    lcd_print("Configuring Sensor...", 0, 0);

    tslp_tsk(5000);

    lcd_clear();
    lcd_print("Performance Test EV3RT", 0, 0);
    const int TEXT_SIZE = 128;
    char text[TEXT_SIZE];

    // test idling
    SYSTIM start_time = TimerMS();
    int count = 0;
    while (count < 1000000000) {
        count++;
    }
    SYSTIM duration = TimerMS() - start_time;
    snprintf(text, TEXT_SIZE, "%ld", duration);
    lcd_print(text, 0, 1);

    // test reading a sensor
    start_time = TimerMS();
    count = 0;
    int sum = 0;
    while (TimerMS() - start_time < 5000) {
        sum += ev3_color_sensor_get_reflect(EV3_PORT_1);
        count++;
    }
    snprintf(text, TEXT_SIZE, "%d %d", count / 5, sum);
    lcd_print(text, 0, 2);

    // test reading unique values from a sensor
    start_time = TimerMS();
    count = 0;
    int unique = 0;
    int prevValue = 0;
    while (TimerMS() - start_time < 5000) {
        int value = ev3_color_sensor_get_reflect(EV3_PORT_1);
        if (prevValue != value && value != 0) {
            prevValue = value;
            unique++;
        }
        count++;
    }
    snprintf(text, TEXT_SIZE, "%d %d", count / 5, unique / 5);
    lcd_print(text, 0, 3);
}