#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
//#include <conio.h>
#include "module/linkStack.h"
#include "numbGuessing.h"

bool continueCheck = 1;
int targetNumb = 0;
int inputNumb = -1;

void rangeInput(GAMEINFO *pstGameInfo){
    bool loopendChecker = 1;
    while(loopendChecker){         
        printf("Please enter the range of num you want to guess:");
        pstGameInfo->inputNumbMax = getNumbInput();
        if(0 < pstGameInfo->inputNumbMax)
            break;        
        printf("\n");
        printf("Input error,please try again.\n");
    }
}

void guessInput(GAMEINFO *pstGameInfo){
    bool loopendChecker = 1;
    while(loopendChecker){         
        printf("Please enter the numb you like:");
        pstGameInfo->inputNumb= getNumbInput();
        printf("\n");        
        if(pstGameInfo->inputNumb == pstGameInfo->targetNumb){            
            printf("BINGO!\n");
            break;     
        } else if(pstGameInfo->inputNumb > pstGameInfo->targetNumb) {
            printf("hmm,perhaps smaller.\n");
        } else if(pstGameInfo->inputNumb < pstGameInfo->targetNumb) {
            printf("hmm,perhaps larger.\n");
        }
    }
}


void numbInit(GAMEINFO *pstGameInfo)
{	
    DEBUG("\n------module numbInit------\n");

    srand((unsigned)time(NULL));
    pstGameInfo->targetNumb = rand() % (pstGameInfo->inputNumbMax - pstGameInfo->inputNumbMin + 1) + pstGameInfo->inputNumbMin;
    //http://www.cnblogs.com/xianghang123/archive/2011/08/24/2152404.html
    //random numb generator

    DEBUG("!!debug!! : finalNum = %d\n",pstGameInfo->targetNumb);
    DEBUG("!!debug!! : finalNum = %d\n",pstGameInfo->inputNumb);
}

int getNumbInput()
{
    //proc saves numbers enter by customers
    LINKSTACK* inputNumbStore;
    char chInput = 0;
    int resultNumb = 0;
    
    MODULE_linkStack_getCharInput(&inputNumbStore);    
    //DEBUG("--------------!!debug!!--------------\n");
    MODULE_linkStack_convertLinkStack2Int(&inputNumbStore, &resultNumb);
    DEBUG("!!debug!! : InputNumb = %d\n",resultNumb);
    MODULE_linkStack_Delete(&inputNumbStore);
    return resultNumb;
}

void continueCheckProc()
{
    DEBUG("\n------module continueCheckPro------\n");
    continueCheck = 0;
}

int main()
{
    DEBUG("Hello world!\n");
	GAMEINFO stGameInfo;
    memset(&stGameInfo, 0, sizeof(GAMEINFO));
    while(continueCheck)
    {
		memset(&stGameInfo,0,sizeof(stGameInfo));        
        rangeInput(&stGameInfo);
        numbInit(&stGameInfo);        
        guessInput(&stGameInfo);
        //continueCheckProc();
    }
    return 0;
}
