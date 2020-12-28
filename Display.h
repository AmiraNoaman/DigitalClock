#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "Main.h"
#include "Timer.h"
#include "ssd.h"
#include "SW.h"


void DISP_Init(void);
void DISP_Update(void);
static void DISPToggleSecondsState(void);
static void DISPToggleMinutesState(void);
static void DISPToggleHoursState(void);

#endif // __DISPLAY_H__
