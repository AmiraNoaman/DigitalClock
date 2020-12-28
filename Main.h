#ifndef __MAIN_H__
#define __MAIN_H__

#include <pic16f877a.h>

/* Fill missing code below */
/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)


/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_DIRECTION    (TRISA)

#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL    (TRISB)

#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL    (TRISC)

#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL    (TRISD)

#define GPIO_PORTE_DATA         (PORTE)
#define GPIO_PORTE_CONTROL    (TRISE)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = ((DIRECTION)? (~GPIO_OUT):(GPIO_OUT)))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))
/* End of code filling */

/*Timer*/

#define TMR0_SET_PRE_SCALER(x) 		PSA = 0;\
									PS0 = (x&0x1);\
									PS1 = (x&0x2)>>1;\
									PS2 = (x&0x4)>>2;

#define TMR0_CHECK_FLAG()			(TMR0IF)
#define TMR0_CLEAR_FLAG()			(TMR0IF = 0)


#define TMR0_SELECT_CLOCK_SOURCE(y)	(T0CS = y)
#define TMR0_DISABLE_CLOCK()         (T0CS = 1)
#define TMR0_ENABLE_CLOCK()         (T0CS = 0)

#define GLOBAL_INTERRUPT_ENABLE()      (GIE = 1)

#define TMR0_SELECT_EDGE(z)			(T0SE = z)

#define TMR0_READ_COUNTER()			(TMR0)
#define TMR0_SET_TIME_MS(t)			(TMR0 = 256 - 8*t)

#define TMR0_SET_INT_STATE(x)		(TMR0IE = x)

#define TMR0_SET_STATE(x)			(T0CS = x)


/* Standard data types */
typedef unsigned int tWord;
typedef unsigned char tByte;

#endif // __MAIN_H__
