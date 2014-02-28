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
#include "Action.h"

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
    return true;
}

bool GainActionStatus::initWithActionGain(CCArray *actions){
    if(!Status::init()){
        return false;
    }
    actionsGained = new CCArray();
    actionsGained->initWithArray(actions);
    return true;
}

void GainActionStatus::addStatusToGameObject(MonsterSprite *monster){
    this->applyStatus();
}

void GainActionStatus::createCardTargets(CardSprite *card)
{
    this->applyStatus();
}

//checks whether the status can be used
bool GainActionStatus::checkStart(){
    return true;
}

//called when status is given to object
void GainActionStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();
    for(int i = 0; i < actionsGained->count(); i++){
        Action *action = (Action*)actionsGained->objectAtIndex(i);
        GM->player->addAction(action->actionType);
    }
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
