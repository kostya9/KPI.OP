#include "window_controls.h"
void createLabels(HWND parent)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hwnd = CreateWindowEx(
                0,
                WC_STATIC,
                "Name",
                WS_CHILD | WS_VISIBLE,
                10, 10, 150, 20,
                parent,
                (HMENU) (rand()%1000),
                hInstance,
                NULL
                );
    HWND hwnd1 = CreateWindowEx(
            0,
            WC_STATIC,
            "Surname",
            WS_CHILD | WS_VISIBLE,
            10, 50, 150, 20,
            parent,
            (HMENU) (rand()%1000),
            hInstance,
            NULL
            );
    HWND hwnd2 = CreateWindowEx(
            0,
            WC_STATIC,
            "AveragePolygons",
            WS_CHILD | WS_VISIBLE,
            10, 90, 150, 20,
            parent,
            (HMENU) (rand()%1000),
            hInstance,
            NULL
            );

}
void createEdits(HWND parent)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hwnd = CreateWindowEx(
            0,
            WC_EDIT,
            "Name",
            WS_CHILD | WS_VISIBLE,
            180, 10, 150, 20,
            parent,
            (HMENU) EDITNAMECLASS,
            hInstance,
            NULL
            );
    HWND hwnd1 = CreateWindowEx(
            0,
            WC_EDIT,
            "Surname",
            WS_CHILD | WS_VISIBLE,
            180, 50, 150, 20,
            parent,
            (HMENU) EDITSURNAMECLASS,
            hInstance,
            NULL
            );
    HWND hwnd2 = CreateWindowEx(
            0,
            WC_EDIT,
            "0.0",
            WS_CHILD | WS_VISIBLE,
            180, 90, 150, 20,
            parent,
            (HMENU) EDITAVERAGEPOLYGONSCLASS,
            hInstance,
            NULL
            );

}
void createCheckBox(HWND parent)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hwnd = CreateWindowEx(
            0,
            WC_BUTTON,
            "Active",
            BS_CHECKBOX | WS_CHILD | WS_VISIBLE,
            180, 130, 150, 20,
            parent,
            (HMENU) CHICKBOXACTIVECLASS,
            hInstance,
            NULL
            );
}
void createButton(HWND parent)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hwnd = CreateWindowEx(
            0,
            WC_BUTTON,
            "Go",
            WS_CHILD | WS_VISIBLE,
            180, 170, 150, 20,
            parent,
            (HMENU) BUTTONCLASS,
            hInstance,
            NULL
            );
}

