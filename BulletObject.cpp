#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    Mix_Chunk *gLaze = NULL;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.y -= y_val_;
    if (rect_.y < 0)
    {
        is_move_ = false;
    }
}

void BulletObject::LoadMusic()
{
    gLaze = Mix_LoadWAV( "sound//lazersound.wav" );
    Mix_PlayChannel( -1, gLaze, 0 );
}
