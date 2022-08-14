/*
 *  Filename: basic_blinky.c
 *  Author: Beau Roland
 * 
 *  Details: Source code for basic blinky application
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/i2c.h>
#include "applications.h"
#include "sx1509b.h"

#if defined(BASIC_DIRECT_BLINKY_APP)

//static const struct i2c_dt_spec io_ex = I2C_DT_SPEC_GET(I2C_IO);

void basic_direct_blinky_app(void)
{
    /*  basic_direct_blinky_app
        Never ending application that toggles the leds to create different colors.
        Uses the sx1509 io expander library directly. (we will need to be able to do this if we want to write our own code that uses the io expander)
        i.e. we want to be able to control a stepper motor via the io expander.
    */
    int ret;
    int i = 0;
    uint8_t r, g, b;
    uint8_t colors[NUM_COLORS][NUM_LEDS] = {
        {0, 0, 0},
        {10, 0, 0},
        {25, 0, 0},
        {45, 0, 0},
        {85, 0, 0},
        {115, 0, 0},
        {150, 0, 0},
        {50, 50, 50}
    };

    io_cfg_t io_cfg;
    io_cfg.r_pin = R_IO_PIN;
    io_cfg.g_pin = G_IO_PIN;
    io_cfg.b_pin = B_IO_PIN;
    led_mode_param_t common_led_params;
    /*
     Static mode means TOnX =0
    */
    common_led_params.t_on = 0;  // 16 -> 1.0445s on time
    common_led_params.t_rise = 0; // fade on
    common_led_params.t_fall = 0; // fade off
    common_led_params.off_b.t_off = 0; // != 0 -> breathing mode. (31 = 2.024s)
    common_led_params.off_b.i_off = 0; // Doesn't necessarily have to be all the way off to be off...
    io_cfg.r_params = &common_led_params;
    io_cfg.g_params = &common_led_params;
    io_cfg.b_params = &common_led_params;
    ret = init_io(&io_cfg);
    if (ret != DRV_SUCCESS)
    {
        return ret;
    }

    while(true){
        r = colors[i][R_IDX];
        g = colors[i][G_IDX];
        b = colors[i][B_IDX];
        i = i + 1;
    
        set_pwm(r, g, b);
        k_msleep(SLEEP_TIME_MS);

        if (i >= NUM_COLORS)
        {
            i=0;

            // For fun, if we reached the end of our colors, wait a bit before repeating the process
            k_msleep(500);
        }
    }
}
#endif // BASIC_DIRECT_BLINKY_APP