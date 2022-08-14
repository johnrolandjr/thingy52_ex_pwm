/*
 *  Filename: basic_blinky.c
 *  Author: Beau Roland
 * 
 *  Details: Source code for basic blinky application
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include "applications.h"

#if defined(BASIC_BLINKY_APP)
/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(R_LED_NODE, gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(G_LED_NODE, gpios);
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(B_LED_NODE, gpios);

int init_rgb_leds(void)
{
    int ret;

    if (!device_is_ready(red_led.port)) {
        return APP_ERROR;
    }

    ret = gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return APP_ERROR;
    }
    gpio_pin_set_dt(&red_led, 0);

    ret = gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return APP_ERROR;
    }
    gpio_pin_set_dt(&green_led, 0);

    ret = gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return APP_ERROR;
    }
    gpio_pin_set_dt(&blue_led, 0);

    return APP_SUCCESS;
}

void basic_blinky_app(void)
{
    int ret;

    ret = init_rgb_leds();

    /*  basic_blink_app
        Never ending application that toggles the leds to create different colors.
    */
    while (1) {
        gpio_pin_toggle_dt(&red_led);
        gpio_pin_toggle_dt(&green_led);
        gpio_pin_toggle_dt(&blue_led);
        k_msleep(SLEEP_TIME_MS);
    }
}
#endif // BASIC_BLINKY_APP
