#pragma once
#include <windows.h>
#include <CommCtrl.h>
#define EDITNAMECLASS 120
#define EDITSURNAMECLASS 121
#define EDITAVERAGEPOLYGONSCLASS 122
#define CHICKBOXACTIVECLASS 123
#define BUTTONCLASS 124
void createLabels(HWND parent);
void createEdits(HWND parent);
void createCheckBox(HWND parent);
void createButton(HWND parent);
