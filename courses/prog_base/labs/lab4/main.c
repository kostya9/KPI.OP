#include <stdlib.h>
#include <stdio.h>
#include "People.h"
#include "Texts.h"
#include "interface.h"
int main(void)
{
    Post * posts;
    Person * ppl;
    int nOfPosts;
    int nOfPeople;
    posts = getPosts(&nOfPosts);
    ppl = getPeople(&nOfPeople);
    initConsole(posts, nOfPosts, ppl, nOfPeople);
    posts = savePosts(posts, &nOfPosts);
    ppl = savePeople(ppl, &nOfPeople);
    return EXIT_SUCCESS;
}
