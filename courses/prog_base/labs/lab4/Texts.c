#include "People.h"
#include "Texts.h"
#include <stdio.h>
#include <stdlib.h>
Post * getPosts(int * nOfPosts)
{
    int i, j;
    char buffer[TEXTBUFFERSIZE];
    int nOfComments;
    int idText;
    int idAuthor;
    FILE * f = fopen("Texts.txt", "r");
    if(f==NULL)
        return NULL;
    fgets(buffer, TEXTBUFFERSIZE, f);
    sscanf(buffer, "%i %i", nOfPosts, &nOfComments);
    Post * posts = (Post *)calloc(*nOfPosts, sizeof(Post));
    for(i = 0; i < nOfComments + *nOfPosts; i++)
    {
        char * curP;
        fgets(buffer, TEXTBUFFERSIZE, f);
        curP = strtok(buffer, " ");
        curP = strtok(NULL, " ");
        sscanf(curP, "%i", &idText);
        curP = strtok(NULL, " ");
        sscanf(curP, "%i", &idAuthor);
        while(curP[0]!='\0' && curP[0]!=' ')
            curP++;
        while(curP[0]=='\0')
            curP++;
        if(buffer[0]=='p')
        {
            posts[idText].authorId = idAuthor;
            posts[idText].postId = idText;
            strcpy(posts[idText].text, curP);
        }
        else if(buffer[0]=='c')
        {
            posts[idText].comments[posts[idText].nOfComments].authorId = idAuthor;
            strcpy(posts[idText].comments[posts[idText].nOfComments].text, curP);
            posts[idText].nOfComments++;
        }
    }
    fclose(f);
    return posts;
}
Post * deletePost(Post * posts, Post * post, int * nOfPosts)
{
    post->postId = -1;
    --(*nOfPosts);
    savePosts(posts, nOfPosts);
    return getPosts(nOfPosts);
}
Post * savePosts(Post * posts, int * nOfPosts)
{
    int i, j;
    int nOfComments = 0;
    FILE * f = fopen("Texts.txt", "w");
    fprintf(f, "%10c\n", ' ');
    for(i = 0; i < *nOfPosts && posts[i].postId>=0; i++)
    {
        fprintf(f, "%c %i %i %s", 'p', posts[i].postId, posts[i].authorId, posts[i].text);
        for(j = 0; j < posts[i].nOfComments; j++)
        {
            fprintf(f, "%c %i %i %s%c", 'c', i, posts[i].comments[j].authorId, posts[i].comments[j].text, j!=0 ? '\n' : ' ');
            nOfComments++;
        }
    }
    fclose(f);
    f = fopen("Texts.txt", "r+");
    fprintf(f, "%i %i", *nOfPosts, nOfComments);
    fclose(f);
    *nOfPosts = 0;
    free(posts);
    return NULL;
}
Post * addPost(Post * posts, Post * pst, int * nOfPosts)
{
    int nOfComments;
    int j;
    char buffer[100];
    posts = savePosts(posts, nOfPosts);
    posts = getPosts(nOfPosts);
    FILE * f = fopen("Texts.txt", "r");
    if(f==NULL)
        return NULL;
    fgets(buffer, TEXTBUFFERSIZE, f);
    sscanf(buffer, "%i %i", nOfPosts, &nOfComments);
    fclose(f);
    f = fopen("Texts.txt", "a");
    fprintf(f, "%c %i %i %s\n", 'p', *nOfPosts, pst->authorId, pst->text);
    for(j = 0; j < pst->nOfComments; j++)
    {
        fprintf(f, "%c %i %i %s\n", 'c', *nOfPosts, pst->comments[j].authorId, pst->comments[j].text);
        nOfComments++;
    }
    (*nOfPosts)++;
    fclose(f);
    f = fopen("Texts.txt", "r+");
    fprintf(f, "%i %i", *nOfPosts, nOfComments);
    fclose(f);
    posts = getPosts(nOfPosts);
    return posts;
}
Post * addComentToPost(int id, Post * posts, const char * comment, int * nOfPosts)
{
    strcpy(posts[id].comments[posts[id].nOfComments].text, comment);
    posts[id].nOfComments++;
    posts = savePosts(posts, nOfPosts);
    posts = getPosts(nOfPosts);
    return posts;
}
