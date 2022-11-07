#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(30);
	ofSetWindowTitle("PA2");
	setupAreas();
	// Declaration and Initialization of States
	player = new Player(100, 6);
	titleState = new TitleState();
	overworldState = new OverworldState(player, currentArea);
	battleState = new BattleState(player, currentArea);
	winState = new WinState();
	endGameState = new EndGameState();
	pausestate=new PauseState();
	loadingstate=new LoadingState();

	// Initial State
	currentState = titleState;
}

//--------------------------------------------------------------
void ofApp::setupAreas()
{
	//each area is 672 pixels wide and 640 pixels high, with 10 and 8 pixels of space between the player and the edge of the map respectively
	//each in-game pixel is 4 * 1 screen pixel

	vector<Enemy *> enemies2;
	vector<Entity *>entities;
	ofPoint entrancePosition2(4 * 110, 4 * 116);
	Enemy *area2Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 120, 4 * 342);
	Enemy *area2Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
	Enemy *area2Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
	Enemy *area2Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
	Enemy *area2Enemy5 = new Enemy("25", 30, 6, "enemy2", 4 * 266, 4 * 312);
	Enemy *area2Enemy6 = new Enemy("26", 30, 6, "enemy2", 4 * 194, 4 * 532);
	Rock *rock1 = new Rock( 4 * 460, 4 * 178,200,200);
	Rock *rock2 = new Rock( 4 * 450, 4 * 432,150,150);
	Rock *rock3 = new Rock( 4 * 250, 4 * 200,250,250);
	Rock *rock4 = new Rock( 4 * 500, 4 * 500,100,100);
	Boss *boss1= new Boss("10", 40, 8, "Boss", 4 * 300, 4 * 400);
	Boss *boss2= new Boss("10", 40, 8, "Boss2", 4 * 300, 4 * 400);
	Friend *friend1 = new Friend("friend", 4 * 400, 4 * 500,"images/entities/friend/UpFrames/friend-ow-up1.png");
	enemies2.push_back(area2Enemy1);
	enemies2.push_back(area2Enemy2);
	enemies2.push_back(area2Enemy3);
	enemies2.push_back(area2Enemy4);
	enemies2.push_back(area2Enemy5); 
	enemies2.push_back(area2Enemy6);
	entities.push_back(rock1);
	entities.push_back(rock2);
	entities.push_back(rock3);
	entities.push_back(rock4);
	entities.push_back(friend1);
	area2 = new Area(NULL, "images/areas/area2.png","Cave","audio/ice.wav", "images/stages/stage2.png", entrancePosition2, enemies2,entities,boss2); 
	vector<Enemy *> enemies1;
	ofPoint entrancePosition1(4 * 414, 4 * 566);
	Enemy *area1Enemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432);
	Enemy *area1Enemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178);
	Enemy *area1Enemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178); 
	Tree *tree1 = new Tree( 4 * 310, 4 * 148,200,200);
	Tree *tree2 = new Tree( 4 * 200, 4 * 110,150,150);
	Tree *tree3 = new Tree( 4 *190, 4 * 300,200,200);
	Tree *tree4 = new Tree( 4 *470, 4 * 115,300,300);
	enemies1.push_back(area1Enemy1);
	enemies1.push_back(area1Enemy2);
	enemies1.push_back(area1Enemy3);
	entities.push_back(tree1);
	entities.push_back(tree2);
	entities.push_back(tree3);
	entities.push_back(tree4);
	area1 = new Area(area2, "images/areas/area1.png","Forest", "audio/forest.wav", "images/stages/stage1.png", entrancePosition1, enemies1, entities,boss1);
	currentArea = area1;
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (currentState != nullptr)
	{
		if(!pausestate->getPause())currentState->tick();
		loadingstate->tick();

		if (currentState->hasFinished())
		{
			currentState->toggleMusic();
			if (currentState->getNextState() == "Title")
			{
				endGameState->setWin(false);
				area1->resetEnemies();
				area2->resetEnemies();
				currentArea = area1;
				battleState->resetPlayer();
				battleState->setStage(currentArea->getStage());
				overworldState->loadArea(currentArea);
				currentState = titleState;
			}
			else if (currentState->getNextState() == "Overworld")
			{
				currentState = overworldState;
				loadingstate->startloading(currentState);

			}
			else if (currentState->getNextState() == "Battle")
			{
				battleState->startBattle(overworldState->getEnemy());
				currentState = battleState;
				loadingstate->startloading(currentState);
			}
			else if (currentState->getNextState() == "Win")
			{
				overworldState->getEnemy()->kill();
				if (!currentArea->getboss()->isDead() && currentArea->getRemainingEnemies()==0){
					currentArea->pushbackboss();

				}
				if (currentArea->getRemainingEnemies() == 0 && currentArea->getboss()->isDead())
				{
					if (currentArea->getNextArea() == NULL)
					{
						endGameState->setWin(true);
						currentState = endGameState;
					}
					else
					{
						currentArea = currentArea->getNextArea();
						overworldState->loadArea(currentArea);
						battleState->setStage(currentArea->getStage());
						currentState = winState;
						loadingstate->startloading(currentState);
					}
				}
				else
				{
					currentState = winState;
				}
			}
			else if (currentState->getNextState() == "End")
				currentState = endGameState;
			if(loadingstate->getloading()==false) currentState->toggleMusic();
			currentState->reset();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (currentState != nullptr)
	{
		if (loadingstate->getloading()==false)currentState->render();
		 loadingstate->render();
	}
	pausestate->render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (currentState != nullptr)
		currentState->keyPressed(key);
	if (currentState==overworldState ||currentState==battleState) pausestate->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (currentState != nullptr)
		currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	if (currentState != nullptr)
		currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}