#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include <vector>
#include <cstdlib>
#include <ctime>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    bool LoadImg(std:: string path, SDL_Renderer* screen );
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen );

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }

    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
    void HandleBullet(SDL_Renderer* des);


// Threats
     void HandelThreatsAction(SDL_Renderer* screen,int score);
     void set_threats_list(std::vector<ThreatsObject*> threats_list)
    {
        p_threats_list_ = threats_list;
    }
    std::vector<ThreatsObject*> get_threats_list() const {return p_threats_list_;}


     void set_bomb_list(std::vector<ThreatsObject*> bomb_list)
    {
        p_bomb_list = bomb_list;
    }
    std::vector<ThreatsObject*> get_bomb_list() const {return p_bomb_list;}


    void HandleThreats(SDL_Renderer* des);

    void RemoveBullet(const int& idx);

    int getHP() const {return HP;}
    void setHP(int x)
    {
        HP = x;
    }

private:
    std::vector<BulletObject*> p_bullet_list_;
    std::vector<ThreatsObject*> p_threats_list_;
    std::vector<ThreatsObject*> p_bomb_list;


    double x_val_;
    double y_val_;

    int x_pos_;
    int y_pos_;

    int HP;
};


#endif // MAINOBJECT_H_INCLUDED
