#include "Decoration.hpp"
#include <camera.hpp>
#include "util/TextureArrays.hpp"
#include <cstdlib>
#include <memory>
#include <cmath>
#include <raylib.h>

Decoration::Decoration(const std::shared_ptr<GameFr::Camera2D> cam) : camera(cam), random(-GetScreenWidth(), GetScreenWidth()){
	position.X = random.GetRandomNumber();
	position.Y = random.GetRandomNumber();
	random.ChangeRange(0, 1);
	texture = Util::TextureArrays::decorations[random.GetRandomNumber()];
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
	//check if distance between this and player is larger than the resolution on X
	if (std::abs(player->position.X - position.X) > camera->resolutionX){
		//make sure that the player's direction is positive so the random minimum is smaller than the max
		if (player->direction.X >= 0){
			random.ChangeRange((int)(player->position.X + camera->resolutionX), (int)(player->position.X  + (camera->resolutionX + 300)));
		}else{
			random.ChangeRange((int)(player->position.X + -1 * (camera->resolutionX + 300)), (int)(player->position.X  + -1 * camera->resolutionX));
		}
		position.X = random.GetRandomNumber();
		random.ChangeRange(0, 1);
		texture = Util::TextureArrays::decorations[random.GetRandomNumber()];
	}
	//check if distance between this and player is larger than the resolution on Y
	if (std::abs(player->position.Y - position.Y) > camera->resolutionY){
		//make sure that the player's direction is positive so the random minimum is smaller than the max
		if (player->direction.Y >= 0) {
			random.ChangeRange((int)(player->position.Y +  camera->resolutionY), (int)(player->position.Y +  (camera->resolutionY + 300)));
		} else {
			random.ChangeRange((int)(player->position.Y + -1 * (camera->resolutionY + 300)), (int)(player->position.Y + -1 * camera->resolutionY));
		}
		position.Y = random.GetRandomNumber();
		random.ChangeRange(0, 1);
		texture = Util::TextureArrays::decorations[random.GetRandomNumber()];
	}
}
