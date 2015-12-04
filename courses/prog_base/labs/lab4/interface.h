#ifndef __inter_
#define __inter_
#include <windows.h>
#include "Texts.h"
#include "People.h"
#define HELPINFO \
"help - to get help \n\
printpeople - print all people who are in database \n\
printposts - print all posts that are in database\n\
signup - to start signing up a person\n\
login (id) - to login as a person, where (id) is is of a person\n\
(lookup id in printppl)\n\
friendset (id) - to  become friends with person with id (id)\n\
writepost (pst) - to write a post as a loginned user where (pst) is the text of a post \n\
comment (id) - to comment a post as a loginned user with id (id) (lookup id in printpsts) \n\
stats - to printout the most commented post and a person with the most friends \n\
logout - to logout from current account \n"
#define LENGTH 100
#define HEIGHT 60
#define SELECTEDCOLOR 0x70
#define STDCOLOR 0x07
BOOL WINAPI SetConsoleScreenBufferSize(
    HANDLE hConsoleOutput,
    COORD  dwSize
);
void initConsole(Post * posts, int nOfPosts, Person * ppl, int nOfPeople);

#endif // __inter_
