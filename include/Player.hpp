#pragma once
#include "util/Texture.hpp"
#include "entities.hpp"
#include <camera.hpp>
#include <memory>

namespace GF = GameFr;

class Player : public GF::Entity2D{
	float speed = 1;
	Util::Texture texture = Util::Texture("resources/Player.png");
	std::shared_ptr<GameFr::Camera2D> camera;
	void Move();
public:
	GF::Vector2 direction;
	void Update() override;
	void SetCamera(const std::shared_ptr<GameFr::Camera2D> cam);
};
