#ifndef __ppl_
#define __ppl_
#define PPLSAVEPLACE "ppl.bin"
#include "mainHead.h"
enum Sex{Male = -2, Female = -1, Else = 0}; //Else is whatever you want it to be
enum Mood{Good = -10, Okay, Bad};
typedef struct
{
    char id;
    char name[100];
    enum Sex sx;
    enum Mood md;
    char friends[20];
} Person;
int savePeople(Person ppl[LIMIT]);
int getPeople(Person ppl[LIMIT]);
void nullifyPeople(Person ppl[LIMIT]);
void deletePerson(Person * prs, Post * psts);
int getFreeIndOfPerson(Person ppl[LIMIT]);
int signUp(Person ppl[LIMIT], char * name, enum Sex sx, enum Mood md);
int getFreeIndOfFriend(char * friends);
int addFriend(Person ppl[LIMIT], char friendId, char yourId);
#endif // __ppl_
