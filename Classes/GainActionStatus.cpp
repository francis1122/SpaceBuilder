//
//  GainActionStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/4/13.
//
//

#include "GainActionStatus.h"

#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool GainActionStatus::init(int powerLevel)
{
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("GainActionStatus");
    actionGainAmount = 2;
    return true;
}


void GainActionStatus::addStatusToGameObject(MonsterSprite *monster){
    
}

//checks whether the status can be used
bool GainActionStatus::checkStart(){
    return true;
}

//called when status is given to object
void GainActionStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->actionsLeft += actionGainAmount;
}

//called when the status ends
void GainActionStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool GainActionStatus::checkEnd(){
    return true;
}

//called at end of turn
void GainActionStatus::updateStatus(){
    
}
