/*
 *  Filename: sx1509b.c
 *  Author: Beau Roland
 * 
 *  Details: Source code for interacting with a sx1509b IO Expander
 */

#include "sx1509b.h"

// Declaring I2C DT Device connected to IO expander
static const struct i2c_dt_spec io_ex = I2C_DT_SPEC_GET(I2C_IO);

static uint8_t r_pin=0;
static uint8_t g_pin=0;
static uint8_t b_pin=0;
static uint8_t current_output_A = 0;

#define REG_IDX 0
#define REG_VAL_IDX 1
void io_ex_write(uint8_t regAddr, uint8_t regValue)
{
    uint8_t buffer[2];

    buffer[REG_IDX] = regAddr;
    buffer[REG_VAL_IDX] = regValue;
    i2c_write_dt(&io_ex, buffer, 2);
}

int init_io(io_cfg_t * cfg)
{
    uint8_t value;

    if (!device_is_ready(io_ex.bus)) {
        return DRV_ERROR;
    }

    r_pin = cfg->r_pin;
    g_pin = cfg->g_pin;
    b_pin = cfg->b_pin;

    // Each Led can operate in 1 of 3 modes
    //   - Static mode (available for all IOs)
    //   - Single shot mode (blinking capable IOs only)
    //   - Blink mode (blinking capable IOs only)
    // Configure our 3 pwm control IOs for leds to be static mode

    /**
     Steps to set up the pwm on the io expander:
    - Disable input buffer (RegInputDisable)
    - Disable pull-up (RegPullUp)
    - Enable open drain (RegOpenDrain)
    - Set direction to output (RegDir) – by default RegData is set high => LED OFF
    - Enable oscillator (RegClock)
    - Configure LED driver clock and mode if relevant (RegMisc)
    - Enable LED driver operation (RegLEDDriverEnable)
    - Configure LED driver parameters (RegTOn, RegIOn, RegOff, RegTRise, RegTFall)
    - Set RegData bit low => LED driver started 
    */

    // Disable Input Buffer
    // 0x01 RegInputDisableA (IOs 7-0)
    value = ((1 << r_pin) | (1 << g_pin) | (1 << b_pin)); // Disabling input on led pins on io
    io_ex_write(SX1509_REG_A_INPUT_DISABLE, value);

    // Disable pull-up
    // 0x07 RegPullUpA (IOs 7-0)
    io_ex_write(SX1509_REG_A_PULLUP, 0x00);

    // Enable Open Drain
    // Skipping, I don't think we want open drain enabled

    // Set direction to output
    // 0x0F RegDirA (IOs 7-0)
    // 0 = output
    io_ex_write(SX1509_REG_A_DIR, 0x00);

    // Enable oscillator
    // 0x1E RegClock
    value = (2 << 5); // 2Mhz internal clock for IOs selected
    io_ex_write(SX1509_REG_A_CLK, value);

    // Configure LED Driver clock and mode
    // 0x1F RegMisc
    value = (1 << 4); // Led driver clock on (ClkX of all IOs)
    io_ex_write(SX1509_REG_A_MISC, value);

    // Enable LED Driver Operation
    // 0x21 RegLEDDriverEnableA
    value = ((1 << r_pin) | (1 << g_pin) | (1 << b_pin)); // enable LED driver output on pins 5,6,7
    io_ex_write(SX1509_REG_A_LED_DRV_EN, value);

    // Configure LED Driver parameters
    // Leaving defaults for PIN 5,6,7
    // Leaving default for RegTOnX
    // Leaving default for RegIOnX
    // Leaving default for RegOffX
    // Leaving default for RegTRiseX
    // Leaving default for RegTFallX

    current_output_A = 0xFF;

    return DRV_SUCCESS;
}

int set_pwm(uint8_t r, uint8_t g, uint8_t b)
{
    int ret = DRV_SUCCESS;
    uint8_t value;

    // Set PWM intensity
    io_ex_write(SX1509_REG_I_ON_5, g);
    io_ex_write(SX1509_REG_I_ON_6, b);
    io_ex_write(SX1509_REG_I_ON_7, r);
    
    // Turn pwm on
    // Likewise, to turn the pwm on, we want to set the bit to 0.
    current_output_A &= ~((1 << r_pin) | (1 << g_pin) | (1 << b_pin));
    io_ex_write(0x11, current_output_A);

    return ret;
}