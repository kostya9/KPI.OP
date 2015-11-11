#ifndef __commands_
#define __commands_
#define HELPINFO \
"Try these commands \n \
nullify - to set all elements equal to 0\n \
change i n - to set an element at index i to n \n \
random - to set all elements to new random numbers \n \
reverse - to get all elements in reverse order \n \
sum - to get the sum of all elements \n \
nnegative - to get number of negative numbers \n \
shift i - simple shift to right by i \n \
cyclesh i - cycle shift to right ny i \n \
powall i - to set all elements to their power of i \n \
firsmin - to get first minimal value and its index \n \
swapmaxmin - to swap last maximum and minimum values \n \
exit - to quit the program"
#define LENGTH 100
#define HEIGHT 30
#define WORKZONE 20
#define TAB 10
#define COMMANDSACTIONS WORKZONE + 6
void writeHelp();
void getCommand(double[], size_t);
void setCursorPosition(int, int);
#endif
