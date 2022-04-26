#pragma once
#include "Texture.h"
//#include "Component.h"
#include <string>

class Image
{

public:
    Image(std::string image);
    ~Image();

    void setTexture(Texture* nTexture){ mTexture = nTexture; }
    

private:
    Texture* mTexture;
    int coorX, coorY;
    bool render = true;
};
