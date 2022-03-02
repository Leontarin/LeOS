#ifndef SNAKE_WINDOW_H_INCLUDED
#define SNAKE_WINDOW_H_INCLUDED
#include <Windows.h>

#define HEIGHT 30
#define WIDTH 80

class Window{
	private:
		class Color{
			public:
				Color();
				~Color();
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
		
	public:
		Color color;
		void cls();
		void setColor(int bgColor, int fgColor); //Background/Foreground
		void setPos(WORD X, WORD Y);
		void drawFrame();
		void clearEntities(COORD snake_pos[], int snake_size);
		Window();
		~Window();
};

#endif

