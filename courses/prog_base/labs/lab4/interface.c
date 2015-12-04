
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "interface.h"
#include "Texts.h"
#include "People.h"
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void clearZone(int xFrom, int yFrom, int xTo, int yTo, int color)
{
    int i, j;
    setConsoleColor(color);
    for(i = xFrom; i <= xTo; i++)
        for(j = yFrom; j <= yTo; j++)
        {
            setCursorPosition(i, j);
            printf(" ");
        }
    setConsoleColor(STDCOLOR);
    setCursorPosition(xFrom, yFrom);
}
void printPosts(const Post * psts,const int nOfPeople, const Person * ppl, const int nOfPosts)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    int curX = SBInfo.dwCursorPosition.X;
    int curY = SBInfo.dwCursorPosition.Y + 1;
    int i = 0;
    char c;
    printf("Press A or D to move to post with less or bigger id. Press q to exit. There are %i post%c\n", nOfPosts, nOfPosts>1 ? 's' : ' ');
    printPost(ppl, &psts[i]);
    while((c = getch())!='q')
    {
        if(c == 'a')
        {
            if(i!=0)
                i--;
            else
                i = nOfPosts - 1;
        }
        else if(c == 'd')
        {
            if(i!=nOfPosts - 1)
                i++;
            else
                i = 0;
        }
        else
            continue;
        clearZone(curX, curY, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, STDCOLOR);
        printPost(ppl, &psts[i]);
    }
    clearZone(curX, curY - 1, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, STDCOLOR);
    puts("Exited from post view.");

}
void printPost(Person * ppl, Post * pst)
{
    int i;
    setConsoleColor(SELECTEDCOLOR);
    puts("Post id");
    setConsoleColor(STDCOLOR);
    printf("%i\n", pst->postId);
    setConsoleColor(SELECTEDCOLOR);
    puts("Author");
    setConsoleColor(STDCOLOR);
    printf("%s\n", ppl[pst->authorId].name);
    setConsoleColor(SELECTEDCOLOR);
    puts("Post text: ");
    setConsoleColor(STDCOLOR);
    printf("%s\n", pst->text);
    setConsoleColor(SELECTEDCOLOR);
    puts("Comments : ");
    for(i = 0; i < pst->nOfComments; i++)
    {
        setConsoleColor(SELECTEDCOLOR);
        printf("Author - %s\n", ppl[pst->comments[i].authorId].name);
        setConsoleColor(STDCOLOR);
        puts(pst->comments[i].text);
    }


}
void printPerson(Person * ppl, Person * prs)
{
    int i;
    char sex[10];
    setConsoleColor(SELECTEDCOLOR);
    puts("Person id");
    setConsoleColor(STDCOLOR);
    printf("%i\n", prs->id);
    setConsoleColor(SELECTEDCOLOR);
    puts("Name");
    setConsoleColor(STDCOLOR);
    printf("%s\n", prs->name);
    setConsoleColor(SELECTEDCOLOR);
    puts("Sex");
    setConsoleColor(STDCOLOR);
    switch(prs->sx)
    {
        case -2:
            puts("Male");
            break;
        case -1:
            puts("Female");
            break;
    }
    setConsoleColor(SELECTEDCOLOR);
    puts("Friends : ");
    setConsoleColor(STDCOLOR);
    for(i = 0; i < prs->nOfFriends; i++)
    {
        setConsoleColor(STDCOLOR);
        printf("%s%s",i ==0 ? "" : ", ", ppl[prs->friends[i]].name);
    }
    puts("");
}
void printPeople(Person * ppl, int nOfPeople)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    int curX = SBInfo.dwCursorPosition.X;
    int curY = SBInfo.dwCursorPosition.Y + 1;
    int i = 0;
    char c;
    printf("Press A or D to move to person with less or bigger id. Press q to exit. There are %i people%c\n", nOfPeople);
    printPerson(ppl, &ppl[i]);
    while((c = getch())!='q')
    {
        if(c == 'a')
        {
            if(i!=0)
                i--;
            else
                i = nOfPeople - 1;
        }
        else if(c == 'd')
        {
            if(i!=nOfPeople - 1)
                i++;
            else
                i = 0;
        }
        else
            continue;
        clearZone(curX, curY, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, STDCOLOR);
        printPerson(ppl, &ppl[i]);
    }
    clearZone(curX, curY - 1, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, STDCOLOR);
    puts("Exited from people view.");
}
Person * signUpInConsole(Person * ppl, int * nOfPeople)
{
    char buffer[BUFFERSIZE];
    int status;
    enum Sex sx;
    char name[100] = "\n";
    puts("Type your name : ");
    while(strlen(name) <= 1)
    {
        fgets(buffer, BUFFERSIZE, stdin);
        sscanf(buffer, "%s", name);
    }
    puts("Type in your gender (-1 for Female, -2 for Male)");
    while(status != 1)
    {
        fgets(buffer, BUFFERSIZE, stdin);
        status = sscanf(buffer, "%i", &sx);
        if(sx!=Male && sx!=Female)
            status = 0;
    }
    ppl = signUp(ppl, nOfPeople, name, sx);
    printf("You were successfully signed up. Type login %i to login\n", *nOfPeople - 1);
    return ppl;
}
Person * getMostFriends(Person * ppl, int nOfPeople)
{
    int i;
    Person * p = NULL;
    int n = 0;
    for(i = 0; i < nOfPeople; i++)
        if(ppl[i].nOfFriends > n)
        {
            n = ppl[i].nOfFriends;
            p = &ppl[i];
        }
    return p;
}
Post * getMostComments(Post * psts, int nOfPosts)
{
    int i;
    Post * p = NULL;
    int n = 0;
    for(i = 0; i < nOfPosts; i++)
        if(psts[i].nOfComments > n)
        {
            n = psts[i].nOfComments;
            p = &psts[i];
        }
    return p;
}
void getCmd(Post * posts, int nOfPosts, Person * ppl, int nOfPeople, int logid)
{
    char buffer[BUFFERSIZE];
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    if(SBInfo.dwCursorPosition.Y > HEIGHT / 2)
    {
        system("cls");
        setCursorPosition(0, 0);
        puts(HELPINFO);
    }
    fgets(buffer, BUFFERSIZE, stdin);
    if(!strcmp(buffer, "help\n"))
    {
        puts(HELPINFO);
    }
    else if(!strcmp(buffer, "printposts\n"))
    {
        printPosts(posts, nOfPeople, ppl, nOfPosts);
    }
    else if(!strcmp(buffer, "printpeople\n"))
    {
        printPeople(ppl, nOfPeople);
    }
    else if(!strcmp(buffer, "signup\n"))
    {
        ppl = signUpInConsole(ppl, &nOfPeople);
    }
    else if(strstr(buffer, "login"))
    {
        int status = 0;
        int tmp;
        status = sscanf(buffer, "login %i", &tmp);
        if(!status || tmp >= nOfPeople || tmp < 0)
            puts("Inapropriate format");
        else
        {
            logid = tmp;
            printf("You were successfully logged in as %s\n", ppl[logid].name);
        }
    }
    else if(strstr(buffer, "friendset "))
    {
        int status = 0;
        int tmp;
        status = sscanf(buffer, "friendset %i", &tmp);
        if(!status || tmp >= nOfPeople || tmp < 0 || logid >= nOfPeople || logid < 0)
            puts("Inapropriate format or you are not logged in");
        else
        {
            int i;
            int hasFriend = 0;
            if(logid==tmp)
                hasFriend = 1;
            for(i = 0; i < ppl[logid].nOfFriends && !hasFriend; i++)
                if(logid == tmp || ppl[logid].friends[i] == tmp)
                    hasFriend = 1;
            if(!hasFriend)
            {
               ppl = addFriend(ppl, &nOfPeople, logid, tmp);
               printf("You and %s are friends now!\n", ppl[tmp].name);
            }
            else
                puts("You are already friends!");
        }
    }
    else if(strstr(buffer, "writepost "))
    {
        if(logid < nOfPeople && logid >=0)
        {
            Post p;
            strcpy(p.text, buffer + 10);
            p.authorId = logid;
            p.nOfComments = 0;
            posts = addPost(posts, &p, &nOfPosts);
            puts("Your post was successfully created");
        }
        else
            puts("You are not logged in");
    }
    else if(strstr(buffer, "comment "))
    {
        int status = 0;
        int tmp;
        status = sscanf(buffer, "comment %i", &tmp);
        if(status && tmp < nOfPosts && tmp>=0 && logid < nOfPeople && logid >=0)
        {
            puts("Start writing your comment");
            fgets(buffer, BUFFERSIZE, stdin);
            if(strlen(buffer)>1)
            {
                posts = addComentToPost(tmp, posts, buffer, logid, &nOfPosts);
                puts("Your comment was created successfully");
            }
        }
        else
            puts("You typed nothing or you were not loginned");
    }
    else if(!strcmp(buffer, "stats\n"))
    {
        system("cls");
        setCursorPosition(0, 0);
        Person * prs = getMostFriends(ppl, nOfPeople);
        Post * pst = getMostComments(posts, nOfPosts);
        if(prs == NULL)
            puts("There are no people with friends");
        else
        {
            setConsoleColor(SELECTEDCOLOR);
            puts("\nThe person with the most number of friends : \n");
            setConsoleColor(STDCOLOR);
            printPerson(ppl, prs);
        }
        if(pst == NULL)
            puts("There are no posts wit comments");
        else
        {
            setConsoleColor(SELECTEDCOLOR);
            puts("\nThe post with the most number of comments : \n");
            setConsoleColor(STDCOLOR);
            printPost(ppl, pst);
        }
    }
    else if(!strcmp(buffer, "logout\n"))
    {
        if(logid < nOfPeople && logid >=0)
        {
            logid = -1;
            puts("You were successfully logged out");
        }
        else
            puts("You were not logged in");
    }

    else if(!strcmp(buffer, "exit\n"))
        return;
    else
        puts("Command was not found. Try help");
    getCmd(posts, nOfPosts, ppl, nOfPeople, logid);
}

void initConsole(Post * posts, int nOfPosts, Person * ppl, int nOfPeople)
{
    char settings[100];
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    SBInfo.dwSize.Y = 500;
    sprintf(settings,"mode con:cols=%i lines=%i", LENGTH, HEIGHT);
    SetConsoleScreenBufferSize(hConsole, SBInfo.dwSize);
    system(settings);
    puts(HELPINFO);
    getCmd(posts, nOfPosts, ppl, nOfPeople, -1);
}
