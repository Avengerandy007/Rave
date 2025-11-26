#include "Projectile.hpp"
#include "util/Globals.hpp"
#include <util/vectors.hpp>

ProjectileFactory::ProjectileFactory(){
	eventInterface.AssignQueue(Global::eventQueue);
}

void ProjectileFactory::Update(){
	const auto ev = eventInterface.Listen(GameFr::Event::Types::SHOOT);
	if (ev){
		Projectile project = Projectile((Projectile::Types)ev->dataPoint.additionalData[0], ev->dataPoint.position, ev->sender->position);
		projectileList.push_back(std::make_shared<Projectile>(project));
	}
}

Projectile::Projectile(const Projectile& other) : type(other.type), random(other.random){
	eventInterface = other.eventInterface;
	speed = other.speed;
	position = other.position;
	targetDirection = other.targetDirection;
	renderingPostion = other.renderingPostion;
}

Projectile::Projectile(const Projectile::Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition) : type(t), targetDirection(target), random(4, 7){
	position = startingPosition;
	speed = random.GetRandomNumber();
	targetDirection.Normalize();
}

void Projectile::Update(){
	Push(targetDirection, speed);
}
