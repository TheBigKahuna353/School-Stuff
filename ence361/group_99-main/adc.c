//*****************************************************************************
//
// adc.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// ADC functions for altitude control
//*****************************************************************************
// Based on the ADCdemo.c by P.J. Bones UCECE
// Which is based on the 'convert' series from 2016
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
#include "adc.h"
#include "helpers.h"


//*****************************************************************************
// Global variables
//*****************************************************************************
static circBuf_t g_inBuffer;        // Buffer of size BUF_SIZE integers (sample values)
static uint32_t g_ulSampCnt;    // Counter for the interrupts
int min_alt;
int max_alt;

//*****************************************************************************
// The handler for the ADC conversion complete interrupt.
// Writes to the circular buffer.
//*****************************************************************************
void
ADCIntHandler(void)
{
    uint32_t ulValue;

    //
    // Get the single sample from ADC0.  ADC_BASE is defined in
    // inc/hw_memmap.h
    ADCSequenceDataGet(ADC0_BASE, 3, &ulValue);
    g_ulSampCnt++;
    //
    // Place it in the circular buffer (advancing write index)
    writeCircBuf (&g_inBuffer, ulValue);

    //
    // Clean up, clearing the interrupt
    ADCIntClear(ADC0_BASE, 3);
}

//*****************************************************************************
// Initialisation the ADC peripheral - based on adcDemo.c by P.J. Bones UCECE
//*****************************************************************************
void
initADC (void)
{
    // The ADC0 peripheral must be enabled for configuration and use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(ALTITUDE_PIN_PERIPH);


    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);

    // Enable sample sequence 3 with a processor signal trigger.  Sequence 3
    // will do a single sample when the processor sends a signal to start the
    // conversion.
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    //
    // Configure step 0 on sequence 3.  Sample channel 0 (ADC_CTL_CH0) in
    // single-ended mode (default) and configure the interrupt flag
    // (ADC_CTL_IE) to be set when the sample is done.  Tell the ADC logic
    // that this is the last conversion on sequence 3 (ADC_CTL_END).  Sequence
    // 3 has only one programmable step.  Sequence 1 and 2 have 4 steps, and
    // sequence 0 has 8 programmable steps.  Since we are only doing a single
    // conversion using sequence 3 we will only configure step 0.  For more
    // on the ADC sequences and steps, refer to the LM3S1968 datasheet.
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH9 | ADC_CTL_IE |
                             ADC_CTL_END);


    //
    // Since sample sequence 3 is now configured, it must be enabled.
    ADCSequenceEnable(ADC0_BASE, 3);

    //
    // Register the interrupt handler
    ADCIntRegister (ADC0_BASE, 3, ADCIntHandler);

    //
    // Enable interrupts for ADC0 sequence 3 (clears any outstanding interrupts)
    ADCIntEnable(ADC0_BASE, 3);


    // hard coded work with specific test rig
    // changed to work for exactly 1v at 100%, not 0.935v

//    min_alt = 4095 * (1.674 / 3.3); // landed

    initCircBuf (&g_inBuffer, BUF_SIZE);

    set_landing_adc();
}


//*****************************************************************************
// gets the mean ADC value
//*****************************************************************************
uint16_t get_mean() {
    // Background task: calculate the (approximate) mean of the values in the
            // circular buffer and display it, together with the sample number.
            // Calculate and display the rounded mean of the buffer contents
    int sum = 0;
    int i;
    for (i = 0; i < BUF_SIZE; i++)
    sum = sum + readCircBuf (&g_inBuffer);
    return (2 * sum + BUF_SIZE) / 2 / BUF_SIZE;
}

//*****************************************************************************
// Sets the mean ADC value corrosponding to the minimum at current altitude
//*****************************************************************************
void set_landing_adc() {
    // wait for the buffer to fill
    // once it is, set the min_alt to the current mean
    // this is the adc value for landed, as it starts at 0
    while (g_ulSampCnt < BUF_SIZE*2) {}
    min_alt = get_mean();
//    max_alt = min_alt - (4095 * (1 / 3.3)); // max = min - range

}

//*****************************************************************************
// return the mean ADC value as percentage
//*****************************************************************************
int get_adc() {
    return clamp((min_alt - get_mean()) * 100 / 1240, 0, 100);
}
