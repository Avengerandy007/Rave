#include "util/Texture.hpp"
#include <raylib.h>

namespace Util{
	Texture::Texture(std::string path){
		image = LoadImage(path.c_str());
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
	Texture::~Texture(){
		UnloadTexture(texture);
	}
}
