#include "raylib.h"
#include "entities.hpp"

namespace GF = GameFr;

class Player : GF::Entity2D{
	Rectangle rect;
	GF::Vector2 direction;
	uint8_t speed;
	void Move();
public:
	void Update() override;
};
