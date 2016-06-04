#include "designers.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <time.h>
#include <libxml/xmlmemory.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#define BUFFER_LENGTH 4096
static void parse_designer(designer_t * des, xmlNodePtr des_node);
int designers_delete_designer(designer_t designers[], size_t des_count, int id)
{
	for (unsigned int i = 0; i < des_count; i++)
	{
		if (designers[i].id != id)
			continue;

		designers[i] = designers[des_count - 1];
		return des_count - 1;
	}
	return des_count;
}
static void designer_to_xml_buffer(xmlTextWriterPtr writer, designer_t * designer)
{
	int bytes_written;
	char write_buffer[100];
	bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"designer");
	sprintf(write_buffer, "%i", designer->id);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"id", (xmlChar*)write_buffer);
	//Name
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"name", (xmlChar*)designer->name);
	//Surname
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"surname", (xmlChar*)designer->surname);
	char buff[BUFFER_LENGTH];
	itoa(designer->projectsCount, buff, 10);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"projectCount", (xmlChar*)buff);
	sprintf(buff, "%f", designer->salary);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"salary", (xmlChar*)buff);
	// ExperienceYears
	sprintf(write_buffer, "%i", designer->experience);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"experienceYears", (xmlChar*)(xmlChar*)write_buffer);
	// Statistics
	bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"statistics");
	//Double to string
	sprintf(write_buffer, "%.2f", designer->averageVertices);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"averageVertices", (xmlChar*)write_buffer);
	// Time to standart time
	struct tm *tminfo;
	tminfo = localtime(&(designer->hireDate));
	sprintf(write_buffer, "%i-%i-%i", tminfo->tm_year + 1900, tminfo->tm_mon + 1, tminfo->tm_mday);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"hireDate", (xmlChar*)write_buffer);
	bytes_written = xmlTextWriterEndElement(writer);

	bytes_written = xmlTextWriterEndElement(writer);
}
void designer_to_xml_string(char * buffer, size_t size, designer_t * designer)
{
	xmlTextWriterPtr writer;
	xmlBufferPtr xml_buf;
	xml_buf = xmlBufferCreate();
	writer = xmlNewTextWriterMemory(xml_buf, 0);
	xmlTextWriterStartDocument(writer, "1.0", "ASCII", "no");
	designer_to_xml_buffer(writer, designer);
	xmlFreeTextWriter(writer);
	strcpy(buffer, (const char *)xml_buf->content);
}
void designer_array_to_xml_string(char * buffer, size_t size, designer_t designers[], size_t designers_count)
{
	xmlTextWriterPtr writer;
	xmlBufferPtr xml_buf;
	xml_buf = xmlBufferCreate();
	writer = xmlNewTextWriterMemory(xml_buf, 0);
	xmlTextWriterStartDocument(writer, "1.0", "ASCII", "no");
	xmlTextWriterStartElement(writer, (xmlChar*) "designers");
	for (unsigned int i = 0; i < designers_count; i++)
	{
		designer_to_xml_buffer(writer, &designers[i]);
	}

	xmlTextWriterEndElement(writer);
	xmlFreeTextWriter(writer);
	strcpy(buffer, (const char *)xml_buf->content);

}
designer_t * designer_get_designer_by_id(int id, designer_t designers[], size_t designers_count)
{
	for (unsigned int i = 0; i < designers_count; i++)
	{
		if (designers[i].id == id)
			return &designers[i];
	}
	return NULL;
}
/*int designers_fill_array(designer_t * designers_arr, size_t size)
{
    LIBXML_TEST_VERSION
    xmlDocPtr doc;
    xmlNodePtr cur;
    doc = xmlParseFile("designers.xml");

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return 0;
    }
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }
    xmlNodePtr des = cur->children->next;
	unsigned int i;
    for(i = 0; i < size && des != NULL; des = des->next, i++)
    {
        if(des->type != XML_ELEMENT_NODE)
        {
            i--;
            continue;
        }
        parse_designer(&designers_arr[i], des);
    }
    xmlFreeDoc(doc);
	for (unsigned int j = 0; j < i; j++)
	{
		int id = findUniqueId(designers_arr, i);
		designers_arr[j].id = id;
	}
	return i;
}*/
int findUniqueId(designer_t designers[], size_t count)
{
	int isUnique = 0;
	int id = 0;
	while (!isUnique)
	{
		isUnique = 1;
		id = rand() % 1000;
		for (unsigned int i = 0; i < count; i++)
		{
			if (designers[i].id == id)
				isUnique = 0;
		}
	}
	return id;
}
static void copy_xmlcontents_to_buffer(char * buffer, xmlNodePtr node)
{
    char * content = xmlNodeGetContent(node);
    strcpy(buffer, content);
    xmlFree(content);
}
static void parse_designer(designer_t * des, xmlNodePtr des_node)
{
    xmlNodePtr des_child = des_node->children->next;
    do
    {
        if(des_child->type != XML_ELEMENT_NODE)
            continue;
        if(xmlStrEqual(des_child->name, "name"))
        {
            copy_xmlcontents_to_buffer(des->name, des_child);
        }
        else if(xmlStrEqual(des_child->name, "surname"))
        {
            copy_xmlcontents_to_buffer(des->surname, des_child);
        }
        else if(xmlStrEqual(des_child->name, "experienceYears"))
        {
            char buffer[STRING_LENGTH_MAX];
            copy_xmlcontents_to_buffer(buffer, des_child);
            int years = atoi(buffer);
            des->experience = years;
        }
        else if(xmlStrEqual(des_child->name, "statistics"))
        {
            xmlNodePtr des_child_stats = des_child->children->next;
            do
            {
                if(des_child_stats->type != XML_ELEMENT_NODE)
                    continue;
                if(xmlStrEqual(des_child_stats->name, "averageVertices"))
                {
                    char buffer[STRING_LENGTH_MAX];
                    copy_xmlcontents_to_buffer(buffer, des_child_stats);
                    float vert = atof(buffer);
                    des->averageVertices = vert;
                }
                else if(xmlStrEqual(des_child_stats->name, "hireDate"))
                {
                    struct tm hire_time;
                    memset(&hire_time, 0, sizeof(struct tm));
                    char buffer[STRING_LENGTH_MAX];
                    copy_xmlcontents_to_buffer(buffer, des_child_stats);
                    sscanf(buffer, "%i-%i-%i", &(hire_time.tm_year), &(hire_time.tm_mon), &(hire_time.tm_mday));
                    hire_time.tm_year -= 1900;
                    hire_time.tm_mon -= 1;
                    des->hireDate = mktime(&hire_time);
                }
            }while((des_child_stats = des_child_stats->next) != NULL);
        }
    }while((des_child = des_child->next)!=NULL);
}
