//*****************************************************************************
//
// RotorControl.c 
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// Control the main and tail rotors of the helicopter
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

#include "driverlib/pin_map.h" //Needed for pin configure


int freq = 200;

int main_duty = 0;
int tail_duty = 0;

//*****************************************************************************
// set power of main rotor
//*****************************************************************************
void setMainRotor(int duty) {

    duty = clamp(duty, 0, 68);
    int period = SysCtlClockGet() / 1 / freq;
    PWMGenPeriodSet(MAIN_ROTOR_BASE, MAIN_ROTOR_GEN, period);

    int width = period * duty / 100;

    PWMPulseWidthSet(MAIN_ROTOR_BASE, PWM_OUT_7, width);

    main_duty = duty;
}

//*****************************************************************************
// set power of tail rotor
//*****************************************************************************
void setTailRotor(int duty) {

    duty = clamp(duty, 0, 68);

    int period = SysCtlClockGet() / 1 / freq;
    PWMGenPeriodSet(TAIL_ROTOR_BASE, TAIL_ROTOR_GEN, period);

    uint32_t width = duty * period / 100;

    PWMPulseWidthSet(TAIL_ROTOR_BASE, PWM_OUT_5, width);

    tail_duty = duty;
}

//*****************************************************************************
// turn main rotor on
//*****************************************************************************
void MainRotorOn() {
    PWMOutputState(MAIN_ROTOR_BASE, PWM_OUT_7_BIT, true);
}

//*****************************************************************************
// turn main rotor off
//*****************************************************************************
void MainRotorOff() {
    PWMOutputState(MAIN_ROTOR_BASE, PWM_OUT_7_BIT, false);
    main_duty = 0;
}

//*****************************************************************************
// turn tail rotor on
//*****************************************************************************
void TailRotorOn() {
    PWMOutputState(TAIL_ROTOR_BASE, PWM_OUT_5_BIT, true);
}

//*****************************************************************************
// turn tail rotor off
//*****************************************************************************
void TailRotorOff() {
    PWMOutputState(TAIL_ROTOR_BASE, PWM_OUT_5_BIT, false);
    tail_duty = 0;
}

//*****************************************************************************
// get duty cycle of main rotor
//*****************************************************************************
int getMainDuty() {
    return main_duty;
}

//*****************************************************************************
// get duty cycle of tail rotor
//*****************************************************************************
int getTailDuty() {
    return tail_duty;
}

//*****************************************************************************
// initialise pwm for main and tail rotors
//*****************************************************************************
void initRotor() {

    SysCtlPeripheralEnable(MAIN_ROTOR_PERIPH);
    SysCtlPeripheralEnable(MAIN_PERIPH_GPIO);
    SysCtlPeripheralEnable(TAIL_ROTOR_PERIPH);
    SysCtlPeripheralEnable(TAIL_PERIPH_GPIO);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    GPIOPinTypePWM(MAIN_GPIO_BASE, MAIN_GPIO_PIN);
    GPIOPinTypePWM(TAIL_GPIO_BASE, TAIL_GPIO_PIN);

    GPIOPinConfigure(MAIN_GPIO_CONFIG);
    GPIOPinConfigure(TAIL_GPIO_CONFIG);

    PWMGenConfigure(MAIN_ROTOR_BASE, MAIN_ROTOR_GEN, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(TAIL_ROTOR_BASE, TAIL_ROTOR_GEN, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    setMainRotor(0);   //default
    setTailRotor(0);   //default

    PWMGenEnable(MAIN_ROTOR_BASE, MAIN_ROTOR_GEN);
    PWMGenEnable(TAIL_ROTOR_BASE, TAIL_ROTOR_GEN);

    PWMOutputState(MAIN_ROTOR_BASE, PWM_OUT_7_BIT, false);
    PWMOutputState(TAIL_ROTOR_BASE, PWM_OUT_5_BIT, false);

}









