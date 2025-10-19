#include "GameManager.hpp"
#include <raylib.h>

int main(){
	SetTargetFPS(60);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1000, 1000, "Rave");
	GameManager game;
	game.player->SetCamera(game.camera);
	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(WHITE);
		game.camera->Update();
		game.player->Update();
		EndDrawing();
	}
	CloseWindow();
}
