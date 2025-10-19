#pragma once
#include "util/Texture.hpp"
#include "entities.hpp"
#include <camera.hpp>
#include <memory>

namespace GF = GameFr;

class Player : public GF::Entity2D{
	GF::Vector2 direction;
	float speed = 1;
	Util::Texture texture = Util::Texture("Player.png");
	std::shared_ptr<GameFr::Camera2D> camera;
	void Move();
public:
	void Update() override;
	void SetCamera(const std::shared_ptr<GameFr::Camera2D> cam);
};
