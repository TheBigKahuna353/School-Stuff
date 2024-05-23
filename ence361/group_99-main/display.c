//*****************************************************************************
//
// display.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// OLED display functions
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "utils/ustdlib.h"
#include "circBufT.h"
#include "OrbitOLED/OrbitOLEDInterface.h"
#include "buttons4.h"
#include "yaw.h"
#include "helpers.h"
#include "RotorControl.h"
#include "state.h"
#include "display.h"
#include "controller.h"
#include "adc.h"
#include "slider.h"


//*****************************************************************************
// initialize OLED display
//*****************************************************************************
void initDisplay (void)
{
    
    OLEDInitialise ();
}


//*****************************************************************************
// updates OLED display with helicopter information
//*****************************************************************************
void display_update()
{
    char string[17];  // 16 characters across the display

    usnprintf(string, sizeof(string), "alt: %3d%%", get_adc());
    OLEDStringDraw(string, 0, 0);

    usnprintf(string, sizeof(string), "yaw: %4d  ", get_yaw());
    OLEDStringDraw(string, 0, 1);

    usnprintf(string, sizeof(string), "Main Duty: %3d%%  ", getMainDuty());
    OLEDStringDraw(string, 0, 2);

    usnprintf(string, sizeof(string), "Tail Duty: %3d%%  ", getTailDuty());
    OLEDStringDraw(string, 0, 3);
}
