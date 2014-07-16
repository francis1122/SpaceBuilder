//
//  CardDrawStatus.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/11/14.
//
//

#include "CardDrawStatus.h"
#include "GameManager.h"
#include "Player.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool CardDrawStatus::initWithCardDraw(int _cardDraw)
{
    cardDraw = _cardDraw;
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    className = new CCString();
    className->initWithFormat("CardDrawStatus");
    return true;
}

void CardDrawStatus::addStatusToPlayer(Player *player){
    int i = 0;
    while( i < cardDraw){
        player->addCardToHand();
        i++;
    }
}

//checks whether the status can be used
bool CardDrawStatus::checkStart(){
    return true;
}

//called when status is given to object
void CardDrawStatus::applyStatus(){
//    GameManager::sharedGameManager()->player->changeMoney(moneyOffset);
}

//called when the status ends
void CardDrawStatus::applyEndStatus(){
    
}

//checks whether the status should be destroyed
bool CardDrawStatus::checkEnd(){
    return true;
}

//called at end of turn
void CardDrawStatus::updateStatus(){
    
}

void CardDrawStatus::updateStatus(Player *player)
{
//    player->changeMoney(moneyOffset);
}
