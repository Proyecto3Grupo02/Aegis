#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include <iostream> // File reading??
#include <string>


class Texture
{

protected:
    
    SDL_Texture* mTexture = nullptr;
	SDL_Renderer* mRenderer = nullptr;
	int width = 0, height = 0;      // Size of the image
	int fWidth = 0, fHeight = 0;    // Size of file
	int nCols = 0, nRows = 0;       // number of rows and cols for tiled texture

public:

    Texture(SDL_Renderer* nRenderer, std::string filename,int cols,int rows) 
        : mRenderer(nRenderer) {  load(filename,cols,rows);   };
    ~Texture();

    // Setter
    void setTexture(SDL_Texture* nTexture){ mTexture = nTexture; }
    
    // Getters
    inline int getWidth() { return width; }
	inline int getHeight() { return height; }
    inline int getCols() { return nCols; }
	inline int getRows() { return nRows; }

    void load(std::string filename, int cols, int rows);

    void setColor(SDL_Color col);

    void cleanTexture();

    // Parser renders
    void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    void render(float posX, float posY, int widthMul, int heightMult, SDL_RendererFlip flip) const;
    
    // SDL render
    void render(const SDL_Rect& srcRect, const SDL_Rect& destRect, int angle, SDL_RendererFlip flip) const;

};