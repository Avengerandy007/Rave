#include "Player.hpp"
#include "Decoration.hpp"
#include "Enemy.hpp"
#include "util/Globals.hpp"
#include <memory>
#include <iostream>

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
	if (IsKeyDown(KEY_LEFT_SHIFT) && speed != 5) speed = 5;
	else if (speed != 1) speed = 1;
}

void Player::StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other){
	if (other->position.X < position.X && direction.X == -1) direction.X = 0;
	else if (other->position.X > position.X && direction.X == 1) direction.X = 0;
	if (other->position.Y < position.Y && direction.Y == -1) direction.Y = 0;
	else if (other->position.Y > position.Y && direction.Y == 1) direction.Y = 0;
}

void Player::Died(){
	std::cout << "You died\n";
}

void Player::Collide(){
	std::shared_ptr<const GameFr::Event> ev = eventInterface.Listen(GetPtr());
	if (!ev) return;
	do{
		if (ev->type == GameFr::Event::Types::COLLISION){
			//check collisions with decorations
			{
				auto sender = std::dynamic_pointer_cast<const Decoration>(ev->sender);
				if (sender){
					StopMovementBasedOnDirection(sender);
				}
			}
			
			//check collisions with enemies
			{
				auto sender = std::dynamic_pointer_cast<const Enemy>(ev->sender);
				if (sender){
					Died();
				}
			}
		}
		ev = eventInterface.Listen(GetPtr());
	} while(ev);
}

void Player::Update(){
	Move();
	GetRenderingPosition(*camera);
	Collide();
	Push(direction, speed);
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}
