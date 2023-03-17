//
// Created by ely6899 on 3/15/23.
//
#include <stdlib.h>

#include "AdptArray.h"

struct AdptArray_{
    PElement *elementArr;
    int arrSize;

    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray adptArray = (PAdptArray) malloc(sizeof (struct AdptArray_));
    if(adptArray == NULL) //If memory allocation failed
        return NULL;

    adptArray->elementArr = NULL;
    adptArray->arrSize = 0;

    adptArray->delFunc = delFunc;
    adptArray->copyFunc = copyFunc;
    adptArray->printFunc = printFunc;

    return adptArray;
}

void DeleteAdptArray(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
        return;

    for(int i = 0; i < pAdptArray->arrSize; i++) {
        pAdptArray->delFunc(pAdptArray->elementArr[i]);
        pAdptArray->elementArr[i] = NULL;
    }

    pAdptArray ->arrSize = 0;

    //Free arr and struct
    free(pAdptArray->elementArr);
    free(pAdptArray);
}

Result SetAdptArrayAt(PAdptArray pAdptArray, int index, PElement pElement){
    if(pAdptArray == NULL || pElement == NULL || index < 0)
        return FAIL;

    if(index >= pAdptArray->arrSize){
        pAdptArray->elementArr = (PElement)realloc(pAdptArray->elementArr, (index + 1) * sizeof(PElement));
    }
    else{ //index < pAdptArray->arrSize
        PElement originalElement = pAdptArray->elementArr[index];
        if(originalElement != NULL){
            pAdptArray->delFunc(originalElement);
        }
    }

    pAdptArray->elementArr[index] = pAdptArray->copyFunc(pElement);
    pAdptArray->arrSize = (index >= pAdptArray->arrSize) ? index + 1 : pAdptArray->arrSize;

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int index){
    if(pAdptArray == NULL || index < 0 || index >= pAdptArray->arrSize)
        return NULL;

    return pAdptArray->elementArr[index];
}

int GetAdptArraySize(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
        return -1;

    return pAdptArray->arrSize;
}

void PrintDB(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
        return;

    for(int i = 0; i < pAdptArray->arrSize; i++){
        if(pAdptArray->elementArr[i] != NULL)
            pAdptArray->printFunc(pAdptArray->elementArr[i]);
    }
}