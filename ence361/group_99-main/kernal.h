//*****************************************************************************
//
// kernal.h
//
// Helicopter Project
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
//
//*****************************************************************************

#ifndef KERNAL_H_
#define KERNAL_H_

#define BUTTON_FREQ 1 

#define DISPLAY_FREQ 5

#define UART_FREQ 50

#define STATE_FREQ 1

#define LOOP_FREQ 200

//*****************************************************************************
// updates the kernal, performs round robin scheduling for background tasks
//*****************************************************************************
void kernal_update();

#endif /* KERNAL_H_ */
