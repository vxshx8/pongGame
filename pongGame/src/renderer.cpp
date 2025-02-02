#include "../headers/renderer.h"


//create the main window for the game
void renderer::createWindow(const char* title, int width, int height) {
	h = height;
	w = width;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << " cannot init SDL: " << SDL_GetError() << "\n";
		return;
	}

	if (TTF_Init() == -1) {
		std::cout << " connot init SDL_TTF: " << TTF_GetError() << "\n";
		return;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << " connot create window: " << SDL_GetError() << "\n";
		return;
	}

	Renderer = SDL_CreateRenderer(window, -1, 0);
	if (!Renderer) {
		std::cout << " connot create a renderer: " << SDL_GetError() << "\n";
		return;
	}

}


//draw the midle stripe and the borders in white color
void renderer::drawBorders() {
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_Rect top = { 0, 0,w,10 };
	SDL_Rect bottom = { 0, w -10,w,10 };
	SDL_Rect left = { 0, 0,10,h };
	SDL_Rect right = { w -10, 0,10,h };

	SDL_Rect stripe = { w / 2 ,20,10,20 };
	for (int a =stripe.y;a <= 800;a += 40) {
		SDL_RenderFillRect(Renderer, &stripe);
		stripe.y = a;
	}

	SDL_RenderFillRect(Renderer, &top);
	SDL_RenderFillRect(Renderer, &bottom);
	SDL_RenderFillRect(Renderer, &left);
	SDL_RenderFillRect(Renderer, &right);
}

//draw the points table on the screen position 0 is left and 1 right
void renderer::DrawText(int point,int position) {
	//convert the int point to string
	std::string points = std::to_string(point);
	
	

	TTF_Font* font = TTF_OpenFont(fontPath.string().c_str(), 32);
	
	if (!font) {
		std::cout << "cannot load the TTF_FONT: " << TTF_GetError() << "\n";
		return;
	}
	
	SDL_Surface* surfaceText = TTF_RenderText_Solid(font, points.c_str(), {255,255,255});
	if (!surfaceText) {
		std::cout << "cannot create surface for text: " << TTF_GetError() << "\n";
		TTF_CloseFont(font);
		return;
	}


	SDL_Texture* textureText = SDL_CreateTextureFromSurface(Renderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	if (!textureText) {
		std::cout << "cannot create texture from surface: " << SDL_GetError() << "\n";
		TTF_CloseFont(font);
		return;
	}
	SDL_Rect destiny;
	if (position == 0) {
		destiny = { (w / 10) * 3, (h/10),100,100 };
	}
	else {
		destiny ={ (w / 10) * 6, (h / 10) ,100,100 };
	}
	SDL_RenderCopy(Renderer, textureText, NULL, &destiny);
	SDL_DestroyTexture(textureText);
	TTF_CloseFont(font);
}

//function to draw the player pillars 
void renderer::DrawPillars(SDL_Rect *P1,SDL_Rect *P2) {
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Renderer, P1);
	SDL_RenderFillRect(Renderer, P2);
	
}

//draw and set square configs
void renderer::drawSquare(SDL_Rect* square) {
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Renderer, square);
	
}

//clear the renderer with the selected color
void renderer::clear() {
	SDL_SetRenderDrawColor(Renderer,0, 0, 0, 255);
	SDL_RenderClear(Renderer);
}

//present the window with the new data of the renderer 
void renderer::present() {
	SDL_RenderPresent(Renderer);
}

//quit fro sdl and TTf libs when the program is over
void renderer::close() {
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
}