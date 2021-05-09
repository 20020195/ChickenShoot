#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "CommonFunc.h"
using namespace std;

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() {return rect_;}

    SDL_Texture* GetObject() const {return p_object_;}

    virtual bool LoadImg(string path, SDL_Renderer* screen );
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void RenderScroll(SDL_Renderer* des, const SDL_Rect* clip, int x, int y);

    void Free();

protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};


#endif // BASEOBJECT_H_INCLUDED
