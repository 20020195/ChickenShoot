#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

class TextObject : public BaseObject
{
public:

    TextObject();
    ~TextObject();

    void SetText(const std::string& text) {str_val = text;}
    std::string GetText() const {return str_val;}

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);

    bool LoadText(TTF_Font* font, SDL_Renderer* screen);

    void RenderText(SDL_Renderer* screen, int xp, int yp);

    void Free();
private:
    std::string str_val;
    SDL_Color text_color;
    SDL_Texture* texture_;
};
#endif // TEXTOBJECT_H_INCLUDED
