//*****************************************************************************
//
// HelicopterMain.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
//
//*****************************************************************************
// Based on the ADCdemo.c by P.J. Bones UCECE
// Which is based on the 'convert' series from 2016
//*****************************************************************************

#include "heliUART.h"
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
#include "driverlib/timer.h"
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
#include "adc.h"
#include "controller.h"
#include "kernal.h"


//*****************************************************************************
// The interrupt handler for the for SysTick interrupt.
//*****************************************************************************
void
SysTickIntHandler(void)
{
    //
    // Initiate a conversion
    //
    ADCProcessorTrigger(ADC0_BASE, 3); 
}


//*****************************************************************************
// Initialisation functions for the clock (incl. SysTick)
//*****************************************************************************
void
initClock (void)
{
    // Set the clock rate to 20 MHz
    SysCtlClockSet (SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    //
    // Set up the period for the SysTick timer.  The SysTick timer period is
    // set as a function of the system clock.
    SysTickPeriodSet(SysCtlClockGet() / SAMPLE_RATE_HZ);
    //
    // Register the interrupt handler
    SysTickIntRegister(SysTickIntHandler);
    //
    // Enable interrupt and device
    SysTickIntEnable();
    SysTickEnable();
}

//*****************************************************************************
// Main helicopter function
//*****************************************************************************
int main(void)
{

    // initialize modules
    initClock();
    initADC();
    initDisplay();
    initButtons();
    init_yaw();
    initRotor();
    controller_init();
    uart_init();


    // Enable interrupts to the processor.
    IntMasterEnable();

    // Call the background tasks via round robin based kernal
    while (1)
    {
        kernal_update();
    }
}
