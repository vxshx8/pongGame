#include "../headers/game.h"


//init and config the window and initial positions from pillars and the point square
game::game(const char* title, int width, int height) {
	Ren.createWindow(title, width, height);
	h = height;
	w = width;
	Pillar1 = { width / 10,height / 3,20,150 };
	Pillar2 = { (width / 10) * 9,height / 3,20,150 };
	Square = { width / 2,height/2,10,10 };
	points1 = points2 = 0;
	turn = true;
	isRunning = true;

}


//clear and present the game
void game::update() {
	Ren.clear();
	Ren.drawBorders();
	Ren.DrawPillars(&Pillar1,&Pillar2);
	Ren.drawSquare(&Square);
	Ren.DrawText(points1, 0);
	Ren.DrawText(points2, 1);
	moveSquare();
	points();
	Ren.present();
}

//function to set the movements from the pillars int the y axis
void game::movePillars(int flag) {
	const float fps = 1000.0f / 60;
	if (turn) {
		if (flag == 1) {
			if (Pillar1.y > 0) {
				Pillar1.y -= 5 * speed ;
			}

		}
		else {
			if (Pillar1.y + Pillar1.h < 800) {
				Pillar1.y += 5 * speed;
			}

		}
	}
	else {
		if (flag == 1) {
			if (Pillar2.y > 0) {
				Pillar2.y -= 5 * speed ;
			}

		}
		else {
			if (Pillar2.y + Pillar2.h < 800) {
				Pillar2.y += 5 * speed;
			}

		}
	}
	
}


//reset the square to the midle of screen
void game::resetSquare() {
	Square.x = w/2;
	Square.y = h/2;
}

// verify if the square made a point by seeing if x axis point is smaller or bigger then the screen width
void game::points() {
	if (Square.x > 800){
		points1++;
		resetSquare();
	}
	if (Square.x < 0) {
		points2++;
		resetSquare();
	}
}

//move the square for the screen if hits y axis change the direction 
void game::moveSquare() {
	Square.x += x * squareSpeed;
	Square.y += y * squareSpeed;
	if (Square.y <= 0 || Square.y + Square.h >= 800) {
		y = -y; 
	}
	// verify colision and change x axis direction 
	if (colision()) {
		x = -x;
		turn = !turn;
		//it hit make the square a little faster
		squareSpeed += 0.2;
	}
}



//handle the eventes of keypres and quit 
void game::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case (SDL_QUIT):
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
				movePillars(1);
			}
			else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
				movePillars(0);
			}
		default:
			break;
		}
		

	}
}

game::~game() {
	Ren.close();
}