#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#pragma once
#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include "Snake_Window.h"

#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80

class Snake{
	private:
		bool _jygocsy;
		void resetSnake();
		COORD food;
		bool borders;
		int score;
		bool _running;
		bool _ingame;
		int size;
		COORD direction;
		COORD pos[WIDTH*HEIGHT];
		
	public:	
		int modifier;
		int tick;
		void Menu(Window window);
		void menuDraw(Window window, int currentPos);
		bool getBorders();
		int getSpeed();
		int speed;
		void set_ingame(bool input);
		bool get_ingame();
		bool running();
		void quit();
		bool alive;
		int getSize();
		void toggleBorders();
		void toggleSpeed();
		void GameOver(Window window);
		void ShowResult(Window window);
		void update(Window window);
		void ShowScore(Window window);
		void pullEvent();
		void update_snake();
		void NewFood();
		void menuCls(Window window, COORD startPos, short int length, short int height);
		Snake();
		~Snake();
};

#endif
