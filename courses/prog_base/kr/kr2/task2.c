#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
typedef struct
{
    int id;
    char name[100];
    char country[100];
} Writer;
typedef struct
{
    char name[100];
    Writer * author;
    int year;;
} Book;
Writer * defaultWriter(Writer * wr);
Book * defaultBook(Book * bk);
Writer * setWriter(Writer * wr);
Book * setBook(Writer * wrs, size_t sz, Book * bk);
int idToIndWriter(Writer * wrts, size_t sz, int id);
Book * getBook();
Writer * getWriter();
Book * freeBook(Book * bk);
Writer * freeWriter(Writer * wr);
void outBook(Book * bk);
void outWriter(Writer * wr);
void outWriters(Writer * wrs, size_t sz);
void outBooks(Book * bks, size_t sz);
int cmpWriter(Writer * wr1, Writer * wr2);
int cmpBook(Book * bk1, Book * bk2);
int main(void)
{
    Writer wrs[] = {{0, "Peter", "Ukraine"}, {1, "Vasya Pupkin", "Canadian"}, {2, "Vasya NePupkin", "Ukraine"}};
    size_t szwrs = sizeof(wrs)/sizeof(wrs[0]);
    Book bks[] = {{"Adventures of ksvk", &wrs[0], 2015}, {"Adventures of dsfdsf", &wrs[1], 2014}, {"Adventures of vbvbb", &wrs[2], 2009}};
    size_t szbks = sizeof(bks)/sizeof(bks[0]);
    int i;
    time_t t = time(NULL);
    for(i = 0; i < szbks; i++)
    {
        struct tm y2k = {0};
        y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
        y2k.tm_year = bks[i].year - 1900; y2k.tm_mon = 0; y2k.tm_mday = 1;
        if((difftime(t, mktime(&y2k))/(3600 * 24 * 365)) < 5)
        {
            outBook(&bks[i]);
            puts("");
        }

    }
    return EXIT_SUCCESS;
}
Writer * defaultWriter(Writer * wr)
{
    strcpy(wr->name, "DEFWRITER");
    strcpy(wr->country, "Ukraine");
    return wr;
}
Book * defaultBook(Book * bk)
{
    strcpy(bk->name, "DEFBOOK");
    bk->author = NULL;
    bk->year = 2015;
    return bk;
}
Writer * setWriter(Writer * wr)
{
    char buffer[100];
    puts("Please, type in the name of the writer");
    fgets(buffer, 100, stdin);
    strcpy(wr->name, buffer);
    puts("Please, type the name of the country where he is from (starting with capital letter)");
    fgets(buffer, 100, stdin);
    sscanf("%s", wr->country);
    return wr;
}
int idToIndWriter(Writer * wrts, size_t sz, int id)
{
    int i;
    for(i = 0; i < sz; i++)
        if(wrts[i].id == id)
            return i;
    return -1;
}
Book * setBook(Writer * wrs, size_t sz, Book * bk)
{
    int id, yr;
    char buffer[100];
    puts("Please, type in the name of the book");
    fgets(buffer, 100, stdin);
    strcpy(bk->name, buffer);
    puts("Please, type the id of the writer");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%i", &id);
    bk->author = &wrs[idToIndWriter(wrs, sz, id)];
    puts("Please, type in the year when the book was published");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%i", &yr);
    bk->year = yr;
    return bk;
}
Book * getBook()
{
    Book * bk = (Book *)malloc(sizeof(Book));
    return bk;
}
Writer * getWriter()
{
    Writer * wr = (Writer *)malloc(sizeof(Writer));
    return wr;
}
Book * freeBook(Book * bk)
{
    free(bk);
    return NULL;
}
Writer * freeWriter(Writer * wr, Book * bks, size_t sz)
{
    int i;
    for(i = 0; i < sz; i++)
        if(bks[i].author == wr)
            free(bks[i]);
    free(wr);
    return NULL;
}
void outBook(Book * bk)
{
    printf("Name : ");
    puts(bk->name);
    printf("Author name : ");
    puts(bk->author->name);
    printf("Published in %i", bk->year);
}
void outWriter(Writer * wr)
{
    printf("Id : %i\n", wr->id);
    puts("Name : ");
    puts(wr->name);
    printf("Country %s", wr->country);
}
void outWriters(Writer * wrs, size_t sz)
{
    int i;
    for(i = 0; i < sz; i++)
    {
        outWriter(&wrs[i]);
    }
}
void outBooks(Book * bks, size_t sz)
{
    int i;
    for(i = 0; i < sz; i++)
    {
        outBook(&bks[i]);
    }
}
int cmpWriter(Writer * wr1, Writer * wr2)
{
    if(strcmp(wr1->name, wr2->name))
        return 0;
    if(strcmp(wr1->country, wr2->country))
        return 0;
    if(wr1->id != wr2->id)
        return 0;
    return 1;
}
int cmpBook(Book * bk1, Book * bk2)
{
    if(strcmp(bk1->name, bk2->name))
        return 0;
    if(bk1->author != bk2->author)
        return 0;
    if(bk1->year != bk2->year)
        return 0;
    return 1;
}
