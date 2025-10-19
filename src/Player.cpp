#include "Player.hpp"
#include <iostream>
#include "raylib.h"
#include <camera.hpp>

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
	GetRenderingPosition(*camera);
	if (rect.x != position.X || rect.y != position.Y) AssignDimensionsToRenderingLibRect<float>(rect.x, rect.y, rect.width, rect.height);
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
	std::cout << (int)position.X << " " << (int)position.Y << "\n";
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}
