#include "mainHead.h"
#include <stdio.h>
#include <string.h>
int savePosts(Post psts[POSTLIMIT])
{
    FILE * f = fopen(PSTSAVEPLACE, "wb");
    if(!f)
        return RETURN_FAILURE;
    int sz = sizeof(Post);
    fwrite(psts, sz, POSTLIMIT, f);
    fflush(f);
    fclose(f);
    return RETURN_SUCCESS;
}
int getPosts(Post psts[POSTLIMIT])
{
    FILE * f = fopen(PSTSAVEPLACE, "rb");
    if(!f)
        return RETURN_FAILURE;
    int sz = sizeof(Post);
    fread(psts, sz, POSTLIMIT, f);
    fclose(f);
    return RETURN_SUCCESS;
}
void nullifyPosts(Post psts[POSTLIMIT])
{
    int i, j;
    for(i = 0; i < POSTLIMIT; i++)
    {
        psts[i].postId = NOTINUSE;
        for(j = 0; j < COMMENTLIMIT; j++)
            psts[i].comments[j].postId = NOTINUSE;
    }

}
int deletePost(Post psts[POSTLIMIT], char postId)
{
    if(postId >= POSTLIMIT || postId < 0)
        return RETURN_FAILURE;
    int i;
    for(i = 0; i < COMMENTLIMIT; i++)
        psts[postId].comments[i].postId = NOTINUSE;
    psts[postId].postId = NOTINUSE;
    return NOTINUSE;
}
char getFreeIndOfPost(Post psts[POSTLIMIT])
{
    int i;
    for(i = 0; i < POSTLIMIT; i++)
        if(psts[i].postId == NOTINUSE)
            return i;
    return NOTINUSE;
}
char writePost(Post psts[POSTLIMIT], char authorId, char * text)
{
    char ind = getFreeIndOfPost(psts);
    if(ind==NOTINUSE)
        return RETURN_FAILURE;
    strcpy(psts[ind].text, text);
    psts[ind].authorId = authorId;
    psts[ind].postId = ind;
    savePosts(psts);
    return ind;
}
int getFreeIndOfComment(Comment * comments)
{
    int i;
    for(i = 0; i < COMMENTLIMIT; i++)
        if(comments[i].postId == NOTINUSE)
            return i;
    return NOTINUSE;
}
int addComment(Post psts[POSTLIMIT], char authorId, char postId, char * text)
{
    if(postId >= POSTLIMIT || postId < 0 || authorId < 0 || authorId >= LIMIT)
        return RETURN_FAILURE;
    int ind = getFreeIndOfComment(psts[postId].comments);
    if(ind==NOTINUSE)
        return RETURN_FAILURE;
    psts[postId].comments[ind].postId = postId;
    psts[postId].nOfComments++;
    psts[postId].comments[ind].authorId = authorId;
    strcpy(psts[postId].comments[ind].text, text);
    return ind;
}

