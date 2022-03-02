#ifndef CDFUNCTIONS_H_INCLUDED
#define CDFUNCTIONS_H_INCLUDED
#include<conio.h>
#include<windows.h>
#include<iostream>
#include "../../LeOS/LeOSData/projectHeader.h"
using namespace std;

int cdMain();

void draw(int i,char input,int hidden,int eraseMode);

void cdDrawOutine(int eraseMode);

void cdHiddenStatus();

void cdColorStatus(int i,int hidden, int eraseMode);

void cdStartupSettings(int i,int hidden,int eraseMode);

void cdEraseDrawing(int i,int hidden,short mouseX,short mouseY,int eraseMode);

void cdCls();

#endif
