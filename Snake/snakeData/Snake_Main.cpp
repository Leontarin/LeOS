#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include "Snake.h"
#include "Snake_Window.h"
using namespace std;


int SnakeStart() {
	Window window;
	Snake snake;
	
	while (snake.running()){
		snake.Menu(window);
		if (snake.get_ingame()){
			window.cls();
			snake.ShowScore(window);
		}
	
		while(snake.get_ingame() && snake.running()){
			snake.pullEvent();
			snake.update(window);
			snake.ShowScore(window);
			Sleep(100);
			
		/*	if(snake.alive == false || snake.getSize() <= 50){
				snake.GameOver(window);
				snake.ShowResult(window);
				while (_getch() != 27){ //press 'esc' to exit
				}
				window.cls();
			}
			*/
		}
		
	}
	return 0;
}

