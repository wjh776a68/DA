
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			FileIOFunctions.cpp				        				*
*								Author:				wjh776a68												*
*  								Function:			File IO Functions set source file.		    			*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/02												*
* 																											*
*************************************************************************************************************/

//#include "pch.h"
#include "FileIOFunctions.h"

#include < io.h> 



//referrence link: https://my.oschina.net/u/4370928/blog/3410688

TCHAR* FileIOFunctionsclass::Reads(){
    // TODO: Add your implementation code here.
    int size = _filelength(_fileno(currentfilestruct));
    TCHAR * buffer = (TCHAR*)malloc(size);
    for (int i = 0; i < size; i++) {
        *(buffer + i) = 0;
    }
    if (size <= 0) {
        MessageBox(NULL,NULL,NULL,NULL);
        return buffer;
    }
    else {
        fread(buffer, size, 1, currentfilestruct);
    }
   

    return buffer;
}


int FileIOFunctionsclass::Saves(TCHAR* filepath, TCHAR* content) {
    lstrcpy(tmpFilePath, filepath);
    if (lstrcmp(tmpFilePath, TEXT(""))) {
        closeFile();

        
       
        _tfopen_s(&currentfilestruct, tmpFilePath, TEXT("w+"));
        fwrite(content, sizeof(TCHAR), lstrlen(content), currentfilestruct);

        fclose(currentfilestruct);
        selectFile(currentFilePath);
    }
    return 0;
}

int FileIOFunctionsclass::Writes(TCHAR* content){
    closeFile();
    _tfopen_s(&currentfilestruct, currentFilePath, TEXT("w+"));
    fwrite(content, sizeof(TCHAR), lstrlen(content),currentfilestruct);
    
    closeFile();

    selectFile(currentFilePath);

    return 0;
}


bool FileIOFunctionsclass::isEndofFile(){
    
    return feof(currentfilestruct);
}


TCHAR FileIOFunctionsclass::Read(){
    TCHAR tmp = { 0 };
    if (!isEndofFile())
        fread(&tmp, sizeof(TCHAR), 1, currentfilestruct);
    return tmp;
}


int FileIOFunctionsclass::GetCurrentLocation(){

    return 0;
}


int FileIOFunctionsclass::SetCurrentLocation(int NewLocation){
    fseek(currentfilestruct, NewLocation, SEEK_SET);
    return 0;
}


int FileIOFunctionsclass::MoveNextLocation(){
    fseek(currentfilestruct, 1, SEEK_CUR);
    return 0;
}


int FileIOFunctionsclass::MovePeriousLocation(){

    fseek(currentfilestruct, -1, SEEK_CUR);
    return 0;
}

void FileIOFunctionsclass::closeFile() {
    if (lstrcmp(currentFilePath, TEXT(""))) {
        fclose(currentfilestruct);
        lstrcpy(currentFilePath, TEXT(""));
    }

}


void FileIOFunctionsclass::selectFile(TCHAR* FilePath) {
    lstrcpy(tmpFilePath, FilePath);
    if (lstrcmp(tmpFilePath, TEXT(""))) {
        lstrcpy(currentFilePath, tmpFilePath);
        _tfopen_s(&currentfilestruct, currentFilePath, TEXT("r+"));
    }
   
}