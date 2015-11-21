#ifndef __commands_
#define __commands_
#define HELPINFO \
"Try these commands \n \
if numbers get too big they will reset \n \
nullify - to set all elements equal to 0\n \
change i n - to set an element at index i to n \n \
random i n - to set all elements to new random numbers in range\n from i to n \n \
reverse - to get all elements in reverse order \n \
sum - to get the sum of all elements \n \
nnegative - to get number of negative numbers \n \
shift i - simple shift to right by i \n \
cyclesh i - cycle shift to right by i \n \
powall i - to set all elements to their power of i \n \
firsmin - to get first minimal value and its index \n \
swapmaxmin - to swap last maximum and minimum values \n \
exit - to quit the program"
#define LENGTH 90
#define HEIGHT 30
#define WORKZONE 20
#define RIGHTBORDER LENGTH - 20
#define BOTBORDER HEIGHT - 5
#define COLORSELECT BACKGROUND_BLUE | BACKGROUND_RED | 0x00
#define COLORDEF 0x07
#define COLORWORKBACK BACKGROUND_BLUE | FOREGROUND_GREEN
#define COLORWORKFOR BACKGROUND_GREEN
#define COLORWORKCOM 0x70
#define COLORERROR BACKGROUND_RED
void writeHelp();
void initConsole();
void getCommand(double[], size_t);
void setCursorPosition(int, int);
#endif
