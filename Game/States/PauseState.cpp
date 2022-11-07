#pragma once
#include "PauseSate.h"


		PauseState::PauseState(){
            pauseimage.load("images/ui/pause.png");

        }
		void PauseState::reset( ){


        }
		void PauseState::tick(){
            

        }
		void PauseState::render(){
            if(pausegame)pauseimage.draw(ofGetWidth()/2-100,ofGetHeight()/2-50,200,100);

        }
		void PauseState::keyPressed(int key){
            if(key=='p' || key=='P') pausegame = !pausegame;

        }
		void PauseState::mousePressed(int x, int y, int button){
            

        }
        
	