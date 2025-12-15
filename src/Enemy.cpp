#include "Enemy.hpp"
#include <camera.hpp>
#include <chrono>
#include <event.hpp>
#include <memory>
#include "Projectile.hpp"
#include "util/Globals.hpp"
#include "util/TextureArrays.hpp"
#include <raylib.h>
#include <util/GFmath.hpp>
#include <util/vectors.hpp>

Enemy::Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam) : player(pl), random(5, 12){
	eventInterface.AssignQueue(Global::eventQueue);
	camera = cam;
	Respawn();
	texture = Util::TextureArrays::enemies[0];
}

void Enemy::Respawn(){
	random.ChangeRange(5, 12);
	speed = random.GetRandomNumber();
	random.ChangeRange(0, 1);
	if (random.GetRandomNumber() == 1){
		random.ChangeRange(player->position.X - GetScreenWidth(), player->position.X - (float)GetScreenWidth() / 2);
	}else{
		random.ChangeRange(player->position.X + (float)GetScreenWidth() / 2, player->position.X + GetScreenWidth());
	}
	position.X = random.GetRandomNumber();
	random.ChangeRange(0, 1);
	if (random.GetRandomNumber() == 1){
		random.ChangeRange(player->position.Y - GetScreenHeight(), player->position.Y - (float)GetScreenHeight() / 2);
	}else{
		random.ChangeRange(player->position.Y + (float)GetScreenHeight() / 2, player->position.Y + GetScreenHeight());
	}
	position.Y = random.GetRandomNumber();

	random.ChangeRange(1, 10);
	shootInterval = std::chrono::seconds(random.GetRandomNumber());
}

void Enemy::Collide(){

	//detect collisions with player
	if (CollidingCircle(*player, 100)){
		GameFr::Util::EventDataPoint data(position, {});
		GameFr::Event ev(GameFr::Event::Types::COLLISION, GetPtr(), player, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
	}

	const std::shared_ptr<const GameFr::Event> ev = eventInterface.Listen(GetPtr());
	if (!ev) return;
	//check if sender is of type Decoration
	{
		const std::shared_ptr<const Decoration> sender = std::dynamic_pointer_cast<const Decoration>(ev->sender);
		if (sender){
			StopMovementBasedOnDirection(sender);
			return;
		}
	}
	//check if sender is projectile
	{
		const std::shared_ptr<const Projectile> sender = std::dynamic_pointer_cast<const Projectile>(ev->sender);
		if (sender){
			Respawn();
		}
	}

}

void Enemy::StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other){
	if (other->position.X < position.X && direction.X < 0) direction.X = 4;
	else if (other->position.X > position.X && direction.X > 0) direction.X = -4;
	if (other->position.Y < position.Y && direction.Y < 0) direction.Y = 4;
	else if (other->position.Y > position.Y && direction.Y > 0) direction.Y = -4;
}

void Enemy::Move(){
	{
		GameFr::Vector2 cp = player->position;
		cp.Normalize();
		if (direction == cp) return;
	}
	direction.X = player->position.X - position.X;
	direction.Y = player->position.Y - position.Y;
	direction.Normalize();
}

void Enemy::ShootAtPlayer(){
	if (std::chrono::system_clock::now() - lastShot >= shootInterval){
		GameFr::Util::EventDataPoint data(GameFr::Vector2::GetDiference(player->position, position), {0});
		GameFr::Event ev(GameFr::Event::Types::SHOOT, GetPtr(), nullptr, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
		lastShot = std::chrono::system_clock::now();
	}
}

void Enemy::Update(){
	GetRenderingPosition(*camera);
	if (onScreen) DrawTexture(texture->texture, renderingPosition.X, renderingPosition.Y, WHITE);
	Move();
	Collide();
	Push(direction, speed);
	ShootAtPlayer();
	if (GameFr::Vector2::GetDistance(position, player->position) >= GameFr::Util::Math::Pythagorean(GetScreenHeight(), GetScreenWidth())){
		Respawn();
	}
}
