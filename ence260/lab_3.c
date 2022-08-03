#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void printViaPtr(int16_t* intPtr)
{
    printf("%d\n", *intPtr);
}


void print2Ints(int16_t number1, int16_t number2)
{
    printViaPtr(&number1);
    printViaPtr(&number2);
}

void swap(uint8_t* address1, uint8_t* address2)
{
    uint8_t temp = *address1;
    *address1 = *address2;
    *address2 = temp;
}

int accumulator(int num)
{
    static int accumulator = 0;
    accumulator += num;
    return accumulator;
}

void convertDistance(const double* metres, double* centimetres, double* kilometres)
{
    *centimetres = *metres * 100;
    *kilometres = *metres / 1000;
}

// void printArray(int32_t* array, size_t n)
// {
//     for (size_t i = 0; i < n; i++) {
//         printf("%d\n", *array);
//         array++;
//     }
// }

// void printArray(int32_t* const array, size_t n)
// {
//     for (size_t i = 0; i < n; i++) {
//         printf("%d\n", *array + i);
//     }
// }

// void printArray(int32_t* array, size_t n)
// {
//     for (size_t i = 0; i < n; i++) {
//         printf("%d\n", array[i]);
//     }
// }

void printArray(int32_t array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d\n", array[i]);
    }
}

void printSquaredArray(const int32_t array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d\n", array[i] * array[i]);
    }
}

void squareArray(int32_t array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        array[i] *= array[i];
    }
}

bool isInData(const uint8_t* data, size_t arraySize, const uint8_t* ptr)
{
    return (ptr >= data && ptr < data + arraySize);
}

void copyArray(const int32_t* src, int32_t* dest, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int32_t index2d(int32_t* array, size_t width, size_t i, size_t j)
{
    return array[i * width + j];
}

bool isWonRow(char player, const char game[3][3], uint8_t rowNum)
{
    for (uint8_t i = 0; i < 3; i++) {
        if (game[rowNum][i] != player) {
            return false;
        }
    }
    return true;
}

// int main(void)
// {
//     int32_t array[100] = {0};
//     int i = 0;
//     do {
//         scanf("%d", &array[i]);
//         i++;
//     } while (array[i-1] != -1 && i <= 100);
//     printf("%d numbers entered\n", i);
//     printArray(array, i);
// }

int main(void)
{
    // char game[3][3] = {{'X', 'O', ' '},{'X', 'X', 'X'}, {' ', ' ', ' '}};
    // printf(isWonRow('X', game, 1) ? "true\n" : "false\n"); 

     char game[3][3] = {{'X', 'O', ' '},{' ', ' ', ' '}, {'X', 'X', 'O'}};
printf(isWonRow('X', game, 2) ? "true\n" : "false\n"); 
}