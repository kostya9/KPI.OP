#include <stdlib.h>
#include <stdio.h>
#include "People.h"
#include "Texts.h"
int main(void)
{
    Post * posts;
    int nOfPosts;
    posts = getPosts(&nOfPosts);
    posts = addComentToPost(0, posts, "This is shit! You are a bastard!!!11", &nOfPosts);
    posts = savePosts(posts, &nOfPosts);
    return EXIT_SUCCESS;
}
