//*****************************************************************************
//
// controller.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// PID control of helicopter Altitude and Yaw
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
#include "driverlib/timer.h"
#include "driverlib/debug.h"
#include "utils/ustdlib.h"
#include "circBufT.h"
#include "OrbitOLED/OrbitOLEDInterface.h"
#include "buttons4.h"
#include "yaw.h"
#include "helpers.h"
#include "RotorControl.h"
#include "controller.h"
#include "adc.h"


double desired_yaw;
double desired_alt;

static double e_int_a = 0.0; // integral error, alt
static double e_prev_a = 0.0; // previous error for derivative, alt

static double e_int_y = 0.0; // integral error, yaw
static double e_prev_y = 0.0; // previous error for derivative, yaw


double MAX_DUTY = 70; // maximum allowable duty cyle for both rotors
double MIN_DUTY_MAIN = 10; // minimum allowable duty cycle for main rotor
double MIN_DUTY_TAIL = 5; // minimum allowable duty cycle for tail rotor

bool usePID = false; // used for disabling PID controller on startup

bool isLanding = false;

//*****************************************************************************
// PID controller for calculating the duty cycle of yaw based on current value 
// of yaw and desired value of yaw
//*****************************************************************************
double update_yaw() {
    double control;
    double e_deriv;

    double error = desired_yaw - get_yaw();

    if (error > 180) {error -= 360;}
    if (error < -180) {error += 360;}

    double new_e_int = e_int_y + error;
    e_deriv = (error - e_prev_y);

    control = error * p_gain_y + new_e_int * i_gain_y + e_deriv * d_gain_y;

    e_prev_y = error;

    // used to prevent intergal windup
    if (control > MAX_DUTY) {
        control = MAX_DUTY;
    } else if (control < MIN_DUTY_TAIL) {
        control = MIN_DUTY_TAIL;
    } else {
        e_int_y = new_e_int;
    }

    return control;
}

//*****************************************************************************
// PID controller for calculating the duty cycle of altitude based on current 
// value of altitude and desired value of altitude
//*****************************************************************************
double update_alt() {
    double control;
    double e_deriv;

    double error = desired_alt - get_adc();

    double new_e_int = e_int_a + error;
    e_deriv = (error - e_prev_a);

    control = error * p_gain_a + new_e_int * i_gain_a + e_deriv * d_gain_a;

    e_prev_a = error;

    //used to prevent intergal windup
    if (control > MAX_DUTY && error > 0) {
        control = MAX_DUTY;
    } else if (control < MIN_DUTY_MAIN && error < 0) {
        control = MIN_DUTY_MAIN;
    } else {
        e_int_a = new_e_int;
    }

    return control;
}

//*****************************************************************************
// resets the intergral error of yaw to help prevent overshoot when calibrating
//*****************************************************************************
void resetErrorYaw() {
    e_int_y = 0;
}

//*****************************************************************************
// interrupt handler for PID controller
//*****************************************************************************
void controllerInt() {
    TimerIntClear(TIMER_BASE, TIMER_INT_MODE);
    double alt = update_alt();
    double yaw = update_yaw();
    if (isLanding) {
        alt = 10;
    }
    if (usePID) {
        setTailRotor((int) yaw);
        setMainRotor((int) alt);
    }
}

//*****************************************************************************
// settting the desired yaw value
//*****************************************************************************
void setDYaw(double val) {
    desired_yaw = val;
    if (desired_yaw > 180) {
        desired_yaw -= 360;
    }
    if (desired_yaw < -180) {
        desired_yaw += 360;
    }
}

//*****************************************************************************
// settting the desired altitude value
//*****************************************************************************
void setDAlt(double val) {
    desired_alt = val;
    desired_alt = clamp(desired_alt, 0, 100);
}

//*****************************************************************************
// adds past value to current altitude
//*****************************************************************************
void addAlt(double val) {
    desired_alt += val;
    desired_alt = clamp(desired_alt, 10, 100);
}

//*****************************************************************************
// adds past value to current yaw
//*****************************************************************************
void addYaw(double val) {
    desired_yaw += val;

    // kepps yaw values within range
    if (desired_yaw > 180) {
        desired_yaw -= 360;
    }
    if (desired_yaw < -180) {
        desired_yaw += 360;
    }
}

//*****************************************************************************
// get the desired yaw value
//*****************************************************************************
int getDYaw() {
    return desired_yaw;
}

//*****************************************************************************
// gets the desired altitude value
//*****************************************************************************
int getDAlt() {
    return desired_alt;
}

//*****************************************************************************
// enables PID controller interrupt when called
//*****************************************************************************
void enableInt() {
    usePID = true;
}

//*****************************************************************************
// disables PID controller interrupt when called
//*****************************************************************************
void disableInt() {
    usePID = false;
}

//*****************************************************************************
// initialize timer module used for PID controller
//*****************************************************************************
void controller_init() {
    desired_yaw = 0;
    desired_alt = 0;

    SysCtlPeripheralEnable(TIMER_PERIPH);

    TimerConfigure(TIMER_BASE, TIMER_CFG_PERIODIC);

    TimerIntRegister(TIMER_BASE,TIMER_MODULE, controllerInt);

    TimerEnable(TIMER_BASE, TIMER_MODULE);

    IntEnable(TIMER_INT);

    TimerIntEnable(TIMER_BASE, TIMER_INT_MODE);

    TimerLoadSet(TIMER_BASE, TIMER_MODULE, SysCtlClockGet() / CONTROLLER_FREQ);
}



