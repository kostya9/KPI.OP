#pragma once
#include <stdlib.h>
#include <time.h>
#define STRING_LENGTH_MAX 50
#define MOTTO_LENGTH_MAX 50
#include "designer_db.h"
/*struct department {
	char company[STRING_LENGTH_MAX];
	char name[STRING_LENGTH_MAX];
};
struct statistics {
	float averagePolygons;
	float averageVertices;
	time_t hireDate;
};
typedef struct designer
{
	unsigned int id;
	char name[STRING_LENGTH_MAX];
	char surname[STRING_LENGTH_MAX];
	struct department dep;
	char motto[MOTTO_LENGTH_MAX];
	int experienceYears;
	struct statistics stats;
} designer;*/
//designer_t * designer_get_designer_by_id(int id, designer_t designers[], size_t designers_count);
//int designers_fill_array(designer_t * designers_arr, size_t size);
void designer_array_to_xml_string(char * buffer, size_t size, designer_t designers[], size_t designers_count);
void designer_to_xml_string(char * buffer, size_t size, designer_t * designer);
//int designers_delete_designer(designer_t designers[], size_t des_count, int id);
//int findUniqueId(designer_t designers[], size_t count);