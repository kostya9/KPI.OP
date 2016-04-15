#include "designer_xml.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <time.h>
#include <libxml/xmlmemory.h>
#include <string.h>
static void parse_designer(designer_s * des, xmlNodePtr des_node);
int designers_fill_array(designer_s * designers_arr, size_t size)
{
    LIBXML_TEST_VERSION
    xmlDocPtr doc;
    xmlNodePtr cur;
    doc = xmlParseFile("designers.xml");

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return 1;
    }
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return 1;
    }
    xmlNodePtr des = cur->children->next;
    int i;
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
    return i;
}
static void copy_xmlcontents_to_buffer(char * buffer, xmlNodePtr node)
{
    // XMLFREE THINGY
    xmlGlobalState xmlMem = {};
    xmlMemGet(  &xmlMem.xmlFree,
                &xmlMem.xmlMalloc,
                &xmlMem.xmlRealloc,
                &xmlMem.xmlMemStrdup
                );
    char * content = (char *)xmlNodeGetContent(node);
    strcpy(buffer, content);
    xmlMem.xmlFree(content);
}
static void parse_designer(designer_s * des, xmlNodePtr des_node)
{
    xmlNodePtr des_child = des_node->children->next;
    do
    {
        if(des_child->type != XML_ELEMENT_NODE)
            continue;
        if(xmlStrEqual((xmlChar*)des_child->name, (xmlChar*)"name"))
        {
            copy_xmlcontents_to_buffer(des->name, des_child);
        }
        else if(xmlStrEqual((xmlChar*)des_child->name, (xmlChar*)"surname"))
        {
            copy_xmlcontents_to_buffer(des->surname, des_child);
        }
        else if(xmlStrEqual((xmlChar*)des_child->name, (xmlChar*)"department"))
        {
            copy_xmlcontents_to_buffer(des->dep.name, des_child);
            copy_xmlcontents_to_buffer(des->dep.company, des_child);
            char * company = (char*)xmlGetProp(des_child, (xmlChar*)"company");
            strcpy(des->dep.company, company);
            free(company);
        }
        else if(xmlStrEqual((xmlChar*)des_child->name, (xmlChar*)"motto"))
        {
            copy_xmlcontents_to_buffer(des->motto, des_child);
        }
        else if(xmlStrEqual((xmlChar*)des_child->name, (xmlChar*)"experienceYears"))
        {
            char buffer[STRING_LENGTH_MAX];
            copy_xmlcontents_to_buffer(buffer, des_child);
            int years = atoi(buffer);
            des->experienceYears = years;
        }
        else if(xmlStrEqual((xmlChar*)des_child->name, (xmlChar*)"statistics"))
        {
            xmlNodePtr des_child_stats = des_child->children->next;
            do
            {
                if(des_child_stats->type != XML_ELEMENT_NODE)
                    continue;
                if(xmlStrEqual(des_child_stats->name, (xmlChar*)"averagePolygons"))
                {
                    char buffer[STRING_LENGTH_MAX];
                    copy_xmlcontents_to_buffer(buffer, des_child_stats);
                    float poly = atof(buffer);
                    des->stats.averagePolygons = poly;
                }
                else if(xmlStrEqual(des_child_stats->name, (xmlChar*)"averageVertices"))
                {
                    char buffer[STRING_LENGTH_MAX];
                    copy_xmlcontents_to_buffer(buffer, des_child_stats);
                    float vert = atof(buffer);
                    des->stats.averageVertices = vert;
                }
                else if(xmlStrEqual(des_child_stats->name, (xmlChar*)"hireDate"))
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
