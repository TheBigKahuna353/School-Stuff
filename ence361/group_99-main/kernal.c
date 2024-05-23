//*****************************************************************************
//
// kernal.c
//
// Helicopter Project
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// round robin scheduling for background tasks
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



// frame counters for each task
int display_count = 0;

int uart_count = 0;

int state_count = 0;

int button_count = 0;


//*****************************************************************************
// updates the kernal, performs round robin scheduling for background tasks
//*****************************************************************************
void kernal_update() {
    if (button_count++ >= BUTTON_FREQ) {
        updateButtons();
        button_count = 0;
    }
    if (state_count++ >= STATE_FREQ) {
        update();
    }

    if (display_count++ >= DISPLAY_FREQ) {
        display();
        display_count = 0;
    }
    if (uart_count++ >= UART_FREQ) {
        uart_update();
        uart_count = 0;
    }

    SysCtlDelay (SysCtlClockGet() / LOOP_FREQ);   // delay

}


