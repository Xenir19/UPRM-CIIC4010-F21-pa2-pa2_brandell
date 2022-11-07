#pragma once
#include "Friend.h"

Friend::Friend(string name,int ox, int oy, string imagepath):Entity (ox, oy, 90, 90, imagepath){

    entityname= name;
    vector<ofImage> downFrames = {};
    vector<ofImage> upFrames = {};
    vector<ofImage> leftFrames = {};
    vector<ofImage> rightFrames = {};
    ofImage temp;
    messegeimage.load("images/ui/hi.png");

    for (int i = 1; i < 5; i++)
    {
        temp.load("images/entities/" + entityname + "/downframes/" + entityname + "-ow-front" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/" + entityname + "/upframes/" + entityname + "-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/" + entityname + "/leftframes/" + entityname + "-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/" + entityname + "/rightframes/" + entityname + "-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
    }


    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);
 
}
void Friend::tickOverworld(){
     if (movetimer == 60 && (!interacting || !caninteract))
    {
        walking = true;
        switch (direction)
        {
        case Direction::left:
            direction = Direction::down;
            break;
        case Direction::right:
            direction = Direction::up;
            break;
        case Direction::up:
            direction = Direction::left;
            break;
        case Direction::down:
            direction = Direction::right;
            break;
        }
    }
    if (movetimer == 45 ||caninteract || interacting) {
        walking = false;
    }
    if(movetimer > 45 && !caninteract && !interacting){
       walking = true; 
    } 
    if(!caninteract && !interacting){
      movetimer--;  
    }
    if (movetimer == 0){
        movetimer = 60;
        walking = true;
    }

    if (walking)
    {
        switch (direction)
        {
        case Direction::left:
            this->ox -= speed;
            walkLeft->tick();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            this->ox += speed;
            walkRight->tick();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            this->oy -= speed;
            walkUp->tick();
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            this->oy += speed;
            walkDown->tick();
            overworldSprite = walkDown->getCurrentFrame();
            break;
        }
    }
    else
    {
        switch (direction)
        {
        case Direction::left:
            overworldSprite.load("images/entities/" + entityname + "/leftframes/" + entityname + "-ow-left1.png");
            break;
        case Direction::right:
            overworldSprite.load("images/entities/" + entityname + "/rightframes/" + entityname + "-ow-right1.png");
            break;
        case Direction::up:
            overworldSprite.load("images/entities/" + entityname + "/upframes/" + entityname + "-ow-up1.png");
            break;
        case Direction::down:
            overworldSprite.load("images/entities/" + entityname + "/downframes/" + entityname + "-ow-front1.png");
            break;
        }
    }
}
void Friend::renderOverworld(){
    overworldSprite.draw(renderx,rendery,ow,oh);
    if(interacting)messegeimage.draw(renderx+50,rendery-40,100,50);
}
Friend::~Friend(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}

