#include "mainHead.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int savePeople(Person ppl[LIMIT])
{
    FILE * f = fopen(PPLSAVEPLACE, "wb");
    if(!f)
        return RETURN_FAILURE;
    int sz = sizeof(Person);
    fwrite(ppl, sz, 20, f);
    fflush(f);
    fclose(f);
    return RETURN_SUCCESS;
}
int getPeople(Person ppl[LIMIT])
{
    FILE * f = fopen(PPLSAVEPLACE, "rb");
    if(!f)
        return RETURN_FAILURE;
    int sz = sizeof(Person);
    fread(ppl, sz, 20, f);
    fclose(f);
    return RETURN_SUCCESS;
}
void nullifyPeople(Person ppl[LIMIT])
{
    int i, j;
    for(i = 0; i < LIMIT; i++)
    {
        ppl[i].id = NOTINUSE;
        for(j = 0; j < LIMIT; j++)
            ppl[i].friends[j] = NOTINUSE;
    }
}
void deletePerson(Person * prs, Post * psts)
{
    int i, j;
    for(i = 0; i < POSTLIMIT; i++)
    {
        if(psts[i].authorId == prs->id)
            psts[i].postId = NOTINUSE;
        for(j = 0; j < COMMENTLIMIT; j++)
            if(psts[i].comments[j].authorId == prs->id)
                psts[i].comments[j].postId = NOTINUSE;
    }
    prs->id = NOTINUSE;
}
int getFreeIndOfPerson(Person ppl[LIMIT])
{
    int i;
    for(i = 0; i < LIMIT; i++)
        if(ppl[i].id == NOTINUSE)
            return i;
    return NOTINUSE;
}
int signUp(Person ppl[LIMIT], char * name, enum Sex sx, enum Mood md)
{
    int ind = getFreeIndOfPerson(ppl);
    strcpy(ppl[ind].name, name);
    ppl[ind].sx = sx;
    ppl[ind].id = ind;
    ppl[ind].md = md;
    savePeople(ppl);
    return ind;
}
int getFreeIndOfFriend(char * friends)
{
    int i;
    for(i = 0; i < LIMIT; i++)
        if(friends[i] == NOTINUSE)
            return i;
    return NOTINUSE;
}
int addFriend(Person ppl[LIMIT], char friendId, char yourId)
{
    char indY = getFreeIndOfFriend(ppl[yourId].friends);
    char indF = getFreeIndOfFriend(ppl[friendId].friends);
    if(indY==NOTINUSE || indF==NOTINUSE)
        return NOTINUSE; // There is no free place for a friend. You are not FOREVERALONE!
    else if(friendId > 19 || friendId < 0 || yourId > 19 || yourId < 0)
        return  RETURN_FAILURE; // he can't be your friend. He's a bad boy\girl
    ppl[yourId].friends[indY] = friendId;
    ppl[friendId].friends[indF] = yourId;
    return indY;
}
void deleteFriend(Person ppl[LIMIT], char yourId, char friendId)
{
    int i;
    for(i = 0; i < LIMIT; i++)
        if(ppl[yourId].friends[i]==friendId)
        {
            ppl[yourId].friends[i] = NOTINUSE;
            break;
        }
    for(i = 0; i < LIMIT; i++)
        if(ppl[friendId].friends[i]==yourId)
        {
            ppl[friendId].friends[i] = NOTINUSE;
            break;
        }
}
