#pragma once
#include "util/Texture.hpp"
#include <camera.hpp>
#include <chrono>
#include <cstdint>
#include <entities.hpp>
#include <util/Randomizer.hpp>
#include "Player.hpp"

class Projectile : public GameFr::Entity2D{ public:
	enum struct Types;
	enum struct Senders;
	Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam, const Senders send);
	Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam, const Senders send, const int p_Speed);
	Projectile(const Projectile& other);
	void Update() override;
private:
	const std::chrono::system_clock::time_point creationTime;
	std::shared_ptr<Util::Texture> texture;
	void Collide();
	void OnCollision();
	const std::shared_ptr<Player> player;
	const Types type;
	const Senders sender;
	float rotation;
	int speed;
	std::shared_ptr<GameFr::Camera2D> camera;
	GameFr::Randomizer random;
	GameFr::Vector2 targetDirection;
	friend class ProjectileFactory;
};

enum struct Projectile::Types{
	NORMAL = 0,
	EXPLOSIVE = 1,
	IDK = 2
};

enum struct Projectile::Senders{
	ENEMY = 0,
	PLAYER = 1,
};

class ProjectileFactory{
	GameFr::EventInterface eventInterface;
	uint16_t headPtr; 	//used to indicate the newest addition to the queue
public:
	//std::vector<std::shared_ptr<Projectile>> projectileList;
	std::array<std::shared_ptr<Projectile>, 750> projectileList;
	ProjectileFactory();
	void Update();
};
