#ifndef __TMRER_H__
#define __TMRER_H__
#include <pic16f877a.h>
#include "Main.h"
#include "Display.h"
#include "Timer.h"
#include "ssd.h"
#include "SW.h"

#define TMR_INTERRUPT_ENABLE

#define TMR_TICK_MS            (5)

void TMR0_Init(void);
void TMR0_Update(void) __interrupt 0;
void TMR0_Start(void);
void TMR0_Stop(void);
tByte TMR0_CheckOverFlow(void);


#endif // __TMR_H__

