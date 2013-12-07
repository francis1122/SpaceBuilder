//
//  DrawCardStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#include "DrawCardStatus.h"

#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool DrawCardStatus::init(int powerLevel)
{
    
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("DrawCardStatus");
    drawCards = powerLevel;
    return true;
}


//checks whether the status can be used
bool DrawCardStatus::checkStart(){
    return true;
}

//called when status is given to object
void DrawCardStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();
    int i = 0;
    while( i < drawCards){
        GM->player->addCardToHand();
        i++;
    }
}

//called when the status ends
void DrawCardStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool DrawCardStatus::checkEnd(){
    return true;
}

//called at end of turn
void DrawCardStatus::updateStatus(){
    
}

