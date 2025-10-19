#pragma once
#include "util/Texture.hpp"
#include <camera.hpp>
#include <entities.hpp>
#include <memory>

class Decoration : public GameFr::Entity2D{
	const Util::Texture texture;
	const std::shared_ptr<GameFr::Camera2D> camera;
public:
	Decoration(const std::string texturePath, const std::shared_ptr<GameFr::Camera2D> cam);
	void Update() override;
};
