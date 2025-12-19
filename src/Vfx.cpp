#include "Vfx.hpp"
#include <util/vectors.hpp>
#include "util/Globals.hpp"
#include "GameManager.hpp"

Vfx::Vfx(const std::shared_ptr<Util::Texture>& p_texture, const std::chrono::milliseconds p_lifespan, const GameFr::Vector2& p_pos) : texture(p_texture), lifespan(p_lifespan), creationTime(std::chrono::system_clock::now()){
	position = p_pos;
}

void Vfx::Update(){
	GetRenderingPosition(*Global::game->camera);
	if (onScreen){
		DrawTexture(texture->texture, renderingPosition.X, renderingPosition.Y, WHITE);
	}
}

bool Vfx::ShouldDestroy(){
	return (std::chrono::system_clock::now() - creationTime >= lifespan);
}
