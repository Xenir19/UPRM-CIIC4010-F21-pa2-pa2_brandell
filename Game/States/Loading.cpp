#pragma once
#include "Loading.h"

LoadingState::LoadingState(){ 
    music.load("audio/stand_by.mp3");


    loadingscreen.load("images/ui/loading.png");
 }

 void LoadingState::tick(){
     if (loading)counter++;
     if (counter==100){
         music.stop();
         counter=0;
         loading=false;
         currentState->toggleMusic();

     }


 }
 void LoadingState::startloading(State* s){
     loading=true;
     currentState=s;
     toggleMusic();
 }
 void LoadingState::render(){
     if (loading)loadingscreen.draw(0,0, ofGetWidth(), ofGetHeight());
 }