//*****************************************************************************
//
// helpers.c
//
// Authors:  Jordan Withell and Lucas 'Keeth' Monteath
//
// helper functions used in various modules
//*****************************************************************************


//*****************************************************************************
// clamp value between 2 values, inclusive
//*****************************************************************************
int clamp(int x, int low, int high) {
    if (x < low) return low;
    if (x > high) return high;
    return x;
}
