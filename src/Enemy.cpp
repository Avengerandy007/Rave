#include "Enemy.hpp"
#include <camera.hpp>
#include <event.hpp>
#include <memory>
#include "util/Globals.hpp"
#include "util/TextureArrays.hpp"
#include <raylib.h>
#include <util/vectors.hpp>

Enemy::Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam) : player(pl), random(2, 5){
	eventInterface.AssignQueue(Global::eventQueue);
	speed = random.GetRandomNumber();
	camera = cam;
	random.ChangeRange(pl->position.X - GetScreenWidth(), pl->position.X);
	position.X = random.GetRandomNumber();
	random.ChangeRange(pl->position.Y - GetScreenHeight(), pl->position.Y);
	position.Y = random.GetRandomNumber();
	texture = Util::TextureArrays::enemies[0];
}

void Enemy::Collide(){

	//detect collisions with player
	if (CollidingCircle(*player, 50)){
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
	
}

void Enemy::StopMovementBasedOnDirection(const std::shared_ptr<const Decoration> other){
	if (other->position.X < position.X && direction.X == -1) direction.X = 0;
	else if (other->position.X > position.X && direction.X == 1) direction.X = 0;
	if (other->position.Y < position.Y && direction.Y == -1) direction.Y = 0;
	else if (other->position.Y > position.Y && direction.Y == 1) direction.Y = 0;
}

void Enemy::Move(){
	if (player->position.X > position.X){
		direction.X = 1;
	}else if (player->position.X < position.X){
		direction.X = -1;
	}
	if (player->position.Y > position.Y){
		direction.Y = 1;
	}else if (player->position.Y < position.Y){
		direction.Y = -1;
	}
}

void Enemy::ShootAtPlayer(){
	random.ChangeRange(0, 50);
	if (random.GetRandomNumber() == 1){
		GameFr::Util::EventDataPoint data(GameFr::Vector2::GetDiference(player->position, position), {0});
		GameFr::Event ev(GameFr::Event::Types::SHOOT, GetPtr(), nullptr, data);
		eventInterface.queue->CreateEvent(std::make_shared<const GameFr::Event>(ev));
	}
}

void Enemy::Update(){
	GetRenderingPosition(*camera);
	if (onScreen) DrawTexture(texture->texture, renderingPostion.X, renderingPostion.Y, WHITE);
	Move();
	Collide();
	Push(direction, speed);
	ShootAtPlayer();
}
