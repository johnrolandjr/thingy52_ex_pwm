/*
 *  Filename: basic_blinky.h
 *  Author: Beau Roland
 * 
 *  Details: Header file for the basic blinky application
 */

#ifndef BASIC_BLINKY_H
#define BASIC_BLINKY_H

// Macros and String Literals
#define SLEEP_TIME_MS   200

/* The devicetree node identifier for the "led0" alias. */
#define R_LED_NODE DT_ALIAS(led0)
#define G_LED_NODE DT_ALIAS(led1)
#define B_LED_NODE DT_ALIAS(led2)

#define APP_SUCCESS 	(0)
#define APP_ERROR 	    (-1)

// Function Prototypes
void basic_blinky_app(void);

#endif // BASIC_BLINKY_H