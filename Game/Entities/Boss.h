#pragma once

#include "Enemy.h" 
#include "Animation.h"

class Boss : public Enemy{
    private:
    int timeskill=0;
    public:
        Boss(string id, int health, int baseDamage, string entityName, int ox, int oy);
        void renderOverworld();
        ~Boss();
        int gettimeskill(){return timeskill;}
        void settimeskill(int n){timeskill=n;}
};