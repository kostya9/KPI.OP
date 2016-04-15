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
typedef struct designer_s
{
    int id;
    char name[STRING_LENGTH_MAX];
    char surname[STRING_LENGTH_MAX];
    struct department dep;
    char motto[MOTTO_LENGTH_MAX];
    int experienceYears;
    struct statistics stats;
} designer_s;
designer_s * designer_get_designer_by_id(int id, designer_s designers[], size_t designers_count);
void designer_to_xml_string(char * buffer, size_t size, designer_s * designer);
void designer_array_to_xml_string(char * buffer, size_t size, designer_s designers[], size_t designers_count);
