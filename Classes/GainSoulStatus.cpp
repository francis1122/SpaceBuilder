//
//  GainSoulStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool GainSoulStatus::initWithSoulGain(int soulGain)
{
    
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("GainSoulStatus");
    soulGainAmount = soulGain;
    return true;
}


void GainSoulStatus::addStatusToGameObject(MonsterSprite *monster){
}

//checks whether the status can be used
bool GainSoulStatus::checkStart(){
    return true;
}

//called when status is given to object
void GainSoulStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->changeSoul(soulGainAmount);

}

//called when the status ends
void GainSoulStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool GainSoulStatus::checkEnd(){
    return true;
}

//called at end of turn
void GainSoulStatus::updateStatus(){
    
}
