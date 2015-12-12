#include <stdlib.h>
#include <windows.h>
#include "mainHead.h"
int main(void)
{
    Person ppl[LIMIT];
    Post psts[POSTLIMIT];
    nullifyPeople(ppl);
    nullifyPosts(psts);
    getPeople(ppl);
    getPosts(psts);
    init(ppl, psts);
    savePeople(ppl);
    savePosts(psts);
    return EXIT_SUCCESS;
}
