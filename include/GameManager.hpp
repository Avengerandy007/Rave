#pragma once
#include "camera.hpp"
#include "Player.hpp"
#include "util/ObjectArray.hpp"
#include "util/Globals.hpp"
#include <memory>

class GameManager{
public:
	std::shared_ptr<Player> player;
	std::shared_ptr<GameFr::Camera2D> camera;
	Util::ObjectArray<Global::nrOfDecorations> decorations;
	Util::ObjectArray<Global::nrOfEnemies> enemies;
	void Update();
	GameManager();
	void InitEntities();
};
