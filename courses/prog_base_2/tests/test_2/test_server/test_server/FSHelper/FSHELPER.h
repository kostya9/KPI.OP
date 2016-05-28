#include <time.h>
#include "../list/list.h"
/**
*   @return the existence of directory
*/
int dir_exists(const char * dirname);

/**
*   Prints out list of files in directory
*
*   @return number of files
*/
list_t * dir_getFilesList(const char * dirname);
/**
*   @return the existence of file
*/
int file_exists(const char * filename);
/**
*   @return -1 if file not found
*/
long long file_getSize(const char * filename);
time_t file_getCreateTime(const char * filename);

/**
*   @return success of the action
*/
int file_create(const char * filename);

/**
*   @return success of the action
*/
int file_remove(const char * filename);