#pragma once
#include "camera.hpp"
#include "Player.hpp"
#include "Decoration.hpp"
#include <array>
#include <memory>

class GameManager{
public:
	std::shared_ptr<Player> player;
	std::shared_ptr<GameFr::Camera2D> camera;
	Decoration deco = Decoration("/home/andrei/Projects/Pacman/Game/resources/Wall.png", camera);
	void Update();
	GameManager();
};
