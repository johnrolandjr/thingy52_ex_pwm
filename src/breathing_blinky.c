/*
 *  Filename: basic_blinky.c
 *  Author: Beau Roland
 * 
 *  Details: Source code for basic blinky application
 */

#include "applications.h"
#include "sx1509b.h"

#if defined(SINGLE_SHOT_BLINKY_APP)
int single_shot_blinky_app(void)
{
    /*  single_shot_blinky_app
        Never ending application that uses the single shot mode on the io expander to control the leds.
    */
    int ret;

    io_cfg_t io_cfg;
    io_cfg.r_pin = R_IO_PIN;
    io_cfg.g_pin = G_IO_PIN;
    io_cfg.b_pin = B_IO_PIN;
    led_mode_param_t common_led_params;
    /*
       Breathing Mode means TOnX != 0 and TOffX = 0
       t_on formula:
       0 -> static mode only
       1-15 -> t_on * 64 * 255 / 2000000 = in seconds
       16-31 -> t_on * 512 * 255 / 2000000 = in seconds
    */
    common_led_params.t_on = 4;  // 16 -> 1.0445s on time
    common_led_params.t_rise = 0; // not going to do fade but, it's available
    common_led_params.t_fall = 0; // not going to do fade but, it's available
    common_led_params.off_b.t_off = 0; // 0 -> single shot mode
    common_led_params.off_b.i_off = 0; // Doesn't necessarily have to be all the way off to be off...
    io_cfg.r_params = &common_led_params;
    io_cfg.g_params = &common_led_params;
    io_cfg.b_params = &common_led_params;

    ret = init_io(&io_cfg);
    if (ret != DRV_SUCCESS)
    {
        return ret;
    }

    // Set the color
    io_set_intensity(R_IO_PIN, 10);
    io_set_intensity(G_IO_PIN, 10);
    io_set_intensity(B_IO_PIN, 10);

    while(true){
        io_start_single_shot();
        k_msleep(SLEEP_TIME_MS);
    }
}
#endif // SINGLE_SHOT_BLINKY_APP

#if defined(BREATHING_BLINKY_APP)
int breathing_blinky_app(void)
{
    /*  breathing_blinky_app
        Never ending application that uses the breathing mode on the io expander to control the leds.
    */
    int ret;

    io_cfg_t io_cfg;
    io_cfg.r_pin = R_IO_PIN;
    io_cfg.g_pin = G_IO_PIN;
    io_cfg.b_pin = B_IO_PIN;
    led_mode_param_t common_led_params;
    /*
     Breathing Mode means TOnX !=0 and TOffX != 0
     t_on and t_off formula
       0 -> static mode only
       1-15 -> t_on * 64 * 255 / 2000000 = in seconds
       16-31 -> t_on * 512 * 255 / 2000000 = in seconds
    */
    common_led_params.t_on = 16;  // 16 -> 1.0445s on time
    common_led_params.t_rise = 16; // fade on
    common_led_params.t_fall = 20; // fade off
    common_led_params.off_b.t_off = 31; // != 0 -> breathing mode. (31 = 2.024s)
    common_led_params.off_b.i_off = 0; // Doesn't necessarily have to be all the way off to be off...
    io_cfg.r_params = &common_led_params;
    io_cfg.g_params = &common_led_params;
    io_cfg.b_params = &common_led_params;

    ret = init_io(&io_cfg);
    if (ret != DRV_SUCCESS)
    {
        return ret;
    }

    // Set the color
    io_set_intensity(R_IO_PIN, 0);
    io_set_intensity(G_IO_PIN, 10);
    io_set_intensity(B_IO_PIN, 10);

    io_start_breathing();

    while(true){}
}
#endif // BREATHING_BLINKY_APP