#pragma once
#include "Entity.h"

class Rock : public Entity {
    private:
        int renderx, rendery;
        
    public:
        Rock(int ox, int oy, int ow, int oh);
        void renderOverworld();
        void tickOverworld(){}
        void setRenderX(int x) {renderx = x;}
        void setRenderY(int y) {rendery = y;}
};