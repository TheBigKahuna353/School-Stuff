#include <stdint.h>
#include "lift.h"

Lift_t lift_init(uint8_t maxPassengers, int16_t startFloor)
{
    Lift_t lift;
    lift.maxPassengers = maxPassengers;
    lift.floor = startFloor;
    lift.passengers = 0;
    return lift;
}

void lift_onboard(Lift_t* lift, uint8_t peopleOff, uint8_t peopleOn)
{
    lift->passengers += peopleOn;
    lift->passengers -= peopleOff;
}

int16_t lift_goToFloor(Lift_t* lift, int16_t floor)
{
    if (lift->passengers <= lift->maxPassengers) {
        lift->floor = floor;
    }
    return lift->floor;
}