#include "app_defs.h"

// Utility functions
u8 posToGridIndex (u8 x, u8 y)
{
    return (x % 8 + 1) + ((y % 8 + 1) * 10);
}