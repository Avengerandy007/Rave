#include "GameManager.hpp"
#include "util/Globals.hpp"
#include "util/Texture.hpp"
#include "util/TextureArrays.hpp"

std::array<std::shared_ptr<Util::Texture>, 4> Util::TextureArrays::decorations;
std::array<std::shared_ptr<Util::Texture>, 2> Util::TextureArrays::enemies;
std::shared_ptr<GameFr::EventQueue> Global::eventQueue;
std::unique_ptr<GameManager> Global::game;

void InitTextureArrays(){
	namespace TA = Util::TextureArrays;
	TA::decorations = {
		std::make_shared<Util::Texture>("resources/Wall.png"),
		std::make_shared<Util::Texture>("resources/Player.png"),
		std::make_shared<Util::AnimatedTexture>("resources/Explosion.gif"),
		std::make_shared<Util::AnimatedTexture>("resources/PlayerShooting.gif")
	};
	TA::enemies = {
		std::make_shared<Util::Texture>("resources/Enemy.png"),
		std::make_shared<Util::Texture>("resources/Projectile.png")
	};
}

int main(){
	SetTargetFPS(60);
	InitWindow(GetScreenWidth(), GetScreenHeight(), "Rave");
	ToggleBorderlessWindowed();
	InitTextureArrays();
	Global::eventQueue = std::make_shared<GameFr::EventQueue>();
	Global::game = std::make_unique<GameManager>();
	Global::game->InitEntities();
	while (!WindowShouldClose()){
		Global::game->Update();
	}
	//unload all textures 
	for (auto& tex : Util::TextureArrays::decorations) tex->Unload();
	for (auto& tex : Util::TextureArrays::enemies) tex->Unload();
	CloseWindow();
}
