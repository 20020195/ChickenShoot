#include "MainObject.h"
#include "CommonFunc.h"


MainObject::MainObject()
{
    x_pos_ = SCREEN_WIDTH/2;
    y_pos_ = 700;
    x_val_ = 0;
    y_val_ = 0;
    HP = 100;

}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    return ret;
}

void MainObject::Show(SDL_Renderer* des)
{
    LoadImg("img//na3.png", des);
    if(x_pos_ > 1199)
    {
        x_pos_ = 1199;
    }

    if(y_pos_ > 750)
    {
        y_pos_ = 750;
    }

    rect_.x = x_pos_-40;
    rect_.y = y_pos_;
    SDL_Rect renderQuad = {rect_.x, rect_.y, 80, 80};
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen )
{
    if( events.type == SDL_MOUSEMOTION )
	{
		SDL_GetMouseState( &x_pos_, &y_pos_ );
	}

	if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {

        BulletObject* p_bullet = new BulletObject();
        p_bullet->LoadImg("img//dan.png", screen);
        p_bullet->SetRect(rect_.x+14, rect_.y-30);
        p_bullet->set_y_val(10);
        p_bullet->set_is_move(true);
        p_bullet->LoadMusic();

        p_bullet_list_.push_back(p_bullet);
    }
}

void MainObject::HandelThreatsAction(SDL_Renderer* screen,int score)
{
    if ((SDL_GetTicks()%80) == 0)
    {
        quaivat_rand = rand()%4;
        int array[9]={0,120,240,360,480,600,720,840,960};
        ThreatsObject* p_threats = new ThreatsObject();
        switch(quaivat_rand)
        {
            case 0:p_threats->LoadImg("img//qv1.png", screen);
            break;

            case 1:p_threats->LoadImg("img//qv2.png", screen);
            break;

            case 2:p_threats->LoadImg("img//qv3.png", screen);
            break;

            case 3:p_threats->LoadImg("img//bomb1.png", screen);
            break;
        }

        if (p_threats_list_.size() == 0)
        {
            x_rand = array[rand()%9];
        }
        else
        {
            int y = array[rand()%9];
            while (y == x_rand)
            {
                y = array[rand()%9];
            }
            x_rand = y;
        }
        p_threats->SetRect(x_rand, -40);

        if (score>=10 && score <=25) tocdodichuyenquaivat=1.8;
        else if (score>25 && score <=50) tocdodichuyenquaivat=2.2;
        else if (score>50 && score<=100) tocdodichuyenquaivat=2.6;
        else if(score>100) tocdodichuyenquaivat=3;
        p_threats->set_y_val_threats(tocdodichuyenquaivat);
        p_threats->set_is_move_threats(true);
        if (quaivat_rand == 3)
        {
            p_bomb_list.push_back(p_threats);
        }
        else
        {
            p_threats_list_.push_back(p_threats);
        }
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for (int i=0; i < p_bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                if (p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::HandleThreats(SDL_Renderer* des)
{
    for (int i=0; i < p_threats_list_.size(); i++)
    {
        ThreatsObject* p_threats = p_threats_list_.at(i);
        if (p_threats != NULL)
        {
            if (p_threats->get_is_move_threats() == true)
            {
                p_threats->HandleMoveThreats(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threats->Render(des);
            }
            else
            {
                p_threats_list_.erase(p_threats_list_.begin() + i);
                if (p_threats != NULL)
                {
                    delete p_threats;
                    p_threats = NULL;
                }
            }
        }
    }
    for (int i=0; i < p_bomb_list.size(); i++)
    {
        ThreatsObject* p_bomb = p_bomb_list.at(i);
        if (p_bomb != NULL)
        {
            if (p_bomb->get_is_move_threats() == true)
            {
                p_bomb->HandleMoveThreats(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bomb->Render(des);
            }
            else
            {
                p_bomb_list.erase(p_bomb_list.begin() + i);
                if (p_bomb != NULL)
                {
                    delete p_bomb;
                    p_bomb = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
