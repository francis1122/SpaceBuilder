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
#include "Statuses.h"

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
    BaseObject::initDefaultState();
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    

    life = 4;
    attack = 2;
    location = 3;
    
    
    //details of card
    CCSize detailSize = CCSizeMake(330, 290);
    detailsLabel = CCLabelTTF::create("", "Arial", 48, detailSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(240,155));
    this->addChild(detailsLabel);
    
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
    afterDeathEffectArray = new CCArray();
    afterDeathEffectArray->init();
    this->setScale(.25);
    
    glowSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    glowSprite->setPosition(ccp(glowSprite->getContentSize().width/2 - 21,glowSprite->getContentSize().height/2 - 21));
    glowSprite->setVisible(false);
    this->addChild(glowSprite, -1);
    
    return true;
}

void MonsterSprite::enableInteractive(){
    glowSprite->setVisible(true);
    isInteractive = true;
}

void MonsterSprite::disableInteractive(){
    glowSprite->setVisible(false);
    isInteractive = false;
}

void MonsterSprite::updateInterface(){
    CCString *lifeString = CCString::createWithFormat("%i", life);
    lifeLabel->setString(lifeString->getCString());
    CCString *attackString = CCString::createWithFormat("%i", attack);
    attackLabel->setString(attackString->getCString());
    
}



void MonsterSprite::onDeath(){
    CCObject *object;
    CCARRAY_FOREACH(afterDeathEffectArray, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
}

void MonsterSprite::turnUpdate(){
    GameManager *GM = GameManager::sharedGameManager();
    
    
    //update status first
    for(int i = activeStatusArray->count() - 1; i >= 0 ;i--){
        Status *status = (Status*)activeStatusArray->objectAtIndex(i);
        status->updateStatus(this);
        if(status->checkEnd()){
            //should remove status
            status->applyEndStatus();
            activeStatusArray->removeObjectAtIndex(i);
        }
    }
    
    if(life > 0){
        if(location > 0){
            //move monster
            location--;
        }else{
            //attack human
            GM->player->health -= attack;
        }
    }
    
    //update monster labels
    updateInterface();
}

