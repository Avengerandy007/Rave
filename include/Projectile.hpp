#include <entities.hpp>
#include <util/Randomizer.hpp>

class ProjectileFactory{
	GameFr::EventInterface eventInterface;
	void Update();
};

class Projectile : public GameFr::Entity2D{
	enum struct Types;
	const Types type;
	int speed;
	GameFr::Randomizer random;
	GameFr::Vector2 targetDirection;
	Projectile(Types t, GameFr::Vector2& target, GameFr::Vector2& position);
	void Update() override;
};

enum struct Projectile::Types{
	IDK1,
	IDK2,
	IDK3
};
