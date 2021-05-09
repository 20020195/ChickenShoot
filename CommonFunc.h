#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static int Max_val=0;
const int SCREEN_WIDTH = 1340;
const int SCREEN_HEIGHT = 750;

static int quaivat_rand;
static int x_rand = 0;
static double tocdodichuyenquaivat = 1.0;
static int score = 0;
static int HPPlayer = 100;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // COMMONFUNC_H_INCLUDED
