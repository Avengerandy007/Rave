#include "Player.hpp"
#include <raylib.h>

int main(){
	Player p;
	SetTargetFPS(60);
	InitWindow(500, 500, "HMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(WHITE);
		p.Update();
		EndDrawing();
	}
	CloseWindow();
}
