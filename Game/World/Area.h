#pragma once

#include "Player.h"
#include "Enemy.h"
#include "OverworldCamera.h"
#include "Boss.h"

class Area 
{
    private:
        ofImage areaImage;
        ofSoundPlayer areaMusic;
        ofImage areaStage;
        ofPoint entrancePosition;
        std::vector<Enemy*> enemies;
        std::vector<Entity*>entities;
        Area *nextArea;
        string areaName;
        Boss *boss;

    public:
        Area(Area *nextArea, string areaImagePath, string areaName, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy*> enemies,vector<Entity*>entities,Boss*boss);
        void resetEnemies();
        ofImage getImage() { return areaImage;};
        ofSoundPlayer getMusic() { return areaMusic;};
        ofImage getStage() { return areaStage;};
        ofPoint getEntrancePos() { return entrancePosition;};
        void setEnemies(std::vector<Enemy*> enemies) { this->enemies = enemies;};
        vector<Enemy*> getEnemies() { return enemies;};
        int getRemainingEnemies();
        Area* getNextArea() { return nextArea;};
        string getAreaName(){return areaName;}
        vector <Entity*>getentities(){return entities;}
        void pushbackboss(){enemies.push_back(boss);}
        Boss*getboss(){return boss;}
        
};