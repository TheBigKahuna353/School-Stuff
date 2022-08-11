#ifndef bulb_h
#define bulb_h

#include <stdint.h>

typedef struct {
    uint8_t model;
    int serial;
} Bulb_t;

Bulb_t bulb_sellModel(uint8_t model);

void bulb_display(Bulb_t bulb);

uint64_t bulb_numSold(uint8_t model);


#endif /* bulb_h */