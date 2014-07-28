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
#include "BuildingObject.h"

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
    buildingSlots = 2;
    //array for actual cards
    //CCArray
    population = 0;
    populationLimit = 6;
    populationGrowth = 1;
    cardArray = new CCArray();
    buildingsArray = new CCArray();
    connectedSystems = new CCArray();
    
    cardArray->init();
    buildingsArray->init();
    connectedSystems->init();
    solarSystemName = NULL;
    
    planetSize = Small;
    planetType = Terran;
    
    populationLabel = CCLabelTTF::create("1", Main_Font, 48);
    nameLabel = CCLabelTTF::create("test", Main_Font, 48);
    resourceGeneration = CCLabelTTF::create("test", Main_Font, 48);
    
    populationLabel->setPosition(ccp(15,47));
    nameLabel->setPosition(ccp(135,47));
    resourceGeneration->setPosition(ccp(90, -18));
    
    this->addChild(populationLabel, 11);
    this->addChild(nameLabel, 11);
    this->addChild(resourceGeneration, 12);
    
    
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
    populationGrowth = 1;
    cardArray->removeAllObjects();
    cardSlots = 6;
    //random cards should be added to planets on creation
    for(int i = 0; i < cardSlots; i++){
        ResourceCardSprite *card;
        if(i == 0 || i == 1){
            card = CardFactory::food();
            card->tier = 1;
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
        card->updateInterface();
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
        if(population >= populationLimit){
            population = populationLimit;
            populationFraction = 0;
            updateInterface();
            owner->updateCardInterfaces();
        }else{
            populationFraction += populationGrowth;
            while(populationFraction > 9){
                population++;
                populationFraction -= 10;
                owner->updateCardInterfaces();
            }
        }
    }
    //update buildings
    for(int i = 0; i < buildingsArray->count(); i++){
        BuildingObject *building = (BuildingObject*)buildingsArray->objectAtIndex(i);
        for(int j = 0; j < building->statusArray->count(); j++){
            Status *status = (Status*)building->statusArray->objectAtIndex(j);
            status->updateStatus(this);
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
    
    //resource calculation
    if(owner){
        int foodTier = getSystemsResourceTier(FoodResource);
        int moneyTier = getSystemsResourceTier(MoneyResource);
        int productionTier = getSystemsResourceTier(ProductionResource);
        int scienceTier = getSystemsResourceTier(TechResource);
        resourceGeneration->setString(CCString::createWithFormat("%i %i %i %i", foodTier, moneyTier * population, productionTier * population, scienceTier * population)->getCString() );
    }else{
        // check for certain resource cards
        int foodTier = getSystemsResourceTier(FoodResource);
        int moneyTier = getSystemsResourceTier(MoneyResource);
        int productionTier = getSystemsResourceTier(ProductionResource);
        int scienceTier = getSystemsResourceTier(TechResource);
        resourceGeneration->setString(CCString::createWithFormat("%i %i %i %i", foodTier, moneyTier, productionTier, scienceTier)->getCString() );
    }
    
}

int SolarSystemObject::getSystemsResourceTier(ResourceTypes type){
    int tier = 0;
    for(int i = 0;i < cardArray->count(); i++){
        ResourceCardSprite *card = (ResourceCardSprite*)cardArray->objectAtIndex(i);
        if(card->resourceType == type){
            tier += card->tier;
        }
    }
    return tier;
}

bool SolarSystemObject::addResourceCard(ResourceCardSprite* card)
{
    if(cardArray->count() < SYSTEM_RESOURCECARD_LIMIT){
        card->homeSolarSystem = this;
        cardArray->addObject(card);
        cardSlots++;
        if(owner){
            owner->acquireCard(card);
        }
        GM->gameLayer->updateInterface();
        return true;
    }else{
        return false;
    }
}

void SolarSystemObject::populationOffset(int populationOffset, int populationFractionOffset)
{
    if(population >= populationLimit){
        population = populationLimit;
        populationFraction = 0;
        updateInterface();
        return;
    }
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

#pragma mark - building manager

//add structure
void SolarSystemObject::addBuilding(BuildingObject *building)
{
    if(buildingsArray->count() < buildingSlots){
        
        buildingsArray->addObject(building);
        building->onAddingToSystem(this);
    }
}

//remove structure
void SolarSystemObject::removeBuilding(BuildingObject *building)
{
    //fire status effects on remove
    building->onRemovalFromSystem(this);
    buildingsArray->removeObject(building);
}

#pragma mark - card managing

void SolarSystemObject::replaceCardAtIndex(CardSprite *card, int index)
{
    
}
