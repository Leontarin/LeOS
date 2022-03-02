#include "Snake.h"
const static std::string SNAKEVERSION = "ver_03_05";

bool Snake::running(){
	return _running;
}

int Snake::getSpeed(){
	return speed;
}

bool Snake::getBorders(){
	return borders;
}

Snake::Snake(){
	_running = true;
	_jygocsy = false;
	 resetSnake();
	_ingame = false;
	speed = 2;
	borders = true;
	alive = true;
}

Snake::~Snake(){
}


void Snake::update(Window window){
	window.setColor(window.color.black, 0);
	window.setPos(pos[size-1].X,pos[size-1].Y);
	std::cout << " ";
	window.clearEntities(pos,size);
	
	update_snake();
	
	if (borders == true){
		if(pos[0].Y < 0 || pos[0].Y >= HEIGHT-1 || pos[0].X < 0 || pos[0].X >= WIDTH){
			alive = false;
		}
	}
	else if(borders == false){
		if(pos[0].Y < 0)
			pos[0].Y = HEIGHT-2;
		if(pos[0].X < 0)
			pos[0].X = WIDTH;
		if(pos[0].Y > HEIGHT-2)
			pos[0].Y = 0;
		if(pos[0].X > WIDTH)
			pos[0].X = 0;
	}
	
	window.setColor(window.color.lightRed, window.color.lightRed);
	window.setPos(food.X, food.Y);
	std::cout << " ";
	if (alive == true){
		window.setColor(window.color.lightYellow, window.color.lightYellow); //Draw Snake
		window.setPos(pos[0].X, pos[0].Y);
		std::cout << " ";
	}
	
	if (_jygocsy == true)
		ShowScore(window);
	
	int nextScore = (100) + (tick*speed*modifier);
	if(pos[0].X == food.X && pos[0].Y == food.Y) {
		score += nextScore;
		size += 1;
		NewFood();
		ShowScore(window);
		tick = 100;
	}
	
	tick -= 10/speed;
	if (tick <= 0)
		tick = 10/speed;
	
}


void Snake::pullEvent(){
	if (_kbhit()){
		char key = _getch();
		switch(key){
			case 27:
				if(_ingame == false){
					_running = false;
					break;
				}
				if(_ingame == true){
					_ingame = false;
					break;
				}
			case UP_ARROW:
				if(direction.Y != 1){
					direction.X = 0;
					direction.Y = -1;
					break;
				}
			case LEFT_ARROW:
				if(direction.X != 1){
					direction.X = -1;
					direction.Y = 0;
					break;
				}
			case RIGHT_ARROW:
				if(direction.X != -1){
					direction.X = 1;
					direction.Y = 0;
					break;
				}
			case DOWN_ARROW:
				if(direction.Y != -1){
					direction.X = 0;
					direction.Y = 1;
					break;
				}
			default:
				break;
		}
	}
}

void Snake::GameOver(Window window){
	window.setColor(window.color.lightGray,window.color.lightGray);
	window.setPos(WIDTH/2-15, HEIGHT/2-5);
		std::cout << "\t\t\t";
	
	window.setPos(WIDTH/2-15, HEIGHT/2-0);
		std::cout << "\t\t\t";
		window.setColor(window.color.black,window.color.lightGray);
		window.setPos(WIDTH/2-15, HEIGHT/2-1);
		std::cout << "  press 'esc' to exit\t";
		
	window.setPos(WIDTH/2-15, HEIGHT/2-4);
	if(alive == false){
		window.setColor(window.color.lightRed, window.color.lightGray);
		std::cout << "\tYou Lose.\t";
	}
	if(alive == true){
		window.setColor(window.color.lightGreen, window.color.lightGray);
		std::cout << "\tYou Win!\t";
	}
	_ingame = false;
}

void Snake::ShowResult(Window window){ 
	window.setPos(WIDTH/2-15, HEIGHT/2-3);
	window.setColor(window.color.lightYellow, window.color.lightGray);
	std::cout << "\tScore: " << score << "\t";
	window.setPos(WIDTH/2-15, HEIGHT/2-2);
	std::cout << "\tSize: " << size << "\t";
}

void Snake::ShowScore(Window window){
	window.setColor(window.color.gray, window.color.gray);
		if(_jygocsy == true)
			window.setColor(window.color.white,rand()%14+1);
	for(int i=0;i<WIDTH-1;i++){
		window.setPos(i, HEIGHT-1);
		std::cout << " ";
	}	
	window.setPos(1, HEIGHT-1);
	window.setColor(window.color.white,window.color.gray);
	if(_jygocsy == true)
		window.setColor(window.color.white,rand()%14+1);
	std::cout << "Score: " << score << "\t\tSize: " << size << "\tMovement: {" << direction.X << "," << direction.Y << "}" << "\tPos: " << "{" << pos[0].X << "," << pos[0].Y << "}";
	for(int i=0;i<size;i++){
		std::cout << "[" << pos[i].X << "," << pos[i].Y << "],";
	}
}

void Snake::NewFood(){
	bool retry = true;
	int new_Y = (rand()%(HEIGHT-1));
	int new_X = (rand()%(WIDTH-1));
	while(retry){
		retry = false;
		for(int i=0;i<size;i++){
			if(new_X == pos[i].X && new_Y == pos[i].Y){
				int new_Y = (rand()%(HEIGHT-1));
				int new_X = (rand()%(WIDTH-1));
				retry = true;
				break;
			}
		}
	}
	if(retry == false){
		food.X = new_X;
		food.Y = new_Y;
	}
}


void Snake::update_snake(){
	for(int i=size;i>0;i--){
		pos[i] = pos[i-1];
		//if(pos[0].X + direction.X == pos[i-1].X && pos[0].Y + direction.Y == pos[i-1].Y) //if snake's next move collides with itself
		//	alive = false;
	}
	pos[0].X += direction.X;
	pos[0].Y += direction.Y;
}

bool Snake::get_ingame(){
	return _ingame;
}

void Snake::set_ingame(bool input){
	_ingame = input;
}

void Snake::quit(){
	_running = false;
}

void Snake::toggleBorders(){
	borders = !borders;
}

void Snake::toggleSpeed(){
	speed += 1;
	if(speed > 3)
		speed = 1;
}

void Snake::Menu(Window window){
	int jygocsy = 0;
	int currentPos = 0;
	COORD pos[4] = { {WIDTH/2-8,HEIGHT/2-4}, {WIDTH/2-8,HEIGHT/2-2}, {WIDTH/2-8,HEIGHT/2}, {WIDTH/2-8,HEIGHT/2+2} };
	menuDraw(window,currentPos);
	while(running() && get_ingame() == false){
		if(_kbhit()){
			char key = _getch();
			switch (key){
				case UP_ARROW:
					if(currentPos > 0)
						currentPos -= 1;
					break;
				case DOWN_ARROW:
					if(currentPos < 3)
						currentPos += 1;
					break;
				case 'z':
				case RIGHT_ARROW:
				case 32: //SPACEBAR
					if(currentPos == 3){
						quit();
					}
					if(currentPos == 1){
						if(_jygocsy == false)
							toggleSpeed();
					}
					if(currentPos == 2){
						if(_jygocsy == false)
							toggleBorders();
					}	
					if(currentPos == 0){
						resetSnake();
						set_ingame(true);
					}
					break;
				case '*':
					jygocsy++;
					break;
				case '-':
					if(_jygocsy == true){
						jygocsy = 0;
						_jygocsy = false;
						toggleSpeed();
					}
					break;
				default:
					break;
			}
		
			menuDraw(window, currentPos);
			if(get_ingame() == true)
				break;
		}
		if (jygocsy >= 100){
			speed = 80;
			borders = true;
			_jygocsy = true;
		}
	}
}

void Snake::menuCls(Window window, COORD startPos, short int length, short int height){
		for(int i = startPos.Y;i<startPos.Y+height;i++){
			for(int i2 = startPos.X;i2<startPos.X+length;i2++){
				window.setColor(window.color.black,window.color.black);
				window.setPos(i2,i);
				std::cout << " ";
			}
		}
}

void Snake::menuDraw (Window window, int currentPos){
	COORD pos[4] = { {WIDTH/2-8,HEIGHT/2-4}, {WIDTH/2-8,HEIGHT/2-2}, {WIDTH/2-8,HEIGHT/2}, {WIDTH/2-8,HEIGHT/2+2} };
	std::string posNames[4] = { "Play", "Speed: ", "Borders: ", "Quit"};
	window.setColor(window.color.white,0);
	//window.cls();
	COORD clsStartPos = {pos[0].X-2,pos[0].Y};
	menuCls(window,clsStartPos,15,10);
	
	window.setPos(pos[0].X,pos[0].Y-3);
	window.setColor(window.color.lightAqua,0);
	std::cout << "S N A K E";
	
	window.setPos(1, HEIGHT-1);
	window.setColor(window.color.lightGray,0);
	std::cout << "Programmed by Leo Feldman";
	window.setPos(WIDTH-9,HEIGHT-1);
	std::cout << SNAKEVERSION;
	
	for(int i=0;i<4;i++){
		window.setColor(window.color.white,0);
		if(currentPos == i)
			window.setColor(window.color.lightYellow,0);
			window.setPos(pos[i].X,pos[i].Y);
			std:: cout << posNames[i];
			
			if(i==1){
				switch(getSpeed()){
					case 1:
						window.setColor(window.color.lightGreen,0);
						std::cout << "Slow";
						break;
					case 2:
						window.setColor(window.color.lightYellow,0);
						std::cout << "Normal";
						break;
					case 3:
						window.setColor(window.color.lightRed,0);
						std::cout << "Fast";
						break;
					case 80:
						window.setColor(rand()%10+1,0);
						std::cout << "Goodluck =)";
						break;
					default:
						break;
				}
			}
			
			if(i==2){
				if(getBorders()){
					window.setColor(window.color.lightGreen,0);
					if(_jygocsy == true)
						window.setColor(window.color.lightYellow,0);
					std::cout << "Yes";
				}
				if(getBorders() == false){
					window.setColor(window.color.lightRed,0);
					std::cout << "None";
				}
			}
	}
	window.setPos(pos[currentPos].X-2,pos[currentPos].Y);
	window.setColor(window.color.lightYellow,0);
	std::cout << ">";
}

int Snake::getSize(){
	return size;
}

void Snake::resetSnake(){
	if(borders)
		modifier = 1.25;
	else if (borders == false)
		modifier = 1;
	tick = 100;
	alive = true;
	score = 0;
	size = 3;
	direction.X = 1;
	direction.Y = 0;
	pos[0].X = 5;
	pos[0].Y = 5;
	food = {40,10};
}
