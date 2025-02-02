#pragma once
#include "SDL2/SDL.h"
#include "TTF/SDL_ttf.h"

#include <iostream>
#include <string>
#include <filesystem>


class renderer {
public:

	void createWindow(const char* title, int width, int height);
	void clear();
	void present();
	void close();
	void drawBorders();
	void DrawPillars(SDL_Rect* Pillar1, SDL_Rect* Pillar2);
	void drawSquare(SDL_Rect* square);
	void DrawText(int point, int position);
private:
	
	int h, w;
	//get the absolut path to the font
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::filesystem::path fontPath = currentPath / "assets" / "fonts" / "8bitOperatorPlus8-Regular.ttf";
	
	//const color for the text font
	SDL_Color fontColor = { 255,255,255 };
	
	SDL_Window* window = nullptr;
	SDL_Renderer* Renderer = nullptr;


};
