#include <entities.hpp>
#include <util/Randomizer.hpp>

class Projectile : public GameFr::Entity2D{
	enum struct Types;
	Types type;
	int speed;
	GameFr::Randomizer random;
	GameFr::Vector2 targetPositon;
};

enum struct Projectile::Types{
	IDK1,
	IDK2,
	IDK3
};
