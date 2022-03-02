#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<algorithm>
#include<cctype>
#include<windows.h>
#include<mmsystem.h>
#include<iostream>
#include<string.h>
#include "projectHeader.h"


void mainIntro(){
	cls();
	init_window(300,150);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	short int x = 2;
	short int y = 1;
	COORD introLine1 = {x,y}, introLine2 = {x,y+1}, introLine3 = {x,y+2}, introLine4 = {x,y+3}, introLine5 = {x,y+4}, introLine6 = {x,y+4};
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hstdout, &cci);
	cci.dwSize = 25;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hstdout, &cci);
	for(int i=0;i<2;i++){
	if(i==0){
		SetConsoleTextAttribute(hstdout,0x0C);
	}
	if(i==1){
		SetConsoleTextAttribute(hstdout,0x0B);
	}
	SetConsoleCursorPosition(hstdout,{x,y-1});
	SetConsoleTitle("["); std::cout << "\t _           _____ _____ " << endl; if(i==0) {Beep(55*4,125); Sleep(125);} //1 - line 0
	SetConsoleCursorPosition(hstdout,introLine5);
	SetConsoleTitle("[ L"); std::cout << "\t\\_____/\\___| \\___/\\____/"; if(i==0) {Beep(61.74*4,125); Sleep(125);} //2 - line 5
	SetConsoleCursorPosition(hstdout,introLine1);
	SetConsoleTitle("[ L e"); std::cout << "\t| |         |  _  /  ___|"; if(i==0) {Beep(65.41*4,125); Sleep(125);} //3 - line 1
	SetConsoleCursorPosition(hstdout,introLine4);
	SetConsoleTitle("[ L e O"); std::cout << "\t| |___|  __/\\ \\_/ /\\__/ /"; if(i==0) {Beep(73.42*4,125); Sleep(125);} //4 - line 4
	SetConsoleCursorPosition(hstdout,introLine2);
	SetConsoleTitle("[ L e O S"); std::cout << "\t| |     ___ | | | \\ `--. "; if(i==0) {Beep(82.41*4,125); Sleep(125); }//5 - line 2
	SetConsoleCursorPosition(hstdout,introLine3);
	SetConsoleTitle("[ L e O S ]"); std::cout << "\t| |    / _ \\| | | |`--. \\"; if(i==0) {Beep(103.83*4,125); Sleep(125);} //6 - line 3
	SetConsoleCursorPosition(hstdout,introLine6);
	if(i==1) {SetConsoleTitle("[LeOS]");  Beep(110*4,800); Sleep(1000); } }
	
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hstdout, &cci);
	
	return;
}


void mainRooms(){
	const string list[] = {"Lobby","CD","Snake","DB","XNOS","\0"}; 
	const string listLow[] = {"lobby","cd","snake","db","xnos","\0"};
	bool roomFound=false;
	int spaceNum;
	std::string roomInput;
	std::cin >> roomInput;
	transform(roomInput.begin(), roomInput.end(), roomInput.begin(), [](unsigned char c){ return std::tolower(c); });
	if(roomInput=="exit"){
		exit(0);
	}
	if(roomInput=="list"){
		spaceNum=0;
		for(int i=0;list[i]!="\0";i++){
			cout << list[i] << ", ";
			if(i-spaceNum>=5){
				spaceNum=i;
				std::cout << endl;
			}
		}
		_getch();
		return;
	}
	for(int i=0;list[i]!="\0";i++){
		if(roomInput==list[i] || roomInput==listLow[i]){
			roomFound=true;
			cls();
			switch (i){
				case 0: //lobby
					mainIntro();
					return;
				case 1: //cd
					cdStart();
					return;
				case 2: //snake
					//std::cout << list[i] << " is disabled.";
					SnakeStart();
					return; 
				case 3: //db
					DBmain();
					return;
				case 4: //xnos
					xnos_main();
					return;
				default:
					cls();
					return;
			}
			
		}
		}
	if(roomFound==false){
			std::cout << endl << "Room \"" << roomInput << "\" does not exist."; 
			_getch();
			return;
			}
	return;
}

void init_window(WORD width, WORD height){
	RECT desktop;
	HWND hwnd = GetConsoleWindow();
	HWND hwndesk = GetDesktopWindow();
	GetWindowRect(hwndesk, &desktop);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if( hwnd != NULL ){ MoveWindow(hwnd ,(desktop.right-width)/3,(desktop.bottom-height)/2,width,height,TRUE); } //set Window size
	ShowScrollBar(hwnd, SB_BOTH, FALSE); 
	ShowScrollBar(hwnd, SB_BOTH, FALSE); // why twice though
	COORD coord;
	coord.X = width/20 + 1;
	coord.Y = height/9 + 1;
	SetConsoleScreenBufferSize(hstdout, coord);
	SetConsoleScreenBufferSize(hstdout, coord); //why twice though
}
