#include "People.h"
#include <stdio.h>
#include <stdlib.h>
Person * signUp(Person * people, int * nOfPeople, char * name, enum Sex sx)
{
    FILE * f = fopen("People.txt", "a");
    if(strlen(name)<100)
        fprintf(f, "%i %i %s %i\n", *nOfPeople, sx, name, 0);
    else
        return NULL;
    fclose(f);
    f = fopen("People.txt", "r+");
    fprintf(f, "%i\n", ++(*nOfPeople));
    fclose(f);
    free(people);
    people = getPeople(&nOfPeople);
    return people;
}
Person * getPeople(int * nOfPeople)
{
    int i, j;
    char buffer[BUFFERSIZE];
    char name[100];
    enum Sex sx;
    int nOfFriends;
    int id;
    FILE * f = fopen("People.txt", "r");
    if(f==NULL)
        return NULL;
    fgets(buffer, BUFFERSIZE, f);
    sscanf(buffer, "%i", nOfPeople);
    if(!nOfPeople)
    {
        fclose(f);
        return NULL;
    }
    Person * people = (Person *)malloc(sizeof(Person) * *nOfPeople);
    for(i = 0; i < *nOfPeople; i++)
    {
        char * curP;
        fgets(buffer, BUFFERSIZE, f);
        sscanf(buffer, "%i %i %s %i", &id, &sx, name, &nOfFriends);
        people[i].id = id;
        strcpy(people[i].name, name);
        people[i].sx = sx;
        people[i].nOfFriends = nOfFriends;
        if(nOfFriends>0)
        {
            strtok(buffer, " ");
            for(j = 0; j < 4; j++)
                curP = strtok(NULL, " ");
            for(j = 0; j < nOfFriends; j++)
            {
                int n;
                sscanf(curP, "%i", &n);
                people[i].friends[j] = n;
                curP = strtok(NULL, " ");
            }
        }
    }
    fclose(f);
    return people;
}

Person * savePeople(Person * people, int * nOfPeople)
{
    int i, j;
    FILE * f = fopen("People.txt", "w");
    fprintf(f, "%i\n", *nOfPeople);
    for(i = 0; (i < *nOfPeople) && (people[i].id >= 0); i++)
    {
        fprintf(f, "%i %i %s %i", people[i].id, people[i].sx, people[i].name, people[i].nOfFriends);
        for(j = 0; j < people[i].nOfFriends; j++)
            fprintf(f, " %i", people[i].friends[j]);
        fprintf(f, "\n");
    }
    fclose(f);
    free(people);
    people = NULL;
    *nOfPeople = 0;
    return people;
}
Person * deletePerson(Person * people, int * nOfPeople, Person * pson)
{
    pson->id = -1;
    people = savePeople(people, *nOfPeople);
    people = getPeople(nOfPeople);
    return people;
}
Person * addFriend(Person * ppl, int * nOfPeople, int persId, int friendId)
{
    ppl[persId].friends[ppl[persId].nOfFriends] = friendId;
    ppl[persId].nOfFriends++;
    ppl[friendId].friends[ppl[friendId].nOfFriends] = persId;
    ppl[friendId].nOfFriends++;
    ppl = savePeople(ppl, nOfPeople);
    ppl = getPeople(nOfPeople);
    return ppl;
}
