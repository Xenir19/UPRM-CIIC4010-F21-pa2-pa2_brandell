
#pragma once

#include "Entity.h" 
#include "Animation.h"




class Friend: public Entity {
    private:
        Direction direction = Direction::up;
        int speed = 8;
        bool walking = false;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight; 
        int renderx=1000;
        int rendery=1000;
        string entityname;
        int movetimer=60;
        bool caninteract=false;
        bool interacting = false;
        ofImage messegeimage;
        
        
    
    public:
        Friend(string name,int ox, int oy, string imagepath);
        ~Friend();
        void tickOverworld();
        void renderOverworld();
        int getSpeed(){return speed;}
        bool getcaninteract(){return caninteract;}
        bool getinteracting(){return interacting;}
        void setcaninteract(bool b) {caninteract = b;}
        void setinteracting(bool b) {interacting = b;}
        void setrenderX(int x){ renderx = x; };
        void setrenderY(int y){ rendery = y; };

        

};