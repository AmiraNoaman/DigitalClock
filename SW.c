#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SW.h"

// Zeyada 3an el push
#define SW_PERIOD_MS  (20)

#define N_SAMPLES  (2)

#define N_SWITCHES  (3)

#define SW_PRESSED_LEVEL  (0)
#define SW_RELEASED_LEVEL  (1)

typedef struct
{
    tByte sw_samples[N_SAMPLES];
    tSW_State sw_state;
}tSW_Info;

static tSW_Info SWs_info[N_SWITCHES];

void SW_Init(void)
{
    tByte index = 0;

    GPIO_InitPortPin(SW_PLUS_PORT_CR, SW_PLUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SW_MINUS_PORT_CR, SW_MINUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SW_SET_PORT_CR, SW_SET_PIN, GPIO_IN);

    for (index = SW_PLUS; index<N_SWITCHES; index++)
    {
        SWs_info[index].sw_samples[0] = SW_RELEASED_LEVEL;
        SWs_info[index].sw_samples[1] = SW_RELEASED_LEVEL;

        SWs_info[index].sw_state = SW_RELEASED;
    }
}

void SW_Update(void)
{
    static tWord SW_counter = 0;
    tByte index = 0;

    SW_counter += TMR_TICK_MS;

    if(SW_counter != SW_PERIOD_MS){
        return;
    }
    SW_counter = 0;

    for(index = SW_PLUS; index < N_SWITCHES; index++)
    {
        SWs_info[index].sw_samples[0] = SWs_info[index].sw_samples[1];
        if(index == SW_PLUS)
        {
            SWs_info[index].sw_samples[1] = GPIO_ReadPortPin(SW_PLUS_PORT_CR,SW_PLUS_PIN);
        } else if(index == SW_MINUS)
        {
            SWs_info[index].sw_samples[1] = GPIO_ReadPortPin(SW_MINUS_PORT_CR,SW_MINUS_PIN);
        } else if(index == SW_SET)
        {
            SWs_info[index].sw_samples[1] = GPIO_ReadPortPin(SW_SET_PORT_CR,SW_SET_PIN);
        } else
        {
            // Do nothing
        }
    }
    switch(SWs_info[index].sw_state)
    {
        case SW_RELEASED:
            if((SWs_info[index].sw_samples[0] == SW_PRESSED_LEVEL) &&
               (SWs_info[index].sw_samples[1] == SW_PRESSED_LEVEL))
            {
                SWs_info[index].sw_state = SW_PRE_PRESSED;
            } else
            {
                // Do nothing
            }
            break;
        case SW_PRE_PRESSED:
            if(SWs_info[index].sw_samples[1] == SW_PRESSED_LEVEL)
            {
                SWs_info[index].sw_state = SW_PRESSED;
            } else
            {
                // Do Nothing
            }
            break;
        case SW_PRESSED:
            if((SWs_info[index].sw_samples[0] == SW_RELEASED_LEVEL) &&
               (SWs_info[index].sw_samples[1] == SW_RELEASED_LEVEL))
            {
                SWs_info[index].sw_state = SW_PRE_RELEASED;
            } else
            {
                // Do nothing
            }
            break;
         case SW_PRE_RELEASED:
            if(SWs_info[index].sw_samples[1] == SW_RELEASED_LEVEL)
            {
                SWs_info[index].sw_state = SW_RELEASED;
            } else
            {
                // Do nothing
            }
            break;
         default:
            break;
    }

}

tSW_State SW_GetState(tSW sw)
{
    return SWs_info[sw].sw_state;
}
