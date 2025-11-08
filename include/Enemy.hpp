#pragma once
#include "entities.hpp"
#include "util/Texture.hpp"
#include "util/Randomizer.hpp"
#include "Player.hpp"
#include "util/TextureArrays.hpp"
#include <camera.hpp>
#include <memory>

class Enemy : public GameFr::Entity2D{
	GameFr::Vector2 direction;	
	int speed = 1;
	std::shared_ptr<Util::Texture> texture = Util::TextureArrays::decorations[1];
	GameFr::Randomizer random;
	const std::shared_ptr<Player> player;
	std::shared_ptr<GameFr::Camera2D> camera;
public:
	Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam);
	void Update() override;
};
