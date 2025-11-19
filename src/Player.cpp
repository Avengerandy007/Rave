#include "Player.hpp"
#include "raylib.h"
#include <camera.hpp>
#include <entities.hpp>
#include <event.hpp>
#include <util/vectors.hpp>
#include "Decoration.hpp"
#include "util/Globals.hpp"
#include <iostream>

Player::Player(){
	std::cout << "Befor event interface\n";
	eventInterface.AssignQueue(std::make_shared<GameFr::EventQueue>(Global::eventQueue)); 
	std::cout << "After event interface\n";
}

void Player::SetTexture(){
	texture.Assign("resources/Player.png");
}

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
	if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 5;
	else speed = 1;

	Push(direction, speed);
}

void Player::Update(){
	Move();
	GetRenderingPosition(*camera);
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}
