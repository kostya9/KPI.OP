#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char * compressed(FILE * fR, size_t * size);
char * decompressed(FILE * fR, size_t * size);
size_t getSizeOfFile(FILE * fp);
int main(int argc, char *argv[])
{
    char mode;
    FILE * fR;
    FILE * fW;
    if(argc > 3)
    {
        char * flag = argv[1];
        if(strlen(flag) != 2)
            exit(EXIT_FAILURE);
        else if(flag[1]=='c' || flag[1]=='d')
            mode = flag[1];
        else
            exit(EXIT_FAILURE);
        char * fNameFrom = argv[2];
        fR = fopen(fNameFrom, "rb");
        char * fNameWhere = argv[3];
        fW = fopen(fNameWhere, "wb");
        if(!fR || !fW)
            exit(EXIT_FAILURE);
    }
    else
        exit(EXIT_FAILURE);
    size_t sz;
    char * writeInfo;
    if(mode=='c')
        writeInfo = compressed(fR, &sz);
    else if(mode=='d')
        writeInfo = decompressed(fR, &sz);
    fwrite(writeInfo, sizeof(char), sz, fW);
    free(writeInfo);
    fclose(fR);
    fclose(fW);
    puts("Successfully");
    return EXIT_SUCCESS;
}
char * compressed(FILE * fR, size_t * size)
{
    unsigned int i;
    char prevByte;
    unsigned int pos = 0, count = 0;
    size_t sz = getSizeOfFile(fR);
    char * readInfo = (char *)malloc(sz);
    char * writeInfo = (char *)malloc(2 * sz);
    fread(readInfo,sizeof(char), sz, fR);
    for(i = 0; i <= sz; i++)
    {
        if(count == 0)
        {
            prevByte = readInfo[i];
            count++;
        }
        else
        {
            char curByte = readInfo[i];
            if(prevByte==curByte && count < 255)
            {
                count++;
            }
            else
            {
                writeInfo[pos] = prevByte;
                writeInfo[pos + 1] = count;
                pos+=2;
                count = 0;
                i--;
            }
        }
    }
    *size = pos;
    free(readInfo);
    return writeInfo;
}
char * decompressed(FILE * fR, size_t * size)
{
    unsigned int i, j;
    unsigned int pos = 0;
    size_t szDec = 0;
    size_t sz = getSizeOfFile(fR);
    char * readInfo = (char *)malloc(sz);
    fread(readInfo, sizeof(char), sz, fR);
    for(i = 1; i < sz; i+=2)
    {
        szDec+=readInfo[i];
    }
    char * writeInfo = (char *)malloc(szDec);
    for(i = 0; i < sz; i+=2)
    {
        char curByte = readInfo[i];
        size_t count = readInfo[i + 1];
        for(j = 0; j < count; j++)
        {
            writeInfo[pos] = curByte;
            pos++;
        }
    }
    free(readInfo);
    *size = pos;
    return writeInfo;
}
size_t getSizeOfFile(FILE * fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}
