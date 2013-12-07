//
//  DeathBlowStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#include "DeathBlowStatus.h"


#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool DeathBlowStatus::init(int powerLevel)
{
    
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("DeathBlowStatus");
    drawCards = powerLevel;
    return true;
}

void DeathBlowStatus::addStatusToGameObject(MonsterSprite *monster){
    monster->killingBlowArray->addObject(this);
}


//checks whether the status can be used
bool DeathBlowStatus::checkStart(){
    return true;
}

//called when status is given to object
void DeathBlowStatus::applyStatus(){
    GameManager *GM = GameManager::sharedGameManager();
    int i = 0;
    while( i < drawCards){
        GM->player->addCardToHand();
        i++;
    }
}

//called when the status ends
void DeathBlowStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool DeathBlowStatus::checkEnd(){
    return true;
}

//called at end of turn
void DeathBlowStatus::updateStatus(){
    
}

