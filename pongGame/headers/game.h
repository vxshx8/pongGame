#pragma once
#include "SDL2/SDL.h"
#include "../headers/renderer.h"
#include <random>


class game {
public:
	~game();
	game(const char*title,int width,int height);
	void update();
	void HandleEvents();
	bool IsRunning() const{ return isRunning; }
	void movePillars(int flag);
	void moveSquare();
	void points();
	void resetSquare();
	
	//use SDL hasintersection to verify colisions between the square and the pillar
	bool colision() { if (turn) { return SDL_HasIntersection(&Square, &Pillar1) == SDL_TRUE; } else { return SDL_HasIntersection(&Square, &Pillar2) == SDL_TRUE; } };
private:
	bool turn;
	int speed = 7;
	int points1 = 0;
	int points2 = 0;
	float squareSpeed = 10.0f;
	float x = -0.4f;
	float y = -0.4f;
	int h, w;
	
	renderer Ren;
	SDL_Rect Square;
	SDL_Rect Pillar1;
	SDL_Rect Pillar2;
	                                                                                                       
	bool isRunning;                           
};                                                              