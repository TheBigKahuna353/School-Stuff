#include "temp.h"
#include <stdio.h>


static float convert(float value, Unit_t unit)
{
    switch (unit) {
        case CELSIUS:
            return value;
        case FAHRENHEIT:
            return (value * 1.8) + 32;
        case KELVIN:
            return value + 273.15;
    }
    return value;
}

static char* unit_toString(Unit_t unit)
{
    switch (unit) {
        case CELSIUS:
            return "Celsius";
        case FAHRENHEIT:
            return "Fahrenheit";
        case KELVIN:
            return "Kelvin";
    }
    return "";
}

void temp_set(Temp_t* temp, float value, Unit_t unit)
{
    temp->value = value;
    temp->unit = unit;
}


void temp_print(const Temp_t* temp, Unit_t unit)
{
    printf("%0.2f %s\n", convert(temp->value, unit), unit_toString(unit));
}