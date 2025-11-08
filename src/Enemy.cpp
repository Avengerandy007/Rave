#include "Enemy.hpp"
#include <camera.hpp>
#include <memory>
#include <raylib.h>
#include <iostream>

Enemy::Enemy(std::shared_ptr<Player> pl, std::shared_ptr<GameFr::Camera2D> cam) : player(pl), random(0, 1){
	camera = cam;
	random.ChangeRange(pl->position.X - GetScreenWidth() - 50, pl->position.X - GetScreenWidth());
	position.X = random.GetRandomNumber();
	random.ChangeRange(pl->position.Y - GetScreenHeight() - 50, pl->position.Y - GetScreenHeight());
	position.Y = random.GetRandomNumber();
}

void Enemy::Update(){
	std::cout << "Hellloooooo\n";
	GetRenderingPosition(*camera);
	if (onScreen) DrawTexture(texture->texture, renderingPostion.X, renderingPostion.Y, WHITE);
}
