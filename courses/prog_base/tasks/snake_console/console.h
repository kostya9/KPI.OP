#ifndef __console_
#define __console_
#define SNAKEFONT 20
#define CONSOLESIZE 50
#define COLORDEF 0x07
/*Windows shit*/
typedef struct _CONSOLE_FONT_INFOEX {
  ULONG cbSize;
  DWORD nFont;
  COORD dwFontSize;
  UINT  FontFamily;
  UINT  FontWeight;
  WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
BOOL WINAPI GetCurrentConsoleFontEx(
   HANDLE               hConsoleOutput,
   BOOL                 bMaximumWindow,
   PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx
);

BOOL WINAPI SetCurrentConsoleFontEx(
   HANDLE               hConsoleOutput,
   BOOL                 bMaximumWindow,
   PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx
);
/*End of windows shit*/
typedef struct
{
    char name[100];
    int points;
}Player;
Player * getScoreBoard(int *);
void addToScoreBoard(Player * player, int * nOfPlayers);
void setFontSize(int x, int y);
void initInterface(Player *, int);
void setConsoleColor(int color);
void setCursorPosition(int x, int y);
void getConsoleAttributes(int * rows, int * columns);
#endif // __console_
