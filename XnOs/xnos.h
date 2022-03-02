#ifndef XNOS_H_INCLUDED
#define XNOS_H_INCLUDED

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#define ESC 27

class XNOS{
	private:
		short int turn;
		short int slot[3][3];
		bool _running;
		bool _replay;
		short int win_state;
		
		class WINDOW{
			private:
				class COLOR{
					public:
						COLOR();
						~COLOR();
						void reset();
						WORD blue;
						WORD green;
						WORD aqua;
						WORD red;
						WORD purple;
						WORD yellow;
						WORD lightGray;
						WORD gray;
						WORD lightBlue;
						WORD black;
						WORD lightGreen;
						WORD lightAqua;
						WORD lightRed;
						WORD lightPurple;
						WORD lightYellow;
						WORD white;
				};
				HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
				HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
				HWND hwnd = GetConsoleWindow();
				INPUT_RECORD InputRecord;
				DWORD Events;
				CONSOLE_CURSOR_INFO cci;
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				
			public:
				WINDOW();
				~WINDOW();
				COLOR color;
				void init_window();
				void cls();
				void set_color(short int bgColor, short int fgColor);
				void set_pos(WORD X, WORD Y);
				void draw_board(short int slot[3][3], short int turn);
				COORD ReadMouse();
				void draw_shape(int shape, COORD coord, short int bgColor);
				void draw_turn(short int turn);
				void draw_win_state(short int win_state, short int turn);
				
				
		};
		
	public:
		WINDOW window;
		XNOS();
		~XNOS();
		void init_game();
		void place(COORD input, short int turn);
		void update(short int location);
		bool running();
		bool replay();
		void GameOver(short int turn); //print Game Over and announce the winner
		short int PlayTurn();
		short int check_click(COORD coord);
		short int validate();
		void conditional_color(short int turn,short int fgColor);
		void end();
		
		
};

#endif
