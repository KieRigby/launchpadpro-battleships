
//______________________________________________________________________________
//
// Headers
//______________________________________________________________________________

#include "app.h"
#include "utils.h"
#include "defs.h"
#include "game.h"

// buffer to store pad states for flash save
#define BUTTON_COUNT 100

u8 g_Buttons[BUTTON_COUNT] = {0};

//______________________________________________________________________________

void app_surface_event(u8 type, u8 index, u8 value)
{
    // u8 data[2];
    // data[0] = index;
    // data[1] = value;
    // hal_send_midi(DINMIDI, NOTEON, data[0], data[1]);
    // hal_plot_led(TYPEPAD, data[0], data[1], 0, 0);
}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{
    if (d1 == READY_FOR_CONNECTION && d2 == READY_FOR_CONNECTION)
    {
        GAME_STATE = PLACEMENT;
        hal_send_midi (DINMIDI, NOTEON, CONNECTION_RECEIVED, CONNECTION_RECEIVED);
    }

    if (d1 == CONNECTION_RECEIVED && d2 == CONNECTION_RECEIVED)
    {
        GAME_STATE = PLACEMENT;
    }
        
}

//______________________________________________________________________________

void app_sysex_event(u8 port, u8 * data, u16 count)
{
}

//______________________________________________________________________________

void app_aftertouch_event(u8 index, u8 value)
{
}

//______________________________________________________________________________

void app_cable_event(u8 type, u8 value)
{
    waiting_for_connection(0);
}

//______________________________________________________________________________

void app_timer_event()
{
    static u32 ms = 0;
    ms++;
    switch (GAME_STATE) {
        case WAITING_FOR_CONNECTION:
            waiting_for_connection(ms);
            break;
        case PLACEMENT:
            placement(ms);
            break;
        case WAITING_TO_PLAY:
            break;
        case MY_TURN:
            break;
        case OTHER_TURN:
            break;
        case WIN:
            break;
        case LOST:
            break;
    }

    // draw(ms);
}

//______________________________________________________________________________

void app_init(const u16 *adc_raw)
{
    initialize();
}
