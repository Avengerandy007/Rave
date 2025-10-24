#pragma once
#include "util/Texture.hpp"
#include "util/Randomizer.hpp"
#include <camera.hpp>
#include <entities.hpp>
#include <memory>

class Decoration : public GameFr::Entity2D{
	Util::Texture texture;
	std::shared_ptr<GameFr::Camera2D> camera;
	void Regenerate();
	GameFr::Randomizer random;
public:
	Decoration(const std::string texturePath, const std::shared_ptr<GameFr::Camera2D> cam);
	void Update() override;
};
