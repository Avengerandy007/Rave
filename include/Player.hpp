#pragma once
#include "util/Texture.hpp"
#include "entities.hpp"
#include <camera.hpp>
#include "Decoration.hpp"
#include <chrono>
#include <util/vectors.hpp>

namespace GF = GameFr;

class GameManager;

class Player : public GF::Entity2D{
	std::chrono::system_clock::time_point lastShot;
	float speed = 8;
	Util::Texture texture;
	std::shared_ptr<GF::Camera2D> camera;
	void Move();
	void Collide();
	void Shoot();
	void StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other);
	void Died();

public:
	GF::Vector2 direction;
	void Update() override;
	Player();
	void SetTexture();
	void SetCamera(const std::shared_ptr<GameFr::Camera2D> cam);
};
