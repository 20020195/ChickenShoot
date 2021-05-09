#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{

}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::ShowExplosion(SDL_Renderer* des, const int& x, const int& y)
{
    LoadImg("img//exp_main3.png", des);
    rect_.x = x;
    rect_.y = y;
    SDL_Rect renderQuad = {rect_.x, rect_.y, 100, 100};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}
