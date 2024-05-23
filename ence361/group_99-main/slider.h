//*****************************************************************************
//
// slider.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// 
//*****************************************************************************

#ifndef SLIDER_H_
#define SLIDER_H_

//configuration for slider switch
#define SLIDER_BUT_PERIPH SYSCTL_PERIPH_GPIOA
#define SLIDER_BUT_PORT_BASE  GPIO_PORTA_BASE
#define SLIDER_BUT_PIN  GPIO_PIN_7
#define SLIDER_BUT_NORMAL  false

//*****************************************************************************
// return the slider switch position
//*****************************************************************************
int slider_check();

//*****************************************************************************
// Initialise the slider switch
//*****************************************************************************
void slider_init();

//*****************************************************************************
// update the slider switch position
//*****************************************************************************
void slider_update();

#endif /* SLIDER_H_ */
