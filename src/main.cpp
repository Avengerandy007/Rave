#include "Player.hpp"
#include <raylib.h>

int main(){
	SetTargetFPS(60);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1000, 1000, "Rave");
	Player p;
	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(WHITE);
		p.Update();
		EndDrawing();
	}
	CloseWindow();
}
