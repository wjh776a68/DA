
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2020											*
* 																											*
*								File Name:			CheckDA.h						        				*
*								Author:				wjh776a68												*
*  								Function:			Words Analyse Class, Analyse Input and output.			*
*	 							CreateTime:			2020/10/03												*
* 								LastUpdateTime:		2020/10/04												*
* 																											*
*************************************************************************************************************/

#pragma once
#ifndef CHECKDA_H_
#define CHECKDA_H_

#include "RichTextDialog.h"
#include <list>

//�ʷ�����״̬����
#define CheckDAclass_STATE_ERROR -1		//����״̬

#define CheckDAclass_STATE_ZERO 0		//0״̬
#define CheckDAclass_STATE_ONE 1		//1״̬
#define CheckDAclass_STATE_TWO 2		//2״̬
#define CheckDAclass_STATE_THREE 3		//3״̬
#define CheckDAclass_STATE_FOUR 4		//4״̬
#define CheckDAclass_STATE_FIVE 5		//5״̬
#define CheckDAclass_STATE_SIX 6		//6״̬
#define CheckDAclass_STATE_SEVEN 7		//7״̬
#define CheckDAclass_STATE_EIGHT 8		//8״̬
#define CheckDAclass_STATE_NINE 9		//9״̬
#define CheckDAclass_STATE_TEN 10		//10״̬
#define CheckDAclass_STATE_ELEVEN 11	//11״̬
#define CheckDAclass_STATE_TWELVE 12	//12״̬
#define CheckDAclass_STATE_THIRTEEN 13	//13״̬
#define CheckDAclass_STATE_FOURTEEN 14	//14״̬
#define CheckDAclass_STATE_FIVTEEN 15	//15״̬




typedef int CheckDAclassState;

//�ʷ�������
class CheckDAclass
{
public:
	CheckDAclass();
	~CheckDAclass() {};
	int DoCheck();																//���дʷ�����
	void BindInputHWND(HWND Input_RichTextDialogclass);							//�����븻�ı���
	void BindOutputHWND(HWND Output_RichTextDialogclass);						//��������ı���

	void AddKeywords(std::string input);
	void AddDivision(std::string input);
	void AddArithmetic(std::string input);
	void AddRelation(std::string input);

private:
	void output_Binded_OutputRichText();										//���ಢ���Ŀǰ����״̬
	bool isinlist(std::list<std::string> inputlist, std::string inputstring);
	//std::string TCHARToString(TCHAR* STR);
	void mixoutput(TCHAR* wc, TCHAR* attrib, TCHAR* wordtype, TCHAR* position);

	std::list<std::string> KeywordsSet;											//�ؼ��ֱ�
	std::list<std::string> DivisionsSet;										//�ֽ����
	std::list<std::string> ArithmeticSet;										//�����������
	std::list<std::string> RelationSet;											//��ϵ�������

	//RichTextDialogclass Output_Bind_RichTextDialogclass;
	HWND				Output_Bind_RichTextDialogclass;
	RichTextDialogclass Input_Bind_RichTextDialogclass;
	int					nIndex;

	CHARFORMAT2 blackstyle;
	CHARFORMAT2 bluestyle;
	CHARFORMAT2 greenstyle;
	CHARFORMAT2 redstyle;

	/*TCHAR tmpbuffer[4*MAXLEN] = TEXT("\
===============================================================================================================================\n\
                              �ʷ��������: \n\
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\
����        ��Ԫ���У������ֱ𣬵������ԣ�        ����                  λ�ã��У��У�\n");*/
	TCHAR output[MAXLEN] = { 0 };
	TCHAR newline[10] = TEXT("\r\n");

	TCHAR wc[10] = { 0 };
	TCHAR attrib[23] = { 0 };
	TCHAR wordtype[10] = { 0 };
	TCHAR position[10] = { 0 };

	TCHAR tcharrow[3] = { 0 };
	TCHAR tcharcol[3] = { 0 };

	std::list<std::string>::iterator iter;

	char str2[MAXLEN];

	CheckDAclassState currentState;
	std::string CheckDAclass_word;							//Ҫ����Ķ̾�

	int col, row;
};

#endif