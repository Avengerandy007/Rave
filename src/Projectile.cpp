#include "Projectile.hpp"

Projectile::Projectile(Projectile::Types t, GameFr::Vector2& target) : type(t), targetDirection(target), random(4, 7){
	speed = random.GetRandomNumber();
	targetDirection.Normalize();
}

void Projectile::Update(){
	Push(targetDirection, speed);
}
