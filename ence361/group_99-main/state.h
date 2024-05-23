//*****************************************************************************
//
// state.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// 
//*****************************************************************************

#ifndef STATE_H_
#define STATE_H_

// set speed of rotors to calibrate yaw
#define CALIRBATE_MAIN_SPEED 10
#define CALIBRATE_TAIL_SPEED 20

//*****************************************************************************
// return current state of helicopter
//*****************************************************************************
char* getMode();

#endif /* STATE_H_ */
