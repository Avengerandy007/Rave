#include "Player.hpp"
#include "raylib.h"

void Player::Move(){
	direction.X = 0;
	direction.Y = 0;
	if (IsKeyDown(KEY_A)){
		direction.X = -1;
	}if (IsKeyDown(KEY_S)){
		direction.Y = 1;
	}if (IsKeyDown(KEY_W)){
		direction.Y = -1;
	}if (IsKeyDown(KEY_D)){
		direction.X = 1;
	}
	Push(direction, speed);
}

void Player::Update(){
	Move();
	if (rect.x != position.X || rect.y != position.Y) AssignDimensionsToRenderingLibRect<float>(rect.x, rect.y, rect.width, rect.height);
	DrawTexture(texture.texture, position.X, position.Y, WHITE);
}
