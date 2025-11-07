#pragma once
#include "util/Texture.hpp"
#include "util/Randomizer.hpp"
#include "Player.hpp"
#include <camera.hpp>
#include <entities.hpp>
#include <memory>

class Decoration : public GameFr::Entity2D{
	std::shared_ptr<Util::Texture> texture;
	std::shared_ptr<GameFr::Camera2D> camera;
	std::shared_ptr<Player> player;
	//Moves this to the front of the player so they can see it again
	void Regenerate();
	GameFr::Randomizer random;
public:
	Decoration(const std::shared_ptr<GameFr::Camera2D> cam);
	void Update() override;
};
