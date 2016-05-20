#include "html_builder.h"
#include <string.h>
#include <stdio.h>
void html_builder_home(http_server_t * self, char * buffer)
{
	strcpy(buffer, "<html> <head> <link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\"> <title> HOME PAGE OF DESIGNERS BUREAU </title> </head> <body> <div class=\"container\"> <div class=\"jumbotron\"> <h1> Homepage AYY</h1> </div> </div> <div class=\"container\"> <a class=\"btn btn-primary btn-default btn-lg btn-block\" href=\"\\designers\">Get those designers</a> </div> </body> </html>");
}

void html_builder_designers(http_server_t * self, char * buffer)
{
	char html_page[BUFFER_LENGTH];
	char designers_table[BUFFER_LENGTH] = "";
	char designers_rows[BUFFER_LENGTH] ="";
	size_t count = self->size;
	for (unsigned int i = 0; i < count; i++)
	{
		char designer_buf[BUFFER_LENGTH];
		designer * des = &(self->data[i]);
		sprintf(designer_buf, "<tr><td>%s</td>"
			"<td>%s</td>"
			"<td> <a class=\"btn btn-primary btn-default btn-block\" href=\"/designers/%i\">View</a></td></tr>", des->name, des->surname, des->id);
		strcat(designers_rows, designer_buf);
	}
	sprintf(designers_table, " <div class=\"container\"><table class=\"table table-bordered table-striped \""
		"<thead><tr><th>Name</th><th>Surname</th><th><a class=\"btn btn-primary btn-default btn-block\" href=\"/new-designer\">Add New</a></th></tr><tbody>%s</tbody></table></div>", designers_rows);
	sprintf(html_page, "<html><link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha/css/bootstrap.min.css\"> <title> Designers list </title><body>"
		"<nav class=\"navbar navbar-dark bg-inverse\"><a class=\"navbar-brand\" href=\"#\">Designers</a><ul class=\"nav navbar-nav\"><li class=\"nav-item\"><a class=\"nav-link\" href=\"/\">Home</a></li></ul></nav>"
		"<br />""<div class=\"container text-center\">"
		"<h2>Designers</h2></div>"
						"%s</body></html>", designers_table);
	strcpy(buffer, html_page);
}

void html_builder_designer(http_server_t * self, designer * des, char * buffer)
{
	char html_page[BUFFER_LENGTH];
	char designers_table[BUFFER_LENGTH] = "";
	char designers_rows[BUFFER_LENGTH] = "";
	size_t count = self->size;
	char designer_buf[BUFFER_LENGTH];
	//10
	struct tm  * date = localtime(&(des->stats.hireDate));
	sprintf(designer_buf, "<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%i</td><td>%f</td><td>%f</td><td>%i-%i-%i</td>"
		"<td> <a class=\"btn btn-primary btn-default btn-block\" onClick=\"doDelete(\'%i\')\" href=\"\\designers\">Delete</a></td></tr>", 
		des->name, des->surname,des->dep.name, des->dep.company, des->motto, des->experienceYears, des->stats.averagePolygons, des->stats.averageVertices, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, des->id);
	strcat(designers_rows, designer_buf);
	sprintf(designers_table, "<div class=\"container\"><div class=\"jumbotron\"><table class=\"table table-reflow table-bordered table-striped\">"
		"<thead><tr><th>Name</th><th>Surname</th><th>Department</th><th>Company</th><th>Motto</th><th>experienceYears</th><th>AveragePolygons</th> <th>AverageVertices</th><th>HireDate</th><th></th></tr><tbody>%s</tbody></table></div></div>", designers_rows);
	sprintf(html_page, "<html> <head><title> Designer</title><link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha/css/bootstrap.min.css\"></head><body>"
		"<nav class=\"navbar navbar-dark bg-inverse\"><a class=\"navbar-brand\" href=\"#\">Designers</a><ul class=\"nav navbar-nav\"><li class=\"nav-item\"><a class=\"nav-link\" href=\"/\">Home</a></li></ul></nav>"
		"<div class=\"container text-center\"><h2>Designer</h2></div>"
		"%s</body>"
		"<script> function doDelete(i) { 		var xhttp = new XMLHttpRequest(); 		xhttp.open(\"DELETE\", \"http://127.0.0.1:8080/designers/\" + i, true); 		xhttp.send(); 	} </script>"
		"</html>", designers_table);
	strcpy(buffer, html_page);
}

void html_builder_new_designer(http_server_t * self, char * buffer)
{
	char html_buf[BUFFER_LENGTH];
	FILE * f = fopen("html_test/input.html", "r");
	size_t sz = fread(html_buf, sizeof(char), BUFFER_LENGTH, f);
	fclose(f);
	html_buf[sz] = '\0';
	strcpy(buffer, html_buf);
}
