#include "Projectile.hpp"

Projectile::Projectile(Projectile::Types t, GameFr::Vector2& target) : type(t), targetPositon(target), random(0, 1){}
