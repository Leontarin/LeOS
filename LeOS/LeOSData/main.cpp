#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<mmsystem.h>
#include<iostream>
#include<string.h>
#include "projectHeader.h"
#define WIDTH 800
#define HEIGHT 600


int main(){
	cls();
//	mainIntro();  
	const std::string versionInfo = "Version 0.4.0.2 - Color Edition";
	while(1){
	init_window(WIDTH,HEIGHT);
	SetConsoleTitleA("LeOS - [Project about Projects]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
	cls();
	std::cout << "----------[LeOS " << versionInfo << "]----------\n\n";
	std::cout << "Hello, Welcome to the 'LOBBY', Where would you like to go? ('list' for options)\n";
	std::cout << "Room: ";
	
	mainRooms();
	}
	return 0;
}

	
