//*****************************************************************************
//
// adc.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
//
//*****************************************************************************
// Based on the ADCdemo.h by P.J. Bones UCECE
// Which is based on the 'convert' series from 2016
//*****************************************************************************

#ifndef ADC_H_
#define ADC_H_

//*****************************************************************************
// Constants
//*****************************************************************************
#define BUF_SIZE 40
#define SAMPLE_RATE_HZ 150

#define ALTITUDE_PIN GPIO_PIN_4 // PE4
#define ALTITUDE_PIN_BASE GPIO_PORTE_BASE
#define ALTITUDE_PIN_PERIPH SYSCTL_PERIPH_GPIOE


//*****************************************************************************
// Global variables
//*****************************************************************************
static circBuf_t g_inBuffer;        // Buffer of size BUF_SIZE integers (sample values)
static uint32_t g_ulSampCnt;        //  Counter for the interrupts

int min_alt;

//*****************************************************************************
// Initialisation the ADC peripheral - based on adcDemo.c by P.J. Bones UCECE
//*****************************************************************************
void initADC (void);

//*****************************************************************************
// Sets the mean ADC value corrosponding to the minimum at current altitude
//*****************************************************************************
void set_landing_adc();

//*****************************************************************************
// return the mean ADC value as percentage
//*****************************************************************************
int get_adc();

#endif /* ADC_H_ */
