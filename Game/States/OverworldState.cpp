#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area)
{
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
    music.setVolume(0.25);
    music.setLoop(true);
}
void OverworldState::loadArea(Area *area)
{
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.25);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}
void OverworldState::playercolitions(){
player->setcanwalkup(true);
player->setcanwalkright(true);
player->setcanwalkleft(true);
player->setcanwalkdown(true);


for(Entity *entity : area->getentities()){
        if(player->getBounds(player->getOX() - player->getSpeed(),player->getOY()).intersects(entity->getBounds())){
            player->setcanwalkleft(false);
        } 
        if(player->getBounds(player->getOX() + player->getSpeed(),player->getOY()).intersects(entity->getBounds())){
            player->setcanwalkright(false);
        } 
        if(player->getBounds(player->getOX(),player->getOY() - player->getSpeed()).intersects(entity->getBounds())){
            player->setcanwalkup(false);
        } 
        if(player->getBounds(player->getOX(),player->getOY() + player->getSpeed()).intersects(entity->getBounds())){
            player->setcanwalkdown(false);
        } 

    }
for(Entity *e : area->getentities()){
        Friend *f = dynamic_cast<Friend*>(e);
        if(f == NULL) continue;
        f->setcaninteract(false);
        if(player->getBounds(player->getOX() - (2 * player->getSpeed()),player->getOY()).intersects(f->getBounds())){
            f->setcaninteract(true);
        }
        if(player->getBounds(player->getOX() + (2 * player->getSpeed()),player->getOY()).intersects(f->getBounds())){
            f->setcaninteract(true);
        }
        if(player->getBounds(player->getOX(),player->getOY() - (2 * player->getSpeed())).intersects(f->getBounds())){
            f->setcaninteract(true);
        }
        if(player->getBounds(player->getOX(),player->getOY() + (2 * player->getSpeed())).intersects(f->getBounds())){
            f->setcaninteract(true);
        }
    }
}
void OverworldState::tick()
{
    playercolitions();
    player->tickOverworld();
    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            area->getEnemies().at(i)->tickOverworld();
            if (player->collides(area->getEnemies().at(i)))
            {
                setEnemy(area->getEnemies().at(i));
                setNextState("Battle");
                setFinished(true);
            }
        }
    }
    for (Entity* e: area->getentities())e->tickOverworld();
    camera->tick();
}

void OverworldState::render()
{
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->renderOverworld();
    

    for (unsigned int i = 0; i < area->getEnemies().size(); i++)
    {
        if (!area->getEnemies().at(i)->isDead())
        {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->renderOverworld();
        }
    for (unsigned int i = 0; i < area->getentities().size(); i++)
    {

        Rock*rock=dynamic_cast<Rock*>(area->getentities().at(i));
        if(rock==NULL)continue;
        int playerDistanceX = area->getentities().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getentities().at(i)->getOY() - camera->getPlayerY();
        rock->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        rock->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        rock->renderOverworld();
        
    }
    for (unsigned int i = 0; i < area->getentities().size(); i++)
    {

        Tree*tree=dynamic_cast<Tree*>(area->getentities().at(i));
        if(tree==NULL)continue;
        int playerDistanceX = area->getentities().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getentities().at(i)->getOY() - camera->getPlayerY();
        tree->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        tree->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        tree->renderOverworld();
        
    }
    for (unsigned int i = 0; i < area->getentities().size(); i++)
    {

        Friend*f=dynamic_cast<Friend*>(area->getentities().at(i));
        if(f==NULL)continue;
        int playerDistanceX = area->getentities().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getentities().at(i)->getOY() - camera->getPlayerY();
        f->setrenderX(camera->getDimensionX() / 2 + playerDistanceX);
        f->setrenderY(camera->getDimensionY() / 2 + playerDistanceY);
        f->renderOverworld();
    }
    }
    drawHUD();
}
void OverworldState::playerinteraction(){
    for (Entity* e:area->getentities()){
        Friend* f = dynamic_cast<Friend*>(e);
        if (f == NULL)continue;
        if (f->getcaninteract())f->setinteracting(!f->getinteracting());
    }
    
}

void OverworldState::drawHUD(){
     ofImage healthbar;
    healthbar.load("images/ui/healthbar.png");
    healthbar.draw(ofGetWidth()-192, 0, 192, 192);

    for (int i = 0; i < 3; i++)
    {
        double playerHealthRatio = (double)player->getCurrentHealth() / (double)player->getHealth();

        if(playerHealthRatio < 0){
            playerHealthRatio = 0;
        }
        else if (playerHealthRatio < 0.33)
        {
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        }
        else if (playerHealthRatio < 0.66)
        {
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        }
        else
        {
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);
        }
        ofDrawRectangle(ofGetWidth()-148, 88 + i * 4, (int)(36 * playerHealthRatio) * 4, 4);
    
    ofFill();
    ofSetColor(255,255,255);   

    area->getRemainingEnemies();
    ofDrawBitmapString( "Current enemies= "+ ofToString(area->getRemainingEnemies()),ofGetWidth()-148,50);
    ofDrawBitmapString(area->getAreaName(),ofGetWidth()-148,30);
    }
    
}



void OverworldState::keyPressed(int key)
{
    player->keyPressed(key);
    if(key=='r'||key=='R')area->resetEnemies();
	if(key=='e'||key=='E')playerinteraction();
    
}

void OverworldState::keyReleased(int key)
{
    player->keyReleased(key);
}

void OverworldState::mousePressed(int x, int y, int button)
{
}

void OverworldState::reset()
{
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}