
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2020											*
* 																											*
*								File Name:			CheckDA.cpp						        				*
*								Author:				wjh776a68												*
*  								Function:			Words Analyse Class, Analyse Input and output.			*
*	 							CreateTime:			2020/10/03												*
* 								LastUpdateTime:		2020/10/03												*
* 																											*
*************************************************************************************************************/

//#include "pch.h"
#include "CheckDA.h"

#define OringinalTheChar Input_Bind_RichTextDialogclass.tmpoutputCHAR[0]
#define TheChar thechar
#define TheCharEqual(value) TheChar == value
#define StateEqual currentState = 
#define TheCharBetween(min,max) TheChar < max && TheChar > min 

CheckDAclass::CheckDAclass() {

	CheckDAclass_word.reserve(MAXLEN);

	currentState = CheckDAclass_STATE_ZERO;

	blackstyle.cbSize = sizeof(CHARFORMAT2);
	blackstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2; // I'm setting only the style information
	blackstyle.crTextColor = RGB(0, 0, 0);
	blackstyle.crBackColor = RGB(255, 255, 255);
	blackstyle.dwEffects = CFE_DISABLED;

	bluestyle.cbSize = sizeof(CHARFORMAT2);
	bluestyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2; // I'm setting only the style information
	bluestyle.crTextColor = RGB(0, 0, 255);
	bluestyle.crBackColor = RGB(255, 255, 255);
	bluestyle.dwEffects = CFE_BOLD;

	greenstyle.cbSize = sizeof(CHARFORMAT2);
	greenstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2; // I'm setting only the style information
	greenstyle.crTextColor = RGB(0, 255, 0);
	greenstyle.crBackColor = RGB(255, 255, 255);
	greenstyle.dwEffects = CFE_BOLD;

	redstyle.cbSize = sizeof(CHARFORMAT2);
	redstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2; // I'm setting only the style information
	redstyle.crTextColor = RGB(255, 0, 0);
	redstyle.crBackColor = RGB(255, 255, 255);
	redstyle.dwEffects = CFE_BOLD;


};



int CheckDAclass::DoCheck()
{
	CheckDAclass_word = "";
	Output_Bind_RichTextDialogclass.RichTextDialog_ClearText();
	
	Output_Bind_RichTextDialogclass.RichTextDialog_SetText(tmpbuffer);

	//Output_Bind_RichTextDialogclass.RichTextDialog_Lock();

	char thechar = OringinalTheChar;
	
	row = 1, col = 1;

	long iterator_pointer = 0;
	long totalLength = Input_Bind_RichTextDialogclass.RichTextDialog_GetLength();
    // TODO: Add your implementation code here.
	for (iterator_pointer = 0; iterator_pointer < totalLength; iterator_pointer++) {
		Input_Bind_RichTextDialogclass.RichTextDialog_GetChar(iterator_pointer);
		thechar = OringinalTheChar;
		do {
			if (TheCharEqual('\n')) {
				row++;
				col = 1;
				CheckDAclass_word = "";
				currentState = CheckDAclass_STATE_ZERO;
				continue;
			}
			else if(TheCharEqual('\r')) {	
				row++;
				col = 1;
				CheckDAclass_word = "";
				currentState = CheckDAclass_STATE_ZERO;
				continue;
			}
			

			switch (currentState) {
			case CheckDAclass_STATE_ZERO:
				if (TheCharEqual(' ')) {
					StateEqual CheckDAclass_STATE_ZERO;
					//col++;
					//lstrcpy(&thechar, TEXT(""));
				}	
				else if (isalpha(TheChar)) {
					StateEqual CheckDAclass_STATE_ONE;
					CheckDAclass_word += thechar;
					col++;
				}			
				else if (isdigit(TheChar))	{
					StateEqual CheckDAclass_STATE_THREE;
					CheckDAclass_word += thechar;
					col++;
				}			
				else if (TheCharEqual('+')) {
					StateEqual CheckDAclass_STATE_FIVE;
					CheckDAclass_word += thechar;
					col++;
				}	
				else if (TheCharEqual('-')) {
					StateEqual CheckDAclass_STATE_SIX;
					CheckDAclass_word += thechar;
					col++;
				}		
				else if (TheCharEqual('*')) {
					StateEqual CheckDAclass_STATE_SEVEN;
					CheckDAclass_word += thechar;
					col++;
				}		
				else if (TheCharEqual('<')) {
					StateEqual CheckDAclass_STATE_EIGHT;
					CheckDAclass_word += thechar;
					col++;
				}	
				else if (TheCharEqual('=')) {
					StateEqual CheckDAclass_STATE_ELEVEN;
					CheckDAclass_word += thechar;
					col++;
				}	
				else if (TheCharEqual(':')) {
					StateEqual CheckDAclass_STATE_FOURTEEN;
					CheckDAclass_word += thechar;
					col++;
				}	
				else {
					StateEqual CheckDAclass_STATE_FIVTEEN;
					CheckDAclass_word += thechar;
					col++;
				}
								
				break;
			case CheckDAclass_STATE_ONE:
				if (isalnum(TheChar)) {
					StateEqual CheckDAclass_STATE_ONE;
					CheckDAclass_word += thechar;
					col++;
				}				
				else {
					StateEqual CheckDAclass_STATE_TWO;
					//lstrcpy(&thechar, TEXT(""));
					iterator_pointer--;
					/*col--;*/
				}			
				break;
			case CheckDAclass_STATE_TWO:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_THREE:
				if (isdigit(TheChar)) {
					StateEqual CheckDAclass_STATE_THREE;
					CheckDAclass_word += thechar;
					col++;
				}				
				else {
					StateEqual CheckDAclass_STATE_FOUR;
					//lstrcpy(&thechar, TEXT(""));
					iterator_pointer--;
					/*col--;*/
				}
				break;
			case CheckDAclass_STATE_FOUR:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_FIVE:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				iterator_pointer--;
				/*col--;*/
				break;
			case CheckDAclass_STATE_SIX:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				iterator_pointer--;
				/*col--;*/
				break;
			case CheckDAclass_STATE_SEVEN:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				iterator_pointer--;
				/*col--;*/
				break;
			case CheckDAclass_STATE_EIGHT:
				if (TheCharEqual('=')) {
					StateEqual CheckDAclass_STATE_NINE;
					CheckDAclass_word += thechar;
					col++;
				}				
				else {
					StateEqual CheckDAclass_STATE_TEN;
					//lstrcpy(&thechar, TEXT(""));
					iterator_pointer--;
					/*col--;*/
				}
				break;
			case CheckDAclass_STATE_NINE:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_TEN:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_ELEVEN:
				if (TheCharEqual('=')) {
					StateEqual CheckDAclass_STATE_TWELVE;
					CheckDAclass_word += thechar;
					col++;
				}			
				else {
					StateEqual CheckDAclass_STATE_THIRTEEN;
					//lstrcpy(&thechar, TEXT(""));
					iterator_pointer--;
					/*col--;*/
				}
					
				break;
			case CheckDAclass_STATE_TWELVE:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_THIRTEEN:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_FOURTEEN:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_FIVTEEN:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				//lstrcpy(&thechar, TEXT(""));
				break;
			default:
				//currentState = CheckDAclass_STATE_ERROR;
				
				row++;
				col = 0;
				CheckDAclass_word = "";
				if (TheCharEqual('\n')) {
					row++;
					col = 0;
					CheckDAclass_word = "";
				}
				
				currentState = CheckDAclass_STATE_ZERO;
				//word += thechar;
				break;
			}
			
			

	
		} while (	currentState == 2  ||
					currentState == 4  ||
					currentState == 10 ||
					currentState == 13 ||
					currentState == 15	 );
	}

	//Output_Bind_RichTextDialogclass.RichTextDialog_UnLock();
    return 0;
}

bool CheckDAclass::isinlist(std::list<std::string> inputlist, std::string inputstring) {
	iter = std::find(inputlist.begin(), inputlist.end(), inputstring);	
	if (iter != inputlist.end()){
		return true;
	}

	return false;
}

//std::string CheckDAclass::TCHARToString(TCHAR* STR) {
//	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
//	char* chRtn = new char[iLen * sizeof(char)];
//	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
//	std::string str(chRtn);
//	return str;
//}

void CheckDAclass::mixoutput(TCHAR* wc,TCHAR* attrib,TCHAR* wordtype,TCHAR* position) {
	int i;
	for ( i = 0; i < MAXLEN; i++) {
		output[i] = '\0';
	}

	lstrcpy(output, wc);
	int keeplength = lstrlen(output);
	for ( i = 0; i < 40-lstrlen(wc); i++) {
		output[keeplength + i] = ' ';
	}
	lstrcat(output, attrib);

	keeplength = lstrlen(output);
	for ( i = 0; i < 38 - lstrlen(attrib); i++) {
		output[keeplength + i] = ' ';
	}
	lstrcat(output, wordtype);

	keeplength = lstrlen(output);
	for ( i = 0; i < 30 - int(lstrlen(wordtype) * 2 / 3 + 1); i++) {
		output[keeplength + i] = ' ';
	}
	lstrcat(output, position);

	//keeplength = lstrlen(output);
	//for ( i = 0; i < 40 - lstrlen(position); i++) {
	//	output[keeplength + i] = ' ';
	//}

	Output_Bind_RichTextDialogclass.RichTextDialog_AppendText(output);
	Output_Bind_RichTextDialogclass.RichTextDialog_AppendText(newline);
}

void CheckDAclass::output_Binded_OutputRichText() {
	int i;

	for ( i = 0; i < sizeof(wc); i++) {
		wc[i] = '\0';
	}
	for (i = 0; i < sizeof(attrib); i++) {
		attrib[i] = '\0';
	}
	for (i = 0; i < sizeof(wordtype); i++) {
		wordtype[i] = '\0';
	}
	for (i = 0; i < sizeof(position); i++) {
		position[i] = '\0';
	}
	for (i = 0; i < sizeof(tcharrow); i++) {
		tcharrow[i] = '\0';
	}
	for (i = 0; i < sizeof(tcharcol); i++) {
		tcharcol[i] = '\0';
	}


	_itot_s(row, tcharrow, 10);
	_itot_s(col- CheckDAclass_word.length(), tcharcol, 10);
	lstrcpy(position, TEXT("("));
	lstrcat(position, tcharrow);
	lstrcat(position, TEXT(","));
	lstrcat(position, tcharcol);
	lstrcat(position, TEXT(")"));
	
	
	strcpy_s(str2,CheckDAclass_word.c_str());

	//_stprintf_s(wc, MAX_PATH, _T("%s"), word.c_str());//%s单字符
	size_t len = strlen(str2);
	size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)str2, int(len), NULL, 0);
	wchar_t* wBuf = new wchar_t[wlen + 1];
	MultiByteToWideChar(CP_ACP, 0, (const char*)str2, int(len), wBuf, int(wlen));
	lstrcpy(wc, wBuf);

	for (size_t i = len; i < 10; i++) {
		wc[i] = '\0';
	}


	if (isalpha(CheckDAclass_word.at(0)) && isinlist(KeywordsSet, CheckDAclass_word)==true) {	//关键字
		
		lstrcpy(attrib, TEXT("(1,"));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("关键字   "));

		
	}
	else if (isalpha(CheckDAclass_word.at(0)) && isinlist(KeywordsSet, CheckDAclass_word) == false) {	//标识符

		lstrcpy(attrib, TEXT("(6,"));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("标识符   "));
	}
	else if (isdigit(CheckDAclass_word.at(0))) {	//常数
		lstrcpy(attrib, TEXT("(5,"));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("常数     "));
	}
	else if (isinlist(RelationSet, CheckDAclass_word)) {	//关系运算符
		lstrcpy(attrib, TEXT("(4,"));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("关系运算符"));
	}
	else if (isinlist(ArithmeticSet, CheckDAclass_word)) {	//算数运算符
		lstrcpy(attrib, TEXT("(3,"));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("算数运算符"));

	}
	else if (isinlist(DivisionsSet, CheckDAclass_word)) {	//分界符
		lstrcpy(attrib, TEXT("(2,"));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("分界符   "));
	}
	else {										//错误
		lstrcpy(attrib, TEXT("Error"));

		lstrcpy(wordtype, TEXT("Error   "));
	}
	
	mixoutput(wc, attrib, wordtype, position);

	CheckDAclass_word = "";

	return;
}

void CheckDAclass::BindInputHWND(HWND Input_RichTextDialogclass)
{
    // TODO: Add your implementation code here.
	HWND tmp = Input_RichTextDialogclass;
	Input_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}


void CheckDAclass::BindOutputHWND(HWND Output_RichTextDialogclass)
{
    // TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	Output_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

void CheckDAclass::AddKeywords(std::string input) {
	KeywordsSet.push_back(input);
}

void CheckDAclass::AddDivision(std::string input) {
	DivisionsSet.push_back(input);
}

void CheckDAclass::AddArithmetic(std::string input) {
	ArithmeticSet.push_back(input);
}

void CheckDAclass::AddRelation(std::string input) {
	RelationSet.push_back(input);
}