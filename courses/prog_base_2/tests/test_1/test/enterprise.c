#include "enterprise.h"
#include <stdio.h>
#include <string.h>
#define NO_PROJECT -1
struct enterprise_s
{
	char name[BUFFER_LENGTH];
	char owner_name[BUFFER_LENGTH];
	list_t * list_projects;
	list_t * list_employees;
};
struct employee_s {
	char name[BUFFER_LENGTH];
	char surname[BUFFER_LENGTH];
	char position[BUFFER_LENGTH];
	int curproject_id;
};
typedef struct project_s {
	int id;
	char name[BUFFER_LENGTH];
	list_t * callbacks;
	char difficulty;
} project_s;

enterprise_t * enterprise_new(char * name, char * owner_name)
{
	enterprise_t * self = (enterprise_t *)malloc(sizeof(enterprise_t));
	list_t * list_projects = list_new();
	list_t * list_employees = list_new();
	strcpy(self->name, name);
	strcpy(self->owner_name, owner_name);
	self->list_projects = list_projects;
	self->list_employees = list_employees;
	return self;
}

project_t * enterprise_get_project(enterprise_t * self, int id)
{
	for (int i = 0; i < list_getSize(self->list_projects); i++)
	{
		project_t * curproj = list_get(self->list_projects, i);
		if (curproj->id == id)
			return curproj;
	}
	return NULL;
}

list_t * enterprise_get_project_list(enterprise_t * self)
{
	if (self == NULL)
		return NULL;
	return self->list_projects;
}

project_t * enterpise_create_project(enterprise_t * self, int id, char * name, char difficulty)
{
	if (self == NULL || name == NULL)
		return NULL;
	for (int i = 0; i < list_getSize(self->list_projects); i++)
	{
		project_t * project = list_get(self->list_projects, i);
		if (project->id == id)
			return NULL;
	}
	project_s * project = malloc(sizeof(project_s));
	strcpy(project->name, name);
	project->id = id;
	project->difficulty = difficulty;
	project->callbacks = list_new();
	list_push_back(self->list_projects, project);
}
int enterprise_get_owner_name(enterprise_t * self, char * buffer)
{
	if (self == NULL || buffer == NULL)
		return OPERATION_ERROR;
	strcpy(buffer, self->owner_name);
	return OPERATION_SUCCESS;
}

employee_t * enterprise_create_employee(enterprise_t * self, char *name, char *surname, char *position)
{
	if (self == NULL || name == NULL || surname == NULL || position == NULL)
		return NULL;
	employee_t * employee = malloc(sizeof(employee_t));
	employee->curproject_id = NO_PROJECT;
	strcpy(employee->name, name);
	strcpy(employee->surname, surname);
	strcpy(employee->position, position);
	list_push_back(self->list_employees, employee);
	return employee;
}

int enterprise_add_employee_to_project(enterprise_t * self, employee_t * employee, int project_id)
{
	if (self == NULL || employee == NULL)
		return OPERATION_ERROR;
	project_t * project = enterprise_get_project(self, project_id);
	if (project == NULL)
		return OPERATION_ERROR;
	employee->curproject_id = project_id;
	return OPERATION_SUCCESS;
}

size_t enterprise_get_employee_count(enterprise_t * self)
{
	if (self == NULL)
		return 0;
	return list_getSize(self->list_employees);
}

list_t * enterprise_get_employee_list(enterprise_t * self)
{
	if (self == NULL)
		return NULL;
	return list_new_copy(self->list_employees);
}

int enterprise_get_employee_name( employee_t * employee, char * buffer)
{
	if (buffer == NULL || employee == NULL)
		return OPERATION_ERROR;
	strcpy(buffer, employee->name);
	return OPERATION_SUCCESS;
}

int enterprise_remove_employee_from_project(enterprise_t * self, employee_t * employee)
{
	if (self == NULL || employee == NULL)
		return OPERATION_ERROR;
	employee->curproject_id = NO_PROJECT;
	return OPERATION_SUCCESS;
}

list_t * enterprise_get_employees_without_project(enterprise_t * self)
{
	if (self == NULL)
		return NULL;
	list_t * list = list_new();
	for (int i = 0; i < list_getSize(self->list_employees); i++)
	{
		employee_t * employee = list_get(self->list_employees, i);
		if (employee->curproject_id == NO_PROJECT)
			list_push_back(list, employee);
	}
	return list;
}

int enterprise_get_project_name(enterprise_t * self, int project_id, char * buffer)
{
	if (self == NULL || buffer == NULL)
		return OPERATION_ERROR;
	project_t * project = enterprise_get_project(self, project_id);
	if (project == NULL)
		return OPERATION_ERROR;
	strcpy(buffer, project->name);
	return OPERATION_SUCCESS;
}

int enterprise_close_project(enterprise_t * self, int project_id)
{
	if (self == NULL)
		return OPERATION_ERROR;
	project_t * project = enterprise_get_project(self, project_id);
	if (project == NULL)
		return OPERATION_ERROR;
	list_t * employees = list_new();
	for (int i = 0; i < list_getSize(self->list_employees); i++)
	{
		employee_t * employee = list_get(self->list_employees, i);
		if (employee->curproject_id == project_id)
		{
			list_push_back(employees, employee);
			employee->curproject_id = NO_PROJECT;
		}
	}
	int index = list_findIndex(self->list_projects, project);
	for (int i = 0; i < list_getSize(project->callbacks); i++)
	{
		enerprise_delete_project_cb cb = list_get(project->callbacks, i);
		cb(project->id, project->name, list_new_copy(employees));
	}
	list_free(employees);
	list_free(project->callbacks);
	list_remove(self->list_projects, index);
	free(project);
	return OPERATION_SUCCESS;
}

int enterprise_add_cb_project_delete(enterprise_t * self, int project_id, enerprise_delete_project_cb cb)
{
	if (self == NULL)
		return OPERATION_ERROR;
	project_t * project = enterprise_get_project(self, project_id);
	if (project == NULL)
		return OPERATION_ERROR;
	list_push_back(project->callbacks, cb);
	return OPERATION_SUCCESS;
}

int enterprise_delete_cb_project_delete(enterprise_t * self, int project_id, enerprise_delete_project_cb cb)
{
	return OPERATION_ERROR;
	project_t * project = enterprise_get_project(self, project_id);
	if (project == NULL)
		return OPERATION_ERROR;
	int index = list_findIndex(project->callbacks, cb);
	if (index == -1)
		return OPERATION_ERROR;
	list_remove(project->callbacks, index);
	return OPERATION_SUCCESS;
}

void enterprise_delete(enterprise_t * self)
{
	for (int i = 0; i < list_getSize(self->list_projects); i++)
	{
		project_t * curproj = list_get(self->list_projects, i);
		list_free(curproj->callbacks);
		free(curproj);
	}
	for (int i = 0; i < list_getSize(self->list_employees); i++)
	{
		employee_t * employee = list_get(self->list_employees, i);
		free(employee);
	}
	list_free(self->list_employees);
	list_free(self->list_projects);
	free(self);
}

