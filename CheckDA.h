
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
#define CheckDAclass_STATE_ERROR -1												//错误状态

#define CheckDAclass_STATE_ZERO 0												//0状态
#define CheckDAclass_STATE_ONE 1												//1状态
#define CheckDAclass_STATE_TWO 2												//2状态
#define CheckDAclass_STATE_THREE 3												//3状态
#define CheckDAclass_STATE_FOUR 4												//4状态
#define CheckDAclass_STATE_FIVE 5												//5状态
#define CheckDAclass_STATE_SIX 6												//6状态
#define CheckDAclass_STATE_SEVEN 7												//7状态
#define CheckDAclass_STATE_EIGHT 8												//8状态
#define CheckDAclass_STATE_NINE 9												//9状态
#define CheckDAclass_STATE_TEN 10												//10状态
#define CheckDAclass_STATE_ELEVEN 11											//11状态
#define CheckDAclass_STATE_TWELVE 12											//12状态
#define CheckDAclass_STATE_THIRTEEN 13											//13状态
#define CheckDAclass_STATE_FOURTEEN 14											//14状态
#define CheckDAclass_STATE_FIVTEEN 15											//15状态

#define CheckDAclass_STATE_CUSTOMED_FIRST 101									//加号后可继续跟加号状态
#define CheckDAclass_STATE_CUSTOMED_SECOND 102									//减号后可继续跟减号状态


typedef int CheckDAclassState;													//定义状态变量结构

//词法分析类
class CheckDAclass
{
public:
	CheckDAclass();																//构造函数
	~CheckDAclass() {};															//析构函数
	int DoCheck();																//进行词法分析
	void BindInputHWND(HWND Input_RichTextDialogclass);							//绑定输入富文本框
	void BindVIWHWND(HWND VIW_RichTextDialogclass);							//绑定输出富文本框
	void BindOutputHWND(HWND Output_RichTextDialogclass);						//绑定输出富文本框

	void AddKeywords(std::string input);										//添加关键词
	void AddDivision(std::string input);										//添加分界符
	void AddArithmetic(std::string input);										//添加算术运算符
	void AddRelation(std::string input);										//添加赋值运算符

	void addVIWtoVIWWindows();													//将特定词汇添加到窗口
private:
	void output_Binded_OutputRichText();										//分类并输出目前单词状态
	bool isinlist(std::list<std::string> inputlist, std::string inputstring);	//判断是否属于集合
	//std::string TCHARToString(TCHAR* STR);
	TCHAR* StringtoTCHAR(std::string input);
	void mixoutput(TCHAR* wc, TCHAR* attrib, TCHAR* wordtype, TCHAR* position);	//输出内容

	std::list<std::string> KeywordsSet;											//关键字表
	std::list<std::string> DivisionsSet;										//分界符表
	std::list<std::string> ArithmeticSet;										//算数运算符表
	std::list<std::string> RelationSet;											//关系运算符表

	//RichTextDialogclass Output_Bind_RichTextDialogclass;
	HWND				Output_Bind_RichTextDialogclass;						//输出列表框句柄
	HWND				VIW_Bind_RichTextDialogclass;							//关键词列表框句柄
	RichTextDialogclass Input_Bind_RichTextDialogclass;							//输入文本框类的引用
	int					nIndex;													//输出列表框单元索引 迭代变量

	CHARFORMAT2 blackstyle;														//黑色外观
	CHARFORMAT2 bluestyle;														//蓝色外观
	CHARFORMAT2 greenstyle;														//绿色外观
	CHARFORMAT2 redstyle;														//红色外观

	/*TCHAR tmpbuffer[4*MAXLEN] = TEXT("\
===============================================================================================================================\n\
                              词法分析结果: \n\
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\
单词        二元序列（单词种别，单词属性）        类型                  位置（行，列）\n");*/
	TCHAR output[MAXLEN] = { 0 };
	TCHAR newline[10] = TEXT("\r\n");											//换行TCHAR*字符串

	TCHAR wc[10] = { 0 };														//单词临时变量
	TCHAR attrib[23] = { 0 };													//单词属性临时变量
	TCHAR wordtype[10] = { 0 };													//单词类型临时变量
	TCHAR position[10] = { 0 };													//单词行列临时变量

	TCHAR tcharrow[3] = { 0 };													//行临时变量
	TCHAR tcharcol[3] = { 0 };													//列临时变量

	std::list<std::string>::iterator iter;										//list列表迭代器

	char str2[MAXLEN];															//转化后字符串临时变量

	CheckDAclassState currentState;												//当前状态
	std::string CheckDAclass_word;												//要输出的短句

	int col, row;																//当前行列
};

#endif