#include "Player.hpp"
#include "Decoration.hpp"
#include "Enemy.hpp"
#include "util/Globals.hpp"
#include <chrono>
#include <event.hpp>
#include <memory>
#include "Projectile.hpp"
#include <raylib.h>
#include <util/vectors.hpp>

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
	if (IsKeyDown(KEY_LEFT_SHIFT) && speed != 5) speed = 8;
	else if (speed != 1) speed = 1;
}

void Player::StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other){
	if (other->position.X < position.X && direction.X == -1) direction.X = 0;
	else if (other->position.X > position.X && direction.X == 1) direction.X = 0;
	if (other->position.Y < position.Y && direction.Y == -1) direction.Y = 0;
	else if (other->position.Y > position.Y && direction.Y == 1) direction.Y = 0;
}

void Player::Shoot(){
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && std::chrono::system_clock::now() - lastShot >= std::chrono::milliseconds(500)){
		GameFr::Vector2 mousePosition(GetMouseX(), GetMouseY());
		GameFr::Vector2 projectileDirection(camera->position.X + mousePosition.X - position.X, camera->position.Y + mousePosition.Y - position.Y); //Convert from camera's cartesian system to game and then get vector connecting them
		GameFr::Util::EventDataPoint data(projectileDirection, {0, (int)Projectile::Senders::PLAYER, 20});
		GameFr::Event ev(GameFr::Event::Types::SHOOT, GetPtr(), nullptr, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
		lastShot = std::chrono::system_clock::now();
	}
}

void Player::Died(){
	GameFr::Util::EventDataPoint data (position, {});
	GameFr::Event ev(GameFr::Event::Types::PLAYER_DEATH, GetPtr(), nullptr, data);
	eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
}

void Player::Collide(){
	std::shared_ptr<const GameFr::Event> ev = eventInterface.Listen(GetPtr());
	while(ev){
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
			//check collisions with projectiles
			{
				auto sender = std::dynamic_pointer_cast<const Projectile>(ev->sender);
				if (sender){
					Died();
				}
			}
		}
		ev = eventInterface.Listen(GetPtr());
	}
}

void Player::Update(){
	Move();
	GetRenderingPosition(*camera);
	Collide();
	Push(direction, speed);
	Shoot();
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}
