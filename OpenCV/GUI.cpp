#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"

#define CONVERTID   1001
#define QUITID         1002
#define UPLOADID_1  1003
#define UPLOADID_2  1004
#define RADIOID_1     1005
#define RADIOID_2     1006

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
);

LRESULT CALLBACK WndProc(
    _In_ HWND   hWnd,
    _In_ UINT   message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);

HINSTANCE hInst;
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Video Type Converting Program");

HWND textLabel[2], textBoxPath[2], uploadButton[2], radioButton[2], statusLabel[2];
HWND convertButton, quitButton;

int radioType = 0;
validation* v1 = new validation();
validation* v2 = new validation();

int WINAPI WinMain(HINSTANCE hInstance,
                            HINSTANCE hPrevInstance,
                            LPSTR lpCmdLine,
                            int nCmdShow){

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application dows not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application

    HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
                                                szWindowClass, szTitle,
                                                WS_OVERLAPPEDWINDOW,
                                                CW_USEDEFAULT, CW_USEDEFAULT,
                                                500, 500,
                                                NULL, NULL, hInstance, NULL
                                                );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


void callValidation(validation* v, int index)
{
    v->isChecked = true;

    int path = v->checkPath(v->input);
    std::string result;

    if (path == 0)  result = "SUCCESS!";
    else if (path == -1) result = "Please Check Your File EXTENSION!";
    else if (path == -2) result = "It is DIRECTORY!";
    else if (path == -3) result = "Please Check Your File PATH!";
    else if (path == -4) result = "Please Insert File Path!";

    SetWindowText(statusLabel[index], TEXT(result.c_str()));
}
void callConvert(validation* v, int index, std::string convertType)
{
    int converter = v->callConverter(v->input, convertType);
    std::string result = "";

    if (converter == 1) result = "MPEG2 Convert Success!";
    if (converter == 2) result = "MPEG4 Convert Success!";
    else if (converter == -1) result = "already " + convertType + "!";
    else if (converter == -2) result = "Please Press Upload Button!";
    else if (converter == -3) result = "Please Check Convert Type!";
    else if (converter == -4) result = "Please Insert File Path!";

    SetWindowText(statusLabel[index], TEXT(result.c_str()));
}
LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
    {
        textLabel[0] = CreateWindow(TEXT("static"), TEXT("Video1 Path : "),
                                              WS_CHILD | WS_VISIBLE,
                                              80, 100, 120, 20,
                                              hWnd, NULL, hInst, NULL);

        textBoxPath[0] = CreateWindow(TEXT("Edit"), TEXT(""),
                                              WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                              170, 100, 200, 20,
                                              hWnd, (HMENU)4, hInst, NULL);

        uploadButton[0] = CreateWindow(TEXT("button"), TEXT("Upload"),
                                                  WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                                  380, 100, 50, 20,
                                                  hWnd, (HMENU)UPLOADID_1, hInst, NULL);

        textLabel[1] = CreateWindow(TEXT("static"), TEXT("Video2 Path : "),
                                              WS_CHILD | WS_VISIBLE,
                                              80, 150, 120, 20,
                                              hWnd, NULL, hInst, NULL);

        textBoxPath[1] = CreateWindow(TEXT("Edit"), TEXT(""),
                                                  WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                                  170, 150, 200, 20,
                                                  hWnd, (HMENU)5, hInst, NULL);

        uploadButton[1] = CreateWindow(TEXT("button"), TEXT("Upload"),
                                                   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                                   380, 150, 50, 20,
                                                   hWnd, (HMENU)UPLOADID_2, hInst, NULL);

        radioButton[0] = CreateWindow(TEXT("button"), TEXT("MPEG2"),
                                                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP | BST_CHECKED,
                                                150, 200, 100, 30,
                                                hWnd, (HMENU)RADIOID_1, hInst, NULL);

        radioButton[1] = CreateWindow(TEXT("button"), TEXT("MPEG4"),
                                                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                                280, 200, 100, 30,
                                                hWnd, (HMENU)RADIOID_2, hInst, NULL);

        convertButton = CreateWindow(TEXT("button"), TEXT("Convert"),
                                                  WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                                  150, 250, 80, 40,
                                                  hWnd, (HMENU)CONVERTID, hInst, NULL);

        quitButton     = CreateWindow(TEXT("button"), TEXT("QUIT"),
                                                  WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                                  280, 250, 80, 40,
                                                  hWnd, (HMENU)QUITID, hInst, NULL);

        statusLabel[0] = CreateWindow(TEXT("static"), TEXT("Insert Video1 Path..."),
                                                WS_CHILD | WS_VISIBLE,
                                                80, 320, 220, 60,
                                                hWnd, NULL, hInst, NULL);

        statusLabel[1] = CreateWindow(TEXT("static"), TEXT("Insert Video2 Path..."),
                                                WS_CHILD | WS_VISIBLE,
                                                80, 380, 220, 60,
                                                hWnd, NULL, hInst, NULL);

        CheckRadioButton(hWnd, 2, 3, 2);
    }
    break;
    case WM_COMMAND:
    {
        switch ( LOWORD(wParam) ) {
        case CONVERTID:
            // MessageBox(hWnd, TEXT("Convert Click"), TEXT("Convert"), MB_OK);

            if(!v1->isChecked) SetWindowText(statusLabel[0], TEXT("Please Press Upload Button!"));
            if (!v2->isChecked) SetWindowText(statusLabel[1], TEXT("Please Press Upload Button!"));

            if (v1->isChecked && v2->isChecked)
            {
                std::string convertType;
                
                if (radioType == 1) convertType = ".mpg";
                else if (radioType == 2) convertType = ".mp4";

                callConvert(v1, 0, convertType);
                callConvert(v2, 1, convertType);
            }
            break;
            
        case QUITID:
            SendMessage(hWnd, WM_CLOSE, 1, 0);
            break;

        case UPLOADID_1:
            GetWindowText(textBoxPath[0], v1->input, 128);
            callValidation(v1, 0);
            break;

        case UPLOADID_2:
            GetWindowText(textBoxPath[1], v2->input, 128);
            callValidation(v2, 1);
            break;

        case RADIOID_1:
            radioType = 1;
            break;

        case RADIOID_2:
            radioType = 2;
            break;
        }
    }
    break;
    case WM_CLOSE:
    {
        DestroyWindow(hWnd);
    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

