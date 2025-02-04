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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui_ImplSDL2_InitForSDLRenderer(Ren.getWindow(),Ren.getRenderer());
	ImGui_ImplSDLRenderer2_Init(Ren.getRenderer());
	ImGui::StyleColorsDark();
}


//clear and present the game
void game::update() {


	if (!gameOver) {
		Ren.clear();
		Ren.drawBorders();
		Ren.DrawPillars(&Pillar1, &Pillar2);
		Ren.drawSquare(&Square);
		Ren.DrawText(points1, 0);
		Ren.DrawText(points2, 1);
		moveSquare();
		points();
		movePillars();
		checkGameover();
		Ren.present();
	}
	else {
		gameOverOptions();
	}	
}

void game::gameOverOptions() {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Game Over",nullptr,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::Text("Jogo finalizado!");
	ImGui::Text("Pontuação Final - Player 1: %d | Player 2: %d", points1, points2);

	if (ImGui::Button("Novo Jogo")) {
		resetSquare();
		resetGame();
	}

	if (ImGui::Button("Sair")) {
		exit(0);
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), Ren.getRenderer());
	Ren.present();
}

//function to set the movements from the pillars int the y axis
void game::movePillars() {

	if (keyState[SDLK_w] && Pillar1.y > 0) {
		Pillar1.y -= 5 * speed;
	}
	if (keyState[SDLK_s] && Pillar1.y + Pillar1.h < 800) {
		Pillar1.y += 5 * speed;
	}
	if (keyState[SDLK_UP] && Pillar2.y > 0) {
		Pillar2.y -= 5 * speed;
	}
	if (keyState[SDLK_DOWN] && Pillar2.y + Pillar2.h < 800) {
		Pillar2.y += 5 * speed;
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
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type)
		{
		case (SDL_QUIT):
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			updateKeyState(event.key.keysym.sym, true);
			break;
		case SDL_KEYUP:
			updateKeyState(event.key.keysym.sym, false);
			break;
		default:
			break;
		}
		

	}
}

game::~game() {
	Ren.close();
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}