#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include "http_server.h"
#include "designer.h"
#define BUFFER_LENGTH 4096
#define arr_len(a) sizeof(a)/sizeof(a[0])

// HTTP SERVER ON 80 PORT
// TO POST USE THE ACTUAL NAMES OF VARIABLES WITHOUT STRUCTS IN STRUCTS etc
// /exit to exit from http server
int main(void)
{

    // Lin init
    LIBXML_TEST_VERSION
    lib_init();
    http_server_t * server = http_server_new(80);
    http_server_start(server, "/designers.xml");
    http_server_delete(server);
    lib_free();
    return EXIT_SUCCESS;
}
