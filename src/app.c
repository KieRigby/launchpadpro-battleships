
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
    hal_send_midi(DINMIDI, NOTEON, data[0], data[1]);
    /*hal_send_midi(USBMIDI, NOTEON, data[0], data[1]);*/
    hal_plot_led(TYPEPAD, data[0], data[1], 0, 0);

    if (value != 0)
    {
        switch (index)
        {
            case 11:
            sfx_sonar();
            break;
            case 12:
            sfx_boom();
            break;
            case 10:
            hal_send_midi(DINMIDI, 129, 60, 0);
            default:
            break;
        }
    }
}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{
    hal_plot_led(TYPEPAD, d1, 0, d2, 0);
    
    

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

void sfx_sonar(void)
{
    hal_send_midi(DINMIDI, 0xB1, 23, 127); //0xB1 should be CC on channel 2
    hal_send_midi(DINMIDI, 0xB1, 55, 127);
    hal_send_midi(DINMIDI, 0xB1, 25, 0);
    hal_send_midi(DINMIDI, 0xB1, 57, 0);
    hal_send_midi(DINMIDI, 0xB1, 27, 0);
    hal_send_midi(DINMIDI, 0xB1, 59, 0);
    hal_send_midi(DINMIDI, 0xB1, 87, 45);
    
    hal_send_midi(DINMIDI, 145, 60, 127);
    //hal_send_midi(DINMIDI, 129, 60, 0);
}

void sfx_boom(void)
{
    hal_send_midi(DINMIDI, 0xB1, 23, 0);
    hal_send_midi(DINMIDI, 0xB1, 55, 0);
    hal_send_midi(DINMIDI, 0xB1, 25, 127);
    hal_send_midi(DINMIDI, 0xB1, 57, 127);
    hal_send_midi(DINMIDI, 0xB1, 27, 127);
    hal_send_midi(DINMIDI, 0xB1, 59, 127);
    hal_send_midi(DINMIDI, 0xB1, 87, 126);
    
    hal_send_midi(DINMIDI, 145, 60, 127);
    //hal_send_midi(DINMIDI, 129, 60, 0);
}