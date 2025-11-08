#include "util/Texture.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"
#include <raylib.h>

std::array<std::shared_ptr<Util::Texture>, 2> Util::TextureArrays::decorations;
std::array<std::shared_ptr<Util::Texture>, 1> Util::TextureArrays::enemies;

void InitTextureArrays(){
	namespace TA = Util::TextureArrays;
	TA::decorations = {
		std::make_shared<Util::Texture>("resources/Wall.png"),
		std::make_shared<Util::Texture>("resources/Player.png")
	};
	TA::enemies = {
		std::make_shared<Util::Texture>("resources/Ghost.png")
	};
}

int main(){
	SetTargetFPS(60);
	InitWindow(GetScreenWidth(), GetScreenHeight(), "Rave");
	ToggleBorderlessWindowed();
	InitTextureArrays();
	GameManager game;
	game.InitEntities();
	while (!WindowShouldClose()){
		game.Update();
	}
	CloseWindow();
}
