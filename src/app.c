
//______________________________________________________________________________
//
// Headers
//______________________________________________________________________________

#include "app.h"
#include "utils.h"
#include "defs.h"

// buffer to store pad states for flash save
#define BUTTON_COUNT 100

u8 g_Buttons[BUTTON_COUNT] = {0};

//______________________________________________________________________________

void app_surface_event(u8 type, u8 index, u8 value)
{
    u8 data[2];
    data[0] = index;
    data[1] = value;
    hal_send_sysex(DINMIDI,data,2);
}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{

}

//______________________________________________________________________________

void app_sysex_event(u8 port, u8 * data, u16 count)
{
    hal_plot_led(TYPEPAD, data[0], data[1], 0, 0);
}

//______________________________________________________________________________

void app_aftertouch_event(u8 index, u8 value)
{
    
}

//______________________________________________________________________________

void app_cable_event(u8 type, u8 value)
{

}

//______________________________________________________________________________

void app_timer_event()
{
    // static u8 ms = 500;

    // if (++ms >= 500)
    // {
    //     enum MIDI_MESSAGE message = WAITING_TO_PAIR;
    //     u8* data = &message;
    //     hal_send_sysex(DINMIDI, data, 1);
    // }
}

//______________________________________________________________________________

void app_init(const u16 *adc_raw)
{

}
