#pragma once
#include "SDL.h"

#include <iostream> // File reading??
#include <string>

#include <SDL_image.h>
class Texture
{
public:
	Texture() = default;
	Texture(SDL_Renderer* rend, const std::string& filename, double width, double height);
	//Texture(SDL_Renderer* rend, const std::string& filename, double width, double height, float angle);
	
	virtual ~Texture(){
		SDL_DestroyTexture(mTexture_);
	}


	void render(const SDL_Rect& src, const SDL_Rect& dest, double angle, const SDL_Point* p = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_RenderCopyEx(mRenderer_, mTexture_, &src, &dest, angle, p, flip);
	}
	void render(const SDL_Rect& src, const SDL_Rect& dest) {
		SDL_RenderCopy(mRenderer_, mTexture_, &src, &dest);
	}
	inline void render(const SDL_Rect& dest) {
		SDL_Rect src = { 0, 0, mWidth_, mHeight_ };
		render(src, dest);
	}
	void render(int x, int y);
	void render(const SDL_Rect& dest, float rotation);
	
private:
	SDL_Texture* mTexture_;
	SDL_Renderer* mRenderer_;

	double mWidth_;
	double mHeight_;
	float mRotation_;

};