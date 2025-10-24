#include "GameManager.hpp"
#include <camera.hpp>
#include "Decoration.hpp"
#include <memory>

GameManager::GameManager() : player(std::make_shared<Player>()), camera(std::make_shared<GameFr::Camera2D>(GameFr::Camera2D::Modes::FOLLOW, player, 1000, 1000)){
	for (auto& a : decorations.array){
		a = std::make_unique<Decoration>("/home/andrei/Projects/Pacman/Game/resources/Wall.png", camera);
	}
}


void GameManager::Update(){
	decorations.UpdateAll();
	player->Update();
	camera->Update();
}
