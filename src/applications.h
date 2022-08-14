/*
 *  Filename: application.h
 *  Author: Beau Roland
 * 
 *  Details: Header file that describes different setup and main entry points.
 */

#ifndef APPLICATIONS_H
#define APPLICATIONS_H

// Select which application by uncommenting a line
//#define BASIC_BLINKY_APP
#define BASIC_DIRECT_BLINKY_APP
//#define PWM_BLINKY_APP

#if defined(BASIC_BLINKY_APP)
    #include "basic_blinky.h"
#endif // BASIC_BLINKY_APP

#if defined(BASIC_DIRECT_BLINKY_APP)
    #include "basic_direct_blinky.h"
#endif // BASIC_DIRECT_BLINKY_APP

#if defined(PWM_BLINKY_APP)
    //#include "pwm_blinky.h"
#endif // PWM_BLINKY_APP

#endif // APPLICATIONS_H