#ifndef __TXTS_
#define __TXTS_
#define TEXTBUFFERSIZE 500
#define MAXCOMMENTNUM 20
typedef struct
{
    char authorId;
    char text[300];
} Comment;
typedef struct
{
    char postId;
    char authorId;
    char text[300];
    int nOfComments;
    Comment comments[MAXCOMMENTNUM];
} Post;
Post * getPosts(int * nOfPosts);
Post * savePosts(Post * posts, int * nOfPosts);
Post * deletePost(Post * posts, Post * post, int * nOfPosts);
Post * addPost(Post * posts, Post * pst, int * nOfPosts);
/*@todo Write a text write a comment(by author and to a post)*/
#endif // __TXTS_
