#pragma once
#include <enterprise.h>
#include <stdio.h>
#include "unit_test_add_employee.h"
void callback_ok(int id, char * name, list_t *employees);
void callback_rude(int id, char * name, list_t *employees);
int main(void)
{
	puts("Testing add_employee to project...");
	test();
	puts("Making a corporation and adding employees to a project. Waitong for callbacks...");
	enterprise_t * enterprise = enterprise_new("OP corp.", "Mr. Genius");
	employee_t * employee = enterprise_create_employee(enterprise, "Halo", "Aloh", "Senior codewriter");
	employee_t * employee1 = enterprise_create_employee(enterprise, "Halo1", "Aloh", "Senior codewriter");
	project_t * project = enterpise_create_project(enterprise, 10, "Ayy Lmao", 4);
	int rc = enterprise_add_employee_to_project(enterprise, employee, 10);
	rc = enterprise_add_employee_to_project(enterprise, employee1, 10);
	rc = enterprise_add_cb_project_delete(enterprise, 10, callback_ok);
	rc = enterprise_add_cb_project_delete(enterprise, 10, callback_rude);
	enterprise_close_project(enterprise, 10);
	enterprise_delete(enterprise);
	getch();
	return 0;
}

void callback_ok(int id, char * name, list_t *employees)
{
	printf("HEYY!\n Project %s with id %i has stopped. I apologise to these employees : \n", name, id);
	for (int i = 0; i < list_getSize(employees); i++)
	{
		employee_t * employee = list_get(employees, i);
		char buffer[100];
		enterprise_get_employee_name(employee, buffer);
		printf("\t%s\n", buffer);
	}
	list_free(employees);
}

void callback_rude(int id, char * name, list_t *employees)
{
	printf("HEYY!\n Project %s has stopped. I wanted to say something to these employees : \n", name);
	for (int i = 0; i < list_getSize(employees); i++)
	{
		employee_t * employee = list_get(employees, i);
		char buffer[100];
		enterprise_get_employee_name(employee, buffer);
		printf("\t%s, GTFO OUT OF HERE\n", buffer);
	}
	list_free(employees);
}