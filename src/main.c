/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "applications.h"

void main(void)
{
#if defined(BASIC_BLINKY_APP)
	basic_blinky_app();
#endif // BASIC_BLINKY_APP

#if defined(BASIC_DIRECT_BLINKY_APP)
	basic_direct_blinky_app();
#endif // BASIC_BLINKY_APP

#if defined(PWM_BLINKY_APP)
    pwm_blinky_app();
#endif // PWM_BLINKY_APP

	// Safe guard, we should never get here.
	while(1){}
}
