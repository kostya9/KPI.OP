#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "designer_db.h"
#define FILE_NAME "des.db"
// There are create table SQL query and an insert query in /sql_queries/
// To create the table launch des_db.sql
// To test launch the insert_designers.sql query
void print_des_count(des_db_t * db);
void print_designer(designer * des);
void one_record_test(des_db_t * db);

int main(void)
{
    des_db_t * db = des_db_new(FILE_NAME);
    one_record_test(db);
    puts("Getting designers by criteria : Salary < 15000 AND ProjectCount > 5  ... ");
    size_t count = 0;
    designer * designers = des_db_get_filtered_designers(db, 5, 15000.0F, &count);
    printf("\nThere are %i of them\n", count);
    if(count > 0)
    {
        puts("Printing them ...");
        for(int i = 0; i < count; i++)
        {
            print_designer(designers + i);
        }
    }
    free(designers);
    des_db_delete(db);
    return EXIT_SUCCESS;
}
void one_record_test(des_db_t * db)
{
    puts("Getting the designers count ...");
    print_des_count(db);
    struct tm tm_time = {.tm_mday = 20, .tm_mon = 4 - 1, .tm_year = 2012 - 1900};
    time_t time = mktime(&tm_time);
    designer des1 = {.id = 3, .name = "Peter", .surname = "Bayleish", .averageVertices = 3.14, .experience = 10, .hireDate = time, .salary = 1005.00, .projectsCount = 100};
    puts("\nAdding a record ... ");
    des_db_add_designer(db, &des1);

    puts("\nGetting the designers count ...");
    print_des_count(db);

    puts("\nGetting the record ... ");
    designer * des1_get = des_db_get_designer(db, 3);
    print_designer(des1_get);
    free(des1_get);

    puts("\nChanging the record's averageVertices to 3.15 ... ");
    des1.averageVertices = 3.15;
    des_db_update_designer(db, &des1);

    puts("\nGetting the record ... ");
    designer * des2 = des_db_get_designer(db, 3);
    print_designer(des2);
    free(des2);

    puts("\nDeleting the record ... ");
    des_db_delete_designer(db, 3);

    puts("\nGetting the designers count ...");
    print_des_count(db);
}
void print_designer(designer * des)
{
    puts("Designer");
    printf("\t %-18s: %-10i\n", "Id", des->id);
    printf("\t %-18s: %-10s\n", "Name", des->name);
    printf("\t %-18s: %-10s\n", "Surname", des->surname);
    printf("\t %-18s: %-8.2f\n", "Average Vertices", des->averageVertices);
    printf("\t %-18s: %-10i\n", "Experience", des->experience);
    printf("\t %-18s: %-8.2f\n", "Salary", des->salary);
    printf("\t %-18s: %-10i\n", "ProjectCount", des->projectsCount);
    struct tm * hireTime = gmtime(&(des->hireDate));
    char time[10];
    sprintf(time, "%i-%i-%i", hireTime->tm_year + 1900, hireTime->tm_mon + 1, hireTime->tm_mday);
    printf("\t %-18s: %-10s\n", "Hire Date", time);
}
void print_des_count(des_db_t * db)
{
    int count = des_db_rows_count(db);
    printf("Desginers count : %i\n", count);
}
