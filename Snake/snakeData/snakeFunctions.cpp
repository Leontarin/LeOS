#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<string>
#include "snakeFunctions.h"
#include "../../LeOS/LeOSData/projectHeader.h"

static HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

struct Border {
	static const int length = 70;
	static const int height = 25;
};

void snakeDrawOutline(){
	

SetConsoleTextAttribute(hstdout,0xEE);
	SetConsoleCursorPosition(hstdout,{0,Border::height});	//BOTTOM
	for(short n=0;n<=Border::length;n++){
	cout << " "; }
	
	SetConsoleCursorPosition(hstdout,{0,0});		//TOP
	for(short n=0;n<=Border::length;n++){
	cout << " "; }
	
	
	SetConsoleCursorPosition(hstdout,{Border::length,0});
	for(short n=0;n<Border::height;n++){
		cout << " ";
		SetConsoleCursorPosition(hstdout,{Border::length,n+1});	//RIGHT SIDE
	}
	SetConsoleCursorPosition(hstdout,{0,0});	//LEFT SIDE
	for(short n=0;n<Border::height;n++){
		cout << " ";
		SetConsoleCursorPosition(hstdout,{0,n+1});
	}
		SetConsoleTextAttribute(hstdout,0xE0);
		SetConsoleCursorPosition(hstdout,{Border::length/2-4,0});
		cout << "S N A K E";
		SetConsoleCursorPosition(hstdout,{1,1});
}


Snake::Snake(){
			_running = true;
			x = 1;
			y = 1;
			direction = "right";
		}

