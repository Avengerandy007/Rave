#include "Decoration.hpp"
#include <camera.hpp>
#include <memory>
#include <raylib.h>

Decoration::Decoration(const std::string texturePath, const std::shared_ptr<GameFr::Camera2D> cam) : texture(texturePath), camera(cam){}

void Decoration::Update(){
	GetRenderingPosition(*camera);
	if (onScreen){
		DrawTexture(texture.texture, renderingPostion.X, renderingPostion.Y, WHITE);
	}
}
