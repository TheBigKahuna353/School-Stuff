//*****************************************************************************
//
// HeliUART.h
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// 
//*****************************************************************************

#ifndef HELIUART_H_
#define HELIUART_H_

// UART configuration
#define UART_BASE UART0_BASE
#define UART_PERIPH SYSCTL_PERIPH_UART0
#define UART_GPIO_PERIPH SYSCTL_PERIPH_GPIOA
#define UART_PORT GPIO_PORTA_BASE
#define UART_PIN_RX GPIO_PIN_0
#define UART_PIN_TX GPIO_PIN_1
#define UART_BAUD 9600
#define UART_DATA_BITS UART_CONFIG_WLEN_8
#define UART_STOP_BITS UART_CONFIG_STOP_ONE
#define UART_PARITY_BITS UART_CONFIG_PAR_NONE

//*****************************************************************************
// intialize UART module
//*****************************************************************************
void uart_init();

//*****************************************************************************
// update serial diplay with helicopter information
//*****************************************************************************
void uart_update();

#endif /* HELIUART_H_ */
