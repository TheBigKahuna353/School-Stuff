#include <stdio.h>
#include "float24.h"




int main() {
     	
    //1
    Float24_t array[100];
    size_t size;
    for (int i = 0; i < 100; i++) {
        array[i] = float24_read();
        if (array[i].exponent == -128 && array[i].mantissa == 0) {
            break;
        }
        size = i + 1;
    }
    //2
    for (int i = 0; i < size; i++) {
        printf("Array[%d]: %0.6f\n", i, float24_asIEEE(array[i]));
        float24_print(array[i]);
    }

    //3
    Float24_t sum = float24_init(0, 0);
    for (int i = 0; i < size; i++) {
        sum = float24_add(sum, array[i]);
    }
    printf("Accumulated Sum: %0.6f\n", float24_asIEEE(sum));

    //4
    Float24_t sqr = float24_multiply(sum, sum);
    printf("Square Accumulated Sum: %0.6f\n", float24_asIEEE(sqr));

    //5
    Float24_t* max = float24_arrayMax(array, size, float24_max);
    printf("Max of Numbers: %0.6f\n", float24_asIEEE(*max));
}