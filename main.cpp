#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"

BaseObject g_background;

BaseObject g_menu;
BaseObject g_gioithieu;
BaseObject g_gameover;

TTF_Font* font_max = NULL;
TTF_Font* font_score = NULL;
TTF_Font* font_skip = NULL;


Mix_Chunk *gLaze = NULL;
Mix_Chunk *gBotDie = NULL;
Mix_Chunk *gGameOver = NULL;


bool InitData()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
			success = false;
		}

		g_window = SDL_CreateWindow( "Ninja Đại Chiến", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( g_window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			g_screen = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( g_screen == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if (TTF_Init() == -1)
                {
                    printf("SDL_TTF failed",TTF_GetError());
                    success = false;
                }

                font_max    = TTF_OpenFont("Font//trebucbi.ttf", 30);
                font_score = TTF_OpenFont("Font//VeraMoBd.ttf", 100);
                font_skip = TTF_OpenFont("Font//VNARIALI.ttf", 50);

                if(font_max == NULL || font_score == NULL || font_skip == NULL)
                {
                    success = false;
                }

				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//bg1.jpg", g_screen);
    if (ret == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void close()
{
	Mix_FreeChunk(gBotDie);
	Mix_FreeChunk(gLaze);
	Mix_FreeChunk(gGameOver);
	gLaze = NULL;
	gBotDie = NULL;
	gGameOver = NULL;

    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

bool LoadMusic()
{
    bool success = true;


	gLaze = Mix_LoadWAV( "sound//lazersound.wav" );
	if( gLaze == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gBotDie = Mix_LoadWAV( "sound//botdie.wav" );
	if( gBotDie == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gGameOver = Mix_LoadWAV( "sound//gameover.wav" );
    if( gGameOver == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	return success;
}

int main(int argc, char* argv[])
{
    srand((int)time(0));

    if (InitData() == false ){
        return -1;
    }
    if (LoadMusic() == false)
    {
        return -1;
    }

    if (g_menu.LoadImg("img//anh1.jpg", g_screen) == false)
    {
        return -1;
    }
    else
    {
        TextObject play;
        play.SetColor(255, 0, 255);
        play.SetText("PLAY");
        play.LoadText(font_skip, g_screen);
        g_menu.Render(g_screen, NULL);
        play.RenderText(g_screen, 150, 300);
        SDL_RenderPresent(g_screen);
        bool is_quit_menu = false;
        SDL_Event g_event_menu;
        while(!is_quit_menu)
        {
            while(SDL_PollEvent(&g_event_menu)!= 0)
            {
                if (g_event_menu.type == SDL_MOUSEBUTTONDOWN && g_event_menu.button.button == SDL_BUTTON_LEFT )
                {
                    SDL_Rect toado;
                    toado.x = 650;
                    toado.y = 700;
                    toado.w = 120;
                    toado.h = 90;

                    int xp, yp;
                    SDL_GetMouseState(&xp, &yp);
                    if (150<xp && xp<350 && 300<yp && yp<400)
                    {
                        is_quit_menu = true;
                        g_menu.Free();
                        SDL_RenderClear(g_screen);
                        Mix_PauseMusic();
                    }
                }
                else if (g_event_menu.type == SDL_QUIT)
                {
                    is_quit_menu = true;
                    close();
                    g_menu.Free();
                }
            }
        }
    }

    SDL_SetRenderDrawColor(g_screen,0, 0, 0, 255);
    SDL_RenderClear(g_screen);

    TextObject max_game;
    max_game.SetColor(0, 0, 0);
    TextObject score_game;
    score_game.SetColor(0, 0, 0);
    TextObject HP;
    HP.SetColor(0, 0, 0);

    bool returngame = false;

while(!returngame)
{
    MainObject p_player;

    ExplosionObject exp_main;
    bool ret = exp_main.LoadImg("img/exp_main.png", g_screen);
    SDL_RenderPresent(g_screen);

    LoadBackground();

    double scrollingOffset = 0;

    bool is_quit = false;

    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event)!= 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
                close();
            }

            p_player.HandelInputAction(g_event, g_screen);
        }

        scrollingOffset -= 0.5;
        if( scrollingOffset < -SCREEN_HEIGHT )
        {
            scrollingOffset = 0;
        }

        SDL_SetRenderDrawColor(g_screen,0, 0, 0, 255);
        SDL_RenderClear(g_screen);

        g_background.RenderScroll(g_screen, NULL, 0, scrollingOffset );
        g_background.RenderScroll(g_screen, NULL, 0, scrollingOffset + SCREEN_HEIGHT );
        g_background.RenderScroll(g_screen, NULL, 0, scrollingOffset + SCREEN_HEIGHT + SCREEN_HEIGHT);

        p_player.HandelThreatsAction(g_screen, score);


        p_player.HandleBullet(g_screen);

        p_player.HandleThreats(g_screen);
        HPPlayer = p_player.getHP();


        p_player.Show(g_screen);

        if (HPPlayer <= 0)
        {
            is_quit = true;
        }

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for(int r = 0; r<bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr[r];
            if(p_bullet != NULL)
            {
                std::vector<ThreatsObject*> threats_list = p_player.get_threats_list();
                std::vector<ThreatsObject*> bomb_list = p_player.get_bomb_list();
                for(int t = 0; t<threats_list.size();t++)
                {
                    ThreatsObject* obj_threats = threats_list.at(t);
                    if(obj_threats != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threats->GetRect().x;
                        tRect.y = obj_threats->GetRect().y;
                        tRect.w = 70;
                        tRect.h = 80;

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if (bCol)
                        {
                            score++;
                            p_player.RemoveBullet(r);
                            obj_threats->Free();
                            obj_threats -> set_is_move_threats(false);
                            threats_list.erase(threats_list.begin() + t);
                            exp_main.ShowExplosion(g_screen, tRect.x+10, tRect.y-20);
                            Mix_PlayChannel(-1, gBotDie, 0);
                            if (score % 5 ==0 && score>0) p_player.setHP(p_player.getHP()+5);
                        }
                    }
                }

                for(int t = 0; t<bomb_list.size();t++)
                {
                    ThreatsObject* obj_bomb = bomb_list.at(t);
                    if(obj_bomb != NULL)
                    {
                        SDL_Rect bombRect;
                        bombRect.x = obj_bomb->GetRect().x;
                        bombRect.y = obj_bomb->GetRect().y;
                        bombRect.w = 46;
                        bombRect.h = 40;
                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, bombRect);

                        if (bCol)
                        {
                            p_player.RemoveBullet(r);
                            obj_bomb->Free();
                            obj_bomb -> set_is_move_threats(false);
                            bomb_list.erase(bomb_list.begin() + t);
                            p_player.setHP(p_player.getHP()-50);
                        }
                    }
                }
            }
        }
// Va cham quai
        int x, y;
        SDL_GetMouseState(&x, &y);
        std::vector<ThreatsObject*> threats_list = p_player.get_threats_list();
        for(int t = 0; t<threats_list.size();t++)
        {
            ThreatsObject* obj_threats = threats_list.at(t);
            if(obj_threats != NULL)
            {
                SDL_Rect tRect;
                tRect.x = obj_threats->GetRect().x;
                tRect.y = obj_threats->GetRect().y;
                tRect.w = 95;
                tRect.h = 80;
                if (tRect.y>=SCREEN_HEIGHT)
                    {
                        p_player.setHP(p_player.getHP()-10);
                        obj_threats -> set_is_move_threats(false);
                        obj_threats->Free();
                        threats_list.erase(threats_list.begin() + t);
                    }

                SDL_Rect pRect;
                pRect.x = x;
                pRect.y = y;
                pRect.w = 130;
                pRect.h = 130;

                bool bCol = SDLCommonFunc::CheckCollision(pRect, tRect);
                if (bCol)
                {
                    obj_threats->Free();
                    obj_threats -> set_is_move_threats(false);
                    threats_list.erase(threats_list.begin() + t);
                    p_player.setHP(p_player.getHP()-50);
                }
            }
        }
        int bx, by;
        SDL_GetMouseState(&bx, &by);
        std::vector<ThreatsObject*> bomb_list = p_player.get_bomb_list();
        for(int t = 0; t<bomb_list.size();t++)
        {
            ThreatsObject* obj_bomb = bomb_list.at(t);
            if(obj_bomb != NULL)
            {
                SDL_Rect BombRect;
                BombRect.x = obj_bomb->GetRect().x;
                BombRect.y = obj_bomb->GetRect().y;
                BombRect.w = 95;
                BombRect.h = 80;

                 if (BombRect.y>=SCREEN_HEIGHT)
                    {
                        p_player.setHP(p_player.getHP()-2);
                        obj_bomb -> set_is_move_threats(false);
                        obj_bomb->Free();
                        bomb_list.erase(bomb_list.begin() + t);
                    }

                SDL_Rect pRect;
                pRect.x = bx;
                pRect.y = by;
                pRect.w = 130;
                pRect.h = 130;

                bool bCol = SDLCommonFunc::CheckCollision(pRect, BombRect);
                if (bCol)
                {
                    obj_bomb->Free();
                    obj_bomb -> set_is_move_threats(false);
                    bomb_list.erase(bomb_list.begin() + t);
                    p_player.setHP(p_player.getHP()-10);
                }
            }
        }



        std::string str_Max = "Max: ";
        std::string str_score = "Score: ";
        std::string str_hp = "HP: ";

        if (Max_val<=score) Max_val=score;

        std::string str_val = std::to_string(Max_val);
        std::string strscore = std::to_string(score);
        std::string hp = std::to_string(HPPlayer);

        str_Max += str_val;
        str_score += strscore;
        str_hp += hp;

        max_game.SetText(str_Max);
        max_game.SetColor(255, 255, 255);
        max_game.LoadText(font_max, g_screen);
        max_game.RenderText(g_screen, 1199, 0);

        score_game.SetText(str_score);
        score_game.SetColor(255, 255, 255);
        score_game.LoadText(font_max, g_screen);
        score_game.RenderText(g_screen, 1199, 300);

        HP.SetText(str_hp);
        HP.SetColor(255, 255, 255);
        HP.LoadText(font_max, g_screen);
        HP.RenderText(g_screen, 1199, 650);

        SDL_RenderPresent(g_screen);
    }

    SDL_SetRenderDrawColor(g_screen,255, 255, 255, 255);
    SDL_RenderClear(g_screen);

    SDL_Event e;
    Mix_PlayChannel(-1, gGameOver, 0);
    bool is_quit_return = false;
    while(!is_quit_return)
    {
        g_gameover.LoadImg("img//screenshot.png", g_screen);
        g_gameover.RenderScroll(g_screen, NULL, 0, 0);
        score_game.SetColor(255, 255, 255);
        score_game.LoadText(font_score, g_screen);
        score_game.RenderText(g_screen, 600, 200);
        SDL_RenderPresent(g_screen);
        while(SDL_PollEvent(&e)!= 0)
        {
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
            {
                is_quit_return = true;
                returngame = false;
                score = 0;
                tocdodichuyenquaivat = 1;
                g_gameover.Free();
                std::vector<ThreatsObject*> threats_list = p_player.get_threats_list();
                for(int i = 0; i<threats_list.size();i++)
                {
                    ThreatsObject* obj_threats = threats_list[i];
                    if(obj_threats != NULL)
                    {
                        threats_list.erase(threats_list.begin() + i);
                        delete obj_threats;
                        obj_threats = NULL;
                    }
                }
                p_player.~BaseObject();
                SDL_RenderClear(g_screen);
            }
            else if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                returngame = true;
                is_quit_return = true;
                g_gameover.Free();

                std::vector<ThreatsObject*> threats_list = p_player.get_threats_list();
                for(int i = 0; i<threats_list.size();i++)
                {
                    ThreatsObject* obj_threats = threats_list[i];
                    if(obj_threats != NULL)
                    {
                        threats_list.erase(threats_list.begin() + i);
                        delete obj_threats;
                        obj_threats = NULL;
                    }
                }
                close();
            }
        }
    }
}
    return 0;
}
