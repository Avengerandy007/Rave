#include "Decoration.hpp"
#include <camera.hpp>
#include "util/TextureArrays.hpp"
#include <cstdlib>
#include <memory>
#include <cmath>
#include <raylib.h>

Decoration::Decoration(const std::shared_ptr<GameFr::Camera2D> cam) : camera(cam), random(-200, 200){
	texture = Util::TextureArrays::decorations[0];
	player = std::reinterpret_pointer_cast<Player>(camera->entity);
}

void Decoration::Update(){
	Regenerate();
	GetRenderingPosition(*camera);
	if (onScreen){
		DrawTexture(texture->texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Decoration::Regenerate(){
	//check if distance between this and player is larger than 650u on X
	if (std::abs(player->position.X - position.X) > 650){
		//make sure that the player's direction is positive so the random minimum is smaller than the max
		if (player->direction.X > 0){
			random.ChangeRange((int)(player->position.X + player->direction.X * 400), (int)(player->position.X  + player->direction.X * 600));
		}else{
			random.ChangeRange((int)(player->position.X + player->direction.X * 600), (int)(player->position.X  + player->direction.X * 400));
		}
		position.X = random.GetRandomNumber();
	}
	//check if distance between this and player is larger than 650u on Y
	if (std::abs(player->position.Y - position.Y) > 600){
		//make sure that the player's direction is positive so the random minimum is smaller than the max
		if (player->direction.Y > 0) {
			random.ChangeRange((int)(player->position.Y + player->direction.Y * 400), (int)(player->position.Y + player->direction.Y * 600));
		} else {
			random.ChangeRange((int)(player->position.Y + player->direction.Y * 600), (int)(player->position.Y + player->direction.Y * 400));
		}
		position.Y = random.GetRandomNumber();
	}
}
