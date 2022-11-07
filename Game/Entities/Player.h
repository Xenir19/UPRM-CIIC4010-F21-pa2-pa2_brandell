
#pragma once

#include "Entity.h" 
#include "Animation.h"
#include "FightingCharacteristics.h"

#define INIT_X 100
#define INIT_Y 100
#define CENTER_X 288
#define CENTER_Y 208

#define OXDIMENSION 2688
#define OYDIMENSION 2560


class Player : public Entity, public FightingCharacteristics {
    private:
        Direction direction = Direction::up;
        int speed = 8;
        int currentHealth=health;
        bool walking = false;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        Animation *fighting;
        vector<char> pressedKeys;
        bool canwalkup=true;
        bool canwalkdown=true;
        bool canwalkright=true;
        bool canwalkleft=true;
        
    
    public:
        Player(int health, int baseDamage);
        ~Player();
        int getCurrentHealth(){return currentHealth;}
        void setcurrentHealth(int h){currentHealth=h;}
        void tickOverworld();
        void tickFighting();
        void renderOverworld();
        void keyPressed(int key);
        void keyReleased(int key);
        void reset();
        void setcanwalkup(bool b){canwalkup=b;}
        void setcanwalkdown(bool b){canwalkdown=b;}
        void setcanwalkright(bool b){canwalkright=b;}
        void setcanwalkleft(bool b){canwalkleft=b;}
        int getSpeed(){return speed;}

};