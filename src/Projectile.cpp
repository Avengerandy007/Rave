#include "Projectile.hpp"
#include "util/Globals.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"
#include <chrono>
#include <util/vectors.hpp>
#include <iostream>

ProjectileFactory::ProjectileFactory(){
	eventInterface.AssignQueue(Global::eventQueue);
}

void ProjectileFactory::Update(){
	auto ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
	while (ev){
		Projectile project = Projectile((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera);
		projectileList.push_back(std::make_shared<Projectile>(project));

		for (size_t i = 0; i < projectileList.size(); i++){
			auto& projectile = projectileList[i];
			projectile->Update();
			if (std::chrono::system_clock::now() - projectile->creationTime >= std::chrono::seconds(10)){
				projectileList.erase(projectileList.begin() + i);
			}
		}

		if (projectileList.size() >= 10000) projectileList.clear();
		ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
	}
}

Projectile::Projectile(const Projectile& other) : type(other.type), random(other.random), creationTime(other.creationTime){
	eventInterface = other.eventInterface;
	camera = other.camera;
	speed = other.speed;
	position = other.position;
	targetDirection = other.targetDirection;
	renderingPostion = other.renderingPostion;
	texture = other.texture;
}

Projectile::Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam) : type(t), targetDirection(target), random(4, 7), creationTime(std::chrono::system_clock::now()){
	position = startingPosition;
	camera = cam;
	speed = random.GetRandomNumber();
	targetDirection.Normalize();
	texture = Util::TextureArrays::decorations[1];
	std::cout << "[" << creationTime << "]: CREATED PROJECTILE\n";
	
}

void Projectile::Update(){
	GetRenderingPosition(*camera);
	if (onScreen) DrawTexture(texture->texture, renderingPostion.X, renderingPostion.Y, WHITE);
	Push(targetDirection, speed);
}
