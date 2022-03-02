#include "xnos.h"


int xnos_main(){
	XNOS xnos;
	short int game = 0; //state of game
	short int slot; //Slot Played		
	while(xnos.replay()){
		xnos.window.init_window();
		xnos.init_game();
		 game = 0;
		 slot = 0;
			while(xnos.running()){  // while a match is running
				
				slot = xnos.PlayTurn();
				if(slot >= 1 && slot <= 9)
					xnos.update(slot);
					
				game = xnos.validate();
				if(game >= 1 && game <= 3)
					xnos.GameOver(game);
			}
		
		xnos.end();

	}
	return 0;
}
