/*
 *  Filename: breathing_blinky.h
 *  Author: Beau Roland
 * 
 *  Details: Header file for the breathing blinky application
 */

#ifndef BREATHING_BLINKY_H
#define BREATHING_BLINKY_H

#include <stdint.h>

// Macros and String Literals

#define SLEEP_TIME_MS   1000

#define APP_SUCCESS 	(0)
#define APP_ERROR 	    (-1)

// Function Prototypes
int single_shot_blinky_app(void);
int breathing_blinky_app(void);

#endif // BREATHING_BLINKY_H