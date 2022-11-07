#pragma once
#include "Entity.h"

class Tree : public Entity {
    private:
        int renderx, rendery;
        
    public:
        Tree(int ox, int oy, int ow, int oh);
        void renderOverworld();
        void tickOverworld(){}
        void setRenderX(int x) {renderx = x;}
        void setRenderY(int y) {rendery = y;}
};