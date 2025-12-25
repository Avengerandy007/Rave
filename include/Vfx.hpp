#pragma once
#include <chrono>
#include <entities.hpp>
#include <util/Texture.hpp>

class Vfx : public GameFr::Entity2D{
protected:
	std::shared_ptr<Util::Texture> texture;
	const std::chrono::milliseconds lifespan;
	const std::chrono::system_clock::time_point creationTime;
public:
	Vfx(const std::shared_ptr<Util::Texture>& p_texture, const std::chrono::milliseconds p_lifespan, const GameFr::Vector2& p_pos);
	virtual void Update() override;
	bool ShouldDestroy();
};

class AnimatedVfx : public Vfx{
	std::shared_ptr<Util::AnimatedTexture> animatedTexture;
public:
	AnimatedVfx(const std::shared_ptr<Util::Texture>& p_texture, const std::chrono::milliseconds p_lifespan, const GameFr::Vector2& p_pos, const uint32_t timePerFrame);
	void Update() override;
};
