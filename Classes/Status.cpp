//
//  Status.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

#include "Status.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool Status::init()
{
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("Status");
    preemptiveBonus = 0;
    return true;
}


void Status::addStatusToGameObject(MonsterSprite *monster){
    this->applyStatus();
}

void Status::addStatusToCardSprite(CardSprite *card){
    this->applyStatus();
}

//checks whether the status can be used
bool Status::checkStart(){
    return true;
}

//called when status is given to object
void Status::applyStatus(){
    
}

//called when the status ends
void Status::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool Status::checkEnd(){
    return true;
}

//called at end of turn
void Status::updateStatus(){
    
}

//called at end of turn
void Status::updateStatus(MonsterSprite *monster){
    
}

