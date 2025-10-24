#include "Decoration.hpp"
#include <camera.hpp>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <raylib.h>

Decoration::Decoration(const std::string texturePath, const std::shared_ptr<GameFr::Camera2D> cam) : texture(texturePath), camera(cam){}

void Decoration::Update(){
	Regenerate();
	GetRenderingPosition(*camera);
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Decoration::Regenerate(){
	if (std::abs(camera->entity->position.X / 2 - position.X) > 200){
		position.X = rand() % (int)(camera->entity->position.X + 150) + (camera->entity->position.X - 150);
	}
	if (std::abs(camera->entity->position.Y / 2 - position.Y) > 200){
		position.Y = rand() % (int)(camera->entity->position.Y + 150) + (camera->entity->position.Y - 150);
	}
}
