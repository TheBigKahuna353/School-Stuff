//*****************************************************************************
//
// state.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// State machine for the helicopter
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
#include "controller.h"
#include "slider.h"
#include "adc.h"

// State machine for the helicopter
enum States {LANDED = 0, TAKINGOFF, FLYING, LANDING};

// initial state
enum States state = LANDED;

// true if switch is down, false otherwise
bool isDown = false;

// tolerance for in range of desired values when landing
int tolerance = 1;

// true if yaw needs to be calibrated, false otherwise
bool needsCalibrating = true;

//*****************************************************************************
// when in landed state check if switch is down, if so change state to taking off
//*****************************************************************************
void landed() {
    //only change state if switch is down
    // so wait till slider is at up, then on change to down change state
    if (slider_check() == RELEASED) {
        isDown = true;
    }
    if (isDown) {
        if (slider_check() == PUSHED) {
            state = TAKINGOFF;
            MainRotorOn();
            TailRotorOn();
            isDown = false;
            setMainRotor(CALIRBATE_MAIN_SPEED);
            setTailRotor(CALIBRATE_TAIL_SPEED);
        }
    }
}

//*****************************************************************************
// return current state of helicopter
//*****************************************************************************
char* getMode() {
    switch (state) {
        case LANDING:
            return "Landing";
        case TAKINGOFF:
            return "Taking Off";
        case FLYING:
            return "Flying";
        case LANDED:
            return "Landed";
    }
    return "Error in Mode";
}

//*****************************************************************************
// return true if helicopter is within rnage of target, for landing
//*****************************************************************************
bool inRange(int val, int target) {
    return (val >= target - tolerance && val <= target + tolerance);
}


//*****************************************************************************
// function to transition form landed to flying state
//*****************************************************************************
void take_off() {

    // if yaw needs to be calibrated, calibrate it, only perform once
    if (needsCalibrating) { 
        if (get_ref()) {
            // if yaw is calibrated, reset integral error and set yaw to current yaw
            calibrate_yaw();
            resetErrorYaw();
            setDYaw(get_yaw());
            enableInt();
            state = FLYING;
            needsCalibrating = false;
            return;
        }
    } else {
        enableInt();
        state = FLYING;
        isDown = false;
    }
}

//*****************************************************************************
// function called when in flying state
//*****************************************************************************
void flying() {
    if (checkButton(UP) == PUSHED) {
        addAlt(10);
    }
    if (checkButton(DOWN) == PUSHED) {
        addAlt(-10);
    }
    if (checkButton(LEFT) == PUSHED) {
        addYaw(-15);
    }
    if (checkButton(RIGHT) == PUSHED) {
        addYaw(15);
    }
    // check if switch is down, if so change state to landing
    // make sure switch starts at up, then on change to down change state
    if (slider_check() == PUSHED) {
            isDown = true;
        }
        if (isDown) {
            if (slider_check() == RELEASED) {
                state = LANDING;
                setDAlt(10);
                setDYaw(0);
                isDown = false;
            }
        }
}

//*****************************************************************************
// fucntion called when in landing state
//*****************************************************************************
void landing() {

    // wait for helicopter to go to 0 yaw, then land smoothly
    if (inRange(get_yaw(), 0)) {
        if (inRange(get_adc(), 10)) {
            disableInt();
            state = LANDED;
            MainRotorOff();
            TailRotorOff();
            setDAlt(0);
        }
    }
}

//*****************************************************************************
// updates the state of the helicopter
//*****************************************************************************
void state_update() {

    if (state == LANDED) {
        landed();
    }
    if (state == TAKINGOFF) {
        take_off();
    }
    if (state == FLYING) {
        flying();
    }
    if (state == LANDING) {
        landing();
    }

}



