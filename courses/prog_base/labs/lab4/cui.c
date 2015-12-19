#include <windows.h>
#include <stdio.h>
#include "mainHead.h"
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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
void clearStdin()
{
    rewind(stdin);
}
void printMenu(char ** menu, size_t sz)
{
    int i;
    for(i = 0; i < sz; i++)
    {
        clearZone(RIGHT, i * 3, LENGTH - 1, i * 3 + 2, COLORSELECT);
        setConsoleColor(COLORSELECT);
        setCursorPosition(RIGHT + (LENGTH - RIGHT - 1)/3, i * 3 + 1);
        printf("%s", menu[i]);
    }
    setConsoleColor(COLORDEF);
    setCursorPosition(RIGHT, 0);
}
void drawMood(enum Mood md, int xFrom, int yFrom)
{
    clearZone(xFrom, yFrom, xFrom + PICWIDTH - 1, yFrom + PICHEIGHT - 1, 0x70);
    setCursorPosition(xFrom + 1, yFrom);
    setConsoleColor(BACKGROUND_BLUE);
    printf(" ");
    setCursorPosition(xFrom + 6, yFrom);
    printf(" ");
    switch(md)
    {
        case Good :
        {
            setCursorPosition(xFrom + 1, yFrom + 3);
            printf("      ");
            setCursorPosition(xFrom + 1, yFrom + 2);
            printf(" ");
            setCursorPosition(xFrom + 6, yFrom + 2);
            printf(" ");
        }break;
        case Okay :
        {
            setCursorPosition(xFrom + 1, yFrom + 2);
            printf("      ");
        }break;
        case Bad :
        {
            setCursorPosition(xFrom + 1, yFrom + 2);
            printf("      ");
            setCursorPosition(xFrom + 1, yFrom + 3);
            printf(" ");
            setCursorPosition(xFrom + 6, yFrom + 3);
            printf(" ");
        }break;
    }

}
void printSelected(char ** menu, int selected)
{
    clearZone(RIGHT, selected * 3, LENGTH - 1, selected * 3 + 2, COLORCHOSEN);
    setConsoleColor(COLORCHOSEN);
    setCursorPosition(RIGHT + (LENGTH - RIGHT - 1)/3, selected * 3 + 1);
    printf("%s", menu[selected]);
    setConsoleColor(COLORDEF);
}
void printTextBlock(int xFrom, int yFrom, int width, char * text)
{
    int i, lttr = 0, ln = 0;
    setCursorPosition(xFrom, yFrom);
    for(i = 0; i < strlen(text); i++)
    {
        if(lttr > width)
        {
            lttr = 0;
            ln++;
        }
        setCursorPosition(xFrom + lttr, yFrom + ln);
        putchar(text[i]);
        lttr++;
        puts("");
    }
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
int doTask(int selected, size_t sz, Person * ppl, Post * psts, int logid)
{
    int i, j;
    int n = 0;
    char c;
    clearStdin();
    switch(selected)
    {
        case 0:
        {
            do
            {
                n = 0;
                clearZone(0, 0, RIGHT - 1, sz * 3 - 1, 0xFF);
                setConsoleColor(0x6F);
                puts("Press d to go to the next page. Press anything else to exit");
                for(i = 0; i < LIMIT && ppl[i].id!=NOTINUSE; i++)
                {
                    if(n * 5 + 4 > sz * 3 - 1)
                    {
                        if(c = getch() == 'd')
                        {
                            n = 0;
                            clearZone(0, 1, RIGHT - 1, sz * 3 - 1, 0xFF);
                        }
                        else
                            return;
                    }
                    char * sx;
                    drawMood(ppl[i].md,0 , n* 5 + 1);
                    setConsoleColor(0xF6);
                    setCursorPosition(8, n * 5+ 1);
                    printf("ID : %i", ppl[i].id);
                    setCursorPosition(8, n * 5 + 2);
                    printf("NAME : %s", ppl[i].name);
                    setCursorPosition(8, n * 5 + 3);
                    if(ppl[i].sx == Male)
                        sx = "Male";
                    else
                        sx = "Female";
                    printf("SEX : %s", sx);
                    for(j = 0; j < LIMIT && ppl[i].friends[j] != NOTINUSE; j++)
                    {
                        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                        if(!j)
                        {
                            setCursorPosition(8, SBInfo.dwCursorPosition.Y + 1);
                            printf("Friends : ");
                            GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                        }
                        SBInfo.dwCursorPosition.X = SBInfo.dwCursorPosition.X < 8 ? 8 : SBInfo.dwCursorPosition.X;
                        printTextBlock(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y, RIGHT - SBInfo.dwCursorPosition.X - 1, ppl[ppl[i].friends[j]].name);
                    }
                    n++;
                }
            }while(getch()=='d');
        }break;
        case 1:
        {
            do
            {
                CONSOLE_SCREEN_BUFFER_INFO SBInfo;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                clearZone(0, 0, RIGHT - 1, sz * 3 - 1, 0xFF);
                setConsoleColor(0x6F);
                puts("Press d to go to the next page. Press anything else to exit");
                int i, n = 0;
                for(i = 0; i < POSTLIMIT && psts[i].postId!=NOTINUSE; i++)
                {
                    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                    setConsoleColor(0xF6);
                    if(((SBInfo.dwCursorPosition.Y +  2 * (1 + psts[i].nOfComments + strlen(psts[i].text)/(RIGHT - 9)) ) > (sz * 3 - 1)))
                    {
                        if(getch()=='d')
                        {
                            clearZone(0, 0, RIGHT - 1, sz * 3 - 1, 0xFF);
                            setConsoleColor(0x6F);
                            puts("Press d to go to the next page. Press anything else to exit");
                            setConsoleColor(0xF6);
                            GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                        }
                        else return;
                    }
                        drawMood(ppl[psts[i].authorId].md, SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y);
                        setCursorPosition(8, SBInfo.dwCursorPosition.Y);
                        setConsoleColor(0x3F);
                        printf("Id : %i ||| ", psts[i].postId);
                        printf("Author : %s", ppl[psts[i].authorId].name);
                        setConsoleColor(0xF3);
                        printTextBlock(8, SBInfo.dwCursorPosition.Y + 1, RIGHT - 9, psts[i].text);
                        for(n = 0; n < COMMENTLIMIT && psts[i].comments[n].postId != NOTINUSE; n++)
                        {
                            setConsoleColor(0xF6);
                            GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                            if(!n)
                            {

                                setCursorPosition(8, SBInfo.dwCursorPosition.Y);
                                printf("\t\tComments : ");
                                SBInfo.dwCursorPosition.Y += 1;
                            }
                            setCursorPosition(8, SBInfo.dwCursorPosition.Y);
                            printf("\tAuthor - %s\n", ppl[psts[i].comments[n].authorId].name);
                            printTextBlock(8, SBInfo.dwCursorPosition.Y + 1, RIGHT - 9, psts[i].comments[n].text);
                        }
                    puts("\n\n");
                                    }

            }while(getch()=='d');
        }break;
        case 2:
        {
            clearZone(0, 0, RIGHT - 1, sz * 3 - 1, 0xFF);
            setConsoleColor(0xF6);
            char buffer[BUFFERSIZE];
            int status;
            enum Sex sx;
            enum Mood md;
            char name[100] = "\n";
            while(strlen(name) <= 1)
            {
                setConsoleColor(0x6F);
                puts("Type your name : ");
                setConsoleColor(0xF6);
                fgets(name, BUFFERSIZE, stdin);
            }
            setConsoleColor(0x6F);
            puts("Type in your gender (-1 for Female, -2 for Male)");
            setConsoleColor(0xF6);
            while(status != 1)
            {
                fgets(buffer, BUFFERSIZE, stdin);
                status = sscanf(buffer, "%i", &sx);
                if(sx!=Male && sx!=Female)
                    status = 0;
            }
            status = 0;
            setConsoleColor(0x6F);
            puts("Type in your mood : Okay or Good or Bad");
            setConsoleColor(0xF6);
            while(status == 0)
            {
                fgets(buffer, BUFFERSIZE, stdin);
                if(!strcmp(buffer, "Okay\n"))
                {
                    md = Okay;
                    status = 1;
                }
                else if(!strcmp(buffer, "Good\n"))
                {
                    md = Good;
                    status = 1;
                }
                else if(!strcmp(buffer, "Bad\n"))
                {
                    md = Bad;
                    status = 1;
                }
                else
                    puts("Try again");
            }
            name[strlen(name) - 1] = '\0';
            int ind = signUp(ppl, name, sx, md);
            if(ind == NOTINUSE)
                puts("There are too much people signed up");
            else
                printf("You were successfully signed up. Your ID is %i\n", ind);
            getch();
        }break;
        case 3:
        {
            if(logid!=NOTINUSE)
            {
                puts("Are you sure you want to delete your account? Press y if you are");
                if(getch() == 'y')
                    deletePerson(&ppl[logid], psts);
                return NOTINUSE;
            }
            else
            {
                setConsoleColor(BACKGROUND_RED);
                puts("You are not loginned");
                setConsoleColor(0xF6);
            }
        }break;
        case 4:
        {
            char c;
            char buffer[100];
            puts("Type in the id of the account you want to login with");
            fgets(buffer, 100, stdin);
            sscanf(buffer, "%i", &c);
            if(c >= LIMIT || c < 0 || ppl[c].id==NOTINUSE)
            {
                puts("Something went wrong");
                getch();
            }
            else
                return c;
        }break;
        case 5:
        {
            int k = -1;
            char buffer[100];
            setConsoleColor(0x6F);
            puts("Please type id of your future friend");
            setConsoleColor(0xF6);
            fgets(buffer, 100, stdin);
            if(!sscanf(buffer, "%i", &k))
                puts("Inappropriate format");
            if(k >= LIMIT || k < 0 || ppl[k].id==NOTINUSE)
            {
                puts("You are not loginned or there is no person with that id");
            }
            else
            {
                addFriend(ppl, k, logid);
                printf("You and %s are friends now!", ppl[k].name);
                getch();
            }

        }break;
        case 6:
        {
            if(logid == NOTINUSE)
            {
                puts("You are not loginned");
                getch();
                return logid;
            }
            else
            {
                char buffer[200];
                int curL = 0;
                int i = 0;
                puts("Type in your post");
                while(1)
                {
                    char c = getch();
                    buffer[i] = c;
                    if(curL == RIGHT)
                    {
                        puts("");
                        curL = 0;
                    }
                    if(c == '\r')
                        break;
                    else if(c == 8)
                    {
                        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                        SBInfo.dwCursorPosition.X -=1;
                        if(curL == 0)
                        {
                            if(SBInfo.dwCursorPosition.Y == 2)
                                continue;
                            curL = RIGHT;
                            SBInfo.dwCursorPosition.Y-=1;
                            SBInfo.dwCursorPosition.X = RIGHT - 1;
                        }
                        setCursorPosition(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y);
                        printf(" ");
                        curL--;
                        curL--;
                        i--;
                        i--;
                    }
                    putchar(c);
                    i++;
                    curL++;
                }
                buffer[i] = '\0';
                writePost(psts, logid, buffer);
            }
        }break;
        case 7:
        {
            setConsoleColor(0x6F);
            puts("Please type id of the post");
            setConsoleColor(0xF6);
            char c = getchar();
            while(c=='\n' || c=='\r')
                getch();
            if(c - '0' >= POSTLIMIT || c - '0' < 0 || logid==NOTINUSE || psts[c - '0'].authorId!=logid)
            {
                puts("You are not loginned or that post is not written by you");
                getch();
            }
            else
                deletePost(psts, c - '0');
        } break;
        case 8:
        {
            if(logid == NOTINUSE)
            {
                puts("You are not loginned");
                getch();
                return logid;
            }
            else/*Bug in deleting*/
            {
                char buffer[200];
                int curL = 0;
                int i = 0;
                puts("Type in the id of the post you want to comment");
                fgets(buffer, 200, stdin);
                sscanf(buffer, "%i", &c);
                if(c < 0 || c >= POSTLIMIT || psts[c].postId == NOTINUSE)
                {
                    puts("Something went wrong");
                    getch();
                    return logid;
                }
                puts("Type in your comment");
                int pId = c;
                while(1)
                {
                    c = getch();
                    buffer[i] = c;
                    if(curL == RIGHT)
                    {
                        puts("");
                        curL = 0;
                    }
                    if(c == '\r' || c=='\n')
                        break;
                    else if(c == 8)
                    {
                        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                        SBInfo.dwCursorPosition.X -=1;
                        if(curL == 0)
                        {
                            if(SBInfo.dwCursorPosition.Y == 2)
                                continue;
                            curL = RIGHT;
                            SBInfo.dwCursorPosition.Y-=1;
                            SBInfo.dwCursorPosition.X = RIGHT - 1;
                        }
                        setCursorPosition(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y);
                        printf(" ");
                        curL--;
                        curL--;
                        i--;
                        i--;
                    }
                    putchar(c);
                    i++;
                    curL++;
                }
                buffer[i] = '\0';
                addComment(psts, logid, pId, buffer);
            }
        }break;
        case 9:
        {
            CONSOLE_SCREEN_BUFFER_INFO SBInfo;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            int i;
            setCursorPosition(0, 0);
            Person * prs = getMostFriends(ppl);
            if(prs)
            {
                setConsoleColor(0x6F);
                puts("The person with most friends : ");
                setConsoleColor(0xF6);
                char * sx;
                drawMood(prs->md,0 , 1);
                setConsoleColor(0xF6);
                setCursorPosition(8, 1);
                printf("ID : %i", prs->id);
                setCursorPosition(8, 2);
                printf("NAME : %s", prs->name);
                setCursorPosition(8, 3);
                if(prs->sx == Male)
                    sx = "Male";
                else
                    sx = "Female";
                printf("SEX : %s", sx);
                for(j = 0; j < LIMIT && prs->friends[j] != NOTINUSE; j++)
                {
                    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                    if(!j)
                    {
                        setCursorPosition(8, SBInfo.dwCursorPosition.Y + 1);
                        printf("Friends : ");
                        GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                    }
                    SBInfo.dwCursorPosition.X = SBInfo.dwCursorPosition.X < 8 ? 8 : SBInfo.dwCursorPosition.X;
                    printTextBlock(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y, RIGHT - SBInfo.dwCursorPosition.X - 1, ppl[prs->friends[j]].name);
                }
            }
            else
                puts("There are no people with friends");

            Post * pst= getMostComments(psts);
            if(pst)
            {
                GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                SBInfo.dwCursorPosition.Y+=1;
                setConsoleColor(0x6F);
                puts("The post with most comments : ");
                drawMood(ppl[pst->authorId].md, SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y);
                setCursorPosition(8, SBInfo.dwCursorPosition.Y);
                setConsoleColor(0x3F);
                printf("Id : %i ||| ", pst->postId);
                printf("Author : %s", ppl[pst->authorId].name);
                setConsoleColor(0xF3);
                printTextBlock(8, SBInfo.dwCursorPosition.Y + 1, RIGHT - 9, pst->text);
                for(n = 0; n < COMMENTLIMIT && pst->comments[n].postId != NOTINUSE; n++)
                {
                    setConsoleColor(0xF6);
                    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
                    if(!n)
                    {

                        setCursorPosition(8, SBInfo.dwCursorPosition.Y);
                        printf("\t\tComments : ");
                        SBInfo.dwCursorPosition.Y += 1;
                    }
                    setCursorPosition(8, SBInfo.dwCursorPosition.Y);
                    printf("\tAuthor - %s\n", ppl[pst->comments[n].authorId].name);
                    printTextBlock(8, SBInfo.dwCursorPosition.Y + 1, RIGHT - 9, pst->comments[n].text);
                }
            }
            else
                puts("There are no posts with comments");

            setConsoleColor(0xF6);
            getch();

        }break;
        case 10:
        {
            return NOTINUSE;
        }break;
        case 11:
        {
            savePosts(psts);
            savePeople(ppl);
            exit(EXIT_SUCCESS);
        }
    }
    return logid;
}
int menuSelect(char ** menu, size_t sz, int selected, Person * ppl, Post * psts, int logid)
{
    printMenu(menu, sz);
    printSelected(menu, selected);
    setCursorPosition(0, 0);
    setConsoleColor(0x6F);
    if(logid!=NOTINUSE)
        printf("You are loginned as %s\n", ppl[logid].name);
    else
        puts("You are not loginned");
    setConsoleColor(0xF6);
    char c = 0;
    switch(c = getch())
    {
        case 's' :
        {
            if(selected < sz - 1)
                selected++;
            else
                selected = 0;
        }break;
        case 'w' :
        {
            if(selected > 0)
                selected--;
            else
                selected = sz - 1;
        }break;
        case '\r' :
        {
            logid = doTask(selected, sz, ppl, psts, logid);
            clearZone(0, 0, RIGHT - 1, sz*3 - 1, 0xFF);
        }break;
    }
    menuSelect(menu, sz,selected, ppl, psts, logid);

}
int init(Person * ppl, Post * psts)
{
    char * menu[] ={"Print people", "Print posts", "Sign up", "Delete account", "Login", "Friend set", "Post", "Delete post", "Comment", "Stats", "Logout", "Exit"};
    size_t sz = sizeof(menu)/ sizeof(menu[0]);
    char settings[100];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    sprintf(settings,"mode con:cols=%i lines=%i", LENGTH, HEIGHT);
    setConsoleColor(0xFF);
    system(settings);
    system("cls");
    clearZone(0, 0, RIGHT - 1, sz * 3 - 1, 0xFF);
    menuSelect(menu, sz, 0, ppl, psts, -1);
}
