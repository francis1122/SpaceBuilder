//
//  ComboStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 2/5/14.
//
//

#include "ComboStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ComboStatus::init(int powerLevel)
{
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("ComboStatus");
    
    return true;
}

bool ComboStatus::initWithStatus(Status *status)
{
    if(!Status::init()){
        return false;
    }
    comboStatus = status;
    return true;
}

void ComboStatus::addStatusToGameObject(MonsterSprite *monster)
{
    comboStatus->addStatusToGameObject(monster);
}

void ComboStatus::addStatusToCardSprite(CardSprite *card)
{
    comboStatus->addStatusToCardSprite(card);
}

//checks whether the status can be used
bool ComboStatus::checkStart(){
    return true;
}

//called when status is given to object
void ComboStatus::applyStatus(){
    comboStatus->applyStatus();
}

//called when the status ends
void ComboStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool ComboStatus::checkEnd(){
    return true;
}

//called at end of turn
void ComboStatus::updateStatus(){
    
}
