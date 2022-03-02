#include "projectHeader.h"
#include <windows.h>

/* void cls()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  // Get the number of cells in the current buffer 
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  // Fill the entire buffer with spaces
  if (!FillConsoleOutputCharacter(hStdOut,(TCHAR) ' ',cellCount,homeCoords,&count)) return;

  // Fill the entire buffer with the current colors and attributes 
  if (!FillConsoleOutputAttribute(hStdOut,csbi.wAttributes,cellCount,homeCoords,&count)) return;

  // Move the cursor home 
  SetConsoleCursorPosition( hStdOut, homeCoords ); 
  } */

  
  void cls(){
  	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
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
