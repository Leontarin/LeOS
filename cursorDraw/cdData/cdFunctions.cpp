#include<conio.h>
#include<windows.h>
#include<iostream>
#include "cdFunctions.h"
using namespace std;

static HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
static int color[] = {0xFF,0xAA,0xBB,0xCC,0xDD,0xEE,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x00};

 void cdCls(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count,cellCount;
	COORD h = {0,0};
	GetConsoleScreenBufferInfo(hstdout,&csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hstdout,(TCHAR) ' ',cellCount,h,&count);
	FillConsoleOutputAttribute(hstdout,0x0E,cellCount,h,&count);
	SetConsoleCursorPosition(hstdout,h);
	return;
} //CLS CURSOR DRAW VERSION

void cdDrawOutline(){
SetConsoleTextAttribute(hstdout,0x44);
	SetConsoleCursorPosition(hstdout,{0,20});	//BOTTOM
	for(short n=0;n<71;n++){
	cout << " "; }
	
	SetConsoleCursorPosition(hstdout,{0,0});		//TOP
	for(short n=0;n<71;n++){
	cout << " "; }
	
	
	SetConsoleCursorPosition(hstdout,{70,0});
	for(short n=0;n<20;n++){
		cout << " ";
		SetConsoleCursorPosition(hstdout,{70,n+1});	//RIGHT SIDE
	}
	SetConsoleCursorPosition(hstdout,{0,0});	//LEFT SIDE
	for(short n=0;n<20;n++){
		cout << " ";
		SetConsoleCursorPosition(hstdout,{0,n+1});
	}
		SetConsoleTextAttribute(hstdout,0x4E);
		SetConsoleCursorPosition(hstdout,{20,0});
		cout << "C u r s o r    D r a w";
}


void draw(int i,char input,int hidden,int eraseMode){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	short mouseX,mouseY;
	GetConsoleScreenBufferInfo(hstdout,&csbi);
	mouseX = csbi.dwCursorPosition.X;
	mouseY = csbi.dwCursorPosition.Y;
	
	if(input=='c'||input=='C'){
		SetConsoleCursorPosition(hstdout,{12,23});
		if(eraseMode==0);
		SetConsoleTextAttribute(hstdout,color[i]);
		if(eraseMode==1)
		SetConsoleTextAttribute(hstdout,color[15]);
		cout << " ";
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY});
	}
	
	if(input=='r' || input=='R' || input=='e' || input=='E'){
		SetConsoleCursorPosition(hstdout,{12,23});
		if(eraseMode==0);
		SetConsoleTextAttribute(hstdout,color[i]);
		if(eraseMode==1)
		SetConsoleTextAttribute(hstdout,color[15]);
		cout << " ";
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY});
	}
	
	
	if(input=='h'){
		SetConsoleCursorPosition(hstdout,{23,23});
		if(hidden==1)
		SetConsoleTextAttribute(hstdout,0xAA);
		if(hidden==0)
		SetConsoleTextAttribute(hstdout,0xCC);
		cout << " ";
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY});
	}
	if(eraseMode==1)
	SetConsoleTextAttribute(hstdout,color[15]);
	if(eraseMode==0)
	SetConsoleTextAttribute(hstdout,color[i]);
	if(input=='p'){
		cdEraseDrawing(i,hidden,mouseX,mouseY,eraseMode);
	}
	
	if((input=='w' || input == 'W') && mouseY!=1){
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY-1});
		if(hidden==0)
		cout<<" ";
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY-1});
		
	}
	if((input=='s' || input == 'S') && mouseY!=19){
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY+1});
		if(hidden==0)
		cout<<" ";
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY+1});
		
	}
	if((input=='d' || input == 'D') && mouseX!=69){
		SetConsoleCursorPosition(hstdout,{mouseX+1,mouseY});
		if(hidden==0)
		cout<<" ";
		SetConsoleCursorPosition(hstdout,{mouseX+1,mouseY});
		
	}
	if((input=='a' || input == 'A') && mouseX!=1){
		
		SetConsoleCursorPosition(hstdout,{mouseX-1,mouseY});
		if(hidden==0)
		cout<<" ";
		SetConsoleCursorPosition(hstdout,{mouseX-1,mouseY});
		
	}
}


void cdHiddenStatus(int hidden){
	SetConsoleTextAttribute(hstdout,0x0E);
	SetConsoleCursorPosition(hstdout,{15,23});
	cout << "HIDDEN:";
	SetConsoleCursorPosition(hstdout,{23,23});
	if(hidden==0)
	SetConsoleTextAttribute(hstdout,0xCC);
	if(hidden==1)
	SetConsoleTextAttribute(hstdout,0xAA);
	cout << " ";
	return;
}


void cdColorStatus(int i,int eraseMode){
	SetConsoleCursorPosition(hstdout,{5,23});
	cout << "COLOR:";
	SetConsoleCursorPosition(hstdout,{12,23});
	if(eraseMode==0)
	SetConsoleTextAttribute(hstdout,color[i]);
	if(eraseMode==1)
	SetConsoleTextAttribute(hstdout,color[15]);
	cout << " ";
	return;
}


void cdStartupSettings(int i,int hidden,int eraseMode){
	
	cdDrawOutline();
	
	SetConsoleTextAttribute(hstdout,0x0E);
	SetConsoleCursorPosition(hstdout,{1,22});
	cout << "'W/S/A/D' to Move, 'E/R' To Change Color, 'P' To Erase all, 'H' to Hide.";
	SetConsoleCursorPosition(hstdout,{30,23});
	cout << "'C' Toggle Eraser,  'B' to exit.";
	
	cdColorStatus(i,eraseMode);
	
	cdHiddenStatus(hidden);
	

	
	
	return;
}


void cdEraseDrawing(int i,int hidden,short mouseX, short mouseY,int eraseMode){
		cdCls();
		
		cdStartupSettings(i,hidden,eraseMode);
		SetConsoleCursorPosition(hstdout,{mouseX,mouseY});
}



