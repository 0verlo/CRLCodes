/*************************************************************************
	> File Name: numbGuessing.h
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Jan 2017 11:53:54 AM CST
 ************************************************************************/

#ifndef _NUMBGUESSING_H
#define _NUMBGUESSING_H

typedef struct _GAME_INFO{
	int inputNumb;
	int targetNumb;
	int inputNumbMax;
	int inputNumbMin;
	bool reSwitch;
}GAMEINFO;

void numbInit();
void numbInput(int* inputNumber,int inputMax,int inputMin,bool reSwitch);
void numbCompare();
void continueCheckProc();

#endif
