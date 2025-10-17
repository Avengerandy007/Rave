#include "Player.hpp"

void Player::Update(){
	AssignDimensionsToRenderingLibRect(rect.x, rect.y, rect.width, rect.height);
	Move();
}
