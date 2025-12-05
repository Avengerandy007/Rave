#pragma once
#include "camera.hpp"
#include "Player.hpp"
#include "util/ObjectArray.hpp"
#include "util/Globals.hpp"
#include "Projectile.hpp"
#include "util/collisionManager.hpp"
#include <event.hpp>
#include <memory>

class GameManager{
	GameFr::EventInterface eventInterface;
	void ListenForEvents();
	void SetObjectArrays();
public:
	std::shared_ptr<Player> player;
	std::shared_ptr<GameFr::Camera2D> camera;
	Util::ObjectArray<Global::nrOfDecorations> decorations;
	Util::ObjectArray<Global::nrOfEnemies> enemies;
	ProjectileFactory projectileFactory;
	void Update();
	GameManager();
	void InitEntities();
};
