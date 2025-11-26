#include <entities.hpp>
#include <util/Randomizer.hpp>
#include <vector>

class Projectile : public GameFr::Entity2D{
public:
	enum struct Types;
	Projectile(const Types t, const GameFr::Vector2 target, const GameFr::Vector2 startingPosition);
	Projectile(const Projectile& other);
	void Update() override;
private:
	const Types type;
	int speed;
	GameFr::Randomizer random;
	GameFr::Vector2 targetDirection;
};

enum struct Projectile::Types{
	IDK1 = 0,
	IDK2 = 1,
	IDK3 = 2
};

class ProjectileFactory{
	GameFr::EventInterface eventInterface;
public:
	std::vector<std::shared_ptr<Projectile>> projectileList;
	ProjectileFactory();
	void Update();
};
