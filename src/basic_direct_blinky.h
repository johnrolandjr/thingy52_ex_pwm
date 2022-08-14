/*
 *  Filename: basic_direct_blinky.h
 *  Author: Beau Roland
 * 
 *  Details: Header file for the basic direct blinky application
 */

#ifndef BASIC_DIRECT_BLINKY_H
#define BASIC_DIRECT_BLINKY_H

#include <stdint.h>

// Macros and String Literals

#define SLEEP_TIME_MS   50

#define NUM_COLORS	8
#define NUM_LEDS 	3

#define R_IDX 0
#define G_IDX 1
#define B_IDX 2

#define APP_SUCCESS 	(0)
#define APP_ERROR 	    (-1)

// Function Prototypes
void basic_direct_blinky_app(void);

#endif // BASIC_DIRECT_BLINKY_H