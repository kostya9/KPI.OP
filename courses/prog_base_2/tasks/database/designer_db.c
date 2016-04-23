#include "designer_db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_NAME_LENGTH 20
#define TABLE_NAME "Designers"
struct des_db_s
{
    sqlite3 * db;
};

static DB_STATUS status = DB_OK;

static int checkRC(des_db_t * self, int rc)
{
    if(rc == SQLITE_ERROR)
    {
        fputs(sqlite3_errmsg(self->db), stderr);
        status = DB_ERROR;
        return 1;
    }
    status = DB_OK;
    return 0;
}
static void fill_designer(sqlite3_stmt * stmt, designer * des)
{
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    double averageVertices = sqlite3_column_double(stmt, 3);
    int experience = sqlite3_column_int(stmt, 4);
    double salary = sqlite3_column_double(stmt, 5);
    int projectCount = sqlite3_column_int(stmt, 6);
    time_t hireDate = (time_t) sqlite3_column_int(stmt, 7);
    strcpy(des->name, (char *)name);
    strcpy(des->surname, (char *)surname);
    des->id = id;
    des->projectsCount = projectCount;
    des->salary = salary;
    des->averageVertices = averageVertices;
    des->experience = experience;
    des->hireDate = hireDate;
}

des_db_t * des_db_new(const char * db_file)
{
    des_db_t * self = malloc(sizeof(struct des_db_s));
    int rc = 0;
    rc = sqlite3_open(db_file, &(self->db));
    if(checkRC(self, rc))
    {
        free(self);
        return NULL;
    }
    return self;
}

void des_db_delete(des_db_t * self)
{
    int rc = sqlite3_close(self->db);
    checkRC(self, rc);
    free(self);
    status = DB_OK;
}

int des_db_rows_count(des_db_t * self)
{
    int rc = 0;
    sqlite3_stmt * stmt = NULL;
    const char * sql = "SELECT COUNT(*) FROM " TABLE_NAME ";";
    rc = sqlite3_prepare_v2(self->db, sql, -1, &stmt, NULL);
    if(checkRC(self, rc))
    {
        return 0;
    }
    rc = sqlite3_step(stmt);
    if(checkRC(self, rc))
    {
        return 0;
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void des_db_add_designer(des_db_t * self, designer * des)
{
    int rc  = 0;
    sqlite3_stmt * stmt;
    char * sql = "INSERT INTO "TABLE_NAME" (Id, Name, Surname, AverageVertices, Experience, Salary, ProjectCount, HireDate) "
                 "VALUES ( ? ,  ? ,  ? ,  ? ,  ? ,  ?, ?, ? );";
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_prepare_v2(self->db, sql, strlen(sql), &stmt, NULL);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 1, des->id);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_text(stmt, 2, des->name, strlen(des->name), SQLITE_STATIC);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_text(stmt, 3, des->surname, strlen(des->surname), SQLITE_STATIC);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_double(stmt, 4, des->averageVertices);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 5, des->experience);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_double(stmt, 6, des->salary);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 7, des->projectsCount);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 8, (int)(des->hireDate));
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_step(stmt);
    if(checkRC(self, rc))
        goto fin;

    fin :
    sqlite3_finalize(stmt);
    return;
}

designer * des_db_get_designer(des_db_t * self, unsigned int id)
{
    int rc  = 0;
    designer * des = NULL;
    sqlite3_stmt * stmt;
    char * sql = "SELECT  * FROM "TABLE_NAME" "
                 "WHERE Id = ?";
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_prepare_v2(self->db, sql, strlen(sql), &stmt, NULL);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 1, id);
    if(checkRC(self, rc))
        goto fin;
    sqlite3_step(stmt);
    des = malloc(sizeof(designer));
    des->id = id;
    fill_designer(stmt, des);
    fin:
    sqlite3_finalize(stmt);
    return des;
}

void des_db_update_designer(des_db_t * self, designer * des)
{
    int rc  = 0;
    sqlite3_stmt * stmt;
    char * sql = "UPDATE  "TABLE_NAME" "
                "SET Name = ?, Surname = ?, averageVertices = ?, Experience = ?, Salary = ?, ProjectsCount = ?, HireDate = ? "
                 "WHERE Id = ?;";
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_prepare_v2(self->db, sql, strlen(sql), &stmt, NULL);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 8, des->id);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_text(stmt, 1, des->name, strlen(des->name), SQLITE_STATIC);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_text(stmt, 2, des->surname, strlen(des->surname), SQLITE_STATIC);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_double(stmt, 3, des->averageVertices);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 4, des->experience);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 5, des->experience);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_double(stmt, 6, (des->salary));
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 7, des->projectsCount);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_step(stmt);
    if(checkRC(self, rc))
        goto fin;

    fin:
    sqlite3_finalize(stmt);
    return;
}

void des_db_delete_designer(des_db_t * self, unsigned int id)
{
    int rc  = 0;
    sqlite3_stmt * stmt;
    char * sql = "DELETE FROM "TABLE_NAME" "
                 "WHERE Id = ?;";
    rc = sqlite3_prepare_v2(self->db, sql, strlen(sql), &stmt, NULL);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 1, id);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_step(stmt);
    if(checkRC(self, rc))
        goto fin;
    fin:
    sqlite3_finalize(stmt);
    return;
}

designer * des_db_get_filtered_designers(des_db_t * self, int websitesCount, float salary, size_t * pcount)
{
    int rc = 0;
    int count = 0;
    int proccessed_count = 0;
    designer * designers = NULL;
    sqlite3_stmt * stmt;
    char * sql_select = "SELECT * FROM "TABLE_NAME" "
                 "WHERE ProjectCount > ? AND Salary < ? ;";
    char * sql_count = "SELECT COUNT(*) FROM "TABLE_NAME" "
             "WHERE ProjectCount > ? AND Salary < ? ;";

    // Get designers count
    rc = sqlite3_prepare_v2(self->db, sql_count, strlen(sql_count), &stmt, NULL);
    rc = sqlite3_bind_int(stmt, 1, websitesCount);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_double(stmt, 2, salary);
    if(checkRC(self, rc))
        goto fin;
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_step(stmt);
    if(checkRC(self, rc))
        goto fin;
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    designers = malloc(sizeof(designer) * count);
    // Get the designers themself
    rc = sqlite3_prepare_v2(self->db, sql_select, strlen(sql_select), &stmt, NULL);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_int(stmt, 1, websitesCount);
    if(checkRC(self, rc))
        goto fin;
    rc = sqlite3_bind_double(stmt, 2, salary);
    if(checkRC(self, rc))
        goto fin;
    for(proccessed_count = 0; proccessed_count < count; proccessed_count++)
    {
        rc = sqlite3_step(stmt);
        if(checkRC(self, rc))
            goto fin;
        fill_designer(stmt, &(designers[proccessed_count]));
    }
    *pcount = proccessed_count;
    fin:
    sqlite3_finalize(stmt);
    return designers;


}
