#pragma once

#include "ev3api.h"

#define MAIN_PRIORITY	5
#define HIGH_PRIORITY	9
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

#ifndef STACK_SIZE
#define	STACK_SIZE		4096
#endif

#ifndef TOPPERS_MACRO_ONLY

#include <stdio.h>

/**
 * Default font
 */
extern int32_t default_menu_font_width;
extern int32_t default_menu_font_height;
#define MENU_FONT (EV3_FONT_MEDIUM)
#define MENU_FONT_WIDTH (default_menu_font_width)
#define MENU_FONT_HEIGHT (default_menu_font_height)

/**
 * Tasks
 */

extern void	main_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */
