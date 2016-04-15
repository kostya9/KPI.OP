#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "designer.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#define BUFFER_LENGTH 4096
#define arr_len(a) sizeof(a)/sizeof(a[0])
static void print_error(char * error)
{
    fprintf(stderr, "Error occured : %s", error);
}
designer_s * designer_get_designer_by_id(int id, designer_s designers[], size_t designers_count)
{
    for(int i = 0; i < designers_count; i++)
    {
        if(designers[i].id == id)
            return &designers[i];
    }
    return NULL;
}
static void designer_to_xml_buffer(xmlTextWriterPtr writer, designer_s * designer)
{
    int bytes_written;
    char write_buffer[100];
    bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"designer");
    sprintf(write_buffer, "%i", designer->id);
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"id", (xmlChar*) write_buffer);
    //Name
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"name", (xmlChar*) designer->name);
    //Surname
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"surname", (xmlChar*) designer->surname);
    //Department
    bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"department");
    bytes_written = xmlTextWriterWriteAttribute(writer, (xmlChar*)"company", (xmlChar*)designer->dep.company);
    bytes_written = xmlTextWriterWriteString(writer, (xmlChar*) designer->dep.name);
    bytes_written = xmlTextWriterEndElement(writer);
    //Motto
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"motto", (xmlChar*) designer->motto);
    // ExperienceYears
    sprintf(write_buffer, "%i", designer->experienceYears);
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"experienceYears", (xmlChar*) (xmlChar*)write_buffer);
    // Statistics
    bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"statistics");

    sprintf(write_buffer, "%.2f", designer->stats.averagePolygons);
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"averagePolygons", (xmlChar*) write_buffer);
    //Double to string
    sprintf(write_buffer, "%.2f", designer->stats.averageVertices);
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"averageVertices", (xmlChar*) write_buffer);
    // Time to standart time
    struct tm *tminfo;
    tminfo = localtime(&(designer->stats.hireDate));
    sprintf(write_buffer, "%i-%i-%i", tminfo->tm_year + 1900, tminfo->tm_mon + 1, tminfo->tm_mday);
    bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"hireDate", (xmlChar*) write_buffer);
    bytes_written = xmlTextWriterEndElement(writer);

    bytes_written = xmlTextWriterEndElement(writer);
}
void designer_to_xml_string(char * buffer, size_t size, designer_s * designer)
{
    xmlTextWriterPtr writer;
    xmlBufferPtr xml_buf;
    xml_buf = xmlBufferCreate();
    writer = xmlNewTextWriterMemory(xml_buf, 0);
    designer_to_xml_buffer(writer, designer);
    xmlFreeTextWriter(writer);
    strcpy(buffer, (const char *)xml_buf->content);
}
void designer_array_to_xml_string(char * buffer, size_t size, designer_s designers[], size_t designers_count)
{
    int bytes_written;
    xmlTextWriterPtr writer;
    xmlBufferPtr xml_buf;
    xml_buf = xmlBufferCreate();
    writer = xmlNewTextWriterMemory(xml_buf, 0);

    xmlTextWriterStartElement(writer, (xmlChar*) "designers");
    for(int i = 0; i < designers_count; i++)
    {
        designer_to_xml_buffer(writer, &designers[i]);
    }

    xmlTextWriterEndElement(writer);
    xmlFreeTextWriter(writer);
    strcpy(buffer, (const char *)xml_buf->content);

}
