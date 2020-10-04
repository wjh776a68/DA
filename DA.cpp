
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2019-2020										*
* 																											*
*								File Name:			DA.cpp							        				*
*								Author:				wjh776a68												*
*  								Function:			main Entrance of DA, GUI source code					*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/03												*
* 																											*
*************************************************************************************************************/

// DA.cpp : Defines the entry point for the application.
//
//#include "pch.h"
#include "framework.h"
#include "DA.h"
#include "DAcommon.h"
#include "CheckDA.h"
#define MAX_LOADSTRING 100

#define IDM_BUTTON_ADDKEYWORDS 10681
#define IDM_BUTTON_ADDDIVISIONS 10682
#define IDM_BUTTON_ADDARITHMETIC 10683
#define IDM_BUTTON_ADDRELATION 10684

// Global Variables:
HINSTANCE               hInst;                                // current instance
WCHAR                   szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR                   szWindowClass[MAX_LOADSTRING];            // the main window class name
TCHAR                   szWindowClass_SubWindows[MAX_LOADSTRING] = _T("childwin32app");

HWND                    main_RichTextBox_VAR;                      //���ı���
HWND                    main_underoutput_RichTextBox_VAR;          //�·�������ı���

HWND                    subwindows_AddVIW_hwnd;
HWND                    SubWindows_TextBox,
                        SubWindows_button_AddKeywords, 
                        SubWindows_button_AddDivisions, 
                        SubWindows_button_AddArithmetic, 
                        SubWindows_button_AddRelation;              //�Ӵ����ı��򡢰�ť����

FileDialogClass         FileDialogCore;
RichTextDialogclass     RichTextDialog_main_core;
RichTextDialogclass     RichTextDialog_output_core;
FileIOFunctionsclass    FileIOFunctionsCore;
CheckDAclass            CheckDACore;

// Forward declarations of functions included in this code module:
ATOM                    MyRegisterClass(HINSTANCE hInstance);
ATOM                    MyRegisterClass_SubWindows(HINSTANCE hInstance);

BOOL                    InitInstance(HINSTANCE, int);
LRESULT CALLBACK        WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK        WndProc_SubWindows(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK        About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    InitCommonControls();
    LoadLibrary(TEXT("Msftedit.dll"));


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MyRegisterClass_SubWindows(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM MyRegisterClass_SubWindows(HINSTANCE hInstance)
{
    WNDCLASSEX childwcex;
    childwcex.cbSize = sizeof(WNDCLASSEX);
    childwcex.style = CS_HREDRAW | CS_VREDRAW;
    childwcex.lpfnWndProc = WndProc_SubWindows;
    childwcex.cbClsExtra = 0;
    childwcex.cbWndExtra = 0;
    childwcex.hInstance = GetModuleHandle(NULL);
    childwcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DA));//�ο�����: https://blog.csdn.net/baidu_24190413/article/details/47430551;
    childwcex.hCursor = LoadCursor(NULL, IDC_ARROW);//���������ʽ
    childwcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���û�ˢ����ɫ
    childwcex.lpszMenuName = NULL;
    childwcex.lpszClassName = szWindowClass_SubWindows;
    childwcex.hIconSm = LoadIcon(childwcex.hInstance, MAKEINTRESOURCE(IDI_DA));
    if (!RegisterClassEx(&childwcex)) {
        MessageBox(NULL, _T("call to RegisterClassEX(child) failed."), _T("TheEditor"), NULL);
        return 1;
    }

    return RegisterClassExW(&childwcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/**************************************************************
*   ��������	createwidgets
*	���ܣ�	�������ı�����
*	����:	hWnd	        HWND	�����ھ��
*	����ֵ��	0|-1       		int 	����������󷵻�-1�����򷵻�0
***************************************************************/
int createwidgets(HWND hWnd) {
    main_RichTextBox_VAR = CreateWindowEx(0, MSFTEDIT_CLASS, TEXT("������ļ����Դ����ļ�.\n"),
        WS_VISIBLE | WS_CHILD | WS_VSCROLL |
        ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | ES_AUTOVSCROLL /*| ES_READONLY*/,
        0, 0, 480, 400,
        hWnd, NULL, hInst, NULL);

    main_underoutput_RichTextBox_VAR = CreateWindowEx(0, MSFTEDIT_CLASS, TEXT("�������.\n"),
        WS_VISIBLE | WS_CHILD | WS_VSCROLL |
        ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | ES_AUTOVSCROLL /*| ES_READONLY*/,
        0, 0, 480, 400,
        hWnd, NULL, hInst, NULL);

    if (!main_underoutput_RichTextBox_VAR | !main_RichTextBox_VAR){
        FatalAppExitA(0, "Couldn't create the rich text box,program exit!");
        return -1;
    }



    return 0;
}

void SubWindows_AddVIW(HWND mainwindows_hWnd) {
    subwindows_AddVIW_hwnd = CreateWindowExW(0, L"childwin32app", TEXT("���ӹؼ��ʡ��ֽ�����������������ϵ�����\n"),
         WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 280,
        mainwindows_hWnd, NULL, GetModuleHandle(NULL), NULL);
    

    SubWindows_TextBox = CreateWindowEx(0, MSFTEDIT_CLASS, TEXT(""),
        WS_VISIBLE | WS_CHILD |
        ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | WS_BORDER/*| ES_READONLY*/,
        20, 10, 360, 50,
        subwindows_AddVIW_hwnd, NULL, GetModuleHandle(NULL), NULL);

    SubWindows_button_AddKeywords = CreateWindowEx(0, L"BUTTON", L"���ӹؼ���",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 100, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDKEYWORDS, NULL/* GetModuleHandle(NULL)*/, NULL);

    SubWindows_button_AddDivisions = CreateWindowEx(0, L"BUTTON", L"���ӷֽ��",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 130, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDDIVISIONS, NULL/* GetModuleHandle(NULL)*/, NULL);

    SubWindows_button_AddArithmetic = CreateWindowEx(0, L"BUTTON", L"�������������",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 160, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDARITHMETIC, NULL/* GetModuleHandle(NULL)*/, NULL);

    SubWindows_button_AddRelation = CreateWindowEx(0, L"BUTTON", L"���ӹ�ϵ�����",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 190, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDRELATION, NULL/* GetModuleHandle(NULL)*/, NULL);

   
    ShowWindow(SubWindows_button_AddKeywords, SW_SHOW);
    ShowWindow(SubWindows_button_AddDivisions, SW_SHOW);
    ShowWindow(SubWindows_button_AddArithmetic, SW_SHOW);
    ShowWindow(SubWindows_button_AddRelation, SW_SHOW);
    ShowWindow(subwindows_AddVIW_hwnd, SW_SHOW);
    UpdateWindow(subwindows_AddVIW_hwnd);

}



LRESULT CALLBACK WndProc_SubWindows(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        break;
    case WM_COMMAND:
    {
        TCHAR caughtVIW[MAXLEN];
        GetWindowText(SubWindows_TextBox, caughtVIW, MAXLEN);

        int iLen = WideCharToMultiByte(CP_ACP, 0, caughtVIW, -1, NULL, 0, NULL, NULL);
        char* chRtn = new char[iLen * sizeof(char)];
        WideCharToMultiByte(CP_ACP, 0, caughtVIW, -1, chRtn, iLen, NULL, NULL);
        std::string str(chRtn);

        switch (LOWORD(wParam)) {
        case IDM_BUTTON_ADDKEYWORDS:
            CheckDACore.AddKeywords(str);
            SetWindowText(SubWindows_TextBox, TEXT(""));
            break;
        case IDM_BUTTON_ADDARITHMETIC:
            CheckDACore.AddArithmetic(str);
            SetWindowText(SubWindows_TextBox, TEXT(""));
            break;
        case IDM_BUTTON_ADDDIVISIONS:
            CheckDACore.AddDivision(str);
            SetWindowText(SubWindows_TextBox, TEXT(""));
            break;
        case IDM_BUTTON_ADDRELATION:
            CheckDACore.AddRelation(str);
            SetWindowText(SubWindows_TextBox, TEXT(""));
            break;
        }

        
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);

        break;
    }
    case WM_SIZE:
        break;
    case WM_DESTROY:
        //PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);

    }

    return 0;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        if(createwidgets(hWnd)==-1) //Error
            return -1;
        RichTextDialog_main_core.RichTextDialog_BindHWND(main_RichTextBox_VAR);
        RichTextDialog_output_core.RichTextDialog_BindHWND(main_underoutput_RichTextBox_VAR);
        break;
    }
    case WM_COMMAND:
    {

        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_FILE_NEW:
            FileDialogCore.getfilepath(FILE_DIALOG_CMD_CREATE);
            RichTextDialog_main_core.RichTextDialog_ClearText();
            break;

        case ID_FILE_OPEN:          
            FileIOFunctionsCore.selectFile(FileDialogCore.getfilepath(FILE_DIALOG_CMD_OPEN));        
            RichTextDialog_main_core.RichTextDialog_SetText(FileIOFunctionsCore.Reads());
            break;
            
        case ID_FILE_SAVE:
            if (FileDialogCore.isfilepathvalid==FALSE) {
                FileIOFunctionsCore.Saves(FileDialogCore.getfilepath(FILE_DIALOG_CMD_CREATE), RichTextDialog_main_core.RichTextDialog_GetText());
            } else {
                FileIOFunctionsCore.Saves(FileDialogCore.getLastfilepath(), RichTextDialog_main_core.RichTextDialog_GetText());
            }     
            break;

        case ID_FILE_CLOSE:
            FileDialogCore.clearLastfilepath();
            RichTextDialog_main_core.RichTextDialog_ClearText();
            break;

        case ID_FILE_ADDVIW:            // Q: How to explain the abbreviation word VIW? A: Do you know what is VIP means?
            SubWindows_AddVIW(hWnd);
            break;

        case ID_FILE_DACHECK:
            
            CheckDACore.BindInputHWND(main_RichTextBox_VAR);
            CheckDACore.BindOutputHWND(main_underoutput_RichTextBox_VAR);

            CheckDACore.DoCheck();
            break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
       
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_SIZE:
    {
        
        LPRECT rect = (LPRECT)malloc(sizeof(tagRECT));
        GetClientRect(hWnd, rect);
        SetWindowPos(main_RichTextBox_VAR, HWND_TOP, 0, 0, rect->right, int(rect->bottom * 0.6), SWP_NOMOVE | SWP_NOZORDER);

        SetWindowPos(main_underoutput_RichTextBox_VAR, HWND_TOP, 0, int(rect->bottom * 0.6) + 1, rect->right, rect->bottom - (int(rect->bottom * 0.6) + 1), SWP_NOZORDER);
        break;
        
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}