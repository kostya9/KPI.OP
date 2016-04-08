#include "designers.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <time.h>
#include <libxml/xmlmemory.h>
static void parse_designer(designer * des, xmlNodePtr des_node);
int designers_fill_array(designer * designers_arr, size_t size)
{
    LIBXML_TEST_VERSION
    xmlDocPtr doc;
    xmlNodePtr cur;
    doc = xmlParseFile("designers.xml");

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return;
    }
    xmlNodePtr des = cur->children->next;
    for(int i = 0; i < size && des != NULL; des = des->next, i++)
    {
        if(des->type != XML_ELEMENT_NODE)
        {
            i--;
            continue;
        }
        parse_designer(&designers_arr[i], des);
    }
    xmlFreeDoc(doc);
}
static void copy_xmlcontents_to_buffer(char * buffer, xmlNodePtr node)
{
    char * content = xmlNodeGetContent(node);
    strcpy(buffer, content);
    xmlFree(content);
}
static void parse_designer(designer * des, xmlNodePtr des_node)
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
        else if(xmlStrEqual(des_child->name, "department"))
        {
            copy_xmlcontents_to_buffer(des->dep.name, des_child);
            copy_xmlcontents_to_buffer(des->dep.company, des_child);
            char * company = xmlGetProp(des_child, "company");
            strcpy(des->dep.company, company);
            free(company);
        }
        else if(xmlStrEqual(des_child->name, "motto"))
        {
            copy_xmlcontents_to_buffer(des->motto, des_child);
        }
        else if(xmlStrEqual(des_child->name, "experienceYears"))
        {
            char buffer[STRING_LENGTH_MAX];
            copy_xmlcontents_to_buffer(buffer, des_child);
            int years = atoi(buffer);
            des->experienceYears = years;
        }
        else if(xmlStrEqual(des_child->name, "statistics"))
        {
            xmlNodePtr des_child_stats = des_child->children->next;
            do
            {
                if(des_child_stats->type != XML_ELEMENT_NODE)
                    continue;
                if(xmlStrEqual(des_child_stats->name, "averagePolygons"))
                {
                    char buffer[STRING_LENGTH_MAX];
                    copy_xmlcontents_to_buffer(buffer, des_child_stats);
                    float poly = atof(buffer);
                    des->stats.averagePolygons = poly;
                }
                else if(xmlStrEqual(des_child_stats->name, "averageVertices"))
                {
                    char buffer[STRING_LENGTH_MAX];
                    copy_xmlcontents_to_buffer(buffer, des_child_stats);
                    float vert = atof(buffer);
                    des->stats.averageVertices = vert;
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
                    des->stats.hireDate = mktime(&hire_time);
                }
            }while((des_child_stats = des_child_stats->next) != NULL);
        }
    }while((des_child = des_child->next)!=NULL);
}
