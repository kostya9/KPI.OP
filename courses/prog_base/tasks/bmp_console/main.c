#include <stdio.h>
#include <windows.h>
#define STDRES 80
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
int main(int argc, char *argv[])
{
    char * fName;
    if(argc>1)
    {
        fName = argv[1];
        puts(argv[1]);
    }
    else
        fName = NULL;
    BITMAPINFOHEADER bh;
    setConsoleColor(0x07);
    system("mode con:cols=100 lines=100");
    unsigned char * bmp = LoadBitmapFile(fName, &bh);
    if(bmp)
    {
        for(int i = 0; i < bh.biHeight; i++)
            for(int j = 0; j < bh.biWidth; j++)
                {
                    unsigned char redRGB = bmp[3*(j + i * bh.biHeight)];
                    unsigned char greenRGB= bmp[3*(j + i * bh.biHeight) + 1];
                    unsigned char blueRGB = bmp[3*(j + i * bh.biHeight) + 2];
                    unsigned char red = redRGB >= 127 ? 1 : 0;
                    unsigned char green = greenRGB >= 127 ? 1 : 0;
                    unsigned char blue = blueRGB >= 127 ? 1 : 0;
                    unsigned char color = (red<<2) | (green<<1) | blue;
                    if(redRGB>180 || greenRGB>180 || blueRGB>180)
                        setConsoleColor((color<<4) | BACKGROUND_INTENSITY);
                    else
                        setConsoleColor(color<<4);
                    setCursorPosition(j, bh.biHeight - i);
                    printf(" ");
                }
        free(bmp);
        return EXIT_SUCCESS;
    }
    else
    {
        puts("Invalid file");
        return EXIT_FAILURE;
    }


}
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;
    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char *bitmapImage;
    int imageIdx=0;
    unsigned char tempRGB;

    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    fread(bitmapImage,sizeof(unsigned char), bitmapInfoHeader->biSizeImage,filePtr);

    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    fclose(filePtr);
    return bitmapImage;
}
