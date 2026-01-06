#pragma once
#include "util/Texture.hpp"
#include "entities.hpp"
#include <camera.hpp>
#include "Decoration.hpp"
#include <chrono>
#include <cstdint>
#include <util/vectors.hpp>

namespace GF = GameFr;

class GameManager;
namespace Weapons{
	struct Upgrade{
		std::chrono::milliseconds firingSpeed;
		uint8_t recoil;
		int projectileSpeed;
		int8_t inaccuracy;
		uint8_t projectileType;
		Upgrade();
	private:	
		GameFr::Randomizer random;
	};

	struct Gun{
		std::chrono::milliseconds firingSpeed;
		std::chrono::system_clock::time_point lastShot;
		uint8_t recoil;
		int projectileSpeed;
		float inaccuracy;
		uint8_t projectileType;
		void ApplyUpgrade(const Upgrade& up);
	};
}

class Player : public GF::Entity2D{
	float speed = 8;
	float rotation;
	std::shared_ptr<Util::Texture> texture;
	std::shared_ptr<GF::Camera2D> camera;
	bool playShootingAnimation;


	void Move();
	void Collide();
	void Shoot();
	void StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other); //don't allow player to move if colliding with object in movement direction
	void Died(); //Create a PLAYER_DEATH event to handle in GameManager
	void RotateTexture();

public:
	GF::Vector2 direction;
	void Update() override;
	Weapons::Gun gun;
	uint32_t killCount;
	Player();
	void SetCamera(const std::shared_ptr<GameFr::Camera2D> cam);
};
