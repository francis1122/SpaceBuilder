//
//  MonsterLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/3/14.
//
//

#include "MonsterLayer.h"
#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"
#include "Constants.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MonsterLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
/*
    CCLayerColor *playArea = CCLayerColor::create(ccc4(80, 80, 80, 190), visibleSize.width, visibleSize.height);
    playArea->setPosition(CCPointMake(0, 0));
    addChild(playArea);*/
    CCSprite *bg = CCSprite::createWithSpriteFrameName("MonsterLayerBG");
    bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
    
    CCSprite *topBar = CCSprite::createWithSpriteFrameName("topBar");
    topBar->setPosition(ccp( topBar->getContentSize().width/2, visibleSize.height - topBar->getContentSize().height/3));
//    this->addChild(topBar, 1000000);
    
    /*CCSprite *rows = CCSprite::createWithSpriteFrameName("rows");
    rows->setPosition(ccp( rows->getContentSize().width/2, rows->getContentSize().height/2 + 270));
    this->addChild(rows, 0);
    */
    
    this->monsterSpawnArray = new CCArray();
    this->monsterSpawnArray->init();
    
    for(int i = 0; i < 5; i++){
        CCSprite *spawnSprite = CCSprite::createWithSpriteFrameName("Card_Image_Attack2");
        spawnSprite->setPosition(ccp(180 + i * 185, visibleSize.height));
        spawnSprite->setScale(.5);
        spawnSprite->setOpacity(50);
        this->monsterSpawnArray->addObject(spawnSprite);
        this->addChild(spawnSprite);
    }
    return true;
}


void MonsterLayer::updateInterface()
{
    CCArray *locationsArray = GM->locationArray;
    for(int i = 0; i < locationsArray->count(); i++){
        CCInteger *value = (CCInteger*)locationsArray->objectAtIndex(i);
        CCSprite *spawnSprite = (CCSprite*)monsterSpawnArray->objectAtIndex(i);
        if(value->getValue() == 0){
            spawnSprite->setVisible(false);
        }else if(value->getValue()){
            spawnSprite->setVisible(true);
            spawnSprite->setColor(ccRED);
        }
    }
}

