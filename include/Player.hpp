#include "raylib.h"
#include "entities.hpp"

namespace GF = GameFr;

class Player : GF::Entity2D{
	Rectangle rect;
	GF::Vector2 direction;
	void Move();
public:
	void Update() override;
};
