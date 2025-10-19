#pragma once
#include "camera.hpp"
#include "Player.hpp"
#include <memory>

class GameManager{
public:
	std::shared_ptr<Player> player;
	std::shared_ptr<GameFr::Camera2D> camera;
	GameManager();
};
