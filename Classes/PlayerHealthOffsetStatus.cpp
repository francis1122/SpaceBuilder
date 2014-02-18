//
//  PlayerHealthOffsetStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/29/14.
//
//

#include "PlayerHealthOffsetStatus.h"

#include "GainSoulStatus.h"
#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"
#include "Constants.h"


USING_NS_CC;


bool PlayerHealthOffsetStatus::initWithHealthOffset(int healthOffset){
    if(!Status::init()){
        return false;
    }
    
    playerHeatlhOffset = healthOffset;
    return true;
}



//checks whether the status can be used
bool PlayerHealthOffsetStatus::checkStart(){
    return true;
}

//called when status is given to object
void PlayerHealthOffsetStatus::applyStatus(){
    GM->player->changeHealth(playerHeatlhOffset);
}

//called when the status ends
void PlayerHealthOffsetStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool PlayerHealthOffsetStatus::checkEnd(){
    return true;
}

//called at end of turn
void PlayerHealthOffsetStatus::updateStatus(){
    
}
