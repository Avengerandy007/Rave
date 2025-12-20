#include "util/Texture.hpp"
#include <raylib.h>
#include <iostream>

namespace Util{
	Texture::Texture(std::string path){
		std::clog << "New image at " << path << "\n";
		image = LoadImage(path.c_str());
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
	Texture::Texture(){
		std::clog << "Texture default ctor called\n";
	}
	void Texture::Assign(const Image& img){
		texture = LoadTextureFromImage(img);
	}

	Texture::Texture(const Texture& other){
		texture = other.texture;
	}

	void Texture::Assign(std::string path){
		std::clog << "New image at " << path << "\n";
		image = LoadImage(path.c_str());
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}

	void Texture::Unload(){
		if (texture.id != 0){
			UnloadTexture(texture);
			texture.id = 0;
		}
	}
}
