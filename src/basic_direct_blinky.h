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

/* The devicetree node identifier for the io expander that is available on the i2c0 bus. */
#define I2C_IO DT_NODELABEL(sx1509b)

#define SLEEP_TIME_MS   50

#define NUM_COLORS	8
#define NUM_LEDS 	3

#define R_IDX 0
#define G_IDX 1
#define B_IDX 2

#define APP_SUCCESS 	(0)
#define APP_ERROR 	    (-1)

// Function Prototypes
void io_ex_write(uint8_t regAddr, uint8_t regValue);
int init_io(void);
int set_pwm(uint8_t r, uint8_t g, uint8_t b);
void basic_direct_blinky_app(void);

#endif // BASIC_DIRECT_BLINKY_H