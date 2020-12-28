#include "Timer.h"
#include "Main.h"
#include "Display.h"
#include"Time.h"
#include"ssd.h"
#include"SW.h"


extern tByte flag;

void TMR0_Init(void)
{
    TMR0_SET_PRE_SCALER(7);
    TMR0_DISABLE_CLOCK();
}
void TMR0_Start(void)
{
    TMR0_CLEAR_FLAG();
    TMR0_SET_TIME_MS(TMR_TICK_MS);
    TMR0_SET_INT_STATE(1); // Enable interrupt
    GLOBAL_INTERRUPT_ENABLE();
    TMR0_ENABLE_CLOCK();          // TMR0 is on
}
tByte TMR0_CheckOverFlow(void)
{
    return TMR0_GET_FLAG; // TMR0_CHECK_FLAG()
}
void TMR0_Stop(void)
{
    TMR0_DISABLE_CLOCK;
}
void TMR0_Update(void) __interrupt 0
{
    RC7 = 1 ^ RC7;

    flag = 1;

    TMR0_CLEAR_FLAG;
    TMR0_SET_TIME_MS(TMR_TICK_MS); // Update register
}
