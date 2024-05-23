//*****************************************************************************
//
// yaw.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// yaw reference and quadrature encoder function for helicopter yaw
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
#include "helpers.h"
#include "yaw.h"
#include "controller.h"


int yaw;
int current_state;

bool onRef = false;

//*****************************************************************************
// get the output state from quadrature encoder
//*****************************************************************************
int getStates() {
    uint32_t a = GPIOPinRead(GPIO_PORTB_BASE, YAW_CHA_PIN) & YAW_CHA_PIN;
    uint32_t b = GPIOPinRead(GPIO_PORTB_BASE, YAW_CHB_PIN) /2;

    return a*10 + b;
}

//*****************************************************************************
// Intterupt handler for yaw
//*****************************************************************************
void YAWIntHandler (void) {
    GPIOIntClear (GPIO_PORTB_BASE, GPIO_INT_PIN_0);
    GPIOIntClear (GPIO_PORTB_BASE, YAW_CHB_PIN);
    int next = getStates();
    if (current_state == 00) {
        if (next == 01) {
            // clockwise
            yaw++;
        } else if (next == 10) {
            // anti clockwise
            yaw--;
        }
    } else if (current_state == 10) {
        if (next == 00) {
            //clockwise
            yaw++;
        } else if (next == 11) {
            // anti clockwise
            yaw--;
        } 
    } else if (current_state == 01) {
        if (next == 11) {
            //clockwise
            yaw++;
        } else if (next == 00) {
            //anti clockwise
            yaw--;
        }
    } else if (current_state == 11) {
        if (next == 10) {
            //clockwise
            yaw++;
        } else if (next == 01) {
            //anti clockwise
            yaw--;
        }
    }
    if (yaw < -MAX_STEPS/2) {yaw += MAX_STEPS;}
    else if (yaw > MAX_STEPS/2) {yaw -= MAX_STEPS;}
    current_state = next;

}

//*****************************************************************************
// interupt handler for yaw reference
//*****************************************************************************
void YawRefHandler() {
    GPIOIntClear (GPIO_PORTC_BASE, YAW_REF_PIN);
    onRef = true;

}

//*****************************************************************************
// return true if helicopter is on the yaw reference
//*****************************************************************************
bool get_ref() {
    return onRef;
}

//*****************************************************************************
// called when calibrating yaw, sets yaw to 0 
//*****************************************************************************
void calibrate_yaw() {
    yaw = 0;
}

//*****************************************************************************
// initialize the yaw reference peripheral
//*****************************************************************************
void init_yaw_ref() {
    SysCtlPeripheralEnable(YAW_REF_PERIPH);

    GPIOIntRegister(YAW_REF_BASE, YawRefHandler);

    GPIOPinTypeGPIOInput (YAW_REF_BASE, YAW_REF_PIN);

    GPIOPadConfigSet (YAW_REF_BASE, YAW_REF_PIN, GPIO_STRENGTH_2MA,
           GPIO_PIN_TYPE_STD_WPD);

    GPIOIntTypeSet (YAW_REF_BASE, YAW_REF_PIN, GPIO_BOTH_EDGES);

    GPIOIntEnable(YAW_REF_BASE, YAW_REF_PIN);

    IntEnable (INT_GPIOC);
}


//*****************************************************************************
// initialize the yaw peripherals
//*****************************************************************************
void init_yaw(void) {

    yaw = 0;

    SysCtlPeripheralEnable(YAW_PERIPH);

    GPIOIntRegister(YAW_BASE, YAWIntHandler);
    GPIOIntRegister(YAW_BASE, YAWIntHandler);

    GPIOPinTypeGPIOInput (YAW_BASE, YAW_CHA_PIN);
    GPIOPinTypeGPIOInput (YAW_BASE, YAW_CHB_PIN);

    GPIOPadConfigSet (YAW_BASE, YAW_CHA_PIN, GPIO_STRENGTH_2MA,
           GPIO_PIN_TYPE_STD_WPD);
    GPIOPadConfigSet (YAW_BASE, YAW_CHB_PIN, GPIO_STRENGTH_2MA,
           GPIO_PIN_TYPE_STD_WPD);

    GPIOIntTypeSet (YAW_BASE, YAW_CHA_PIN, GPIO_BOTH_EDGES);
    GPIOIntTypeSet (YAW_BASE, YAW_CHB_PIN, GPIO_BOTH_EDGES);

    GPIOIntEnable(YAW_BASE, YAW_CHA_PIN);
    GPIOIntEnable(YAW_BASE, YAW_CHB_PIN);

    IntEnable (INT_GPIOB);

    current_state = getStates();

    init_yaw_ref();
}

//*****************************************************************************
// return the yaw value in degrees
//*****************************************************************************
int get_yaw() {
    return (yaw*360)/(MAX_STEPS);
}

