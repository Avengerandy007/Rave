#include "Enemy.hpp"
#include <camera.hpp>
#include <memory>
#include "util/TextureArrays.hpp"
#include <raylib.h>

Enemy::Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam) : player(pl), random(2, 5){
	speed = random.GetRandomNumber();
	camera = cam;
	random.ChangeRange(pl->position.X - GetScreenWidth(), pl->position.X);
	position.X = random.GetRandomNumber();
	random.ChangeRange(pl->position.Y - GetScreenHeight(), pl->position.Y);
	position.Y = random.GetRandomNumber();
	texture = Util::TextureArrays::enemies[0];
}

void Enemy::Move(){
	if (player->position.X > position.X){
		position.X += speed;
	}else if (player->position.X < position.X){
		position.X -= speed;
	}
	if (player->position.Y > position.Y){
		position.Y += speed;
	}else if (player->position.Y < position.Y){
		position.Y -= speed;
	}
}

void Enemy::Update(){
	GetRenderingPosition(*camera);
	if (onScreen) DrawTexture(texture->texture, renderingPostion.X, renderingPostion.Y, WHITE);
	Move();
}
