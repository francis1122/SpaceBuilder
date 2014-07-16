//
//  SolarSystemObject.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/7/14.
//
//

#include "SolarSystemObject.h"
#include "CardSprite.h"
#include "CardTargets.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "Constants.h"
#include "HandLayer.h"
#include "Utility.h"
#include "Statuses.h"
#include "CardTargets.h"
#include "CardSprite.h"
#include "Targets.h"
#include "CardFactory.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool SolarSystemObject::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    //////////////////////////////
    // 1. super init first
    if ( !CCSprite::initWithSpriteFrameName(pszSpriteFrameName) )
    {
        return false;
    }
    
    BaseObject::initDefaultState();
    owner = NULL;
    cardSlots = 0;
    //array for actual cards
    //CCArray
    population = 0;
    populationLimit = 6;
    cardArray = new CCArray();
    cardArray->init();
    solarSystemName = NULL;
    
    planetSize = Small;
    planetType = Terran;
    
    populationLabel = CCLabelTTF::create("1", Main_Font, 48);
    nameLabel = CCLabelTTF::create("test", Main_Font, 48);
    
    populationLabel->setPosition(ccp(15,47));
    nameLabel->setPosition(ccp(135,47));
    
    this->addChild(populationLabel, 11);
    this->addChild(nameLabel, 11);
    
    
    infoSprite = CCSprite::createWithSpriteFrameName("solarSystem_Label");
    infoSprite->setPosition(ccp(110, 35));
    this->addChild(infoSprite, 10);
    

    updateInterface();
    return true;
}

void SolarSystemObject::setupHomeResourceSlots()
{
    planetType = Terran;
    this->setScale(.65);
    planetSize = Large;
    population = 3;
    populationLimit = 7;
    cardArray->removeAllObjects();
    cardSlots = 6;
    //random cards should be added to planets on creation
    for(int i = 0; i < cardSlots; i++){
        ResourceCardSprite *card;
        if(i == 0 || i == 1){
            card = CardFactory::food();
            card->tier = 2;
        }else if(i == 2){
            card = CardFactory::production();
            card->tier = 2;
        }else if(i == 3 || i == 4){
            card = CardFactory::money();
        }else{
            card = CardFactory::tech();
            card->tier = 2;
        }
        card->setHomeSolarSystem(this);
        cardArray->addObject(card);
    }
}

void SolarSystemObject::setupResourceSlots(int slots)
{
    cardArray->removeAllObjects();
    cardSlots = slots;
    //random cards should be added to planets on creation
    for(int i = 0; i < cardSlots; i++){
        CardSprite *card;
        if(i == 0){
            card = CardFactory::food();
        }else if(i == 1){
            card = CardFactory::production();
        }else if(i == 2){
            card = CardFactory::money();
        }else{
            card = CardFactory::tech();
        }
        card->setHomeSolarSystem(this);
        cardArray->addObject(card);
    }
}

void SolarSystemObject::update()
{
    //only increase population if planet is owned
    if(owner){
        populationFraction++;
        while(populationFraction > 9){
            population++;
            populationFraction -= 10;
            if(owner){
                owner->updateCardInterfaces();
            }
        }
    }
    updateInterface();

}

void SolarSystemObject::updateInterface()
{
    CCString *populationString = CCString::createWithFormat("%i" , population);
    populationLabel->setString(populationString->getCString());

    if(solarSystemName){
        nameLabel->setString(solarSystemName->getCString());
    }
    
    for(int i = 0; i < cardArray->count(); i ++){
        CardSprite *card = (CardSprite*) cardArray->objectAtIndex(i);
        card->setHomeSolarSystem(this);
    }
}

void SolarSystemObject::populationOffset(int populationOffset, int populationFractionOffset)
{
    population += populationOffset;
    populationFraction += populationFractionOffset;
    while(populationFraction > 9){
        population++;
        populationFraction -= 10;
        if(owner){
            owner->updateCardInterfaces();
        }
    }
    updateInterface();

}

void SolarSystemObject::setHighlighted(bool enabled)
{
    if(enabled){
        setColor(ccYELLOW);
    }else{
        setColor(ccWHITE);
    }
}

#pragma mark - card managing

void SolarSystemObject::replaceCardAtIndex(CardSprite *card, int index)
{
    
}
