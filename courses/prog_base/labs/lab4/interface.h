#ifndef __inter_
#define __inter_
#define HELPINFO \
"\nhelp - to get help \n\n\
printpeople - print all people who are in database \n\n\
printposts - print all posts that are in database\n\n\
signup - to start signing up a person\n\n\
deleteacc - to delete the account which you are signed in \n\n\
login (id) - to login as a person, where (id) is is of a person\n\
(lookup id in printpeople)\n\n\
friendset (id) - to  become friends with person with id (id)\n\n\
post - to start writing a post as a loginned user \n\n\
deletepost (id) - to delete a post  with id (id) which is written by the loginned person\n\n\
comment (id) - to comment a post as a loginned user with id (id) (lookup id in printposts) \n\n\
BE ACCURATE you can't delete your comments in our social network(unless you delete your account).\nThats our feature\n\n\
deleteacc - to delete the account which the person is loginned with\n\n\
stats - to printout the most commented post and a person with the most friends \n\n\
logout - to logout from current account \nPress enter to continue..."
#define COLORDEF 0x07
#define TOP 2
#define COLORSELECT 0x70
#define BUFFERSIZE 100
#define HEIGHT 50
#define LENGTH 100
#endif // __inter_
