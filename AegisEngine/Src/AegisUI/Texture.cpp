#pragma once
#include "Texture.h"


Texture::Texture(SDL_Renderer* rend, const std::string& filename, double width, double height):
	mRenderer_(rend), mWidth_(width), mHeight_(height), mTexture_(nullptr), mRotation_(0)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface != nullptr) {
		mTexture_ = SDL_CreateTextureFromSurface(mRenderer_, surface);
	}
}

void Texture::render(int x, int y)
{
	SDL_Rect dest = { x, y, mWidth_, mHeight_ };
	render(dest);
}

void Texture::render(const SDL_Rect& dest, float rotation)
{
	SDL_Rect src = { 0, 0, mWidth_, mHeight_ };
	render(src, dest, rotation);
}


