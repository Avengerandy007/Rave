#pragma once
#include <string>
#include "raylib.h"

namespace Util{
	class Texture{
		Image image;
	public:
		Texture2D texture;
		Texture(std::string path);
		Texture();
		Texture(const Texture& other);
		void Assign(std::string path);
		~Texture();
	};
}
