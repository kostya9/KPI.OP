#pragma once
#include "list/list.h"
#define OPERATION_SUCCESS 0
#define OPERATION_ERROR 1
#define BUFFER_LENGTH 128
typedef void(*enerprise_delete_project_cb)(int id, char * name, list_t *employees);
typedef struct enterprise_s enterprise_t;
typedef struct employee_s employee_t;
typedef struct project_s project_t;

enterprise_t * enterprise_new(char * name, char *owner_name);

list_t * enterprise_get_project_list(enterprise_t * self);
project_t * enterpise_create_project(enterprise_t * self, int id, char * name, char difficulty);
project_t * enterprise_get_project(enterprise_t * self, int id);
int enterprise_get_owner_name(enterprise_t * self, char * buffer);

size_t enterprise_get_employee_count(enterprise_t * self);
list_t * enterprise_get_employee_list(enterprise_t * self);
int enterprise_get_employee_name(employee_t * employee, char * buffer);

employee_t * enterprise_create_employee(enterprise_t * self, char *name, char *surname, char *position);
int enterprise_add_employee_to_project(enterprise_t * self, employee_t * employee, int project_id);
int enterprise_remove_employee_from_project(enterprise_t * self, employee_t * employee);
list_t * enterprise_get_employees_without_project(enterprise_t * self);

int enterprise_get_project_name(enterprise_t * self, int project_id, char * buffer);

int enterprise_close_project(enterprise_t * self, int project_id);
int enterprise_add_cb_project_delete(enterprise_t * self, int project_id, enerprise_delete_project_cb cb);
int enterprise_delete_cb_project_delete(enterprise_t * self, int project_id, enerprise_delete_project_cb cb);
void enterprise_delete(enterprise_t * self);
