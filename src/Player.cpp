#include "Player.hpp"
#include "Decoration.hpp"
#include "Enemy.hpp"
#include "util/Globals.hpp"
#include <chrono>
#include <event.hpp>
#include <memory>
#include "Projectile.hpp"
#include "util/TextureArrays.hpp"
#include <raylib.h>
#include <util/vectors.hpp>

Player::Player(){
	eventInterface.AssignQueue(Global::eventQueue); 
	width = 200;
	height = 100;
	texture = Util::TextureArrays::decorations[1];
}

void Player::Move(){
	direction.X = 0;
	direction.Y = 0;
	rotation = 0;
	if (IsKeyDown(KEY_A)){
		direction.X = -1;
		rotation = 0;
	}if (IsKeyDown(KEY_S)){
		direction.Y = 1;
		rotation = 90;
	}if (IsKeyDown(KEY_W)){
		direction.Y = -1;
		rotation = 90;
	}if (IsKeyDown(KEY_D)){
		direction.X = 1;
		rotation = 0;
	}
	if (direction.Magnitude() != 1 && direction.Magnitude() != 0){
		rotation = (direction.X * direction.Y <= 0) ? -45 : 45;
	}
	if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 10;
	else if (IsKeyDown(KEY_LEFT_CONTROL)) speed = 4;
	else if (speed != 8) speed = 8;
}

void Player::StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other){
	if (other->position.X < position.X && direction.X == -1) direction.X = 1;
	else if (other->position.X > position.X && direction.X == 1) direction.X = -1;
	if (other->position.Y < position.Y && direction.Y == -1) direction.Y = 1;
	else if (other->position.Y > position.Y && direction.Y == 1) direction.Y = -1;
}

void Player::Shoot(){
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && std::chrono::system_clock::now() - gun.lastShot >= gun.firingSpeed){
		GameFr::Vector2 mousePosition(GetMouseX(), GetMouseY());
		GameFr::Vector2 projectileDirection(camera->position.X + mousePosition.X - position.X, camera->position.Y + mousePosition.Y - position.Y); //Convert from camera's cartesian system to game and then get vector connecting them
		GameFr::Util::EventDataPoint data(projectileDirection, {(int)gun.projectileType, (int)Projectile::Senders::PLAYER, gun.projectileSpeed});
		GameFr::Event ev(GameFr::Event::Types::SHOOT, GetPtr(), nullptr, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
		gun.lastShot = std::chrono::system_clock::now();
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
		DrawTexturePro(texture->texture, (Rectangle){0, 0, (float)width, (float)height}, (Rectangle){renderingPosition.X, renderingPosition.Y, (float)width, (float)height}, Vector2((float)width / 2, (float)height / 2), rotation, WHITE);
	}
}

void Player::SetCamera(const std::shared_ptr<GameFr::Camera2D> cam){
	camera = cam;
}
