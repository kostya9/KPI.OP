#include "student.h"
#include "http_server.h"
#include <libxml\xmlwriter.h>
#include <libxml\encoding.h>
#include <string.h>
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
	char * output = malloc(BUFFER_LENGTH);
	char write_buffer[BUFFER_LENGTH];
	xmlTextWriterPtr writer;
	xmlBufferPtr xml_buf;
	xml_buf = xmlBufferCreate();
	writer = xmlNewTextWriterMemory(xml_buf, 0);
	xmlTextWriterStartDocument(writer, "1.0", "ASCII", NULL);
	xmlTextWriterStartElement(writer, "student");
	xmlTextWriterWriteElement(writer, "name", student->name);
	xmlTextWriterWriteElement(writer, "group", student->group_name);
	char buff[100];
	xmlTextWriterWriteElement(writer, "variant", itoa(student->variant, buff, 10));
	xmlTextWriterEndElement(writer);
	xmlTextWriterEndDocument(writer);
	xmlFreeTextWriter(writer);
	strcpy(output, (const char *)(xml_buf->content));
	return output;
}
