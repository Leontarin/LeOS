#include "xnos.h"



const static LPCSTR title = "[LeOS] X n O's 	<0.1.1>";

const COORD button_size = {16,8};
const COORD starting_coord = {5,2};
const COORD button_pos[9] = { //button positions for easy access
	{starting_coord.X, starting_coord.Y}, {(button_pos[0].X + button_size.X + 1),(button_pos[0].Y)}, {(button_pos[1].X + button_size.X + 1),(button_pos[1].Y)},
	{(button_pos[0].X),(button_pos[0].Y + button_size.Y + 1)}, {(button_pos[0+3].X + button_size.X + 1),(button_pos[0+3].Y)}, {(button_pos[0+4].X + button_size.X + 1),(button_pos[0+4].Y)},
	{(button_pos[0+3].X),(button_pos[0+3].Y + button_size.Y + 1)}, {(button_pos[0+6].X + button_size.X + 1),(button_pos[0+6].Y)}, {(button_pos[0+7].X + button_size.X + 1),(button_pos[0+7].Y)}
}; 

XNOS::XNOS(){
	_running = true;
	_replay = true;
}

XNOS::~XNOS(){
}

void XNOS::init_game(){
	_running = true;
	turn = 1;
	for(int i=0;i<3;i++){
		for(int i2=0;i2<3;i2++){
			slot[i][i2] = 0;
		}
	}
	
	window.draw_board(slot, turn);
}

short int XNOS::validate(){ //tests for game over
	for(int i=0;i<3;i++){
			if(slot[0][i] == slot[1][i] && slot[1][i] == slot[2][i] && slot[0][i] != 0){ 
				win_state = i+1;
				return slot[0][i];
			}
			if(slot[i][0] == slot[i][1] && slot[i][1] == slot[i][2] && slot[i][0] != 0){
				win_state = i+1+3;
				return slot[i][0];
			}
	}
	if(slot[0][0] == slot[1][1] && slot[1][1] == slot[2][2] && slot[0][0] != 0){
		win_state = 7;
		return slot[0][0];
	}
	if(slot[0][2] == slot[1][1] && slot[1][1] == slot[2][0] && slot[0][2] != 0){
		win_state = 8;
		return slot[0][2];
	}
	int unplayed = 0;
	for(int i=0;i<3;i++){
		for(int i2=0;i2<3;i2++){
			if(slot[i][i2] == 0)
				unplayed++;
		}
	}
	if(unplayed == 0){
		return 3;
	}
	return 0;
}

void XNOS::place(COORD input, short int turn){
	slot[input.Y][input.X] = turn; 
}

bool XNOS::running(){
	return _running;
}

bool XNOS::replay(){
	return _replay;
}

void XNOS::update(short int location){
	if(location >= 0 && location <= 9){
			short int x = location;
			short int y = 0;
			while(x>3){
				x -=3 ;
				y++;
			}
			if(slot[y][x-1] == 0){
				COORD coord;
				coord.X = x-1;
				coord.Y = y;
				place(coord,turn);
				turn = 3-turn;
				window.cls();
				window.draw_board(slot, turn);
			}
			/*else{
				window.set_pos(button_pos[6].X,button_pos[7].Y+3);
				window.set_color(window.color.black,window.color.lightYellow);
				std::cout << "Position taken by player " << slot[y][x-1];
			}*/
		}	
}

void XNOS::conditional_color(short int turn,short int fgColor){
		if(turn == 1)
			window.set_color(window.color.red,fgColor);
		if(turn == 2)
			window.set_color(window.color.blue,fgColor);
		if(turn == 3)
			window.set_color(window.color.yellow,fgColor);	
	}

void XNOS::GameOver(short int turn){
	_running = false;
	_replay = false;
	if(turn == 1 || turn == 2)
		window.draw_win_state(win_state, turn);
	
	COORD start;
	start.X = button_pos[8].X+button_size.X+2;
	start.Y = button_pos[8].Y;
	
	
	
	conditional_color(turn, window.color.white);
	for(short int y=start.Y;y<start.Y+button_size.Y;y++){
		for(short int x=start.X;x<=start.X+button_size.X*2;x++){
			window.set_pos(x,y);
			std::cout << " ";
		}
	}
	
	window.set_pos(start.X+(button_size.X/2+3),start.Y+1);
	conditional_color(turn, window.color.white);
	std::cout << "[GAME OVER]";
	window.set_pos(start.X+2,start.Y+3);
	if(turn == 1){
		std::cout << "Winner: ";
		conditional_color(turn, window.color.lightYellow);
		std::cout << "X (Cross)";
	}
	if(turn == 2){
		std::cout << "Winner: ";
		conditional_color(turn, window.color.lightAqua);
		std::cout << "O (Circle)";
	}
	if(turn == 3){
		conditional_color(turn, window.color.lightYellow);
		std::cout << "Match ended in a Tie.";
	}
	

	for(short int y=start.Y+button_size.Y-3;y<start.Y+button_size.Y;y++){
		for(short int x=start.X;x<=start.X+button_size.X*2;x++){
			window.set_color(window.color.green,window.color.green);
			if(x > start.X+button_size.X)
				window.set_color(window.color.gray,window.color.gray);
			window.set_pos(x,y);
			std::cout << " ";
		}
	}
	window.set_color(window.color.green,window.color.white);
	window.set_pos(start.X+3,start.Y+button_size.Y-2);
	std::cout << "PLAY AGAIN";
	window.set_color(window.color.gray,window.color.black);
	window.set_pos(start.X+button_size.X+4,start.Y+button_size.Y-2);
	std::cout << "EXIT GAME";
	
	
	window.color.reset();
}

void XNOS::end(){
	COORD coord = {-1, -1};
	short int click = 0;
	while(click != -2 && click != 101){
		coord = window.ReadMouse();
		click = check_click(coord);
	}
	
	if(click == 101){
		_replay = true;
		_running = false;
	}
	
	if(click == -2){
		_running = false;
		_replay = false;
	}
	
}

short int XNOS::PlayTurn() {
	COORD coord = {-1,-1};
	short int location = -1;
	COORD exit_button[2] = {{69,0},{70,1}};
	while(coord.X == -1 && coord.Y == -1) {
		coord = window.ReadMouse();	
		location = check_click(coord);
		Sleep(50);
	}
	if(location >= 1 && location <= 9){
		return location;
	}
	conditional_color(turn, window.color.white);
		
	return 0;
}

short int XNOS::check_click(COORD coord){
	for(int i=0;i<9;i++){
		if( (coord.X >= button_pos[i].X) && (coord.X <= button_pos[i].X+button_size.X-1) && 
			(coord.Y >= button_pos[i].Y) && (coord.Y <= button_pos[i].Y+button_size.Y-1))
			{
				return i+1;
			}
		}
		
		COORD start;
		start.X = button_pos[8].X+button_size.X+2;
		start.Y = button_pos[8].Y;
		
		if(coord.X >= start.X && coord.Y >= start.Y+button_size.Y-3 && coord.X <= start.X+button_size.X && coord.Y < start.Y+button_size.Y){
			return 101;
		}
		if(coord.X > start.X+button_size.X && coord.Y >= start.Y+button_size.Y-3 && coord.X <= start.X+button_size.X*2 && coord.Y < start.Y+button_size.Y ){
			return -2;
		}
	return -1;
}


//-------------------------------------------------------------------------
	

XNOS::WINDOW::WINDOW(){
	init_window();
}

XNOS::WINDOW::~WINDOW(){
}

COORD XNOS::WINDOW::ReadMouse(){
		ReadConsoleInput(hin, &InputRecord, 1, &Events);
	if(InputRecord.EventType == MOUSE_EVENT && InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
		COORD coord = {InputRecord.Event.MouseEvent.dwMousePosition.X, InputRecord.Event.MouseEvent.dwMousePosition.Y};
		return coord;
	}
	return {-1,-1};
}

void XNOS::WINDOW::init_window(){
	color.reset();
	cls();
	
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(title);
	GetConsoleCursorInfo(hout, &cci);
	cci.dwSize = 25;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hout, &cci);
	SetConsoleMode(hin, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ~ENABLE_QUICK_EDIT_MODE);
	
	//Get Desktop Resolution
	RECT desktop;
	HWND hwndesk = GetDesktopWindow();
	GetWindowRect(hwndesk, &desktop);
	
	if( hwnd != NULL ){ MoveWindow(hwnd ,(desktop.right-1366)/2,(desktop.bottom-768)/2,1366,768,TRUE); } //set Window size
	
	ShowScrollBar(hwnd, SB_BOTH, FALSE);
	ShowScrollBar(hwnd, SB_BOTH, FALSE);
	
}


void XNOS::WINDOW::set_color (short int bgColor,short int fgColor){
	int color_set = (bgColor << 4)+fgColor;
	SetConsoleTextAttribute(hout, color_set);
}

void XNOS::WINDOW::set_pos(WORD X, WORD Y){
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

void XNOS::WINDOW::cls(){
	set_color(color.black,color.black);
  	if(hout == INVALID_HANDLE_VALUE) return;
  	CONSOLE_SCREEN_BUFFER_INFO csbi;
  	DWORD count, cellCount;
  	COORD homeCoords = {0,0};
	if(!GetConsoleScreenBufferInfo(hout,&csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	if(!FillConsoleOutputCharacter(hout,(TCHAR) ' ',cellCount,homeCoords,&count)) return;
	if(!FillConsoleOutputAttribute(hout,csbi.wAttributes,cellCount,homeCoords,&count)) return;
	set_pos(0,0);
}

void XNOS::WINDOW::draw_shape(int shape, COORD coord, short int bgColor){
		set_color(bgColor,bgColor);
		short int x_exc[2] = {button_pos[1].X-1, button_pos[2].X-1};
		short int y_exc[2] = {button_pos[4].Y-1, button_pos[7].Y-1};
		for(short int y=coord.Y;y<coord.Y+button_size.Y;y++){
			for(short int x=coord.X;x<coord.X+button_size.X;x++){
				set_pos(x,y);
				if((x == x_exc[0] || x == x_exc[1]) || (y == y_exc[0] || y == y_exc[1]) ){
						set_color(0,0);	
				}
				else{
						set_color(bgColor,bgColor);				
				}	
				std::cout << " " << std::flush;
			}
		}
	set_pos(coord.X,coord.Y);
	set_color(color.black,color.white);
	if(shape==1){ //DRAW X
		set_color(bgColor,color.lightRed);
		set_pos(coord.X+(button_size.X/2)-3,coord.Y+1); std::cout << "\\    /";
		set_pos(coord.X+(button_size.X/2)-3,coord.Y+2); std::cout << " \\  / ";
		set_pos(coord.X+(button_size.X/2)-3,coord.Y+3); std::cout << "  \\/  ";
		set_pos(coord.X+(button_size.X/2)-3,coord.Y+4); std::cout << "  /\\  ";
		set_pos(coord.X+(button_size.X/2)-3,coord.Y+5); std::cout << " /  \\ ";
		set_pos(coord.X+(button_size.X/2)-3,coord.Y+6); std::cout << "/    \\";
		
	}
	if(shape==2){//DRAW CIRCLE
		set_color(bgColor,color.lightBlue);
		set_pos(coord.X+(button_size.X/2)-4,coord.Y+1); std::cout << "  ____   ";
		set_pos(coord.X+(button_size.X/2)-4,coord.Y+2); std::cout << " /    \\ ";
		set_pos(coord.X+(button_size.X/2)-4,coord.Y+3); std::cout << "|      | ";
		set_pos(coord.X+(button_size.X/2)-4,coord.Y+4); std::cout << "|      | ";
		set_pos(coord.X+(button_size.X/2)-4,coord.Y+5); std::cout << " \\____/ ";
		set_pos(coord.X+(button_size.X/2)-4,coord.Y+6); std::cout << "         ";
	}
	if(shape==0){
	}
		
}

void XNOS::WINDOW::draw_board(short int slot[3][3], short int turn){
	for(short int y=0;y<3;y++){
		for(short int x=0;x<3;x++){
			if(slot[y][x] == 0)
				draw_shape(slot[y][x],button_pos[(y*3)+x],color.lightGray);
			else
			draw_shape(slot[y][x],button_pos[(y*3)+x],color.lightGray);
		}
	}
	
	draw_turn(turn);
	
}

void XNOS::WINDOW::draw_turn(short int turn){
	short int x = button_pos[2].X+button_size.X+3;
	short int y = button_pos[2].Y+2;
	set_color(color.lightYellow,color.lightYellow);
	//T - letter
	set_pos(x+0,y+0); std::cout << "######"; 
	set_pos(x+2,y+1); std::cout <<   "##"  ;
	set_pos(x+2,y+2); std::cout <<   "##"  ;
	set_pos(x+2,y+3); std::cout <<   "##"  ;
	set_pos(x+2,y+4); std::cout <<   "##"  ;
	//U - letter
	x += 7;
	set_pos(x+0,y+0); std::cout << "##"; set_color(0,0); std::cout << "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##"; 
	set_pos(x+0,y+1); std::cout << "##"; set_color(0,0); std::cout << "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	set_pos(x+0,y+2); std::cout << "##"; set_color(0,0); std::cout << "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	set_pos(x+0,y+3); std::cout << "##"; set_color(0,0); std::cout << "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	set_pos(x+1,y+4); std::cout << "####";
	//R - Letter
	x+= 7;
	set_pos(x+0,y+0); std::cout << "#####"; 
	set_pos(x+0,y+1); std::cout << "##"; set_color(0,0); std::cout <<  "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	set_pos(x+0,y+2); std::cout << "####";
	set_pos(x+0,y+3); std::cout << "##"; set_color(0,0); std::cout <<  " "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	set_pos(x+0,y+4); std::cout << "##"; set_color(0,0); std::cout <<  "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	//N - letter
	x+= 7;
	set_pos(x+0,y+0); std::cout << "##"; set_color(0,0); std::cout <<  "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##"; 
	set_pos(x+0,y+1); std::cout << "###"; set_color(0,0); std::cout <<  " "; set_color(color.lightYellow,color.lightYellow); std::cout << "##"; 
	set_pos(x+0,y+2); std::cout << "######"; 
	set_pos(x+0,y+3); std::cout << "##"; set_color(0,0); std::cout <<  " "; set_color(color.lightYellow,color.lightYellow); std::cout << "###"; 
	set_pos(x+0,y+4); std::cout << "##"; set_color(0,0); std::cout <<  "  "; set_color(color.lightYellow,color.lightYellow); std::cout << "##";
	COORD turn_coord;
	turn_coord.X = button_pos[2].X+button_size.X+12;
	turn_coord.Y = y+7;
	draw_shape(turn,turn_coord,color.gray);
}

void XNOS::WINDOW::draw_win_state(short int win_state, short int turn){
	short int x,y;
	short int x2,y2;
	short int mod;
	short int mod2;
	if(turn == 1)
		set_color(color.lightRed,color.lightRed);
	if(turn == 2)
		set_color(color.lightBlue,color.lightBlue);
	
	if(win_state > 0 && win_state < 7){	
		if((win_state - 1)/3 == 0){ //between 1 and 3
			mod = 0;
			mod2 = 0;
		}
		if((win_state - 1)/3 == 1){
		//	mod = 3-((win_state-4)*2);
		//	mod2 = 1-((win_state-4)*2);
			switch (win_state){ //"band-aid" fix for win-state 4->6 bug misbehaving
				case 4:
					mod = 3;
					mod2 = 1;
					break;
				case 5:
					mod = 1;
					mod2 = -1;
					break;
				case 6:
					mod = -1;
					mod2 = -3;
					break;
			}
		}	
		//
		x = button_pos[win_state-1+mod].X+(button_size.X/2)-1; y = button_pos[win_state-1+mod].Y+(button_size.Y/2);
		x2 = button_pos[win_state-1+mod2].X+(button_size.X/2)-1; y2 = button_pos[win_state-1+6].Y+(button_size.Y/2);
		if(win_state >= 1 && win_state <= 3){
			for(short int i=y;i<=y2;i++){
				set_pos(x,i);
				std::cout << "##";
			} 
		}
		if(win_state >= 4 && win_state <= 6){
			for(short int i=x;i<=x2;i++){
			 	set_pos(i,y);
			 	std::cout << "##";
			}
		}
		
	}
	
	if(win_state == 7){
		x = button_pos[0].X + (button_size.X/2); y = button_pos[0].Y+(button_size.Y/2);
		x2 = button_pos[8].X + (button_size.X/2); y2 = button_pos[8].Y + (button_size.Y/2);
		short int i = x;
		short int i2 = y+1;
		while (i<=x2 && i2<=y2){
			set_pos(i,i2);
			std::cout << "  ";
			i += 2;
			i2++;
		}
	}
	
	if(win_state == 8){
		x = button_pos[6].X + (button_size.X/2); y = button_pos[6].Y+(button_size.Y/2);
		x2 = button_pos[2].X + (button_size.X/2); y2 = button_pos[2].Y + (button_size.Y/2);
		short int i = x;
		short int i2 = y-1;
		while (i<=x2 && i2>=y2){
			set_pos(i,i2);
			std::cout << "  ";
			i += 2;
			i2--;
		}
	}
	set_pos(0,28);
}

XNOS::WINDOW::COLOR::COLOR(){
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

void XNOS::WINDOW::COLOR::reset(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
}

XNOS::WINDOW::COLOR::~COLOR(){
}
