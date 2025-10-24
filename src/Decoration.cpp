#include "Decoration.hpp"
#include <camera.hpp>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <raylib.h>

Decoration::Decoration(const std::string texturePath, const std::shared_ptr<GameFr::Camera2D> cam) : texture(texturePath), camera(cam), random(-200, 200){}

void Decoration::Update(){
	Regenerate();
	GetRenderingPosition(*camera);
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}

void Decoration::Regenerate(){
	if (std::abs(camera->entity->position.X - position.X) > 500){
		random.ChangeRange((camera->entity->position.X - 300), (camera->entity->position.X - 100));
		position.X = random.GetRandomNumber();
	}
	if (std::abs(camera->entity->position.Y - position.Y) > 500){
		random.ChangeRange((camera->entity->position.Y - 300), (camera->entity->position.Y + 100));
		position.Y = random.GetRandomNumber();
	}
}
