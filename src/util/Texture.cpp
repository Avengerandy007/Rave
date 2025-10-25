#include "util/Texture.hpp"
#include <raylib.h>
#include <iostream>

namespace Util{
	Texture::Texture(std::string path){
		std::cout << "New image at " << path << "\n";
		image = LoadImage(path.c_str());
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
	Texture::Texture(){
		std::cout << "Texture default ctor called\n";
	}
	
	Texture::~Texture(){
		UnloadTexture(texture);
	}
}
