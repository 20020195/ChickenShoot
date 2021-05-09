#ifndef EXPLOSIONOBJECT_H_INCLUDED
#define EXPLOSIONOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void ShowExplosion(SDL_Renderer* des,const int& x, const int& y);
};

#endif // EXPLOSIONOBJECT_H_INCLUDED
