#include "app.h"

u8 GAME_STATE;
u8 DRAW_RATE;

//stores x,y and colour in RGB
u8 grid[8][8][3];

void initialize()
{
    GAME_STATE = WAITING_FOR_CONNECTION;
    DRAW_RATE = 100;

    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            for (int colour = 0; colour < 3; ++colour)
                grid[x][y][colour] = 0;
}


void draw(u8 ms)
{
    if (ms >= DRAW_RATE)
    {
        // Draw the grid
        for (int x = 0; x < 8; ++x)
            for (int y = 0; y < 8; ++y)
            {
                u8 r = grid[x][y][0];
                u8 g = grid[x][y][1];
                u8 b = grid[x][y][2];
                hal_plot_led (TYPEPAD, pos_to_grid_index(x,y), r,g,b);
            }
    } 
}


/**
 *  Called when the device is in the WAITING_FOR_CONNECTION state.
 */
void waiting_for_connection(u32 ms)
{
    static u8 loading = 1;
    // Send a ready for connection every 1s
    if (ms % 500 == 0)
    {
        hal_send_midi(DINMIDI, NOTEON, READY_FOR_CONNECTION, READY_FOR_CONNECTION);
        //flash on session (95) button
        hal_plot_led (TYPEPAD, 95, MAXLED * loading, 0, 0);
        loading = 1 - loading;
    }
    
    //Draw loading 

}

void placement(u32 ms)
{
    //Turn off Session button
    hal_plot_led (TYPEPAD, 95, 0,0,0);
    //Turn on the Connection light
    hal_plot_led(TYPESETUP, 0, 0, MAXLED, 0); // green
}