#ifndef float24_h

#define float24_h

#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    int16_t mantissa : 16;
    int16_t exponent : 8;
} Float24_t;


Float24_t float24_init(int16_t mantissa, int8_t exponent);


void float24_print(Float24_t value);



Float24_t float24_multiply(Float24_t num1, Float24_t num2);


Float24_t float24_add(Float24_t num1, Float24_t num2);


Float24_t float24_read(void);


float float24_asIEEE();


void float24_max(Float24_t* num1, Float24_t* num2, Float24_t** max);


Float24_t* float24_arrayMax(Float24_t* array, size_t size, void (*func)(Float24_t*, Float24_t*, Float24_t**));


#endif /* float24_h */