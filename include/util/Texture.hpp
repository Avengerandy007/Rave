#pragma once
#include <string>
#include "raylib.h"
#include <inttypes.h>

namespace Util{
	class Texture{
	protected:
		Image image;
	public:
		Texture2D texture;
		Texture(std::string path);
		Texture();
		Texture(const Texture& other);
		virtual void Assign(const std::string path);
		virtual void Assign(const Image& img);
		virtual void Unload();
	};

	class AnimatedTexture : public Texture{
		uint32_t frame;
		uint32_t frameCounter;
		int totalFrames;
		int frameOffset;
	public:
		uint32_t frameDelay;
		AnimatedTexture(const std::string path);
		AnimatedTexture();
		AnimatedTexture(const AnimatedTexture& other);
		void Assign(const std::string path) override;
		void Assign(const Image& img) override;
		void Update();
		void Unload() override;
	};
}
