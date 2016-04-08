#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "designers.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#define DESIGNERS_COUNT 4
int main() {
    designer designers[DESIGNERS_COUNT];
    designers_fill_array(designers, DESIGNERS_COUNT);
    for(int i = 0; i < DESIGNERS_COUNT; i++)
    {
        printf("name : %s\n", designers[i].name);
        printf("surname : %s\n", designers[i].surname);
        printf("department(company : %s) : %s\n", designers[i].dep.company, designers[i].dep.name);
        printf("motto : %s\n",designers[i].motto);
        printf("experienceYears : %i\n",designers[i].experienceYears);
        puts("statistics : ");
        printf("averagePolygons : %.2f\n",designers[i].stats.averagePolygons);
        printf("averageVertices : %.2f\n",designers[i].stats.averageVertices);
        printf("hireDate : %s\n",ctime(&(designers[i].stats.hireDate)));
        puts("\n");
    }
	return 0;
}
