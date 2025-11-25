#include <entities.hpp>
#include <util/Randomizer.hpp>

class Projectile : public GameFr::Entity2D{
	enum struct Types;
	const Types type;
	int speed;
	GameFr::Randomizer random;
	const GameFr::Vector2 targetPositon;
	Projectile(Types t, GameFr::Vector2& target);
};

enum struct Projectile::Types{
	IDK1,
	IDK2,
	IDK3
};
