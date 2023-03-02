#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct PolarVec_s {
    uint32_t radius;
    float angle;
};

struct PolarVec_s initPolarVec(uint32_t radius, float angle)
{
    struct PolarVec_s polarVec;
    polarVec.radius = radius;
    polarVec.angle = angle;
    return polarVec;
}

void printPolarVec(struct PolarVec_s v)
{
    printf("%d : %0.1f\n", v.radius, v.angle);
}

typedef struct Coord_t {
    float lat;
    float lon;
    float alt;
} Coord_t;

bool isBelowSeaLevel(const Coord_t coord)
{
    return coord.alt < 0;
}

uint64_t numBelowSeaLevel(const Coord_t coords[], size_t n)
{
    uint64_t count = 0;
    for (size_t i = 0; i < n; i++) {
        if (isBelowSeaLevel(coords[i])) {
            count++;
        }
    }
    return count;
}

// typedef struct {
//     int32_t x;
//     int32_t y;
//     int32_t vx;
//     int32_t vy;
// } Particle_t ;

// void setVelocity(Particle_t* particle, int32_t vx, int32_t vy)
// {
//     (*particle).vx = vx;
//     (*particle).vy = vy;
// }

// void update(Particle_t* particle)
// {
//     (*particle).x += (*particle).vx;
//     (*particle).y += (*particle).vy;
// }

typedef struct Vec_t {
    int32_t x;
    int32_t y;
} Vec_t;

Vec_t vecSum(Vec_t v1, Vec_t v2)
{
    Vec_t result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    return result;
}

typedef struct {
    Vec_t position;
    Vec_t velocity;
} Particle_t;

void update(Particle_t* particle)
{
    (*particle).position = vecSum((*particle).position, (*particle).velocity);
}

void setVelocity(Particle_t* particle, int32_t vx, int32_t vy)
{
    (*particle).velocity.x = vx;
    (*particle).velocity.y = vy;
}

void addToVec(Vec_t* v1, Vec_t v2)
{
    v1->x += v2.x;
    v1->y += v2.y;
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

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Heading_t;

typedef enum {
    REVERSE = -1,
    NEUTRAL,
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    FIFTH,
} Gear_t;

typedef enum {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} Weekday_t;

typedef struct {
    Weekday_t weekday;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} Date_t;

Date_t setDate(Weekday_t weekday, int day, int month, uint16_t year)
{
    Date_t date;
    date.weekday = weekday;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

void printDate(const Date_t* date)
{
    printf("%s %d/%d/%d\n",
           (date->weekday == MONDAY) ? "Monday" :
           (date->weekday == TUESDAY) ? "Tuesday" :
           (date->weekday == WEDNESDAY) ? "Wednesday" :
           (date->weekday == THURSDAY) ? "Thursday" :
           (date->weekday == FRIDAY) ? "Friday" :
           (date->weekday == SATURDAY) ? "Saturday" :
           (date->weekday == SUNDAY) ? "Sunday" : "Unknown",
           date->day, date->month, date->year);
}

typedef enum {
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
} Suit_t;

typedef enum {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} Rank_t;

typedef struct {
    Suit_t suit;
    Rank_t rank;
} Card_t;

Card_t makeCard(Rank_t rank, Suit_t suit)
{
    Card_t card;
    card.rank = rank;
    card.suit = suit;
    return card;
}

bool isSnap(Card_t card1, Card_t card2)
{
    return card1.rank == card2.rank;
}

bool isTrump(Card_t card, Suit_t trumpSuit)
{
    return card.suit == trumpSuit;
}

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "temp.h"


#define MAX_PASSENGERS 12

int main(void)
{
    Temp_t temp;
    float value = 0;
    temp_set(&temp, value, CELSIUS);
    temp_print((const Temp_t*)&temp, CELSIUS);
    temp_print((const Temp_t*)&temp, FAHRENHEIT);
    temp_print((const Temp_t*)&temp, KELVIN);
}