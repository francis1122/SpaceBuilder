//
//  SolarSystemDetailsLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#include "SolarSystemDetailsLayer.h"

#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"
#include "Constants.h"
#include "SolarSystemObject.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool SolarSystemDetailsLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
        CCLayerColor *playArea = CCLayerColor::create(ccc4(80, 80, 80, 190), visibleSize.width, visibleSize.height);
     playArea->setPosition(CCPointMake(0, 0));
     addChild(playArea);
     CCSprite *bg = CCSprite::createWithSpriteFrameName("MonsterLayerBG");
     bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
     this->addChild(bg);
     
    population = CCLabelTTF::create("population: 10", Main_Font, 48);
    income = CCLabelTTF::create("income: 10", Main_Font, 48);
    cardLimit = CCLabelTTF::create("cardLimit: 10", Main_Font, 48);
    
    population->setPosition(ccp(160,  visibleSize.height - 220));
    income->setPosition(ccp(160,  visibleSize.height - 60));
    cardLimit->setPosition(ccp(160, visibleSize.height - 140));
    
    this->addChild(population, 3);
    this->addChild(income, 3);
    this->addChild(cardLimit, 3);

    //this->monsterSpawnArray = new CCArray();
    //this->monsterSpawnArray->init();
    /*
     for(int i = 0; i < 5; i++){
     CCSprite *spawnSprite = CCSprite::createWithSpriteFrameName("Card_Image_Attack2");
     spawnSprite->setPosition(ccp(180 + i * 185, visibleSize.height));
     spawnSprite->setScale(.5);
     spawnSprite->setOpacity(50);
     this->monsterSpawnArray->addObject(spawnSprite);
     this->addChild(spawnSprite);
     }
     */
    return true;
}


void SolarSystemDetailsLayer::updateInterface(SolarSystemObject *solarSystem)
{
    
    CCString *populationString = CCString::createWithFormat("population: %i - %i" ,solarSystem->population, solarSystem->populationFraction);
    population->setString(populationString->getCString());
    CCString *incomeString = CCString::createWithFormat("income: %i", solarSystem->incomeGeneration);
    income->setString(incomeString->getCString());
    CCString *cardLimitString = CCString::createWithFormat("cardLimit: %i", solarSystem->cardSlots);
    cardLimit->setString(cardLimitString->getCString());
    
    
    
    /* CCArray *locationsArray = GM->locationArray;
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
     */
}