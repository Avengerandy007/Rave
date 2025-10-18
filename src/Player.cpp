#include "Player.hpp"
#include "raylib.h"
#include <iostream>

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
	AssignDimensionsToRenderingLibRect<float>(rect.x, rect.y, rect.width, rect.height);
	DrawTexture(texture.texture, position.X, position.Y, WHITE);
	std::cout << (int)position.X << " " << (int)position.Y << "\n";
}
