#include<conio.h>
#include<windows.h>
#include<iostream>
#include "cdFunctions.h"
using namespace std;

static HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
static int color[] = {0xFF,0xAA,0xBB,0xCC,0xDD,0xEE,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0x00};
int cdStart(){
	cls();
	const string versionInfo = "0.5.1.1 - Not MS Paint Edition.";
	SetConsoleTitle("CursorDraw - Not MS Paint");
	string answer;
	SetConsoleTextAttribute(hstdout,0x0E);
	cout << "\t[ Welcome to Cursor Draw - " << versionInfo << " ]" << endl;
	cout << "Would you like to start CursorDraw? (yes/no)" << endl << "Answer: ";
	cin >> answer;
	if(answer=="yes"){
		cls();
		cdMain();
		return 0;
	}
	if(answer=="no"){
		cls();
		return 0;
	}
}

int cdMain(){
	int i=0, hidden=0, eraseMode=0;
	COORD hCoords = {1,1};
						
	cdStartupSettings(i,hidden,eraseMode);
	
	SetConsoleTextAttribute(hstdout,0xFF);
	SetConsoleCursorPosition(hstdout,hCoords);
	cout << " ";
	SetConsoleCursorPosition(hstdout,hCoords);
	
	char input;
	while(1){
		input = getch();
		
		if(input=='c' || input=='C'){
			if(eraseMode==0){
				eraseMode=1;
			}
			else if(eraseMode==1){
				eraseMode=0;
			}
		}
		
		if(input=='h' || input=='H'){
			if(hidden==1){
				hidden=0;
			}
			else if(hidden==0){
				hidden=1;
			}
		}
		if(eraseMode==0){
		if(input=='r' || input=='R'){
			if(i==14){
				i=0;
			}
			else if(i!=14)
			i++;
			}
		if(input=='e' || input=='E'){
			if(i==0){
				i=14;
			}
			else if(i!=0)
			i--;
				
		
		}}
		if(input=='b' || input=='B'){
			SetConsoleTextAttribute(hstdout,0x0F);
			main();
		}
		draw(i,input,hidden,eraseMode);
	}
	return 0;
}







//CLS(); CLEAR SCREEN FUNCTION

