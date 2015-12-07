#ifndef __texts_
#define __texts_
#define PSTSAVEPLACE "texts.bin"
#define POSTLIMIT (LIMIT * 2)
#define COMMENTLIMIT LIMIT
#define COMMENTSIZE 150
#define TEXTSIZE 300
#define MAXCOMMENTNUM 20
typedef struct
{
    char postId;
    char authorId;
    char text[COMMENTSIZE];
} Comment;
typedef struct
{
    char postId;
    char authorId;
    char text[TEXTSIZE];
    int nOfComments;
    Comment comments[COMMENTLIMIT];
} Post;
#endif // __texts_
