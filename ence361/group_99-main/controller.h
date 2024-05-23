//*****************************************************************************
//
// controller.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
//*****************************************************************************

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


// Altitude PID gain values
#define p_gain_a 0.7 
#define i_gain_a 0.001 
#define d_gain_a 0.7 

// Yaw PID gain values
#define p_gain_y 0.6 
#define i_gain_y 0.001 
#define d_gain_y 0.2 

// PID controller update frequency
#define CONTROLLER_FREQ 100.0


// Controller timer interrupt configuration
#define TIMER_PERIPH SYSCTL_PERIPH_TIMER0
#define TIMER_MODULE TIMER_A
#define TIMER_BASE TIMER0_BASE
#define TIMER_INT INT_TIMER0A
#define TIMER_INT_MODE TIMER_TIMA_TIMEOUT

//*****************************************************************************
// resets the intergral error of yaw to help prevent overshoot when calibrating
//*****************************************************************************
void resetErrorYaw();

//*****************************************************************************
// initialize timer module used for PID controller
//*****************************************************************************
void controller_init();

//*****************************************************************************
// enables PID controller interrupt when called
//*****************************************************************************
void enableInt();

//*****************************************************************************
// disables PID controller interrupt when called
//*****************************************************************************
void disableInt();

//*****************************************************************************
// settting the desired altitude value
//*****************************************************************************
void setDAlt(double val);

//*****************************************************************************
// settting the desired yaw value
//*****************************************************************************
void setDYaw(double val);

//*****************************************************************************
// adds past value to current altitude
//*****************************************************************************
void addYaw(double val);

//*****************************************************************************
// adds past value to current yaw
//*****************************************************************************
void addAlt(double val);


#endif /* CONTROLLER_H_ */
