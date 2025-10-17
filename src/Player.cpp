#include "Player.hpp"
#include "raylib.h"
#include <iostream>

void Player::Move(){
	speed = 0;
	switch(GetKeyPressed()){
		case KEY_A:
			direction.X = -1;
		case KEY_S:
			direction.Y = 1;
		case KEY_W:
			direction.Y = -1;
		case KEY_D:
			direction.X = 1;
		default:
			speed = 1;
	}
	Push(direction, speed);
}

void Player::Update(){
	AssignDimensionsToRenderingLibRect(rect.x, rect.y, rect.width, rect.height);
	Move();
	std::cout << position.X << " " << position.Y << "\n";
}
