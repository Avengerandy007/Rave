#pragma once
#include "util/Texture.hpp"
#include <camera.hpp>
#include <chrono>
#include <entities.hpp>
#include <util/Randomizer.hpp>
#include <vector>

class Projectile : public GameFr::Entity2D{
public:
	enum struct Types;
	Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam);
	Projectile(const Projectile& other);
	void Update() override;
	const std::chrono::system_clock::time_point creationTime;
private:
	std::shared_ptr<Util::Texture> texture;
	const Types type;
	int speed;
	std::shared_ptr<GameFr::Camera2D> camera;
	GameFr::Randomizer random;
	GameFr::Vector2 targetDirection;
};

enum struct Projectile::Types{
	IDK1 = 0,
	IDK2 = 1,
	IDK3 = 2
};

class ProjectileFactory{
	GameFr::EventInterface eventInterface;
public:
	std::vector<std::shared_ptr<Projectile>> projectileList;
	ProjectileFactory();
	void Update();
};
