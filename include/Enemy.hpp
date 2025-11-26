#pragma once
#include "Player.hpp"

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
public:
	Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam);
	void Update() override;
	void Move();
};
