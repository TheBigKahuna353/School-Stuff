#ifndef temp_h
#define temp_h

typedef enum {
    CELSIUS,
    FAHRENHEIT,
    KELVIN
} Unit_t;

typedef struct {
    float value;
    Unit_t unit;
} Temp_t;

void temp_set(Temp_t* temp, float value, Unit_t unit);

void temp_print(const Temp_t* temp, Unit_t unit);

#endif /* temp_h */