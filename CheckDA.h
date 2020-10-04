
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

//词法分析状态定义
#define CheckDAclass_STATE_ERROR -1		//错误状态

#define CheckDAclass_STATE_ZERO 0		//0状态
#define CheckDAclass_STATE_ONE 1		//1状态
#define CheckDAclass_STATE_TWO 2		//2状态
#define CheckDAclass_STATE_THREE 3		//3状态
#define CheckDAclass_STATE_FOUR 4		//4状态
#define CheckDAclass_STATE_FIVE 5		//5状态
#define CheckDAclass_STATE_SIX 6		//6状态
#define CheckDAclass_STATE_SEVEN 7		//7状态
#define CheckDAclass_STATE_EIGHT 8		//8状态
#define CheckDAclass_STATE_NINE 9		//9状态
#define CheckDAclass_STATE_TEN 10		//10状态
#define CheckDAclass_STATE_ELEVEN 11	//11状态
#define CheckDAclass_STATE_TWELVE 12	//12状态
#define CheckDAclass_STATE_THIRTEEN 13	//13状态
#define CheckDAclass_STATE_FOURTEEN 14	//14状态
#define CheckDAclass_STATE_FIVTEEN 15	//15状态




typedef int CheckDAclassState;

//词法分析类
class CheckDAclass
{
public:
	CheckDAclass();
	~CheckDAclass() {};
	int DoCheck();																//进行词法分析
	void BindInputHWND(HWND Input_RichTextDialogclass);							//绑定输入富文本框
	void BindOutputHWND(HWND Output_RichTextDialogclass);						//绑定输出富文本框

	void AddKeywords(std::string input);
	void AddDivision(std::string input);
	void AddArithmetic(std::string input);
	void AddRelation(std::string input);

private:
	void output_Binded_OutputRichText();										//分类并输出目前单词状态
	bool isinlist(std::list<std::string> inputlist, std::string inputstring);
	//std::string TCHARToString(TCHAR* STR);
	void mixoutput(TCHAR* wc, TCHAR* attrib, TCHAR* wordtype, TCHAR* position);

	std::list<std::string> KeywordsSet;											//关键字表
	std::list<std::string> DivisionsSet;										//分界符表
	std::list<std::string> ArithmeticSet;										//算数运算符表
	std::list<std::string> RelationSet;											//关系运算符表

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
                              词法分析结果: \n\
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\
单词        二元序列（单词种别，单词属性）        类型                  位置（行，列）\n");*/
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
	std::string CheckDAclass_word;							//要输出的短句

	int col, row;
};

#endif