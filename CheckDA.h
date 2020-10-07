
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
#define CheckDAclass_STATE_ERROR -1												//����״̬

#define CheckDAclass_STATE_ZERO 0												//0״̬
#define CheckDAclass_STATE_ONE 1												//1״̬
#define CheckDAclass_STATE_TWO 2												//2״̬
#define CheckDAclass_STATE_THREE 3												//3״̬
#define CheckDAclass_STATE_FOUR 4												//4״̬
#define CheckDAclass_STATE_FIVE 5												//5״̬
#define CheckDAclass_STATE_SIX 6												//6״̬
#define CheckDAclass_STATE_SEVEN 7												//7״̬
#define CheckDAclass_STATE_EIGHT 8												//8״̬
#define CheckDAclass_STATE_NINE 9												//9״̬
#define CheckDAclass_STATE_TEN 10												//10״̬
#define CheckDAclass_STATE_ELEVEN 11											//11״̬
#define CheckDAclass_STATE_TWELVE 12											//12״̬
#define CheckDAclass_STATE_THIRTEEN 13											//13״̬
#define CheckDAclass_STATE_FOURTEEN 14											//14״̬
#define CheckDAclass_STATE_FIVTEEN 15											//15״̬

#define CheckDAclass_STATE_CUSTOMED_FIRST 101									//�Ӻź�ɼ������Ӻ�״̬
#define CheckDAclass_STATE_CUSTOMED_SECOND 102									//���ź�ɼ���������״̬


typedef int CheckDAclassState;													//����״̬�����ṹ

//�ʷ�������
class CheckDAclass
{
public:
	CheckDAclass();																//���캯��
	~CheckDAclass() {};															//��������
	int DoCheck();																//���дʷ�����
	void BindInputHWND(HWND Input_RichTextDialogclass);							//�����븻�ı���
	void BindVIWHWND(HWND VIW_RichTextDialogclass);							//��������ı���
	void BindOutputHWND(HWND Output_RichTextDialogclass);						//��������ı���

	void AddKeywords(std::string input);										//��ӹؼ���
	void AddDivision(std::string input);										//��ӷֽ��
	void AddArithmetic(std::string input);										//������������
	void AddRelation(std::string input);										//��Ӹ�ֵ�����

	void addVIWtoVIWWindows();													//���ض��ʻ���ӵ�����
private:
	void output_Binded_OutputRichText();										//���ಢ���Ŀǰ����״̬
	bool isinlist(std::list<std::string> inputlist, std::string inputstring);	//�ж��Ƿ����ڼ���
	//std::string TCHARToString(TCHAR* STR);
	TCHAR* StringtoTCHAR(std::string input);
	void mixoutput(TCHAR* wc, TCHAR* attrib, TCHAR* wordtype, TCHAR* position);	//�������

	std::list<std::string> KeywordsSet;											//�ؼ��ֱ�
	std::list<std::string> DivisionsSet;										//�ֽ����
	std::list<std::string> ArithmeticSet;										//�����������
	std::list<std::string> RelationSet;											//��ϵ�������

	//RichTextDialogclass Output_Bind_RichTextDialogclass;
	HWND				Output_Bind_RichTextDialogclass;						//����б����
	HWND				VIW_Bind_RichTextDialogclass;							//�ؼ����б����
	RichTextDialogclass Input_Bind_RichTextDialogclass;							//�����ı����������
	int					nIndex;													//����б��Ԫ���� ��������

	CHARFORMAT2 blackstyle;														//��ɫ���
	CHARFORMAT2 bluestyle;														//��ɫ���
	CHARFORMAT2 greenstyle;														//��ɫ���
	CHARFORMAT2 redstyle;														//��ɫ���

	/*TCHAR tmpbuffer[4*MAXLEN] = TEXT("\
===============================================================================================================================\n\
                              �ʷ��������: \n\
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\
����        ��Ԫ���У������ֱ𣬵������ԣ�        ����                  λ�ã��У��У�\n");*/
	TCHAR output[MAXLEN] = { 0 };
	TCHAR newline[10] = TEXT("\r\n");											//����TCHAR*�ַ���

	TCHAR wc[10] = { 0 };														//������ʱ����
	TCHAR attrib[23] = { 0 };													//����������ʱ����
	TCHAR wordtype[10] = { 0 };													//����������ʱ����
	TCHAR position[10] = { 0 };													//����������ʱ����

	TCHAR tcharrow[3] = { 0 };													//����ʱ����
	TCHAR tcharcol[3] = { 0 };													//����ʱ����

	std::list<std::string>::iterator iter;										//list�б������

	char str2[MAXLEN];															//ת�����ַ�����ʱ����

	CheckDAclassState currentState;												//��ǰ״̬
	std::string CheckDAclass_word;												//Ҫ����Ķ̾�

	int col, row;																//��ǰ����
};

#endif