
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			RichTextDialog.cpp				        				*
*								Author:				wjh776a68												*
*  								Function:			RichTextbox functions set source file.					*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/04												*
* 																											*
*************************************************************************************************************/

//#include "pch.h"
#include "RichTextDialog.h"

#define TCHARBUFFER_MAXLEN 4096
TCHAR tchar_buffer[TCHARBUFFER_MAXLEN] = { 0 };

//void RichTextDialogclass::RichTextDialog_Lock() {
//	//GetWindowText(RichTextDialog_bindhWnd, lockCache, TCHARBUFFER_MAXLEN);
//	
//
//}
//
//void RichTextDialogclass::RichTextDialog_UnLock() {
//	//SetWindowText(RichTextDialog_bindhWnd, lockCache);
//}

TCHAR* RichTextDialogclass::RichTextDialog_GetText() {
	GetWindowText(RichTextDialog_bindhWnd, tchar_buffer, TCHARBUFFER_MAXLEN);
	
	return tchar_buffer;
}

void RichTextDialogclass::RichTextDialog_AppendText(TCHAR* content) {
	GetWindowText(RichTextDialog_bindhWnd, tchar_buffer, TCHARBUFFER_MAXLEN);
	lstrcat(tchar_buffer, content);
	//lstrcat(lockCache, content);
	SetWindowText(RichTextDialog_bindhWnd, tchar_buffer);
}

void RichTextDialogclass::RichTextDialog_BindHWND(HWND bindhWnd) {
	RichTextDialog_bindhWnd = bindhWnd;
}

void RichTextDialogclass::RichTextDialog_ClearText() {
	SetWindowText(RichTextDialogclass::RichTextDialog_bindhWnd, blank);
	//lstrcpy(lockCache, TEXT(""));

}

void RichTextDialogclass::RichTextDialog_SetText(TCHAR* content) {
	SetWindowText(RichTextDialog_bindhWnd, content);
	//lstrcpy(lockCache, content);
}

long RichTextDialogclass::RichTextDialog_GetLength() {
	_gettextlengthex CurrentTextLength;
	CurrentTextLength.flags = GTL_DEFAULT;
	CurrentTextLength.codepage = CP_ACP;
	return (long)SendMessage(RichTextDialog_bindhWnd, EM_GETTEXTLENGTHEX, (WPARAM)&CurrentTextLength, 0);
}

CHAR* RichTextDialogclass::RichTextDialog_GetChar(long position) {
	
	_textrange CurrentSelectTextRange_iterator;
	CHARRANGE CurrentSelectTextCharRange_iterator;
	
	CurrentSelectTextRange_iterator.lpstrText = tmpoutputCHAR;
	long currentlength = RichTextDialog_GetLength();
	if(position<currentlength) {
		CurrentSelectTextCharRange_iterator.cpMin = position;
		CurrentSelectTextCharRange_iterator.cpMax = position + 1;
		CurrentSelectTextRange_iterator.chrg = CurrentSelectTextCharRange_iterator;
	
		SendMessage(RichTextDialog_bindhWnd, EM_GETTEXTRANGE, 0, (LPARAM)&CurrentSelectTextRange_iterator);
	}
	else {
		*tmpoutputCHAR = '\0';
	}
	

	
	return tmpoutputCHAR;
}