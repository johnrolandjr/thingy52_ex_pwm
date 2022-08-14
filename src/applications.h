/*
 *  Filename: application.h
 *  Author: Beau Roland
 * 
 *  Details: Header file that describes different setup and main entry points.
 */

#ifndef APPLICATIONS_H
#define APPLICATIONS_H

// Select which application by uncommenting a line
#define BASIC_BLINKY_APP
//#define BASIC_DIRECT_BLINKY_APP
//#define SINGLE_SHOT_BLINKY_APP
//#define BREATHING_BLINKY_APP

#if defined(BASIC_BLINKY_APP)
    #include "basic_blinky.h"
#endif // BASIC_BLINKY_APP

#if defined(BASIC_DIRECT_BLINKY_APP)
    #include "basic_direct_blinky.h"
#endif // BASIC_DIRECT_BLINKY_APP

#if defined(SINGLE_SHOT_BLINKY_APP) || defined(BREATHING_BLINKY_APP)
    #include "breathing_blinky.h"
#endif // SINGLE_SHOT_BLINKY_APP

#endif // APPLICATIONS_H