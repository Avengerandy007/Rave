#include "GameManager.hpp"
#include <camera.hpp>
#include "Enemy.hpp"
#include "Decoration.hpp"
#include <raylib.h>
#include <memory>

GameManager::GameManager() : player(std::make_shared<Player>()), camera(std::make_shared<GameFr::Camera2D>(GameFr::Camera2D::Modes::FOLLOW, player, GetScreenWidth(), GetScreenHeight())){
	for (auto& a : decorations.array){
		a = std::make_unique<Decoration>(camera);
	}
	for(auto& a : enemies.array){
		a = std::make_unique<Enemy>(player, camera);
	}
}


void GameManager::Update(){
	BeginDrawing();
	ClearBackground(WHITE);

	decorations.UpdateAll();
	player->Update();
	camera->Update();

	EndDrawing();
}

void GameManager::InitEntities(){
	player->SetCamera(camera);
}
