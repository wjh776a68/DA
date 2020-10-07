
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2020											*
* 																											*
*								File Name:			CheckDA.cpp						        				*
*								Author:				wjh776a68												*
*  								Function:			Words Analyse Class, Analyse Input and output.			*
*	 							CreateTime:			2020/10/03												*
* 								LastUpdateTime:		2020/10/04												*
* 																											*
*************************************************************************************************************/

//#include "pch.h"
#include "CheckDA.h"

//宏定义
#define OringinalTheChar Input_Bind_RichTextDialogclass.tmpoutputCHAR[0]		//原始读取到的字符
#define TheChar thechar															//追加字符内容 为保持前后版本兼容
#define TheCharEqual(value) TheChar == value									//判断字符是否相等
#define StateEqual currentState =												//判断状态是否满足
#define TheCharBetween(min,max) TheChar < max && TheChar > min					//判断字符是否介于 之间


/******************************************************************************
*				函数名：		CheckDAclass
*				函数功能：	初始化CheckDAclass
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
CheckDAclass::CheckDAclass() {

	CheckDAclass_word.reserve(MAXLEN);								//设置输入文本字符串的缓存长度

	currentState = CheckDAclass_STATE_ZERO;							//设置初始状态为0状态

	//白底黑字	富文本框样式
	blackstyle.cbSize = sizeof(CHARFORMAT2);						//文本格式
	blackstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;	//文本效果
	blackstyle.crTextColor = RGB(0, 0, 0);							//文本颜色
	blackstyle.crBackColor = RGB(255, 255, 255);					//背景颜色
	blackstyle.dwEffects = CFE_DISABLED;							//文本效果

	//白底蓝字	富文本框样式
	bluestyle.cbSize = sizeof(CHARFORMAT2);							//文本格式
	bluestyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;	//文本效果
	bluestyle.crTextColor = RGB(0, 0, 255);							//文本颜色
	bluestyle.crBackColor = RGB(255, 255, 255);						//背景颜色
	bluestyle.dwEffects = CFE_BOLD;									//文本效果

	//白底绿字	富文本框样式
	greenstyle.cbSize = sizeof(CHARFORMAT2);						//文本格式
	greenstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;	//文本效果
	greenstyle.crTextColor = RGB(0, 255, 0);						//文本颜色
	greenstyle.crBackColor = RGB(255, 255, 255);					//背景颜色
	greenstyle.dwEffects = CFE_BOLD;								//文本效果

	//白底红字	富文本框样式
	redstyle.cbSize = sizeof(CHARFORMAT2);							//文本格式
	redstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;		//文本效果
	redstyle.crTextColor = RGB(255, 0, 0);							//文本颜色
	redstyle.crBackColor = RGB(255, 255, 255);						//背景颜色
	redstyle.dwEffects = CFE_BOLD;									//文本效果


};



/******************************************************************************
*				函数名：		DoCheck
*				函数功能：	对绑定的输入文本框进行词法分析
*				传入参数：	void
*				传出参数：	0		int		返回0
*******************************************************************************/
int CheckDAclass::DoCheck()
{
	CheckDAclass_word = "";

	SendMessage(Output_Bind_RichTextDialogclass, LVM_DELETEALLITEMS, 0, 0);

	nIndex = 0;
	//Output_Bind_RichTextDialogclass.RichTextDialog_ClearText();
	
	//Output_Bind_RichTextDialogclass.RichTextDialog_SetText(tmpbuffer);

	//Output_Bind_RichTextDialogclass.RichTextDialog_Lock();

	char thechar = OringinalTheChar;
	
	row = 1, col = 1;
	//bool isnowtoflush = false;
	long iterator_pointer = 0;
	long totalLength = Input_Bind_RichTextDialogclass.RichTextDialog_GetLength();
    // TODO: Add your implementation code here.
	for (iterator_pointer = 0; iterator_pointer < totalLength + 2; iterator_pointer++) {
		if (iterator_pointer == totalLength) {
			thechar = '\r';
		}
		else if (iterator_pointer == totalLength + 1) {
			thechar = '\n';
		}
		else {
			Input_Bind_RichTextDialogclass.RichTextDialog_GetChar(iterator_pointer);
			thechar = OringinalTheChar;
		}

		do {
			if (TheCharEqual('\n')) {
				row++;
				col = 1;
				//isnowtoflush = true;
				continue;
			}
			else if(TheCharEqual('\r')) {	
				row++;
				col = 1;
				//isnowtoflush = true;
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
				else if (TheCharEqual('+') || TheCharEqual('-') || TheCharEqual('*') || TheCharEqual('<') || TheCharEqual('=') || TheCharEqual(':') || TheCharEqual('>') || TheCharEqual('/')) {
					StateEqual CheckDAclass_STATE_FIVE;
					CheckDAclass_word += thechar;
					col++;
				}
				/*else if (TheCharEqual('+')) {
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
				}	*/
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
				
				if (isalpha(thechar) || isdigit(thechar) || TheCharEqual('.')) {						//自己加的 有空格的话不当非数字 直接过滤
					StateEqual CheckDAclass_STATE_THREE;
					CheckDAclass_word += thechar;
					col++;
				}
				else {				
					
					StateEqual CheckDAclass_STATE_FOUR;
					iterator_pointer--;
				}
				
				//if (isdigit(TheChar) || TheCharEqual('.')) {
				//	StateEqual CheckDAclass_STATE_THREE;
				//	CheckDAclass_word += thechar;
				//	col++;
				//}
				//else if (TheCharEqual(' ') || !isalpha(TheChar)) {						//自己加的 有空格的话不当非数字 直接过滤
				//	StateEqual CheckDAclass_STATE_FOUR;
				//	iterator_pointer--;
				//}
				//else {
				//	StateEqual CheckDAclass_STATE_FOUR;
				//	//lstrcpy(&thechar, TEXT(""));
				//	CheckDAclass_word += thechar;
				//	col++;
				//	//iterator_pointer--;
				//	/*col--;*/
				//}
				break;
			case CheckDAclass_STATE_FOUR:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_FIVE:
				if (TheCharEqual('+') || TheCharEqual('-') || TheCharEqual('*') || TheCharEqual('<') || TheCharEqual('=') || TheCharEqual(':') || TheCharEqual('>') || TheCharEqual('/')) {
					StateEqual CheckDAclass_STATE_FIVE;
					CheckDAclass_word += thechar;
					col++;
				}
				else {
					StateEqual CheckDAclass_STATE_CUSTOMED_FIRST;
					iterator_pointer--;
				}
				break;
						//output_Binded_OutputRichText();
						//StateEqual CheckDAclass_STATE_ZERO;
						//iterator_pointer--;
						///*col--;*/
						//break;
			case CheckDAclass_STATE_CUSTOMED_FIRST:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				break;
			case CheckDAclass_STATE_SIX:
				if (TheCharEqual('-') || TheCharEqual('=')) {
					StateEqual CheckDAclass_STATE_CUSTOMED_SECOND;
					CheckDAclass_word += thechar;
					col++;
				}
				else {
					StateEqual CheckDAclass_STATE_CUSTOMED_SECOND;
					iterator_pointer--;
				}
				break;
				/*output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
				iterator_pointer--;
				break;*/
				/*col--;*/
			case CheckDAclass_STATE_CUSTOMED_SECOND:
				output_Binded_OutputRichText();
				StateEqual CheckDAclass_STATE_ZERO;
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
					CheckDAclass_word += thechar;+
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
				iterator_pointer--;
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
					currentState == 13 || currentState == CheckDAclass_STATE_CUSTOMED_FIRST ||
					currentState == 15	 );
	}

	//Output_Bind_RichTextDialogclass.RichTextDialog_UnLock();
    return 0;
}

/******************************************************************************
*				函数名：		isinlist
*				函数功能：	向绑定的输出列表框输出一行结果
*				传入参数：	inputlist		list<string>	字符串list集合
*							inputstring		string			待查找字符串
*				传出参数：					bool			是否属于该list，
															存在返回true，
															不存在返回false
*******************************************************************************/
bool CheckDAclass::isinlist(std::list<std::string> inputlist, std::string inputstring) {
	iter = std::find(inputlist.begin(), inputlist.end(), inputstring);	
	if (iter != inputlist.end()){
		return true;
	}

	return false;
}

/******************************************************************************
*				函数名：		TCHARToString
*				函数功能：	将TCHAR类型字符串转化为string类型字符串
*				传入参数：	STR			TCHAR*		要转化字符串
*				传出参数：	str			string		转化后的字符串
*******************************************************************************/
//std::string CheckDAclass::TCHARToString(TCHAR* STR) {
//	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
//	char* chRtn = new char[iLen * sizeof(char)];
//	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
//	std::string str(chRtn);
//	return str;
//}
#include <atlstr.h>
TCHAR* CheckDAclass::StringtoTCHAR(std::string input) {
	_tcscpy_s(wc, CA2T(input.c_str()));
	return wc;
}
/******************************************************************************
*				函数名：		mixoutput
*				函数功能：	向绑定的输出列表框输出一行结果
*				传入参数：	wc			TCHAR*		单词
*							attrib		TCHAR*		单词属性
*							wordtype	TCHAR*		单词类别
*							position	TCHAR*		单词所在行列
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::mixoutput(TCHAR* wc,TCHAR* attrib,TCHAR* wordtype,TCHAR* position) {

	LV_ITEM lv;
	lv.mask = LVIF_TEXT;
	lv.iSubItem = 0;
	lv.iItem = nIndex++;
	lv.iImage = 0;
	lv.pszText = wc;
	ListView_InsertItem(Output_Bind_RichTextDialogclass, &lv);
	lv.iSubItem = 1;
	lv.pszText = attrib;
	ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);
	lv.iSubItem = 2;
	lv.pszText = wordtype;
	ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);
	lv.iSubItem = 3;
	lv.pszText = position;
	ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);





	//int i;
	//for ( i = 0; i < MAXLEN; i++) {
	//	output[i] = '\0';
	//}

	//lstrcpy(output, wc);
	//int keeplength = lstrlen(output);
	//for ( i = 0; i < 40-lstrlen(wc); i++) {
	//	output[keeplength + i] = ' ';
	//}
	//lstrcat(output, attrib);

	//keeplength = lstrlen(output);
	//for ( i = 0; i < 38 - lstrlen(attrib); i++) {
	//	output[keeplength + i] = ' ';
	//}
	//lstrcat(output, wordtype);

	//keeplength = lstrlen(output);
	//for ( i = 0; i < 30 - int(lstrlen(wordtype) * 2 / 3 + 1); i++) {
	//	output[keeplength + i] = ' ';
	//}
	//lstrcat(output, position);

	////keeplength = lstrlen(output);
	////for ( i = 0; i < 40 - lstrlen(position); i++) {
	////	output[keeplength + i] = ' ';
	////}

	//Output_Bind_RichTextDialogclass.RichTextDialog_AppendText(output);
	//Output_Bind_RichTextDialogclass.RichTextDialog_AppendText(newline);
}

bool isAlldigit(std::string input) {
	//bool result = true;
	int sum = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input.at(i) == '.') {
			sum++;
			continue;
		}
		else if (isdigit(input.at(i))==false) {
			//result = false;
			//break;
			return false;
		}
	}

	if (sum < 2) {
		return true;
	}
	else {
		return false;
	}
}


/******************************************************************************
*				函数名：		output_Binded_OutputRichText
*				函数功能：	向绑定的输出文本框输出一条词法分析器的分析结果
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
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
	lstrcat(position, TEXT(", "));
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
		
		lstrcpy(attrib, TEXT("(1, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("关键字   "));

		
	}
	else if (isalpha(CheckDAclass_word.at(0)) && isinlist(KeywordsSet, CheckDAclass_word) == false) {	//标识符

		lstrcpy(attrib, TEXT("(6, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("标识符   "));
	}
	else if (isAlldigit(CheckDAclass_word)) {	//常数
		lstrcpy(attrib, TEXT("(5, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("常数     "));
	}
	else if (isinlist(RelationSet, CheckDAclass_word)) {	//关系运算符
		lstrcpy(attrib, TEXT("(4, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("关系运算符"));
	}
	else if (isinlist(ArithmeticSet, CheckDAclass_word)) {	//算数运算符
		lstrcpy(attrib, TEXT("(3, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("算数运算符"));

	}
	else if (isinlist(DivisionsSet, CheckDAclass_word)) {	//分界符
		lstrcpy(attrib, TEXT("(2, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("分界符   "));
	}
	else {										//错误
		lstrcpy(attrib,   TEXT("Error   "));

		lstrcpy(wordtype, TEXT("Error   "));
	}
	
	mixoutput(wc, attrib, wordtype, position);

	CheckDAclass_word = "";

	return;
}

void CheckDAclass::addVIWtoVIWWindows() {
	std::list<std::string>::iterator i;
	LV_ITEM lv;
	lv.mask = LVIF_TEXT;
	lv.iImage = 0;

	lv.iSubItem = 0;
	nIndex = 0;
	for (i = KeywordsSet.begin(); i != KeywordsSet.end(); i++) {
		lv.iItem = nIndex++;
		lv.pszText = StringtoTCHAR(i->c_str());

		ListView_InsertItem(VIW_Bind_RichTextDialogclass, &lv);
	}

	lv.iSubItem = 1;
	nIndex = 0;
	for (i = DivisionsSet.begin(); i != DivisionsSet.end(); i++) {
		lv.iItem = nIndex++;
		lv.pszText = StringtoTCHAR(i->c_str());

		ListView_SetItem(VIW_Bind_RichTextDialogclass, &lv);
	}

	lv.iSubItem = 2;
	nIndex = 0;
	for (i = ArithmeticSet.begin(); i != ArithmeticSet.end(); i++) {
		lv.iItem = nIndex++;
		lv.pszText = StringtoTCHAR(i->c_str());

		ListView_SetItem(VIW_Bind_RichTextDialogclass, &lv);
	}

	lv.iSubItem = 3;
	nIndex = 0;
	for (i = RelationSet.begin(); i != RelationSet.end(); i++) {
		lv.iItem = nIndex++;
		lv.pszText = StringtoTCHAR(i->c_str());

		ListView_SetItem(VIW_Bind_RichTextDialogclass, &lv);
	}


}

/******************************************************************************
*				函数名：		BindInputHWND
*				函数功能：	绑定输入文本框的窗口句柄
*				传入参数：	Input_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::BindInputHWND(HWND Input_RichTextDialogclass)
{
    // TODO: Add your implementation code here.
	HWND tmp = Input_RichTextDialogclass;
	Input_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

/******************************************************************************
*				函数名：		BindOutputHWND
*				函数功能：	绑定输出列表框的窗口句柄
*				传入参数：	Output_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::BindOutputHWND(HWND Output_RichTextDialogclass)
{
    // TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	Output_Bind_RichTextDialogclass = tmp;
	//Output_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

/******************************************************************************
*				函数名：		BindVIWHWND
*				函数功能：	绑定VIW列表框的窗口句柄
*				传入参数：	VIW_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::BindVIWHWND(HWND viwhwnd) {
	HWND tmp = viwhwnd;
	VIW_Bind_RichTextDialogclass = tmp;
}

/******************************************************************************
*				函数名：		AddKeywords
*				函数功能：	添加关键词
*				传入参数：	input string 要添加的关键词
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::AddKeywords(std::string input) {
	KeywordsSet.push_back(input);
}

/******************************************************************************
*				函数名：		AddDivision
*				函数功能：	添加分界符
*				传入参数：	input string 要添加的分界符
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::AddDivision(std::string input) {
	DivisionsSet.push_back(input);
}

/******************************************************************************
*				函数名：		AddArithmetic
*				函数功能：	添加算术运算符
*				传入参数：	input string 要添加的算术运算符
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::AddArithmetic(std::string input) {
	ArithmeticSet.push_back(input);
}

/******************************************************************************
*				函数名：		AddRelation
*				函数功能：	添加关系运算符
*				传入参数：	input string 要添加的关系运算符
*				传出参数：	void
*******************************************************************************/
void CheckDAclass::AddRelation(std::string input) {
	RelationSet.push_back(input);
}

