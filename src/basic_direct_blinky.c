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

#if defined(BASIC_DIRECT_BLINKY_APP)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
// static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(R_LED_NODE, gpios);
// static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(G_LED_NODE, gpios);
// static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(B_LED_NODE, gpios);

#define I2C_IO DT_NODELABEL(sx1509b)
static const struct i2c_dt_spec io_ex = I2C_DT_SPEC_GET(I2C_IO);

#define REG_IDX 0
#define REG_VAL_IDX 1
void io_ex_write(uint8_t regAddr, uint8_t regValue)
{
	uint8_t buffer[2];

	buffer[REG_IDX] = regAddr;
	buffer[REG_VAL_IDX] = regValue;
	i2c_write_dt(&io_ex, buffer, 2);
}

int init_io(void)
{
	uint8_t value;

	if (!device_is_ready(io_ex.bus)) {
		return APP_ERROR;
	}

	// Each Led can operate in 1 of 3 modes
	//   - Static mode (available for all IOs)
	//   - Single shot mode (blinking capable IOs only)
	//   - Blink mode (blinking capable IOs only)
	// Configure our 3 pwm control ios for leds to be static mode

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
	value = ((1 << 5) | (1 << 6) | (1 << 7)); // Disabling input on led pins on io
	io_ex_write(0x01, value);

	// Disable pull-up
	// 0x07 RegPullUpA (IOs 7-0)
	io_ex_write(0x07, 0x00);

	// Enable Open Drain
	// Skipping, I don't think we want open drain enabled

	// Set direction to output
	// 0x0F RegDirA (IOs 7-0)
	// 0 = output
	io_ex_write(0x0F, 0x00);

	// Enable oscillator
	// 0x1E RegClock
	value = (2 << 5); // 2Mhz internal clock for IOs selected
	io_ex_write(0x1E, value);

	// Configure LED Driver clock and mode
	// 0x1F RegMisc
	value = (1 << 4); // Led driver clock on (ClkX of all IOs)
	io_ex_write(0x1F, value);

	// Enable LED Driver Operation
	// 0x21 RegLEDDriverEnableA
	value = ((1 << 5) | (1 << 6) | (1 << 7)); // enable LED driver output on pins 5,6,7
	io_ex_write(0x21, value);

	// Configure LED Driver parameters
	// Leaving defaults for PIN 5,6,7
	// Leaving default for RegTOnX
	// Leaving default for RegIOnX
	// Leaving default for RegOffX
	// Leaving default for RegTRiseX
	// Leaving default for RegTFallX

	return APP_SUCCESS;
}

int set_pwm(uint8_t r, uint8_t g, uint8_t b)
{
	int ret = APP_SUCCESS;
	uint8_t value;

	// turn pwm off
	// Setting RegData for a bit to 0 turns the output on. So we need to set the bit(s) to 1 to be off.
	value = ((1 << 5) | (1 << 6) | (1 << 7)); // Set outputs on for the pins connected to our leds
	io_ex_write(0x11, value);

	// Set PWM intensity
	io_ex_write(0x3B, g);
	io_ex_write(0x40, b);
	io_ex_write(0x45, r);
	
	// turn pwm on
	// Likewise, to turn the pwm on, we want to set the bit to 0.
	io_ex_write(0x11, 0);

	return ret;
}

void basic_direct_blinky_app(void)
{
    /*  basic_direct_blink_app
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
		{135, 0, 0},
		{200, 0, 0},
		{255, 0, 0}
	};

	ret = init_io();
	if (ret != APP_SUCCESS)
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