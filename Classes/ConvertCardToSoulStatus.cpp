//
//  ConvertCardToSoulStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 12/6/13.
//
//

#include "ConvertCardToSoulStatus.h"

#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool ConvertCardToSoulStatus::init(int powerLevel)
{
    
    if(!Status::init()){
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    className = new CCString();
    className->initWithFormat("ConvertCardToSoulStatus");
    return true;
}



void ConvertCardToSoulStatus::addStatusToCardSprite(CardSprite *card){
    GameManager *GM = GameManager::sharedGameManager();
    GM->player->changeSoul(card->soulCost + soulGainAmount);
}

//checks whether the status can be used
bool ConvertCardToSoulStatus::checkStart(){
    return true;
}

//called when status is given to object
void ConvertCardToSoulStatus::applyStatus(){

}

//called when the status ends
void ConvertCardToSoulStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool ConvertCardToSoulStatus::checkEnd(){
    return true;
}

//called at end of turn
void ConvertCardToSoulStatus::updateStatus(){
    
}