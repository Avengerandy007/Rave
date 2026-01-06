#pragma once
#include "util/Texture.hpp"
#include <camera.hpp>
#include <chrono>
#include <cstdint>
#include <entities.hpp>
#include <util/Randomizer.hpp>
#include <util/vectors.hpp>
#include "Player.hpp"

class Projectile : public GameFr::Entity2D{ 
public:
	enum struct Types;
	enum struct Senders;
	Projectile();
	Projectile(const Projectile& other);
	void Update() override;
private:
	bool active;
	std::chrono::system_clock::time_point creationTime;
	std::shared_ptr<Util::Texture> texture;
	void Collide();
	void OnCollision();
	const std::shared_ptr<Player> player;
	Types type;
	Senders sender;
	float rotation;
	int speed;
	const std::shared_ptr<GameFr::Camera2D> camera;
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
	std::array<std::shared_ptr<Projectile>, 800> projectileList;
	ProjectileFactory();
	void OverrideProjectile(std::shared_ptr<Projectile>& projectile, const Projectile::Types type, const GameFr::Vector2 targetPos, const GameFr::Vector2 startPos, const Projectile::Senders senderType, const int p_speed);
	void Update();
};
