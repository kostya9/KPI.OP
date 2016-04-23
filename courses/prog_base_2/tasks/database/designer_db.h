#pragma once
#include <stdlib.h>
#include <time.h>
#define DB_BUFFER_LENGTH 100
typedef enum DB_STATUS {DB_OK, DB_ERROR} DB_STATUS;
typedef struct des_db_s des_db_t;
typedef struct designer
{
    unsigned int id;
    char name[DB_BUFFER_LENGTH];
    char surname[DB_BUFFER_LENGTH];
    double averageVertices;
    int experience;
    float salary;
    int projectsCount;
    time_t hireDate;

} designer;

des_db_t * des_db_new(const char * db_file);
void des_db_delete(des_db_t * self);

int des_db_rows_count(des_db_t * self);

// CRUD
void des_db_add_designer(des_db_t * self, designer * des);
designer * des_db_get_designer(des_db_t * self, unsigned int id);
void des_db_update_designer(des_db_t * self, designer * des);
void des_db_delete_designer(des_db_t * self, unsigned int id);

// Writes number of designers to count
designer * des_db_get_filtered_designers(des_db_t * self, int websitesCount, float salary, size_t * pcount);

DB_STATUS des_db_get_last_status();


