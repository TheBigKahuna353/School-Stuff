//*****************************************************************************
//
// slider.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// Module for slider switch
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "inc/tm4c123gh6pm.h"  // Board specific defines (for PF0)
#include "slider.h"

int position; // 1 if slider is UP, 0 if DOWN

//*****************************************************************************
// Initialise the slider switch
//*****************************************************************************
void slider_init() {

    // RIGHT slider switch (active HIGH)
    SysCtlPeripheralEnable (SLIDER_BUT_PERIPH);
    GPIOPinTypeGPIOInput (SLIDER_BUT_PORT_BASE, SLIDER_BUT_PIN);
    GPIOPadConfigSet (SLIDER_BUT_PORT_BASE, SLIDER_BUT_PIN, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPD);
    slider_update();

}

//*****************************************************************************
// update the slider switch position
//*****************************************************************************
void slider_update() {
    position = GPIOPinRead(SLIDER_BUT_PORT_BASE, SLIDER_BUT_PIN) == SLIDER_BUT_PIN;
}

//*****************************************************************************
// return the slider switch position
//*****************************************************************************
int slider_check() {
    return position;
}
