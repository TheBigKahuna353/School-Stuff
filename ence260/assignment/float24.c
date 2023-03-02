#include "float24.h"

Float24_t float24_init(int16_t mantissa, int8_t exponent)
{
    Float24_t temp;
    temp.mantissa = mantissa;
    temp.exponent = exponent;
    return temp;
}



void float24_print(Float24_t value)
{
    printf("%d * 2 ^ %d\n", value.mantissa, value.exponent);
}

Float24_t static float24_normalise(int32_t oversizeMantissa, int8_t exponent)
{
    Float24_t temp;
    while (oversizeMantissa > INT16_MAX || oversizeMantissa < -INT16_MAX) {
        oversizeMantissa = oversizeMantissa >> 1;
        exponent++;
    }
    temp.mantissa = oversizeMantissa;
    temp.exponent = exponent;
    return temp;
}

Float24_t float24_multiply(Float24_t num1, Float24_t num2)
{
    int32_t mantissa = num1.mantissa * num2.mantissa;
    int8_t exponent = num1.exponent + num2.exponent;
    return float24_normalise(mantissa, exponent);
}

Float24_t float24_add(Float24_t num1, Float24_t num2)
{
    int32_t mantissa;
    int8_t exponent;
    if (num1.exponent > num2.exponent) {
        mantissa = num1.mantissa + (num2.mantissa >> (num1.exponent - num2.exponent));
        exponent = num1.exponent;
    } else {
        mantissa = num2.mantissa + (num1.mantissa >> (num2.exponent - num1.exponent));
        exponent = num2.exponent;
    }
    return float24_normalise(mantissa, exponent);
}

int min(int first, int second)
{
    if (first < second) {
        return first;
    } else {
        return second;
    }
}

Float24_t float24_read(void)
{
    char c;
    int sign = 1;
    int mantissa = 0;
    int exponent = 0;
    bool haveExponent = false;
    bool mantissaStarted = true;
    do {
        c = getchar();
        if (c == '-') {
            sign = -1;
        } else if (c == '+') {
            sign = 1;
        } else if (c >= '0' && c <= '9') {
            if (mantissaStarted) {
                mantissa = mantissa * 10 + (c - '0');
            } else {
                exponent = exponent * 10 + (c - '0');
                haveExponent = true;
            }
        } else if (c == 'b') {
            mantissa *= sign;
            sign = 1;
            mantissaStarted = false;
        } else {
            if (!haveExponent) {
                return float24_init(0, -128);
            }
            exponent *= sign;
            exponent = min(exponent, 127);
            return float24_normalise(mantissa, exponent);
        }
    } while (1);
}


void float24_max(Float24_t* num1, Float24_t* num2, Float24_t** max)
{
    Float24_t negativeNum2 = float24_multiply(*num2, float24_init(-1, 0)); // -num2
    Float24_t temp = float24_add(*num1, negativeNum2);                 // num1 - num2
    if (temp.mantissa > 0) {    
        *max = num1;
    } else {
        *max = num2;
    }
}

Float24_t* float24_arrayMax(Float24_t* array, size_t size, void (*func)(Float24_t*, Float24_t*, Float24_t**))
{
    Float24_t* max = array;
    for (int i = 1; i < size; i++) {
        func(max, array + i, &max);
    }
    return max;
}