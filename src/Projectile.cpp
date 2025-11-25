#include "Projectile.hpp"

Projectile::Projectile(Projectile::Types t, GameFr::Vector2& target) : type(t), targetDirection(target), random(0, 1){}
