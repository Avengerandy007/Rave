#include "Player.hpp"
#include "Decoration.hpp"
#include "util/Globals.hpp"
#include <iostream>
#include <memory>

Player::Player(){
	eventInterface.AssignQueue(Global::eventQueue); 
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

void Player::Collide(){
	const std::shared_ptr<const GameFr::Event> ev = eventInterface.Listen(GetPtr());

	if (!ev) {
		return;
	}

	if (ev->type == GameFr::Event::Types::COLLISION){
		std::cout << "COLLIDED\n";
		auto sender = std::dynamic_pointer_cast<const Decoration>(ev->sender);
		if (sender){
			std::cout << "COLLIDED WITH DECORATION\n";
			texture.Assign("resources/Wall.png");
		}
	}
}

void Player::Update(){
	Move();
	GetRenderingPosition(*camera);
	Collide();
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}
