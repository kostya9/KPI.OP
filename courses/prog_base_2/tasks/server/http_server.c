#include "http_server.h"
#include "http.h"
#include "libsocket/socket.h"
#include "designer.h"
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "designer_xml.h"
#define BUFFER_LENGTH 4096
#define arr_len(a) sizeof(a)/sizeof(a[0])
#define MAX_DESIGNERS_COUNT 100
typedef struct http_server_s{
    socket_t * server_sock;
} http_server_s;
http_server_t * http_server_new(int port)
{
    socket_t * server_sock = socket_new();
    if(server_sock == NULL)
        return NULL;
    socket_bind(server_sock, port);
    http_server_t * server = malloc(sizeof(http_server_s));
    server->server_sock = server_sock;
    return server;
}
static int delete_designer(designer_s designers[], size_t des_count,int id)
{
    for(int i = 0; i < des_count ; i++)
    {
        if(designers[i].id != id)
            continue;

        designers[i] = designers[des_count - 1];
        return des_count - 1;
    }
    return des_count;
}
static void error_page_no_id(char * buffer)
{
    char * message = "There is no such ID";
    sprintf(buffer, "HTTP/1.1 200 OK\r\n"
                    "Content-length:%zu\r\n\r\n%s",
                    strlen(message), message
            );
}
static void error_page_illegal_arguments(char * buffer)
{
    char * message = "|ERROR ILLEGAL ARGUMENTS|\nCheck that name/surname/motto/company/department string length is less than 100\n"
                    "Check the format of the hireDate and that averageVertices, averagePolygons are floats, experienceYears is an integer";
    sprintf(buffer, "HTTP/1.1 200 OK\r\n"
                    "Content-length:%zu\r\n\r\n%s",
                    strlen(message), message
            );
}
static int message_proccess(char * output, size_t output_size, char * input, size_t input_size,
                             designer_s * designers, size_t * des_count)
{
    char buffer[BUFFER_LENGTH];
    http_request_t req = http_request_parse(input);
    if(strcmp(req.method, "GET") == 0)
    {
        if(strcmp(req.uri, "/designers") == 0)
        {
            designer_array_to_xml_string(buffer, arr_len(buffer), designers, *des_count);
            strcpy(output, buffer);
            return 0;
        }
        else if(strstr(req.uri, "/designers/") > 0)
        {
            int id;
            int count = sscanf(req.uri, "/designers/%i", &id);
            if(count != 1)
            {
                error_page_no_id(output);
                return 0;
            }
            designer_s * designer = designer_get_designer_by_id(id, designers, *des_count);
            if(designer == NULL)
            {
                error_page_no_id(output);
                return 0;
            }
            designer_to_xml_string(buffer, arr_len(buffer), designer);
            sprintf(output, "HTTP/1.1 200 OK\r\n"
                "Content-length:%zu\r\n\r\n%s",
                strlen(buffer), buffer
            );
            return 0;
        }
        else if (strcmp(req.uri, "/exit") == 0)
            return 1;
        else
        {
            strcpy(buffer, "Unknown page");
            sprintf(output, "HTTP/1.1 200 OK\r\n"
            "Content-length:%zu\r\n\r\n%s",
            strlen(buffer), buffer
            );
            return 0;
        }
    }
    else if(strcmp(req.method, "POST") == 0)
    {
        int id;
        int count = sscanf(req.uri, "/designers/%i", &id);
        if(count != 1)
        {
            error_page_no_id(output);
            return 0;
        }
        designer_s * designer = designer_get_designer_by_id(id, designers, *des_count);
        if(designer == NULL)
        {
            error_page_no_id(output);
            return 0;
        }
        for(int i = 0; i < req.formLength; i++)
        {
            if(strcmp(req.form[i].key, "name") == 0)
            {
                if(strlen(req.form[i].value) > STRING_LENGTH_MAX)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                strcpy(designer->name, req.form[i].value);
            }
            else if(strcmp(req.form[i].key, "surname") == 0)
            {
                if(strlen(req.form[i].value) > STRING_LENGTH_MAX)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                strcpy(designer->surname, req.form[i].value);
            }
            else if(strcmp(req.form[i].key, "motto") == 0)
            {
                if(strlen(req.form[i].value) > STRING_LENGTH_MAX)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                strcpy(designer->motto, req.form[i].value);
            }
            else if(strcmp(req.form[i].key, "experienceYears") == 0)
            {
                int val;
                int status = sscanf(req.form[i].value, "%i", &val);
                if(status < 1)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                designer->experienceYears = val;
            }
            else if(strcmp(req.form[i].key, "company") == 0)
            {
                if(strlen(req.form[i].value) > STRING_LENGTH_MAX)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                strcpy(designer->dep.company, req.form[i].value);
            }
            else if(strcmp(req.form[i].key, "department") == 0)
            {
                if(strlen(req.form[i].value) > STRING_LENGTH_MAX)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                strcpy(designer->dep.name, req.form[i].value);
            }
            else if(strcmp(req.form[i].key, "averagePolygons") == 0)
            {
                float val;
                int status = sscanf(req.form[i].value, "%f", &val);
                if(status < 1)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                designer->stats.averagePolygons = val;
            }
            else if(strcmp(req.form[i].key, "averageVertices") == 0)
            {
                float val;
                int status = sscanf(req.form[i].value, "%f", &val);
                if(status < 1)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                designer->stats.averageVertices = val;
            }
            else if(strcmp(req.form[i].key, "hireDate") == 0)
            {
                struct tm hire_time;
                memset(&hire_time, 0, sizeof(struct tm));
                int status = sscanf(req.form[i].value, "%i-%i-%i", &(hire_time.tm_year), &(hire_time.tm_mon), &(hire_time.tm_mday));
                if(status < 3)
                {
                    error_page_illegal_arguments(output);
                    return 0;
                }
                hire_time.tm_year -= 1900;
                hire_time.tm_mon -= 1;
                designer->stats.hireDate = mktime(&hire_time);
            }
        }
        designer_array_to_xml_string(buffer, arr_len(buffer), designers, *des_count);
        sprintf(output, "HTTP/1.1 200 OK\r\n"
            "Content-length:%zu\r\n\r\nPOST SUCCEEDED\n%s",
            strlen(buffer), buffer
        );
        return 0;

    }
    else if(strcmp(req.method, "DELETE") == 0)
    {
        int prev_des_count = des_count;
        if(strstr(req.uri, "/designers/") > 0)
        {
            int id;
            int count = sscanf(req.uri, "/designers/%i", &id);
            if(count != 1)
            {
                error_page_no_id(output);
                return 0;
            }
            (*des_count) = delete_designer(designers, *des_count, id);
        }
        designer_array_to_xml_string(buffer, arr_len(buffer), designers, *des_count);
        if(prev_des_count == des_count)
        {
            error_page_no_id(output);
            return 0;
        }
        sprintf(output, "HTTP/1.1 200 OK\r\n"
            "Content-length:%zu\r\n\r\DELETE SUCCEEDED\n%s",
            strlen(buffer), buffer
        );
        return 0;
    }
    return -1;
}
void http_server_start(http_server_t * server, char * path_to_designers)
{
    char input[BUFFER_LENGTH];
    char output[BUFFER_LENGTH] = "HEY";
    socket_listen(server->server_sock);
    designer_s designers[MAX_DESIGNERS_COUNT];
    size_t des_count = designers_fill_array(designers, MAX_DESIGNERS_COUNT);
    for(int i = 0; i < des_count; i++)
    {
        int id;
        do
            id = rand();
        while(designer_get_designer_by_id(id, designers, des_count) != NULL);
        designers[i].id = id;
    }
    while(1)
    {
        socket_t * client = socket_accept(server->server_sock);
        int sz = socket_read(client, input, arr_len(input));
        if(message_proccess(output, arr_len(output), input, sz,designers, &des_count) == 1)
        {
            socket_write_string(client, "BYEBYE");
            socket_close(client);
            socket_free(client);
            return;
        }
        socket_write(client, output, strlen(output));
        socket_close(client);
        socket_free(client);
    }
}
void http_server_delete(http_server_t * server)
{
    socket_close(server->server_sock);
    socket_free(server->server_sock);
    free(server);
}
