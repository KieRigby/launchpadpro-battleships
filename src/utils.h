#include "app_defs.h"

// Utility functions


u8 pos_to_grid_index (u8 x, u8 y)
{
    return (x % 8 + 1) + ((y % 8 + 1) * 10);
}

u8 getX(u8 index)
{
    return (index % 10) - 1;
}

u8 getY(u8 index)
{
    return (index / 10) - 1;
}

//returns 1 if index is in the 8x8 grid
u8 is_index_in_grid (u8 index)
{
    u8 xPos = index % 10;
    u8 xValid = xPos > 0 && xPos < 9;
    u8 yValid = index > 10 && index < 89;
    return xValid && yValid;
}