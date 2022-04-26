#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include <iostream> // File reading??
#include <string>

class Texture
{

protected:
    
    SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	int width = 0, height = 0;      // Size of the image
	int fWidth = 0, fHeight = 0;    // Size of file
	int nCols = 0, nRows = 0;       // number of rows and cols for tiled texture

public:
    Texture(SDL_Renderer* mRenderer,string filename,int cols,int rows) : renderer(rend) {
        load(filename,cols,rows);
    };
    ~Texture();

    // Setter
    void setTexture(Texture* nTexture){ mTexture = nTexture; }
    
    // Getters
    inline int getWidth() { return width; }
	inline int getHeight() { return height; }
    inline int getCols() { return nCols; }
	inline int getRows() { return nRows; }

    void load(string filename,int cols,int rows){
        SDL_Surface* tempSurface;
        tempSurface = IMG_Load(filename.c_str());
        //puede fallar incluir debug
        //if (tempSurface == nullptr)
            //throw AssetsExceptions::TextureException("Unable to load texture: ", filename);
        //else {
            cleanTexture();
            texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
            //assert(texture == nullptr); // For debugging

            nCols = cols;
            nRows = rows;
            width = tempSurface->w;
            height = tempSurface->h;
            fWidth = width / cols;
            fHeight = height / rows;

            SDL_FreeSurface(tempSurface);
        //}
    }
    void setColor(SDL_Color col){
        SDL_SetTextureColorMod(texture, col.r, col.g, col.b);
	    SDL_SetTextureAlphaMod(texture, col.a);
        }

    void cleanTexture(){
        if (texture != nullptr) {
            SDL_DestroyTexture(texture); // delete current texture
            //posible debug necesario
            texture = nullptr;
            width = 0;
            height = 0;
        }
    }

    // Parser renders
    // 
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    { render(destRect, 0, 0, 0, flip); }
    void render(Vector2D pos, int widthMul, int heightMult, SDL_RendererFlip flip) const
    {
	SDL_Rect rect = { pos.getX(), pos.getY(), width * widthMul, height *  heightMult };
	render(rect, 0, 0, 0, flip);
    }
    
    // SDL render
    void Texture::render(const SDL_Rect& srcRect, const SDL_Rect& destRect, int angle, SDL_RendererFlip flip) const
    {
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
    }

};
