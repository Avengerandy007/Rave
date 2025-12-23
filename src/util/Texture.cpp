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


	AnimatedTexture::AnimatedTexture(const std::string path){
		image = LoadImageAnim(path.c_str(), &totalFrames);
		texture = LoadTextureFromImage(image);
		frameDelay = 1;
	}

	AnimatedTexture::AnimatedTexture(){
		std::clog << "Animated texture default ctor\n";
	}

	AnimatedTexture::AnimatedTexture(const AnimatedTexture& other){
		frame = other.frame;
		frameDelay = other.frameDelay;
		image = other.image;
		texture = other.texture;
	}

	void AnimatedTexture::Assign(const std::string path){
		image = LoadImageAnim(path.c_str(), &totalFrames);
		texture = LoadTextureFromImage(image);
	}
	
	void AnimatedTexture::Assign(const Image& img){
		image = img;
	}

	void AnimatedTexture::Update(){
		frameCounter++;
		if (frameCounter >= frameDelay){
			frameCounter = 0;;
			frame++;
			if (frame >= totalFrames) frame = 0;
			frameOffset = image.width * image.height * 4 * frame;
			UpdateTexture(texture, (unsigned char *)image.data + frameOffset);
		}
	}

	void AnimatedTexture::Unload(){
		if (image.data){
			UnloadImage(image);
		}
		if (texture.id != 0){
			UnloadTexture(texture);
			texture.id = 0;
		}
	}
}
