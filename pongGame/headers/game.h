#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "SDL2/SDL.h"
#include "../headers/renderer.h"
#include <random>
#include <map>

class game {
public:
	~game();
	game(const char*title,int width,int height);
	void update();
	void HandleEvents();
	bool IsRunning() const{ return isRunning; }
	void movePillars();
	void moveSquare();
	void points();
	void resetSquare();
	void resetGame() { points1 = 0; points2 = 0;gameOver = false; };
	void checkGameover() { if (points1 == 10 || points2 == 10) { gameOver = true; } }
	void gameOverOptions();
	void updateKeyState(SDL_Keycode key, bool isPressed) {keyState[key] = isPressed;}
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
	bool gameOver = false;
	std::map<SDL_Keycode, bool> keyState; // Estado das teclas
	renderer Ren;
	SDL_Rect Square;
	SDL_Rect Pillar1;
	SDL_Rect Pillar2;
	                                                                                                       
	bool isRunning;                           
};                                                              