//*****************************************************************************
//
// HeliUART.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// Module for displaying helicopter information over serial
//*****************************************************************************


#include "heliUART.h"
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
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
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


//*****************************************************************************
// Send string to buffer
//*****************************************************************************
void send(char *buffer) {

    while (*buffer) {
        UARTCharPut(UART_BASE, *buffer);
        buffer++;
    }
}

//*****************************************************************************
// update serial diplay with helicopter information
//*****************************************************************************
void uart_update() {
    char string[20];  // 20 characters across the display

    usnprintf(string, sizeof(string), "alt: %3d%% [%d] \r\n", get_adc(), getDAlt());
    send(string); 

    usnprintf(string, sizeof(string), "Mode: %s \r\n", getMode());
    send(string);

    usnprintf(string, sizeof(string), "Yaw: %d [%d] \r\n", get_yaw(), getDYaw());
    send(string);

    usnprintf(string, sizeof(string), "Tail Duty: %d%% \r\n", getTailDuty());
    send(string);

    usnprintf(string, sizeof(string), "Main Duty: %d%% \r\n", getMainDuty());
    send(string);

    send("\n\n\r\n"); // seperate 
}


//*****************************************************************************
// intialize UART module
//*****************************************************************************
void uart_init() {

    SysCtlPeripheralEnable(UART_PERIPH);
    SysCtlPeripheralEnable(UART_GPIO_PERIPH);

    GPIOPinTypeUART(UART_PORT, UART_PIN_RX | UART_PIN_TX);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    UARTConfigSetExpClk(UART_BASE, SysCtlClockGet(), UART_BAUD, UART_DATA_BITS | UART_STOP_BITS | UART_PARITY_BITS);

    UARTFIFOEnable(UART_BASE);

    UARTEnable(UART_BASE);
}



