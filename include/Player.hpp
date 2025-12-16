#pragma once
#include "util/Texture.hpp"
#include "entities.hpp"
#include <camera.hpp>
#include "Decoration.hpp"
#include <chrono>
#include <cstdint>
#include <util/vectors.hpp>

namespace GF = GameFr;

class GameManager;

struct Gun{
	std::chrono::milliseconds firingSpeed;
	std::chrono::system_clock::time_point lastShot;
	uint8_t recoil;
	int projectileSpeed;
	uint8_t inaccuracy;
	uint8_t projectileType;
};

class Player : public GF::Entity2D{
	float speed = 8;
	float rotation;
	std::shared_ptr<Util::Texture> texture;
	std::shared_ptr<GF::Camera2D> camera;

	Gun gun;

	void Move();
	void Collide();
	void Shoot();
	void StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other);
	void Died();

public:
	GF::Vector2 direction;
	void Update() override;
	Player();
	void SetCamera(const std::shared_ptr<GameFr::Camera2D> cam);
};
