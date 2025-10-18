#include "raylib.h"
#include "util/Texture.hpp"
#include "entities.hpp"

namespace GF = GameFr;

class Player : GF::Entity2D{
	Rectangle rect;
	GF::Vector2 direction;
	float speed = 5;
	Util::Texture texture = Util::Texture("Player.png");
	void Move();
public:
	void Update() override;
};
