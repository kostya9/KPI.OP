#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>
#include <enterprise.h>
static void add_employee_CreateEmployeeAdd_IsInEmployeeList(void ** state)
{
	enterprise_t * enterprise = enterprise_new("OP corp.", "Mr. Genius");
	project_t * project = enterpise_create_project(enterprise, 10, "Ayy Lmao", 4);
	employee_t * employee = enterprise_create_employee(enterprise, "Halo", "Aloh", "Senior codewriter");
	int rc = enterprise_add_employee_to_project(enterprise, employee, 10);
	list_t * list = enterprise_get_employee_list(enterprise);
	int index = list_findIndex(list, employee);
	assert_int_not_equal(index, -1);
}
static void add_employee_CreateEmployeeAdd_ReturnCodeSuccess(void ** state)
{
	enterprise_t * enterprise = enterprise_new("OP corp.", "Mr. Genius");
	project_t * project = enterpise_create_project(enterprise, 10, "Ayy Lmao", 4);
	employee_t * employee = enterprise_create_employee(enterprise, "Halo", "Aloh", "Senior codewriter");
	int rc = enterprise_add_employee_to_project(enterprise, employee, 10);
	assert_int_equal(rc, OPERATION_SUCCESS);
}
static void add_employee_AddNullEmployee_ReturnCodeError(void ** state)
{
	enterprise_t * enterprise = enterprise_new("OP corp.", "Mr. Genius");
	project_t * project = enterpise_create_project(enterprise, 10, "Ayy Lmao", 4);
	employee_t * employee = NULL;
	int rc = enterprise_add_employee_to_project(enterprise, employee, 10);
	assert_int_equal(rc, OPERATION_ERROR);
}
static void add_employee_AddNullEmployee_GetEmployeeNameIsEqual(void ** state)
{
	enterprise_t * enterprise = enterprise_new("OP corp.", "Mr. Genius");
	project_t * project = enterpise_create_project(enterprise, 10, "Ayy Lmao", 4);
	employee_t * employee = enterprise_create_employee(enterprise, "Halo", "Aloh", "Senior codewriter");
	int rc = enterprise_add_employee_to_project(enterprise, employee, 10);
	char buffer[100];
	char * expected = "Halo";
	enterprise_get_employee_name(employee, buffer);
	assert_string_equal(expected, buffer);
}
int test()
{
	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(add_employee_CreateEmployeeAdd_ReturnCodeSuccess),
		cmocka_unit_test(add_employee_AddNullEmployee_ReturnCodeError),
		cmocka_unit_test(add_employee_CreateEmployeeAdd_IsInEmployeeList),
		cmocka_unit_test(add_employee_AddNullEmployee_GetEmployeeNameIsEqual)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}