#include <stdlib.h>
#include "mainHead.h"
int main(void)
{
    Person ppl[LIMIT];
    Post psts[POSTLIMIT];
    nullifyPeople(ppl);
    nullifyPosts(psts);
    getPeople(ppl);
    getPosts(psts);
    initConsole(psts, ppl);
    return EXIT_SUCCESS;
}
