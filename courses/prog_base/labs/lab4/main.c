#include <stdlib.h>
#include <stdio.h>
#include "People.h"
#include "Texts.h"
int main(void)
{
    Post * posts;
    int nOfPosts;
    posts = getPosts(&nOfPosts);
    deletePost(posts, &posts[1], &nOfPosts);
    posts = savePosts(posts, &nOfPosts);
    return EXIT_SUCCESS;
}
