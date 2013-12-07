//
//  MonsterSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/20/13.
//
//

#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MonsterSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName("monstercard") )
    {
        return false;
    }
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
    life = 4;
    attack = 2;
    location = 4;
    
    
    attackLabel = CCLabelTTF::create("2", "Arial", 128);
    lifeLabel =  CCLabelTTF::create("4", "Arial", 128);
    attackLabel->setColor(ccYELLOW);
    lifeLabel->setColor(ccYELLOW);
    
    attackLabel->setPosition(CCPointMake(80, 73));
    lifeLabel->setPosition(CCPointMake(390, 73));
    
    this->addChild(lifeLabel);
    this->addChild(attackLabel);
    
    activeStatusArray = new CCArray();
    activeStatusArray->init();
    killingBlowArray = new CCArray();
    killingBlowArray->init();
    this->setScale(.25);
    
    return true;
}

void MonsterSprite::updateInterface(){
    CCString *lifeString = CCString::createWithFormat("%i", life);
    lifeLabel->setString(lifeString->getCString());
    CCString *attackString = CCString::createWithFormat("%i", attack);
    attackLabel->setString(attackString->getCString());

}

void MonsterSprite::turnUpdate(){
    GameManager *GM = GameManager::sharedGameManager();
    //update life label
    updateInterface();
    
    if(location > 0){
        //move monster
        location--;
    }else{
        //attack human
        GM->player->health -= attack;
        
    }
}

