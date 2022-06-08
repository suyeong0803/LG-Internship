#include <windows.h>
#include <string>
#include "Controller.h"
#include "Validation.h" 

#define ID_BUTTON_VIDEO_1 1002
#define ID_TEXT_VIDEO_1 1003
#define ID_BUTTON_VIDEO_2 1004
#define ID_TEXT_VIDEO_2 1005
#define ID_BUTTON_SAVE_PATH_CHECK 1006
#define ID_TEXT_SAVE_PATH 1007
#define ID_TEXT_SAVE_NAME 1008
#define ID_BUTTON_MERGE 1009

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain, textLabel[6], textBox[4], uploadButton[4];;
LPCTSTR lpszClass = TEXT("Video Edit Program");
Controller* controller;
Validation* validation;
TCHAR GetVideo1Path[500], GetVideo2Path[500], GetSavePath[500], GetSaveName[500];
std::string filePath1, filePath2, savePath;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WndProc;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&WndClass);

    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
        NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&Message, NULL, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    OPENFILENAME OFN;
    TCHAR filePathName[100] = "";
    TCHAR lpstrFile[100] = "";
    static TCHAR filter[] = "모든 파일\0*.*\0MPEG2 파일\0*.mpg\0MPEG4 파일\0*.mp4";



    memset(&OFN, 0, sizeof(OPENFILENAME));
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = filter;
    OFN.lpstrFile = lpstrFile;
    OFN.nMaxFile = 100;
    OFN.lpstrInitialDir = ".";

    switch (iMessage) {
    case WM_CREATE:
        hWndMain = hWnd;
        textLabel[0] = CreateWindow(TEXT("static"), TEXT("병합할 파일 2개의 경로를 입력하세요."), WS_CHILD | WS_VISIBLE,
            80, 100, 410, 25,
            hWnd, (HMENU)NULL, g_hInst, NULL);

        textLabel[1] = CreateWindow(TEXT("static"), TEXT("Video1"), WS_CHILD | WS_VISIBLE,
            80, 130, 60, 25,
            hWnd, (HMENU)NULL, g_hInst, NULL);

        textBox[0] = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            150, 130, 250, 25,
            hWnd, (HMENU)ID_TEXT_VIDEO_1, g_hInst, NULL);

        uploadButton[0] = CreateWindow(TEXT("button"), TEXT("파일 열기"), WS_CHILD | WS_VISIBLE | WS_BORDER,
            410, 130, 80, 25,
            hWnd, (HMENU)ID_BUTTON_VIDEO_1, g_hInst, NULL);

        textLabel[2] = CreateWindow(TEXT("static"), TEXT("Video2"), WS_CHILD | WS_VISIBLE,
            80, 160, 60, 25,
            hWnd, (HMENU)NULL, g_hInst, NULL);

        textBox[1] = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            150, 160, 250, 25,
            hWnd, (HMENU)ID_TEXT_VIDEO_2, g_hInst, NULL);

        uploadButton[1] = CreateWindow(TEXT("button"), TEXT("파일 열기"), WS_CHILD | WS_VISIBLE | WS_BORDER,
            410, 160, 80, 25,
            hWnd, (HMENU)ID_BUTTON_VIDEO_2, g_hInst, NULL);

        textLabel[3] = CreateWindow(TEXT("static"), TEXT("병합된 파일을 저장할 경로를 입력하세요."), WS_CHILD | WS_VISIBLE,
            80, 260, 410, 25,
            hWnd, (HMENU)NULL, g_hInst, NULL);

        textLabel[4] = CreateWindow(TEXT("static"), TEXT("경로"), WS_CHILD | WS_VISIBLE,
            80, 290, 60, 25,
            hWnd, (HMENU)NULL, g_hInst, NULL);

        textBox[2] = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            150, 290, 250, 25,
            hWnd, (HMENU)ID_TEXT_SAVE_PATH, g_hInst, NULL);

        uploadButton[2] = CreateWindow(TEXT("button"), TEXT("확인"), WS_CHILD | WS_VISIBLE | WS_BORDER,
            410, 290, 80, 25,
            hWnd, (HMENU)ID_BUTTON_SAVE_PATH_CHECK, g_hInst, NULL);

        uploadButton[3] = CreateWindow(TEXT("button"), TEXT("Merge"), WS_CHILD | WS_VISIBLE | WS_BORDER,
            250, 400, 80, 55,
            hWnd, (HMENU)ID_BUTTON_MERGE, g_hInst, NULL);
        return 0;
     case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BUTTON_VIDEO_1:
            
            if (GetOpenFileName(&OFN) != 0) {
                SetWindowText(textBox[0], TEXT(OFN.lpstrFile));
                filePath1 = OFN.lpstrFile;
            }
            else {
                MessageBox(hWnd, "파일이 존재하지 않습니다. 경로를 다시 확인해주세요", TEXT("Alert"), MB_OK);
                SetWindowText(textBox[0], "");
            }
            return 0;

        case ID_BUTTON_VIDEO_2:
            if (GetOpenFileName(&OFN) != 0) {
                SetWindowText(textBox[1], TEXT(OFN.lpstrFile));
                GetWindowText(textBox[1], GetVideo1Path, 128);
                filePath2 = OFN.lpstrFile;
            }
            else {
                MessageBox(hWnd, "파일이 존재하지 않습니다. 경로를 다시 확인해주세요", TEXT("Alert"), MB_OK);
                SetWindowText(textBox[1], "");
            }
            return 0;

        case ID_BUTTON_SAVE_PATH_CHECK:
            GetWindowText(textBox[2], GetSavePath, 128);
            GetWindowText(textBox[3], GetSaveName, 128);

            if (validation->isExisted(GetSavePath) == FILE_EXISTS) {
                MessageBox(hWnd, "이미 존재하는 파일 이름이거나 올바르지 않은 경로입니다.", TEXT("Alert"), MB_OK);
            }
            else {
                savePath = GetSavePath;
                MessageBox(hWnd, "성공", TEXT("결과"), MB_OK);
            }
            return 0;

        case ID_BUTTON_MERGE:
            std::cout << filePath1 + " " << filePath2 + " " << savePath;
            if (filePath1.size() > 0 && filePath2.size() > 0 && savePath.size() > 0) {
                controller->callMerge(filePath1, filePath2, savePath);
                MessageBox(hWnd, "성공", TEXT("결과"), MB_OK);
            }
            else {
                MessageBox(hWnd, "실패", TEXT("결과"), MB_OK);
            }
            return 0;
        } 
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
