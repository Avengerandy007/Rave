#include "util/Texture.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"
#include <raylib.h>

std::array<std::shared_ptr<Util::Texture>, 2> Util::TextureArrays::decorations;

void InitTextureArrays(){
	namespace TA = Util::TextureArrays;
	TA::decorations = {std::make_shared<Util::Texture>("/home/andrei/Projects/Pacman/Game/resources/Wall.png")};
}

int main(){
	SetTargetFPS(60);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1000, 1000, "Rave");
	InitTextureArrays();
	GameManager game;
	game.InitEntities();
	while (!WindowShouldClose()){
		game.Update();
	}
	CloseWindow();
}
