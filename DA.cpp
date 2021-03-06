
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2020								    		*
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

#define IDM_LISTBOX_OUTPUT 10685
#define IDM_BUTTON_ADDKEYWORDS 10681
#define IDM_BUTTON_ADDDIVISIONS 10682
#define IDM_BUTTON_ADDARITHMETIC 10683
#define IDM_BUTTON_ADDRELATION 10684

// Global Variables:
HINSTANCE               hInst;                                // current instance
WCHAR                   szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR                   szWindowClass[MAX_LOADSTRING];            // the main window class name
TCHAR                   szWindowClass_SubWindows[MAX_LOADSTRING] = _T("childwin32app");

HWND                    main_RichTextBox_VAR;                      //富文本框
//HWND                    main_underoutput_RichTextBox_VAR;          //下方输出富文本框
HWND                    hwndList;                                   //下方输出表单
HWND                    VIW_hwndList;

HWND                    subwindows_AddVIW_hwnd;
HWND                    SubWindows_TextBox,
                        SubWindows_button_AddKeywords, 
                        SubWindows_button_AddDivisions, 
                        SubWindows_button_AddArithmetic, 
                        SubWindows_button_AddRelation;              //子窗口文本框、按钮框句柄

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
void                    ChangeSizetoDefault(HWND hwnd);

//文件主入口
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
    childwcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DA));//参考文献: https://blog.csdn.net/baidu_24190413/article/details/47430551;
    childwcex.hCursor = LoadCursor(NULL, IDC_ARROW);//设置鼠标样式
    childwcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//设置画刷背景色
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


void createDAWindows(HWND mainwindows_hWnd) {
    hwndList = CreateWindowEx(0, WC_LISTVIEW, TEXT(""),
        WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT | WS_THICKFRAME | WS_EX_TOPMOST | (WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX)   /* | LVS_EDITLABELS*/,
        0, 400, 480, 400,
        mainwindows_hWnd, (HMENU)IDM_LISTBOX_OUTPUT, hInst, 0);


    SetWindowPos(hwndList, HWND_TOP, NULL, NULL, NULL, NULL, SWP_NOSIZE | SWP_NOMOVE | SWP_NOCOPYBITS);

    ListView_SetExtendedListViewStyle(hwndList, LVS_EX_FULLROWSELECT /*| LVS_EX_CHECKBOXES*/ | LVS_EX_GRIDLINES);

    tagLVCOLUMNW lvcolum;
    TCHAR wordtext[] = TEXT("单词"), attribtext[] = TEXT("二元序列（单词种别，单词属性）"), typetext[] = TEXT("类型"), positiontext[] = TEXT("位置（行，列）");

    lvcolum.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvcolum.fmt = LVCFMT_CENTER;
    lvcolum.cx = 150;
    lvcolum.pszText = wordtext;
    lvcolum.iSubItem = 0;
    ListView_InsertColumn(hwndList, 0, &lvcolum);
    lvcolum.cx = 340;
    lvcolum.pszText = attribtext;
    lvcolum.iSubItem = 1;
    ListView_InsertColumn(hwndList, 1, &lvcolum);
    lvcolum.cx = 190;
    lvcolum.pszText = typetext;
    lvcolum.iSubItem = 2;
    ListView_InsertColumn(hwndList, 2, &lvcolum);
    lvcolum.cx = 760;
    lvcolum.pszText = positiontext;
    lvcolum.iSubItem = 3;
    ListView_InsertColumn(hwndList, 3, &lvcolum);
}

void createVIWWindows(HWND mainwindows_hWnd) {
    VIW_hwndList = CreateWindowEx(0, WC_LISTVIEW, TEXT(""),
        WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT | WS_THICKFRAME | WS_EX_TOPMOST | (WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX)   /* | LVS_EDITLABELS*/,
        0, 400, 480, 400,
        mainwindows_hWnd, (HMENU)IDM_LISTBOX_OUTPUT, hInst, 0);


    SetWindowPos(VIW_hwndList, HWND_TOP, NULL, NULL, NULL, NULL, SWP_NOSIZE | SWP_NOMOVE | SWP_NOCOPYBITS);

    ListView_SetExtendedListViewStyle(VIW_hwndList, LVS_EX_FULLROWSELECT /*| LVS_EX_CHECKBOXES*/ | LVS_EX_GRIDLINES);

    tagLVCOLUMNW lvcolum;
    TCHAR wordtext[] = TEXT("关键字"), attribtext[] = TEXT("分界符"), typetext[] = TEXT("赋值运算符"), positiontext[] = TEXT("关系运算符");

    lvcolum.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvcolum.fmt = LVCFMT_CENTER;
    lvcolum.cx = 150;
    lvcolum.pszText = wordtext;
    lvcolum.iSubItem = 0;
    ListView_InsertColumn(VIW_hwndList, 0, &lvcolum);
    lvcolum.cx = 340;
    lvcolum.pszText = attribtext;
    lvcolum.iSubItem = 1;
    ListView_InsertColumn(VIW_hwndList, 1, &lvcolum);
    lvcolum.cx = 190;
    lvcolum.pszText = typetext;
    lvcolum.iSubItem = 2;
    ListView_InsertColumn(VIW_hwndList, 2, &lvcolum);
    lvcolum.cx = 760;
    lvcolum.pszText = positiontext;
    lvcolum.iSubItem = 3;
    ListView_InsertColumn(VIW_hwndList, 3, &lvcolum);

    CheckDACore.BindVIWHWND(VIW_hwndList);
}

/**************************************************************
*   函数名：	createwidgets
*	功能：	创建富文本框函数
*	输入:	hWnd	        HWND	父窗口句柄
*	返回值：	0|-1       		int 	如果发生错误返回-1，否则返回0
***************************************************************/
int createwidgets(HWND hWnd) {
    main_RichTextBox_VAR = CreateWindowEx(0, MSFTEDIT_CLASS, TEXT("点击“文件”以打开新文件.\n"),
        WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_THICKFRAME | WS_OVERLAPPED |
        ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | ES_AUTOVSCROLL /*| ES_READONLY*/,
        0, 0, 480, 400,
        hWnd, NULL, hInst, NULL);
   

    //main_underoutput_RichTextBox_VAR = CreateWindowEx(0, MSFTEDIT_CLASS, TEXT("暂无输出.\n"),
    //    WS_VISIBLE | WS_CHILD | WS_VSCROLL |
    //    ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | ES_AUTOVSCROLL /*| ES_READONLY*/,
    //    0, 0, 480, 400,
    //    hWnd, NULL, hInst, NULL);

    if (/*!main_underoutput_RichTextBox_VAR |*/ !main_RichTextBox_VAR){
        FatalAppExitA(0, "Couldn't create the rich text box,program exit!");
        return -1;
    }

    
    createDAWindows(hWnd);

    ShowWindow(hwndList,SW_SHOWNORMAL);
    UpdateWindow(hwndList);
    UpdateWindow(hWnd);
    return 0;
}


void StartDAWindows(HWND mainwindows_hWnd){
    PWINDOWINFO tmp = (PWINDOWINFO)malloc(sizeof(WINDOWINFO));
    tmp->cbSize = sizeof(WINDOWINFO);
    if (GetWindowInfo(hwndList, tmp) == true) {
        ShowWindow(hwndList, SW_SHOWNORMAL);
        UpdateWindow(hwndList);
        UpdateWindow(mainwindows_hWnd);
    }
    else {
        createDAWindows(mainwindows_hWnd);       
    }
    ChangeSizetoDefault(mainwindows_hWnd);
}

void StartVIWWindows(HWND mainwindows_hWnd) {
    PWINDOWINFO tmp = (PWINDOWINFO)malloc(sizeof(WINDOWINFO));
    tmp->cbSize = sizeof(WINDOWINFO);
    if (GetWindowInfo(VIW_hwndList, tmp) == true) {
        ShowWindow(VIW_hwndList, SW_SHOWNORMAL);
        UpdateWindow(VIW_hwndList);
        UpdateWindow(mainwindows_hWnd);
    }
    else {
        createVIWWindows(mainwindows_hWnd);
    }
    ChangeSizetoDefault(mainwindows_hWnd);
    CheckDACore.addVIWtoVIWWindows();
}

/**************************************************************
*   函数名：	SubWindows_AddVIW
*	功能：	创建添加关键词子窗口
*	输入:	mainwindows_hWnd    HWND	父窗口句柄
*	返回值： void 	
***************************************************************/
void SubWindows_AddVIW(HWND mainwindows_hWnd) {
    subwindows_AddVIW_hwnd = CreateWindowExW(0, L"childwin32app", TEXT("添加关键词、分界符、算术运算符、关系运算符\n"),
         WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 280,
        mainwindows_hWnd, NULL, GetModuleHandle(NULL), NULL);
    

    SubWindows_TextBox = CreateWindowEx(0, MSFTEDIT_CLASS, TEXT(""),
        WS_VISIBLE | WS_CHILD |
        ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | WS_BORDER/*| ES_READONLY*/,
        20, 10, 360, 50,
        subwindows_AddVIW_hwnd, NULL, GetModuleHandle(NULL), NULL);

    SubWindows_button_AddKeywords = CreateWindowEx(0, L"BUTTON", L"添加关键字",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 100, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDKEYWORDS, NULL/* GetModuleHandle(NULL)*/, NULL);

    SubWindows_button_AddDivisions = CreateWindowEx(0, L"BUTTON", L"添加分界符",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 130, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDDIVISIONS, NULL/* GetModuleHandle(NULL)*/, NULL);

    SubWindows_button_AddArithmetic = CreateWindowEx(0, L"BUTTON", L"添加算术运算符",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP |
        ES_NOHIDESEL /*| ES_READONLY*/,
        20, 160, 360, 30,
        subwindows_AddVIW_hwnd, (HMENU)IDM_BUTTON_ADDARITHMETIC, NULL/* GetModuleHandle(NULL)*/, NULL);

    SubWindows_button_AddRelation = CreateWindowEx(0, L"BUTTON", L"添加关系运算符",
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


//
//  FUNCTION: WndProc_SubWindows(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the sub window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the sub window
//  WM_DESTROY  - post a quit message and return
//
//
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

void ChangeSizetoDefault(HWND hWnd) {
    PWINDOWINFO tmp = (PWINDOWINFO)malloc(sizeof(WINDOWINFO));
    tmp->cbSize = sizeof(WINDOWINFO);   
    LPRECT rect = (LPRECT)malloc(sizeof(tagRECT));
    GetClientRect(hWnd, rect);

    SetWindowPos(main_RichTextBox_VAR, HWND_BOTTOM, 0, 0, rect->right, int(rect->bottom * 0.6), SWP_NOMOVE | SWP_NOZORDER);
    if (GetWindowInfo(hwndList, tmp) == true) {
       
        SetWindowPos(hwndList, HWND_TOP, 0, int(rect->bottom * 0.6) + 1, rect->right, rect->bottom - (int(rect->bottom * 0.6) + 1), SWP_NOZORDER);
    }
    if (GetWindowInfo(VIW_hwndList, tmp) == true) {
        SetWindowPos(VIW_hwndList, HWND_TOP, 0, int(rect->bottom * 0.6) + 1, rect->right, rect->bottom - (int(rect->bottom * 0.6) + 1), SWP_NOZORDER);
    }
   
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
       // RichTextDialog_output_core.RichTextDialog_BindHWND(main_underoutput_RichTextBox_VAR);
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
            //CheckDACore.BindOutputHWND(main_underoutput_RichTextBox_VAR);
            CheckDACore.BindOutputHWND(hwndList);      
            CheckDACore.DoCheck();
            break;

        case IDM_MORE_DA:
            StartDAWindows(hWnd);
            break;
        case IDM_MORE_VIW:
            StartVIWWindows(hWnd);
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
        
        ChangeSizetoDefault(hWnd);
        // SetWindowPos(main_underoutput_RichTextBox_VAR, HWND_TOP, 0, int(rect->bottom * 0.6) + 1, rect->right, rect->bottom - (int(rect->bottom * 0.6) + 1), SWP_NOZORDER);
        
        //UpdateWindow(main_RichTextBox_VAR);
       // UpdateWindow(hwndList);
        //UpdateWindow(hWnd);
       
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
