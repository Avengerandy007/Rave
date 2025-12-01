#include "Projectile.hpp"
#include "util/Globals.hpp"
#include "util/TextureArrays.hpp"
#include "GameManager.hpp"
#include <chrono>
#include <event.hpp>
#include <util/vectors.hpp>
#include <iostream>

ProjectileFactory::ProjectileFactory(){
	eventInterface.AssignQueue(Global::eventQueue);
}

void ProjectileFactory::Update(){
	auto ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
	while (ev){
		if (projectileList.size() >= 600) {
			projectileList.erase(projectileList.begin());
		}
		if (ev->dataPoint.additionalData[2] == 0)
			projectileList.emplace_back(std::make_shared<Projectile>((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera, (Projectile::Senders)ev->dataPoint.additionalData[1]));
		else
			projectileList.emplace_back(std::make_shared<Projectile>((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position, Global::game->camera, (Projectile::Senders)ev->dataPoint.additionalData[1], ev->dataPoint.additionalData[2]));
		ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
	}
	for (size_t i = 0; i < projectileList.size(); i++){
		auto& projectile = projectileList[i];
		if (std::chrono::system_clock::now() - projectile->creationTime >= std::chrono::seconds(5)){
			projectileList.erase(projectileList.begin() + i);
		}
		projectileList[i]->Update();
	}
}

Projectile::Projectile(const Projectile& other) : type(other.type), random(other.random), creationTime(other.creationTime), player(Global::game->player), sender(other.sender){
	eventInterface = other.eventInterface;
	camera = other.camera;
	speed = other.speed;
	position = other.position;
	targetDirection = other.targetDirection;
	renderingPostion = other.renderingPostion;
	texture = other.texture;
}

Projectile::Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam, const Senders send) : type(t), targetDirection(target), random(4, 7), creationTime(std::chrono::system_clock::now()), player(Global::game->player), sender(send){
	eventInterface.AssignQueue(Global::eventQueue);
	position = startingPosition;
	camera = cam;
	speed = random.GetRandomNumber();
	targetDirection.Normalize();
	texture = Util::TextureArrays::decorations[1];
}

Projectile::Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition, const std::shared_ptr<GameFr::Camera2D> cam, const Senders send, const int p_Speed) : type(t), targetDirection(target), random(4, 7), creationTime(std::chrono::system_clock::now()), player(Global::game->player), sender(send){
	eventInterface.AssignQueue(Global::eventQueue);
	position = startingPosition;
	camera = cam;
	speed = p_Speed;
	targetDirection.Normalize();
	texture = Util::TextureArrays::decorations[1];
}

void Projectile::Collide(){
	if (CollidingCircle(*player, 50) && sender != Senders::PLAYER){
		std::clog << "\n[" << std::chrono::system_clock::now() << "]: PLAYER COLLIDED WITH PROJECTILE\n";
		GameFr::Util::EventDataPoint data(position, {});
		GameFr::Event ev (GameFr::Event::Types::COLLISION, GetPtr(), player, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
	}
}

void Projectile::Update(){
	GetRenderingPosition(*camera);
	if (onScreen) DrawTexture(texture->texture, renderingPostion.X, renderingPostion.Y, WHITE);
	Collide();
	Push(targetDirection, speed);
}
