#include "student.h"

student student_new(char * name, char * group_name, size_t variant)
{
	student st;
	strcpy(st.name, name);
	strcpy(st.group_name, group_name);
	st.variant = variant;
	return st;
}

char * student_to_xml(student * student)
{
	
}
