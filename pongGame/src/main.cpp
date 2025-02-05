#include <iostream>
#include "../headers/game.h"



int main(int argc, char* argv[]) {


	game g("PongGame",800,800);
	
	while (g.IsRunning()) {
		g.HandleEvents();
		g.update();
		SDL_Delay(16);
	}


	return 0;
}