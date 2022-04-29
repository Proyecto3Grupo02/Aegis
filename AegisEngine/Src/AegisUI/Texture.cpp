#pragma once
#include "Texture.h"

void Texture::load(std::string filename, int cols, int rows) {
    SDL_Surface* tempSurface;
    tempSurface = IMG_Load(filename.c_str());
    //puede fallar incluir debug
    //if (tempSurface == nullptr)
        //throw AssetsExceptions::TextureException("Unable to load texture: ", filename);
    //else {
    cleanTexture();
    mTexture = SDL_CreateTextureFromSurface(mRenderer, tempSurface);
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

void Texture::setColor(SDL_Color col) {
    SDL_SetTextureColorMod(mTexture, col.r, col.g, col.b);
    SDL_SetTextureAlphaMod(mTexture, col.a);
}

void Texture::cleanTexture() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture); // delete current texture
        //posible debug necesario
        mTexture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture::render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const
{
    render(rect, 0, 0, 0, flip);
}

void Texture::render(float posX, float posY, int widthMul, int heightMult, SDL_RendererFlip flip) const
{
    SDL_Rect rect = { posX, posY, width * widthMul, height * heightMult };
    render(rect, 0, 0, 0, flip);
}

// SDL render
void Texture::render(const SDL_Rect& srcRect, const SDL_Rect& destRect, int angle, SDL_RendererFlip flip) const
{
    SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, 0, flip);
}