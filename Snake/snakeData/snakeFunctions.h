#ifndef SNAKEFUNCTIONS_H_INCLUDED
#define SNAKEFUNCTIONS_H_INCLUDED
#include "../../LeOS/LeOSData/projectHeader.h"

void snakeMain();
void snakeDrawOutline();

class Snake{
	private:
		int x,y;
		std::string directions[4] = {"up","down","left","right"};
		std::string direction;
		bool _running = false;
		
	public:
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
		std::string getDirection(){
			return direction;
		}
		bool isRunning(){
			return _running;
		}
		
		Snake();
	
		
};

#endif
