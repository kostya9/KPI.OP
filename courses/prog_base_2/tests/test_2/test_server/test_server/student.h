#pragma once
#include <stdlib.h>
#define STUDENT_BUFFER_LEN 100
typedef struct student {
	char name[STUDENT_BUFFER_LEN];
	char group_name[STUDENT_BUFFER_LEN];
	size_t variant;
} student;

student student_new(char * name, char * group_name, size_t variant);
char * student_to_xml(student * student);