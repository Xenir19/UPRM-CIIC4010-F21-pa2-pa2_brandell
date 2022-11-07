#pragma once
#include "Boss.h"

Boss::Boss(string id, int health, int baseDamage, string entityName, int ox, int oy) : Enemy(id, health, baseDamage, entityName, ox, oy){
    this->id = id;
    this->health = health;
    this->baseDamage = baseDamage;
    this->entityName = entityName;
    this->ox = ox;
    this->oy = oy;


    this->ow = 150;
    this->oh = 150;
    

    vector<ofImage> downFrames = {};
    vector<ofImage> upFrames = {};
    vector<ofImage> leftFrames = {};
    vector<ofImage> rightFrames = {};
    vector<ofImage> fightingFrames = {};

  
    ofImage temp;

    for (int i = 1; i < 5; i++)
    {
        temp.load("images/entities/" + entityName + "/downframes/" + entityName + "-ow-down" + std::to_string(i == 3 ? 1 : i) + ".png");
        downFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/upframes/" + entityName + "-ow-up" + std::to_string(i == 3 ? 1 : i) + ".png");
        upFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/leftframes/" + entityName + "-ow-left" + std::to_string(i == 3 ? 1 : i) + ".png");
        leftFrames.push_back(temp);
        temp.load("images/entities/" + entityName + "/rightframes/" + entityName + "-ow-right" + std::to_string(i == 3 ? 1 : i) + ".png");
        rightFrames.push_back(temp);
      
    }

    temp.load("images/entities/" + entityName + "/fighting frames/" + entityName + "-f1.png");
    fightingFrames.push_back(temp);
    temp.load("images/entities/" + entityName + "/fighting frames/" + entityName + "-f2.png");
    fightingFrames.push_back(temp);


    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);

    fighting = new Animation(7, fightingFrames);

   

}

void Boss::renderOverworld()
{
   
    overworldSprite.draw(renderX, renderY, ow, oh);
  
}
Boss::~Boss(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
    delete fighting;
}