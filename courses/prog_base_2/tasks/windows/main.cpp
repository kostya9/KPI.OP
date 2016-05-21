#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <ctype.h>
#include <stdio.h>
#include "window_controls.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           400,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

int isFloat(char * number)
{
    int dots = 0;
    int len = strlen(number);
    for(int i = 0; i < len; i++)
    {
        if(isdigit(number[i]) == 0)
        {
            if(number[i] == '.')
            {
                dots++;
            }
            else
                return 0;
        }
    }
    if(dots > 1)
        return 0;
    return 1;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            createLabels(hwnd);
            createEdits(hwnd);
            createCheckBox(hwnd);
            createButton(hwnd);
            HWND hwndName = GetDlgItem(hwnd, EDITNAMECLASS);
            HWND hwndSurName = GetDlgItem(hwnd, EDITSURNAMECLASS);
            HWND hwndAveragePolygons = GetDlgItem(hwnd, EDITAVERAGEPOLYGONSCLASS);
            CheckDlgButton(hwnd, CHICKBOXACTIVECLASS, BST_UNCHECKED);
            EnableWindow(hwndName, 0);
            EnableWindow(hwndSurName, 0);
            EnableWindow(hwndAveragePolygons, 0);
        }break;
        case WM_COMMAND:
        {
            HWND hwndName = GetDlgItem(hwnd, EDITNAMECLASS);
            HWND hwndSurName = GetDlgItem(hwnd, EDITSURNAMECLASS);
            HWND hwndAveragePolygons = GetDlgItem(hwnd, EDITAVERAGEPOLYGONSCLASS);
             switch(LOWORD(wParam))
             {
                case CHICKBOXACTIVECLASS:
                {
                    BOOL checked = IsDlgButtonChecked(hwnd, CHICKBOXACTIVECLASS);
                    if(checked)
                    {
                        CheckDlgButton(hwnd, CHICKBOXACTIVECLASS, BST_UNCHECKED);
                        EnableWindow(hwndName, 0);
                        EnableWindow(hwndSurName, 0);
                        EnableWindow(hwndAveragePolygons, 0);
                    }
                    else{
                        CheckDlgButton(hwnd, CHICKBOXACTIVECLASS, BST_CHECKED);
                        EnableWindow(hwndName, 1);
                        EnableWindow(hwndSurName, 1);
                        EnableWindow(hwndAveragePolygons, 1);
                    }
                }break;
                case BUTTONCLASS:
                {
                    TCHAR buffName[1024];
                    TCHAR buffSurName[1024];
                    TCHAR buffAveragePolygons[1024];
                    GetWindowText(hwndName, buffName, 1024);
                    GetWindowText(hwndSurName, buffSurName, 1024);
                    GetWindowText(hwndAveragePolygons, buffAveragePolygons, 1024);
                    char buff[1000];
                    sprintf(buff, "You have selected %s %s with average polygons at %s. Good job!", buffName, buffSurName, buffAveragePolygons);
                    if(isFloat(buffAveragePolygons) == 0)
                    {
                        MessageBox(
                            NULL,
                            (LPCSTR)TEXT("AveragePolygons incorrect format. Is it a float?"),
                            (LPCSTR)TEXT("Error"),
                            MB_OK
                        );
                        return 0;
                    }

                    int msgboxID = MessageBox(
                            NULL,
                            (LPCSTR)TEXT(buff),
                            (LPCSTR)TEXT("Designer"),
                            MB_OK
                        );

                }break;
             }

        }break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
