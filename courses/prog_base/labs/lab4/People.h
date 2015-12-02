#ifndef __PPL_
#define __PPL_
#define BUFFERSIZE 200
enum Sex{Male= -2, Female};
typedef struct
{
    char id;
    enum Sex sx;
    char name[100];
    int nOfFriends;
    char friends[100];
} Person;
Person * signUp(Person * people, int * nOfPeople, char * name, enum Sex sx);
Person * getPeople(int * nOfPeople);
Person * savePeople(Person * people, int * nOfPeople);
Person * deletePerson(Person * people, int * nOfPeople, Person * pson);
Person * addFriend(Person * pers, int friendId);
#endif // __PPL_
