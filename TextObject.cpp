#include "TextObject.h"

TextObject::TextObject()
{
    texture_ = NULL;
    text_color.r = 255;
    text_color.g = 0;
    text_color.b = 0;
}

TextObject::~TextObject()
{

}

bool TextObject::LoadText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if (text_surface != NULL)
    {
        texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
        SDL_FreeSurface(text_surface);
    }
    return texture_ != NULL;
}

void TextObject::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void TextObject::RenderText(SDL_Renderer* screen, int xp, int yp)
{
    SDL_Rect renderQuad = {xp, yp, 120, 120};
    SDL_RenderCopy(screen, texture_, NULL, &renderQuad);
}
