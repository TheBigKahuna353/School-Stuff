#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int32_t add_odd(const int32_t data[], size_t n)
{
    int32_t sum = 0;
    for (size_t i = 0; i < n; i++) {
        if (data[i] % 2 != 0) {
            sum += data[i];
        }
    }
    return sum;
}

size_t lineLength(char* string)
{
    size_t length = 0;
    while (*string != '\n') {
        length++;
        string++;
    }
    return length;
}

uint16_t scanBase6(void)
{
    uint16_t result = 0;
    char c;
    while ((c = getchar()) != -1) {
        if (c >= '0' && c <= '5') {
            result = result * 6 + (c - '0');
        } else {
            break;
        }
    }
    return result;
}

void min_swap(int16_t* a, int16_t* b)
{
    if (*a > *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

void swap3_abc(int16_t* x, int16_t* y, int16_t* z)
{
    min_swap(x, y);
    min_swap(x, z);
    min_swap(y, z);
}

size_t myIndex(int8_t arr[], int8_t* element)
{
    return element - arr;
}

typedef struct
{
    char description[25];
    float duration;
    int priority;

} Task_t;

typedef struct {
    int64_t x;
    int64_t y;
    int64_t z;
} Vector3d_t;

Vector3d_t vector(int64_t x, int64_t y, int64_t z)
{
    Vector3d_t v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

int64_t vectorDotProduct(Vector3d_t a, Vector3d_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

typedef struct {
    uint64_t id;
    uint8_t age;
    float gpa;
} Student_t;

Student_t newStudent(uint64_t id, uint8_t age, float gpa)
{
    Student_t student;
    student.id = id;
    student.age = age;
    student.gpa = gpa;
    return student;
}

void printStudent(const Student_t* student)
{
    printf("%lu: Age %u, GPA %0.2f\n", student->id, student->age, student->gpa);
}

void updateGpa(Student_t* student, float newGpa)
{
    student->gpa = newGpa;
}

void findInArray(uint16_t* array, size_t n, uint16_t value, uint16_t** foundValueDest)
{
    for (size_t i = 0; i < n; i++) {
        if (array[i] == value) {
            *foundValueDest = &array[i];
            return;
        }
    }
    *foundValueDest = NULL;
}

uint64_t* newCopy(void* array, size_t numElements)
{
    uint64_t* newArray = malloc(numElements * sizeof(uint64_t));
    for (size_t i = 0; i < numElements; i++) {
        newArray[i] = ((uint64_t*)array)[i];
    }
    return newArray;
}

uint16_t callPassedFunc(uint16_t(*f)(uint16_t), uint16_t value)
{
    return f(value);
}

uint16_t func(uint32_t x)
{
    return x/2; //Only an example - could be anything. 
}

int main()
{


uint32_t arg = 10;
uint16_t directRetVal = func(arg);
uint16_t indirectRetVal = callPassedFunc(&func, arg);
printf("%d\n", directRetVal == indirectRetVal);
}