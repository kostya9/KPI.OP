#include <windows.h>
#include <stdio.h>
#include "mainHead.h"
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
    setConsoleColor(COLORDEF);
    setCursorPosition(xFrom, yFrom);
}
void drawHead(Person ppl[LIMIT], char logid)
{
    char * name;
    char * notS;
    char * asS;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    int curX = SBInfo.dwCursorPosition.X;
    int curY = SBInfo.dwCursorPosition.Y;
    clearZone(0, 0, SBInfo.srWindow.Right, TOP, COLORSELECT);
    setCursorPosition(SBInfo.srWindow.Right/3, TOP - 1);
    if(logid == NOTINUSE)
    {
        name = "";
        notS = "not";
        asS = "";
    }
    else
    {
        name = ppl[logid].name;
        notS = "";
        asS = "as";
    }
    setConsoleColor(COLORSELECT);
    printf("You are %s loginned %s %s", notS, asS, name);
    if(curY < 3)
        curY = 3;
    setCursorPosition(curX, curY);
    setConsoleColor(COLORDEF);
}
void printPosts(Post psts[POSTLIMIT],Person ppl[POSTLIMIT])
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    int curX = SBInfo.dwCursorPosition.X;
    int curY = SBInfo.dwCursorPosition.Y + 1;
    int i = 0;
    char c;
    for(i = 0;psts[i].postId==NOTINUSE && i < LIMIT; i++);
    if(i == LIMIT)
    {
        puts("There are no posts");
        return;
    }
    i = 0;
    puts("Press A or D to move to post with less or bigger id. Press q to exit.");
    printPost(ppl, &psts[i]);
    while((c = getch())!='q')
    {
         do
        {
            if(c == 'a')
            {
                if(i!=0)
                    i--;
                else
                    i = LIMIT - 1;
            }
            else if(c == 'd')
            {
                if(i!=LIMIT - 1)
                    i++;
                else
                    i = 0;
            }
            else
                continue;
        }while(psts[i].postId==NOTINUSE);
        clearZone(curX, curY, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, COLORDEF);
        printPost(ppl, &psts[i]);
    }
    clearZone(curX, curY - 1, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, COLORDEF);
    puts("Exited from post view.");

}
void printPost(Person * ppl, Post * pst)
{
    int i;
    setConsoleColor(COLORSELECT);
    puts("Post id");
    setConsoleColor(COLORDEF);
    printf("%i\n", pst->postId);
    setConsoleColor(COLORSELECT);
    puts("Author");
    setConsoleColor(COLORDEF);
    printf("%s\n", ppl[pst->authorId].name);
    setConsoleColor(COLORSELECT);
    puts("Post text: ");
    setConsoleColor(COLORDEF);
    printf("%s\n", pst->text);
    setConsoleColor(COLORSELECT);
    puts("Comments : ");
    for(i = 0; pst[i].comments[i].postId != NOTINUSE && i < pst->nOfComments; i++)
    {
        setConsoleColor(COLORSELECT);
        printf("Author - %s\n", ppl[pst->comments[i].authorId].name);
        setConsoleColor(COLORDEF);
        puts(pst->comments[i].text);
    }


}
void printPerson(Person * ppl, Person * prs)
{
    int i;
    char sex[10];
    setConsoleColor(COLORSELECT);
    puts("Person id");
    setConsoleColor(COLORDEF);
    printf("%i\n", prs->id);
    setConsoleColor(COLORSELECT);
    puts("Name");
    setConsoleColor(COLORDEF);
    printf("%s\n", prs->name);
    setConsoleColor(COLORSELECT);
    puts("Sex");
    setConsoleColor(COLORDEF);
    switch(prs->sx)
    {
        case -2:
            puts("Male");
            break;
        case -1:
            puts("Female");
            break;
    }
    setConsoleColor(COLORSELECT);
    puts("Friends : ");
    setConsoleColor(COLORDEF);
    for(i = 0; i < LIMIT && prs->friends[i]!=NOTINUSE; i++)
    {
        setConsoleColor(COLORDEF);
        printf("%s%s",i ==0 ? "" : ", ", ppl[prs->friends[i]].name);
    }
    puts("");
}
void printPeople(Person * ppl)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    int curX = SBInfo.dwCursorPosition.X;
    int curY = SBInfo.dwCursorPosition.Y + 1;
    int i = 0;
    char c;
    for(i = 0;ppl[i].id==NOTINUSE && i < LIMIT; i++);
    if(i == LIMIT)
    {
        puts("There are no people");
        return;
    }
    i = 0;
    puts("Press A or D to move to person with less or bigger id. Press q to exit.");
    printPerson(ppl, &ppl[i]);
    while((c = getch())!='q')
    {
        do
        {
            if(c == 'a')
            {
                if(i!=0)
                    i--;
                else
                    i = LIMIT - 1;
            }
            else if(c == 'd')
            {
                if(i!=LIMIT - 1)
                    i++;
                else
                    i = 0;
            }
            else
                continue;
        }while(ppl[i].id==NOTINUSE);
        clearZone(curX, curY, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, COLORDEF);
        printPerson(ppl, &ppl[i]);
    }
    clearZone(curX, curY - 1, SBInfo.srWindow.Right - 1, SBInfo.srWindow.Bottom - 1, COLORDEF);
    puts("Exited from people view.");
}
void signUpInConsole(Person * ppl)
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
    int ind = signUp(ppl, name, sx);
    if(ind == NOTINUSE)
        puts("There are too much people signed up");
    else
        printf("You were successfully signed up. Type login %i to login\n", ind);
}
Person * getMostFriends(Person * ppl)
{
    int i, j;
    Person * p = NULL;
    int prevC = 0;
    int curC = 0;
    for(i = 0; i < LIMIT; i++)
    {
        curC = 0;
        for(j = 0; ppl[i].friends[j]!=NOTINUSE && j < LIMIT; j++)
            curC++;
        if(curC > prevC)
            p = &ppl[i];
    }

    return p;
}
Post * getMostComments(Post * psts)
{
    int i;
    Post * p = NULL;
    int n = 0;
    for(i = 0; psts[i].postId!=NOTINUSE && i < POSTLIMIT; i++)
        if(psts[i].postId!=NOTINUSE && psts[i].nOfComments > n)
        {
            n = psts[i].nOfComments;
            p = &psts[i];
        }
    return p;
}
void getCmd(Post psts[POSTLIMIT], Person ppl[LIMIT], int logid)
{
    static char buffer[BUFFERSIZE];
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    if(SBInfo.dwCursorPosition.Y > (2 * HEIGHT) / 3)
    {
        clearZone(0,TOP + 1, SBInfo.srWindow.Right, SBInfo.srWindow.Bottom, COLORDEF);
        setCursorPosition(0, TOP + 1);
        puts("Type help to get commands");
        printf(buffer);
    }
    drawHead(ppl, logid);
    fgets(buffer, BUFFERSIZE, stdin);
    if(!strcmp(buffer, "help\n"))
    {
        puts(HELPINFO);
        getchar();
        puts("\n\n");
    }
    else if(!strcmp(buffer, "printposts\n"))
    {
        printPosts(psts, ppl);
    }
    else if(!strcmp(buffer, "printpeople\n"))
    {
        printPeople(ppl);
    }
    else if(!strcmp(buffer, "signup\n"))
    {
        signUpInConsole(ppl);
    }
    else if(strstr(buffer, "login"))
    {
        int status = 0;
        int tmp;
        status = sscanf(buffer, "login %i", &tmp);
        if(!status || tmp >= LIMIT || tmp < 0 || ppl[logid].id==NOTINUSE)
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
        if(!status || tmp >= LIMIT || tmp < 0 || logid >= LIMIT || logid < 0)
            puts("Inapropriate format or you are not logged in");
        else
        {
            int i;
            int hasFriend = 0;
            if(logid==tmp)
                hasFriend = 1;
            for(i = 0; i < LIMIT && !hasFriend; i++)
                if(ppl[logid].friends[i] == tmp)
                    hasFriend = 1;
            if(!hasFriend)
            {
               addFriend(ppl, tmp, logid);
               printf("You and %s are friends now!\n", ppl[tmp].name);
            }
            else
                puts("You are already friends!");
        }
    }
    else if(!strcmp(buffer, "post\n"))
    {
        if(logid < LIMIT && logid >=0)
        {
            puts("Start writing your post");
            fgets(buffer, BUFFERSIZE, stdin);
            if(strlen(buffer)>1)
            {
                writePost(psts, logid, buffer + 10);
                puts("Your post was successfully created");
            }

        }
        else
            puts("You are not logged in or you typed nothing");
    }
    else if(strstr(buffer, "comment "))
    {
        int status = 0;
        int tmp;
        status = sscanf(buffer, "comment %i", &tmp);
        if(status && tmp < POSTLIMIT && tmp>=0 && logid < LIMIT && logid >=0)
        {
            puts("Start writing your comment");
            fgets(buffer, BUFFERSIZE, stdin);
            if(strlen(buffer)>1)
            {
                addComment(psts, logid, tmp, buffer);
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
        Person * prs = getMostFriends(ppl);
        Post * pst = getMostComments(psts);
        if(prs == NULL)
            puts("There are no people with friends");
        else
        {
            setConsoleColor(COLORSELECT);
            puts("\nThe person with the most number of friends : \n");
            setConsoleColor(COLORDEF);
            printPerson(ppl, prs);
        }
        if(pst == NULL)
            puts("There are no posts wit comments");
        else
        {
            setConsoleColor(COLORSELECT);
            puts("\nThe post with the most number of comments : \n");
            setConsoleColor(COLORDEF);
            printPost(ppl, pst);
        }
    }
    else if(!strcmp(buffer, "logout\n"))
    {
        if(logid < LIMIT && logid >=0)
        {
            logid = -1;
            puts("You were successfully logged out");
        }
        else
            puts("You were not logged in");
    }
    else if(strstr(buffer, "deletepost "))
    {
        int tmp;
        int status = sscanf(buffer, "deletepost %i", &tmp);
        if(status && tmp < POSTLIMIT && tmp >= 0)
            deletePost(psts, tmp);
        else
            puts("Inappropriate format");
    }
    else if(!strcmp(buffer, "deleteacc\n"))
    {
        if(logid >= 0 && logid < LIMIT)
        {

            puts("Are you sure? This will delete all of your posts and comments. Press y if you are.");
            if(getch()=='y')
            {
                 deletePerson(&ppl[logid], psts);
                 puts("This account was deleted successfully");
            }
            else
                puts("No");
        }

        else
            puts("You are not loginned");
    }
    else if(!strcmp(buffer, "exit\n"))
        return;
    else
        puts("Command was not found. Try help");
    savePeople(ppl);
    savePosts(psts);
    getCmd(psts, ppl, logid );
}

void initConsole(Post psts[POSTLIMIT], Person ppl[LIMIT])
{
    char settings[100];
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    SBInfo.dwSize.Y = 500;
    sprintf(settings,"mode con:cols=%i lines=%i", LENGTH, HEIGHT);
    SetConsoleScreenBufferSize(hConsole, SBInfo.dwSize);
    system(settings);
    puts("Type help to get commands");
    getCmd(psts, ppl, -1);
    savePeople(ppl);
    savePosts(psts);
}
