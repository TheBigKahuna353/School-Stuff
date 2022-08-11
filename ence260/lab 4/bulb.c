#include "bulb.h"
#include <stdint.h>
#include <stdio.h>

static int serial[255];

Bulb_t bulb_sellModel(uint8_t model)
{
    Bulb_t bulb;
    bulb.model = model;
    bulb.serial = serial[model];
    serial[model]++;
    return bulb;
}

void bulb_display(Bulb_t bulb)
{
    printf("Model %d, SN%06d\n", bulb.model, bulb.serial);
}

uint64_t bulb_numSold(uint8_t model)
{
    return serial[model];
}