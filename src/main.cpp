#include "Player.hpp"
#include <raylib.h>

int main(){
	SetTargetFPS(60);
	InitWindow(500, 500, "HMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
	Player p;
	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(WHITE);
		p.Update();
		EndDrawing();
	}
	CloseWindow();
}
