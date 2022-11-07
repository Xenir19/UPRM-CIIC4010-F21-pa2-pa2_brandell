#pragma once
#include "Rock.h"

Rock::Rock(int ox, int oy, int ow, int oh) : Entity(ox,oy,ow,oh,"images/entities/rock.png"){}

void Rock::renderOverworld(){overworldSprite.draw(renderx,rendery,ow,oh);}