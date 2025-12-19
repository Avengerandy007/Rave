#pragma once
#include <chrono>
#include <entities.hpp>
#include <util/Texture.hpp>

class Vfx : public GameFr::Entity2D{
	const std::shared_ptr<Util::Texture> texture;
	const std::chrono::milliseconds lifespan;
	const std::chrono::system_clock::time_point creationTime;
public:
	Vfx(const std::shared_ptr<Util::Texture>& p_texture, const std::chrono::milliseconds p_lifespan, const GameFr::Vector2& p_pos);
	void Update() override;
	bool ShouldDestroy();
};
