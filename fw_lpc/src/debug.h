#ifndef DEBUG_H_
#define DEBUG_H_

#include "lpc_types.h"
#include <stdio.h>

/**
 * @brief	Initializes board UART for output, required for printf redirection
 * @return	None
 */
void DEBUG_Init(void);

/**
 * @brief	Sends a single character on the UART, required for printf redirection
 * @param	ch	: character to send
 * @return	None
 */
void DEBUG_UARTPutChar(char ch);

/**
 * @brief	Get a single character from the UART, required for scanf input
 * @return	EOF if not character was received, or character value
 */
int DEBUG_UARTGetChar(void);

/**
 * @brief	Prints a string to the UART
 * @param	str	: Terminated string to output
 * @return	None
 */
void DEBUG_UARTPutSTR(char *str);

/* The DEBUG* functions are selected based on system configuration.
   Code that uses the DEBUG* functions will have their I/O routed to
   the UART, semihosting, or nowhere. */
#if defined(DEBUG_ENABLE)
#if defined(DEBUG_SEMIHOSTING)
#define DEBUGINIT()
#define DEBUGOUT(...) printf(__VA_ARGS__)
#define DEBUGSTR(str) printf(str)
#define DEBUGIN() (int) EOF

#else
#define DEBUGINIT() DEBUG_Init()
#define DEBUGOUT(...) printf(__VA_ARGS__)
#define DEBUGSTR(str) DEBUG_UARTPutSTR(str)
#define DEBUGIN() DEBUG_UARTGetChar()
#endif /* defined(DEBUG_SEMIHOSTING) */

#else
#define DEBUGINIT()
#define DEBUGOUT(...)
#define DEBUGSTR(str)
#define DEBUGIN() (int) EOF
#endif /* defined(DEBUG_ENABLE) */

#endif /* DEBUG_H_ */
