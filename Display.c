#include"Display.h"




static void DSIPToggleSecondsState(void);
static void DISP_BlinkSeconds(tTIM_TIME *time);
static void DISP_BlinkHours(tTIM_TIME *time);
static void DISP_BlinkMinutes(tTIM_TIME *time);


void DISP_Init(void)
{
	SSD_Init(SSD_MINUTES_UNITS);
	SSD_Init(SSD_MINUTES_TENS);
	SSD_Init(SSD_HOURS_UNITS);
	SSD_Init(SSD_HOURS_TENS);

	SSD_SetValue(SSD_MINUTES_UNITS, SSD_0);
    SSD_SetValue(SSD_MINUTES_TENS, SSD_0);
    SSD_SetValue(SSD_HOURS_UNITS, SSD_0);
    SSD_SetValue(SSD_HOURS_TENS, SSD_0);
}
void DISP_Update(void)
{
    static tWord DISP_counter = 0;

    tTIM_Time TIM_Time;
    tTIM_State TIM_State;

    DISP_counter += TMR_TICK_MS;

    if(DISP_counter != DISP_PERIOD_MS)
    {
        return;
    }
    DISP_counter = 0;
    TIM_GetTime(&TIM_Time);

    if (DISP_blink_count != DISP_SECOND_BLINK_MS)
    {
        return;
    }

    DISP_blink_count = 0;

    TIM_State = TIM_GetState();
    switch (TIM_State)
    {
    case TIM_NORMAL:
        DISP_BlinkSeconds(&TIM_Time);
        break;
    case TIM_SET_HOURS:
        DISP_BlinkHours(&TIM_Time);
        break;
    case TIM_SET_MINUTES:
        DISP_BlinkMinutes(&TIM_Time);
        break;
    default:
        break;
    }

}
static void DISPToggleSecondsState(void)
{
    if(SecondsDotState == SSD_OFF)
    {
        SSD_SetDotState(SSD_ON);
    }
}

