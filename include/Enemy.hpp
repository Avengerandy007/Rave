#pragma once
#include "Player.hpp"
#include <chrono>

class Enemy : public GameFr::Entity2D{
	int speed = 1;
	GameFr::Vector2 direction;

	std::shared_ptr<Util::Texture> texture;
	GameFr::Randomizer random;
	const std::shared_ptr<Player> player;
	std::shared_ptr<GameFr::Camera2D> camera;

	void Collide();
	void StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other);
	void ShootAtPlayer();

	std::chrono::seconds shootInterval;
	std::chrono::system_clock::time_point lastShot;
public:
	Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam);
	void Respawn();
	void Update() override;
	void Move();
};
