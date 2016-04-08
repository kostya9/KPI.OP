#pragma once
#include <stdlib.h>
#include <time.h>
#define STRING_LENGTH_MAX 100
#define MOTTO_LENGTH_MAX 100
struct department{
    char company[STRING_LENGTH_MAX];
    char name[STRING_LENGTH_MAX];
};
struct statistics{
    float averagePolygons;
    float averageVertices;
    time_t hireDate;
};
typedef
struct designer
{
    char name[STRING_LENGTH_MAX];
    char surname[STRING_LENGTH_MAX];
    struct department dep;
    char motto[MOTTO_LENGTH_MAX];
    int experienceYears;
    struct statistics stats;
} designer;
int designers_fill_array(designer * designers_arr, size_t size);
