#pragma once
#include "Tree.h"

Tree::Tree(int ox, int oy, int ow, int oh) : Entity(ox,oy,ow,oh,"images/entities/tree.png"){}

void Tree::renderOverworld(){overworldSprite.draw(renderx,rendery,ow,oh);}