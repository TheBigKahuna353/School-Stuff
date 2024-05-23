//*****************************************************************************
//
// yaw.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// 
//*****************************************************************************

#ifndef YAW_H_
#define YAW_H_

// yaw quadrature encoder configuration
#define YAW_CHA_PIN GPIO_PIN_0 //PB0
#define YAW_CHB_PIN GPIO_PIN_1 //PB1
#define YAW_BASE GPIO_PORTB_BASE
#define YAW_PERIPH SYSCTL_PERIPH_GPIOB

// yaw reference pin configuration
#define YAW_REF_PIN GPIO_PIN_4
#define YAW_REF_BASE GPIO_PORTC_BASE
#define YAW_REF_PERIPH SYSCTL_PERIPH_GPIOC

#define MAX_STEPS 448

//*****************************************************************************
// initialize the yaw peripherals
//*****************************************************************************
void init_yaw(void);

//*****************************************************************************
// return the yaw value in degrees
//*****************************************************************************
int get_yaw();

//*****************************************************************************
// called when calibrating yaw, sets yaw to 0 
//*****************************************************************************
void calibrate_yaw();

//*****************************************************************************
// return true if helicopter is on the yaw reference
//*****************************************************************************
bool get_ref();


#endif /* YAW_H_ */
