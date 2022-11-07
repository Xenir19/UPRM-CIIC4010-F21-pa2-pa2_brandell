#pragma once
#include "State.h"
class LoadingState:public State{
    public:
        LoadingState();
        void reset(){}
        void tick();
        void render();
        void keyPressed(int key){}
        void mousePressed(int x, int y, int button){}
        void startloading(State* s);
        bool getloading(){return loading;}


    private:
    ofImage loadingscreen;
    bool loading=false;
    int counter=0;
    
    State* currentState;
};