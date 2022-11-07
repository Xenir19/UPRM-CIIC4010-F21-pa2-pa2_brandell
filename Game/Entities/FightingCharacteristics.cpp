#pragma once
#include "FightingCharacteristics.h"

FightingCharacteristics::FightingCharacteristics(int fx, int fy, int fw, int fh, int health, int baseDamage, string fightingPath){
    this->fx=fx;
    this->fy=fy;
    this->fw=fw;
    this->fh=fh;
    this->health=health;
    this->baseDamage=baseDamage;
    fightingSprite.load(fightingPath);
    
}
 void FightingCharacteristics::renderFighting(){
     fightingSprite.draw(fx,fy,fw,fh);
 }