#include "DBFunctions.h"

int DBmain(){
	cls();
	SetConsoleTitle("DeepBeeps - Beep Music Player");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0b);
	const string versionInfo = "Version 0.1.2.4 - Crow Edition";
	const string list[] = {"AshCrow","\0"};
	string input;
	while(1){
		cls();
		cout << "----------[ [LeOS] DeepBeeps " << versionInfo << " ]----------" << endl << endl;
		cout << "Insert the Song you wish to Play ('list' for song list)" << endl << "Song: ";
		cin >> input;
		cout << endl << endl;
		for(int i=0;list[i]!="\0";i++){
			if(input=="list"){
				cout << list[i] << ", ";
				getch();
				break;
			}
			if(input=="exit"){
				return 0;
				break;
			}
			if(input==list[i]){
				if(input=="AshCrow"){
					cout << "Now playing: AshCrow" << endl;
					cout << "Notes: A A ABE, A A BCBCD, E C - E C, C C ABA" << endl
						 << "       A A AB E(LOWER), A A BCBCD, E C - E C, C C ABA";
					AshCrow();
					break;
				}
				cout << "The Track has ended.";
				getch();	
			}
		}
		
	}
}
