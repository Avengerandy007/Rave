#include "Projectile.hpp"
#include <util/vectors.hpp>

Projectile::Projectile(Projectile::Types t, GameFr::Vector2& target, GameFr::Vector2& startingPosition) : type(t), targetDirection(target), random(4, 7){
	position = startingPosition;
	speed = random.GetRandomNumber();
	targetDirection.Normalize();
}

void Projectile::Update(){
	Push(targetDirection, speed);
}
