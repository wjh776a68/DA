
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

//�궨��
#define OringinalTheChar Input_Bind_RichTextDialogclass.tmpoutputCHAR[0]		//ԭʼ��ȡ�����ַ�
#define TheChar thechar															//׷���ַ����� Ϊ����ǰ��汾����
#define TheCharEqual(value) TheChar == value									//�ж��ַ��Ƿ����
#define StateEqual currentState =												//�ж�״̬�Ƿ�����
#define TheCharBetween(min,max) TheChar < max && TheChar > min					//�ж��ַ��Ƿ���� ֮��


/******************************************************************************
*				��������		CheckDAclass
*				�������ܣ�	��ʼ��CheckDAclass
*				���������	void
*				����������	void
*******************************************************************************/
CheckDAclass::CheckDAclass() {

	CheckDAclass_word.reserve(MAXLEN);								//���������ı��ַ����Ļ��泤��

	currentState = CheckDAclass_STATE_ZERO;							//���ó�ʼ״̬Ϊ0״̬

	//�׵׺���	���ı�����ʽ
	blackstyle.cbSize = sizeof(CHARFORMAT2);						//�ı���ʽ
	blackstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;	//�ı�Ч��
	blackstyle.crTextColor = RGB(0, 0, 0);							//�ı���ɫ
	blackstyle.crBackColor = RGB(255, 255, 255);					//������ɫ
	blackstyle.dwEffects = CFE_DISABLED;							//�ı�Ч��

	//�׵�����	���ı�����ʽ
	bluestyle.cbSize = sizeof(CHARFORMAT2);							//�ı���ʽ
	bluestyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;	//�ı�Ч��
	bluestyle.crTextColor = RGB(0, 0, 255);							//�ı���ɫ
	bluestyle.crBackColor = RGB(255, 255, 255);						//������ɫ
	bluestyle.dwEffects = CFE_BOLD;									//�ı�Ч��

	//�׵�����	���ı�����ʽ
	greenstyle.cbSize = sizeof(CHARFORMAT2);						//�ı���ʽ
	greenstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;	//�ı�Ч��
	greenstyle.crTextColor = RGB(0, 255, 0);						//�ı���ɫ
	greenstyle.crBackColor = RGB(255, 255, 255);					//������ɫ
	greenstyle.dwEffects = CFE_BOLD;								//�ı�Ч��

	//�׵׺���	���ı�����ʽ
	redstyle.cbSize = sizeof(CHARFORMAT2);							//�ı���ʽ
	redstyle.dwMask = CFM_COLOR | CFM_BACKCOLOR | CFM_EFFECTS2;		//�ı�Ч��
	redstyle.crTextColor = RGB(255, 0, 0);							//�ı���ɫ
	redstyle.crBackColor = RGB(255, 255, 255);						//������ɫ
	redstyle.dwEffects = CFE_BOLD;									//�ı�Ч��


};



/******************************************************************************
*				��������		DoCheck
*				�������ܣ�	�԰󶨵������ı�����дʷ�����
*				���������	void
*				����������	0		int		����0
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
				
				if (isalpha(thechar) || isdigit(thechar) || TheCharEqual('.')) {						//�Լ��ӵ� �пո�Ļ����������� ֱ�ӹ���
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
				//else if (TheCharEqual(' ') || !isalpha(TheChar)) {						//�Լ��ӵ� �пո�Ļ����������� ֱ�ӹ���
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
*				��������		isinlist
*				�������ܣ�	��󶨵�����б�����һ�н��
*				���������	inputlist		list<string>	�ַ���list����
*							inputstring		string			�������ַ���
*				����������					bool			�Ƿ����ڸ�list��
															���ڷ���true��
															�����ڷ���false
*******************************************************************************/
bool CheckDAclass::isinlist(std::list<std::string> inputlist, std::string inputstring) {
	iter = std::find(inputlist.begin(), inputlist.end(), inputstring);	
	if (iter != inputlist.end()){
		return true;
	}

	return false;
}

/******************************************************************************
*				��������		TCHARToString
*				�������ܣ�	��TCHAR�����ַ���ת��Ϊstring�����ַ���
*				���������	STR			TCHAR*		Ҫת���ַ���
*				����������	str			string		ת������ַ���
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
*				��������		mixoutput
*				�������ܣ�	��󶨵�����б�����һ�н��
*				���������	wc			TCHAR*		����
*							attrib		TCHAR*		��������
*							wordtype	TCHAR*		�������
*							position	TCHAR*		������������
*				����������	void
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
*				��������		output_Binded_OutputRichText
*				�������ܣ�	��󶨵�����ı������һ���ʷ��������ķ������
*				���������	void
*				����������	void
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

	//_stprintf_s(wc, MAX_PATH, _T("%s"), word.c_str());//%s���ַ�
	size_t len = strlen(str2);
	size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)str2, int(len), NULL, 0);
	wchar_t* wBuf = new wchar_t[wlen + 1];
	MultiByteToWideChar(CP_ACP, 0, (const char*)str2, int(len), wBuf, int(wlen));
	lstrcpy(wc, wBuf);

	for (size_t i = len; i < 10; i++) {
		wc[i] = '\0';
	}


	if (isalpha(CheckDAclass_word.at(0)) && isinlist(KeywordsSet, CheckDAclass_word)==true) {	//�ؼ���
		
		lstrcpy(attrib, TEXT("(1, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("�ؼ���   "));

		
	}
	else if (isalpha(CheckDAclass_word.at(0)) && isinlist(KeywordsSet, CheckDAclass_word) == false) {	//��ʶ��

		lstrcpy(attrib, TEXT("(6, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("��ʶ��   "));
	}
	else if (isAlldigit(CheckDAclass_word)) {	//����
		lstrcpy(attrib, TEXT("(5, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("����     "));
	}
	else if (isinlist(RelationSet, CheckDAclass_word)) {	//��ϵ�����
		lstrcpy(attrib, TEXT("(4, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("��ϵ�����"));
	}
	else if (isinlist(ArithmeticSet, CheckDAclass_word)) {	//���������
		lstrcpy(attrib, TEXT("(3, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("���������"));

	}
	else if (isinlist(DivisionsSet, CheckDAclass_word)) {	//�ֽ��
		lstrcpy(attrib, TEXT("(2, "));
		lstrcat(attrib, wc);
		lstrcat(attrib, TEXT(")"));

		lstrcpy(wordtype, TEXT("�ֽ��   "));
	}
	else {										//����
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
*				��������		BindInputHWND
*				�������ܣ�	�������ı���Ĵ��ھ��
*				���������	Input_RichTextDialogclass HWND Ҫ�󶨵Ĵ��ھ��
*				����������	void
*******************************************************************************/
void CheckDAclass::BindInputHWND(HWND Input_RichTextDialogclass)
{
    // TODO: Add your implementation code here.
	HWND tmp = Input_RichTextDialogclass;
	Input_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

/******************************************************************************
*				��������		BindOutputHWND
*				�������ܣ�	������б��Ĵ��ھ��
*				���������	Output_RichTextDialogclass HWND Ҫ�󶨵Ĵ��ھ��
*				����������	void
*******************************************************************************/
void CheckDAclass::BindOutputHWND(HWND Output_RichTextDialogclass)
{
    // TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	Output_Bind_RichTextDialogclass = tmp;
	//Output_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

/******************************************************************************
*				��������		BindVIWHWND
*				�������ܣ�	��VIW�б��Ĵ��ھ��
*				���������	VIW_RichTextDialogclass HWND Ҫ�󶨵Ĵ��ھ��
*				����������	void
*******************************************************************************/
void CheckDAclass::BindVIWHWND(HWND viwhwnd) {
	HWND tmp = viwhwnd;
	VIW_Bind_RichTextDialogclass = tmp;
}

/******************************************************************************
*				��������		AddKeywords
*				�������ܣ�	��ӹؼ���
*				���������	input string Ҫ��ӵĹؼ���
*				����������	void
*******************************************************************************/
void CheckDAclass::AddKeywords(std::string input) {
	KeywordsSet.push_back(input);
}

/******************************************************************************
*				��������		AddDivision
*				�������ܣ�	��ӷֽ��
*				���������	input string Ҫ��ӵķֽ��
*				����������	void
*******************************************************************************/
void CheckDAclass::AddDivision(std::string input) {
	DivisionsSet.push_back(input);
}

/******************************************************************************
*				��������		AddArithmetic
*				�������ܣ�	������������
*				���������	input string Ҫ��ӵ����������
*				����������	void
*******************************************************************************/
void CheckDAclass::AddArithmetic(std::string input) {
	ArithmeticSet.push_back(input);
}

/******************************************************************************
*				��������		AddRelation
*				�������ܣ�	��ӹ�ϵ�����
*				���������	input string Ҫ��ӵĹ�ϵ�����
*				����������	void
*******************************************************************************/
void CheckDAclass::AddRelation(std::string input) {
	RelationSet.push_back(input);
}

