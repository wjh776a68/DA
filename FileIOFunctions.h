
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			FileIOFunctions.h				        				*
*								Author:				wjh776a68												*
*  								Function:			File IO Functions set header file.		    			*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/02												*
* 																											*
*************************************************************************************************************/

#pragma once

#include<fstream>
#include<ios>
#include "DAcommon.h"

#ifndef FILEIOFUNCTIONS_CLASS
#define FILEIOFUNCTIONS_CLASS

class FileIOFunctionsclass
{
public:
	FileIOFunctionsclass() {};
	void selectFile(TCHAR* FilePath);
	TCHAR* Reads();
	int Saves(TCHAR* filepath, TCHAR* content);
	int Writes(TCHAR* content);
	bool isEndofFile();
	TCHAR Read();
	int GetCurrentLocation();
	int SetCurrentLocation(int NewLocation);
	int MoveNextLocation();
	int MovePeriousLocation();
	void closeFile();
private:
	std::FILE* currentfilestruct;
	TCHAR currentFilePath[PATHMAXLEN + SUFFIXMAXLEN];
	TCHAR tmpFilePath[SUFFIXMAXLEN + PATHMAXLEN];
};

#endif