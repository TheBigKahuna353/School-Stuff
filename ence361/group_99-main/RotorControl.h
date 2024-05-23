//*****************************************************************************
//
// RotorControl.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// 
//*****************************************************************************

#ifndef ROTORCONTROL_H_
#define ROTORCONTROL_H_

// pwm config main rotor
#define MAIN_ROTOR_BASE PWM0_BASE
#define MAIN_ROTOR_PERIPH SYSCTL_PERIPH_PWM0
#define MAIN_ROTOR_GEN PWM_GEN_3

// pwm config tail rotor
#define TAIL_ROTOR_BASE PWM1_BASE
#define TAIL_ROTOR_PERIPH SYSCTL_PERIPH_PWM1
#define TAIL_ROTOR_GEN PWM_GEN_2

// gpio config main rotor
#define MAIN_GPIO_BASE   GPIO_PORTC_BASE
#define MAIN_GPIO_CONFIG GPIO_PC5_M0PWM7
#define MAIN_GPIO_PIN GPIO_PIN_5
#define MAIN_PERIPH_GPIO SYSCTL_PERIPH_GPIOC

// gpio config tail rotor
#define TAIL_GPIO_BASE   GPIO_PORTF_BASE
#define TAIL_GPIO_CONFIG GPIO_PF1_M1PWM5
#define TAIL_GPIO_PIN GPIO_PIN_1
#define TAIL_PERIPH_GPIO SYSCTL_PERIPH_GPIOF

//*****************************************************************************
// initialise pwm for main and tail rotors
//*****************************************************************************
void initRotor();

//*****************************************************************************
// turn main rotor on
//*****************************************************************************
void MainRotorOn();

//*****************************************************************************
// turn tail rotor on
//*****************************************************************************
void TailRotorOn();

//*****************************************************************************
// turn tail rotor off
//*****************************************************************************
void TailRotorOff();

//*****************************************************************************
// turn main rotor off
//*****************************************************************************
void MainRotorOff();

//*****************************************************************************
// get duty cycle of tail rotor
//*****************************************************************************
int getTailDuty();

//*****************************************************************************
// get duty cycle of main rotor
//*****************************************************************************
int getMainDuty();

//*****************************************************************************
// set power of main rotor
//*****************************************************************************
void setMainRotor(int duty);

//*****************************************************************************
// set power of tail rotor
//*****************************************************************************
void setTailRotor(int duty);


#endif /* ROTORCONTROL_H_ */
