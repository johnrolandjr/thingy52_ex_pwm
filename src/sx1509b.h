/*
 *  Filename: sx1509b.h
 *  Author: Beau Roland
 * 
 *  Details: Header file for the basic direct blinky application
 */

#include <zephyr.h>
#include <drivers/i2c.h>

#ifndef DRV_SX1509B_H
#define DRV_SX1509B_H

typedef struct
{
    uint8_t r_pin;
    uint8_t g_pin;
    uint8_t b_pin;
} io_cfg_t;

// Macros and String Literals

/* The devicetree node identifier for the io expander that is available on the i2c0 bus. */
#define I2C_IO DT_NODELABEL(sx1509b)

#define R_IO_PIN    7
#define G_IO_PIN    5
#define B_IO_PIN    6

#define DRV_SUCCESS 0
#define DRV_ERROR   1

// Register Addresses
#define SX1509_REG_A_INPUT_DISABLE 0x01
#define SX1509_REG_A_LONG_SLEW 0x00
#define SX1509_REG_A_LOW_DRIVE 0x00
#define SX1509_REG_A_PULLUP 0x07
#define SX1509_REG_A_PULLDOWN 0x00
#define SX1509_REG_A_OPEN_DRAIN 0x00
#define SX1509_REG_A_POLARITY 0x00
#define SX1509_REG_A_DIR 0x0F
#define SX1509_REG_A_DATA 0x00
#define SX1509_REG_A_INTERRUPT_MASK 0x00
#define SX1509_REG_A_SENSE_HIGH 0x00
#define SX1509_REG_A_SENSE_LOW 0x00
#define SX1509_REG_A_INTERRUPT_SRC 0x00
#define SX1509_REG_A_EVENT_STS 0x00
#define SX1509_REG_A_LVL_SHIFTER 0x00
#define SX1509_REG_A_CLK 0x1E
#define SX1509_REG_A_MISC 0x1F
#define SX1509_REG_A_LED_DRV_EN 0x21

#define SX1509_REG_I_ON_5 0x3B
#define SX1509_REG_I_ON_6 0x40
#define SX1509_REG_I_ON_7 0x45

// Function Prototypes
void io_ex_write(uint8_t regAddr, uint8_t regValue);
int init_io(io_cfg_t * cfg);
int set_pwm(uint8_t r, uint8_t g, uint8_t b);

#endif // DRV_SX1509B_H