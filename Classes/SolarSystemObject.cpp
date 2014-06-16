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
    cardSlots = 3;
    //array for actual cards
    //CCArray
    incomeGeneration = 3;
    population = 0;
    populationLimit = 6;
    cardArray = new CCArray();
    cardArray->init();
    solarSystemName = new CCString();
    solarSystemName->initWithFormat("Sol");
    
    populationLabel = CCLabelTTF::create("1", Main_Font, 48);
    incomeLabel = CCLabelTTF::create("3", Main_Font, 36);
    nameLabel = CCLabelTTF::create("Sol", Main_Font, 48);
    
    populationLabel->setPosition(ccp(15,47));
    incomeLabel->setPosition(ccp(100,105));
    nameLabel->setPosition(ccp(135,47));
    
    this->addChild(populationLabel, 11);
    this->addChild(incomeLabel, 11);
    this->addChild(nameLabel, 11);
    
    
    infoSprite = CCSprite::createWithSpriteFrameName("solarSystemInfo");
    infoSprite->setPosition(ccp(100, 50));
    this->addChild(infoSprite, 10);
    //random cards should be added to planets on creation
    for(int i = 0; i < cardSlots; i++){
        if(i < 1){
            CardSprite *card = new CardSprite();
            card->cardImageFile = "sword";
            card->initWithSpriteFrameName("YellowCard");
            card->detailsLabel->setString("increase population of solar system by 1");
            //Make card ability
            SolarSystemTargets *cardTargets = new SolarSystemTargets();
            cardTargets->initWithCardSprite(card);
            cardTargets->targetFriendlySystems = true;
            
            
            PopulationOffsetStatus *status = new PopulationOffsetStatus();
            status->initWithPopulationOffset(1, 0);
            cardTargets->statuses->addObject(status);
            
            card->cardTargets = cardTargets;
            cardArray->addObject(card);
            
        }else{
            
            CardSprite *card = new CardSprite();
            card->cardImageFile = "sword";
            card->initWithSpriteFrameName("YellowCard");
            //Make card ability
            CardTargets *cardTargets = new PlayAreaTargets();
            cardTargets->initWithCardSprite(card);
            
            MoneyOffsetStatus *status = new MoneyOffsetStatus();
            status->initWithMoneyOffset(10);
            cardTargets->statuses->addObject(status);
            
            card->cardTargets = cardTargets;
            cardArray->addObject(card);
        }
    }
        updateInterface();
    return true;
}

void SolarSystemObject::update()
{
    //only increase population if planet is owned
    if(owner){
        populationFraction++;
        while(populationFraction > 4){
            population++;
            populationFraction -= 5;
        }
    }
    updateInterface();
}

void SolarSystemObject::updateInterface()
{
    CCString *populationString = CCString::createWithFormat("%i" , population);
    populationLabel->setString(populationString->getCString());
    CCString *incomeString = CCString::createWithFormat("%i", incomeGeneration);
    incomeLabel->setString(incomeString->getCString());
    nameLabel->setString(solarSystemName->getCString());
}

void SolarSystemObject::populationOffset(int populationOffset, int populationFractionOffset)
{
    population += populationOffset;
    populationFraction += populationFractionOffset;
    while(populationFraction > 4){
        population++;
        populationFraction -= 5;
    }
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
