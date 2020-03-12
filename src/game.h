#include "app.h"

u8 GAME_STATE;
u8 DRAW_RATE;

#define NUM_SHIPS 5
#define MAX_SHIP_SIZE 5
#define NEXT_SHIP_BUTTON 89

u8 ships[NUM_SHIPS][MAX_SHIP_SIZE];
u8 current_ship = 0;
u8 current_ship_size = 0;

u8 you_are_ready;
u8 i_am_ready;

//stores x,y and colour in RGB
u8 grid[8][8][3];

void initialize()
{
    GAME_STATE = WAITING_FOR_CONNECTION;
    DRAW_RATE = 100;

    you_are_ready = 0;
    i_am_ready = 0;
 
    current_ship = 0;
    current_ship_size = 0;

    for (int i = 0; i < NUM_SHIPS; ++i)
        for (int j = 0; j < MAX_SHIP_SIZE; ++j)
            ships[i][j] = 0;

    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            for (int colour = 0; colour < 3; ++colour)
                grid[x][y][colour] = 0;
}

void clear_grid ()
{
    for (int i = 0; i < 100; ++i)
        hal_plot_led(TYPEPAD,i,0,0,0);

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
    static u8 blink = 1;
    // Send a ready for connection every 1s
    if (ms % 500 == 0)
    {
        hal_send_midi(DINMIDI, NOTEON, READY_FOR_CONNECTION, READY_FOR_CONNECTION);
        //flash on session (95) button
        hal_plot_led (TYPEPAD, 95, MAXLED * blink, 0, 0);
        blink = 1 - blink;
    }
    
    //Draw loading 

}

void placement(u32 ms)
{
    //Turn off Session button
    hal_plot_led (TYPEPAD, 95, 0,0,0);
    //Turn on the Connection light
    hal_plot_led(TYPESETUP, 0, 0, MAXLED, 0); // green

    static u8 blink = 1;
    // Send a ready for connection every 1s
    if (ms % 500 == 0 && !i_am_ready)
    {
        //flash on session (95) button
        hal_plot_led (TYPEPAD, NEXT_SHIP_BUTTON, 0, 0, MAXLED * blink);
        blink = 1 - blink;
    }

}

void my_turn(u32 ms) {
    hal_plot_led(TYPEPAD, 10, 0,MAXLED, 0);
}

void your_turn(u32 ms) {
    hal_plot_led(TYPEPAD, 10,MAXLED, 0, 0);
}





void placement_surface_event(u8 index)
{
    if (index == NEXT_SHIP_BUTTON)
    {
        if (current_ship_size > 1)
        {
            current_ship++;

            if (current_ship < NUM_SHIPS)
            {
                current_ship_size = 0;
                hal_plot_led(TYPEPAD, 80 - current_ship * 10, 0,0,MAXLED);
            } else {
                i_am_ready = 1;
                if (you_are_ready)
                    GAME_STATE = YOUR_TURN;
 
                hal_send_midi(DINMIDI, NOTEON, READY_FOR_PLAY, READY_FOR_PLAY);
                clear_grid();
            }

        }
    } else if (current_ship_size < MAX_SHIP_SIZE) {
        if (is_index_in_grid(index))
        {
            ships[current_ship][current_ship_size] = index;

            u8 r = 10;
            u8 g = current_ship * 15;
            u8 b = 30;

            grid[getX(index)][getY(index)][0] = r;
            grid[getX(index)][getY(index)][1] = g;
            grid[getX(index)][getY(index)][2] = b;

            current_ship_size++;
        }
    }
}