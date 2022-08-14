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
    uint8_t t_rise;
    uint8_t t_on;
    uint8_t t_fall;
    union
    {
        uint8_t off;
        struct{
            uint8_t i_off : 3; // bits 0:2
            uint8_t t_off : 5; // bits 3:7
        } off_b;
    };
    uint8_t i_on;
} led_mode_param_t;
typedef struct
{
    uint8_t r_pin;
    uint8_t g_pin;
    uint8_t b_pin;
    led_mode_param_t * r_params;
    led_mode_param_t * g_params;
    led_mode_param_t * b_params;
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
#define SX1509_REG_A_PULLUP 0x07
#define SX1509_REG_A_PULLDOWN 0x00
#define SX1509_REG_A_POLARITY 0x00
#define SX1509_REG_A_DIR 0x0F
#define SX1509_REG_A_CLK 0x1E
#define SX1509_REG_A_MISC 0x1F
#define SX1509_REG_A_LED_DRV_EN 0x21

#define SX1509_REG_T_ON_5 0x3A
#define SX1509_REG_I_ON_5 0x3B
#define SX1509_REG_OFF_5 0x3C
#define SX1509_REG_T_RISE_5 0x3D
#define SX1509_REG_T_FALL_5 0x3E

#define SX1509_REG_T_ON_6 0x3F
#define SX1509_REG_I_ON_6 0x40
#define SX1509_REG_OFF_6 0x41
#define SX1509_REG_T_RISE_6 0x42
#define SX1509_REG_T_FALL_6 0x43

#define SX1509_REG_T_ON_7 0x44
#define SX1509_REG_I_ON_7 0x45
#define SX1509_REG_OFF_7 0x46
#define SX1509_REG_T_RISE_7 0x47
#define SX1509_REG_T_FALL_7 0x48


// Function Prototypes
void io_ex_write(uint8_t regAddr, uint8_t regValue);
int set_led_params(uint8_t pin, led_mode_param_t * params);
int init_io(io_cfg_t * cfg);
int set_pwm(uint8_t r, uint8_t g, uint8_t b);
void io_set_intensity(uint8_t pin, uint8_t intensity);
void io_start_single_shot(void);
void io_start_breathing(void);
void io_stop_breathing(void);

#endif // DRV_SX1509B_H