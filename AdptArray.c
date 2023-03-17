//
// Created by ely6899 on 3/15/23.
//
#include <stdlib.h>
#include <string.h>

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

    //Empty array initialization
    adptArray->elementArr = NULL;
    adptArray->arrSize = 0;
    /*if(adptArray->elementArr == NULL)
        return NULL;*/

    //Initialize functions
    adptArray->delFunc = delFunc;
    adptArray->copyFunc = copyFunc;
    adptArray->printFunc = printFunc;

    return adptArray;
}

void DeleteAdptArray(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
        return;

    for(int i = 0; i < pAdptArray->arrSize; i++) { //Delete each non-null element in the array
        if(pAdptArray->elementArr[i] != NULL){
            pAdptArray->delFunc(pAdptArray->elementArr[i]);
            pAdptArray->elementArr[i] = NULL;
        }
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
        PElement *newArr = (PElement) calloc(index + 1, sizeof(PElement));
        if(newArr == NULL) //If the new array fails to allocate memory
            return FAIL;

        //Copy smaller array data into bigger array, then replace arrays.
        memcpy(newArr, pAdptArray->elementArr, pAdptArray->arrSize * sizeof(PElement));
        free(pAdptArray->elementArr);
        pAdptArray->elementArr = newArr;

        /*pAdptArray->elementArr = (PElement)realloc(pAdptArray->elementArr, (index + 1) * sizeof(PElement));
        if(pAdptArray->elementArr == NULL)
            return FAIL;*/
    }
    else{ //index < pAdptArray->arrSize
        PElement originalElement = pAdptArray->elementArr[index]; //Initialized for better readability.
        if(originalElement != NULL){
            pAdptArray->delFunc(originalElement);
        }
    }

    pAdptArray->elementArr[index] = pAdptArray->copyFunc(pElement); //Put in array desired element copy.
    pAdptArray->arrSize = (index >= pAdptArray->arrSize) ? index + 1 : pAdptArray->arrSize; //Change array size accordingly.

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int index){
    if(pAdptArray == NULL || index < 0 || index >= pAdptArray->arrSize || pAdptArray->elementArr[index] == NULL)
        return NULL;

    return pAdptArray->copyFunc(pAdptArray->elementArr[index]); //Return desired element copy.
}

int GetAdptArraySize(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
        return -1;

    return pAdptArray->arrSize;
}

void PrintDB(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
        return;

    for(int i = 0; i < pAdptArray->arrSize; i++){ //Print each non-null element in the array.
        if(pAdptArray->elementArr[i] != NULL)
            pAdptArray->printFunc(pAdptArray->elementArr[i]);
    }
}