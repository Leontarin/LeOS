#include "Snake_Window.h"
#include <iostream>
#include "Snake_Main.h"

HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

Window::Window(){
	SetConsoleTitle("[LeOS] Snake");
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, (WIDTH)*8, (HEIGHT)*12,TRUE);
	
	GetConsoleScreenBufferInfo(hstdout , &csbi);
	csbi.dwSize.X = WIDTH;
	csbi.dwSize.Y = HEIGHT;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);
	
	ShowWindow(console, SW_MAXIMIZE);
	
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hstdout, &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(hstdout, &cci);
}

Window::~Window(){
}

void Window::clearEntities(COORD snake_pos[], int size){
	setColor(color.black, color.black); //draw snake
	for (int i=0;i<size;i++){
		setPos(snake_pos[i].X, snake_pos[i].Y);
		std::cout << " ";
	}
}

void Window::setColor (int bgColor, int fgColor){
	int color_set = (fgColor*16)+bgColor;
	SetConsoleTextAttribute(hstdout, color_set);
}

void Window::setPos(WORD X, WORD Y){
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hstdout, coord);
}
Window::Color::Color(){
	blue = 1;
	green = 2;
	aqua = 3;
	red = 4;
	purple = 5;
	yellow = 6;
	lightGray = 7;
	gray = 8;
	lightBlue = 9;
	black = 0;
	lightGreen = 10;
	lightAqua = 11;
	lightRed = 12;
	lightPurple = 13;
	lightYellow = 14;
	white = 15;
}

void Window::cls(){
	setColor(color.black,color.black);
  	if(hstdout == INVALID_HANDLE_VALUE) return;
  	CONSOLE_SCREEN_BUFFER_INFO csbi;
  	DWORD count, cellCount;
  	COORD homeCoords = {0,0};
	if(!GetConsoleScreenBufferInfo(hstdout,&csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	if(!FillConsoleOutputCharacter(hstdout,(TCHAR) ' ',cellCount,homeCoords,&count)) return;
	if(!FillConsoleOutputAttribute(hstdout,csbi.wAttributes,cellCount,homeCoords,&count)) return;
	SetConsoleCursorPosition(hstdout, homeCoords);
}

Window::Color::~Color(){
	
}
