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
#include "Constants.h"
#include "Utility.h"
#include "AnimationManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MonsterSprite::init()
{
    //////////////////////////////
    // 1. super init first
    
    if ( !CCSprite::initWithSpriteFrameName("monstercard2") )
    {
        return false;
    }
    BaseObject::initDefaultState();
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
    life = 4;
    maxLife = 4;
    attack = 2;
    location = 3;
    hasTaunt = false;
    hasRange = false;
    
    //details of card
    CCSize detailSize = CCSizeMake(325, 240);
    detailsLabel = CCLabelTTF::create("", Main_Font, 48, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(240,235));
    this->addChild(detailsLabel);
    
    attackLabel = CCLabelTTF::create("2", LARGE_NUMBER_FONT, 128);
    lifeLabel =  CCLabelTTF::create("4", LARGE_NUMBER_FONT, 128);
    attackLabel->setColor(ccWHITE);
    lifeLabel->setColor(ccWHITE);
    
    attackLabel->setPosition(CCPointMake(85, 92));
    lifeLabel->setPosition(CCPointMake(379, 92));
    

    
    this->addChild(lifeLabel, 1);
    this->addChild(attackLabel, 1);
    
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
    glowSprite->setScaleY(.7);
    this->addChild(glowSprite, -1);
    lifeRender = NULL;
    
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
    if(lifeRender){
        lifeRender->removeFromParentAndCleanup(true);
        lifeRender = NULL;
    }
    
    if(attackRender){
        attackRender->removeFromParentAndCleanup(true);
        attackRender = NULL;
    }
    lifeRender = Utility::createTTFStroke(lifeLabel, 7, ccBLACK, 255);
    attackRender = Utility::createTTFStroke(attackLabel, 7, ccBLACK, 255);
    this->addChild(lifeRender);
    this->addChild(attackRender);
    
}



void MonsterSprite::onDeath(){
    CCObject *object;
    CCARRAY_FOREACH(afterDeathEffectArray, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
}

void MonsterSprite::turnUpdate(){
    
    
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
    
    if(life > maxLife){
        life = maxLife;
    }
    
    if(life > 0){
        if(hasRange){
            GM->player->health -= attack;
        }else{

            if(location > 0){
                //move monster
                location--;
            }else{
                //attack human
                GM->player->health -= attack;
            }

        }
    }else{
        isDead = true;
    }

    
    //update monster labels
    updateInterface();
}

void MonsterSprite::setupMonsterImage(CCString* monserSpriteName)
{
    CCSprite *image = CCSprite::createWithSpriteFrameName(monserSpriteName->getCString());
    image->setPosition(ccp(235,473));
    this->addChild(image);
}

void MonsterSprite::changeMonsterHealth(int healthOffset){
    if(healthOffset < 0){
        AM->createDamageIcon(healthOffset, this->getPosition());
    }
    life += healthOffset;
}
