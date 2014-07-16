//
//  CardFactory.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/27/14.
//
//

#include "CardFactory.h"

#include "Player.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "HandLayer.h"
#include "Statuses.h"
#include "CardTargets.h"
#include "Constants.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "CardSprite.h"
#include "Targets.h"
#include "SolarSystemObject.h"
#include "Constants.h"
#include "ResourceCardSprite.h"

USING_NS_CC;

CardFactory::CardFactory()
{
    
}

#pragma mark - Resource Cards

ResourceCardSprite *CardFactory::food()
{
    ResourceCardSprite *card = new ResourceCardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("Resource_food");
    card->resourceType = FoodResource;
    card->cardType = Resource;
    card->cardNameLabel->setString("food");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

ResourceCardSprite *CardFactory::production()
{
    ResourceCardSprite *card = new ResourceCardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("Resource_production");
    card->resourceType = ProductionResource;
    card->cardType = Resource;
    card->cardNameLabel->setString("production");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

ResourceCardSprite *CardFactory::money()
{
    ResourceCardSprite *card = new ResourceCardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("Resource_money");
    card->resourceType = MoneyResource;
    card->cardType = Resource;
    card->cardNameLabel->setString("money");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

ResourceCardSprite *CardFactory::tech()
{
    ResourceCardSprite *card = new ResourceCardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("Resource_science");
    card->resourceType = TechResource;
    card->cardType = Resource;
    card->cardNameLabel->setString("tech");
    //Make card ability
    CardTargets *cardTargets = new ResearchTargets();
    cardTargets->initWithCardSprite(card);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

#pragma mark - Neutral Cards

#pragma mark tier one

CardSprite* CardFactory::colonize()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 40;
    card->detailsLabel->setString("colonize card");
    card->cardNameLabel->setString("Colonize");
    
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetNeutralSystems = true;
    ColonizeStatus *status = new ColonizeStatus();
    status->init();
    cardTargets->statuses->addObject(status);
    
    
    card->researchType =  ExpansionTech;
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}


#pragma mark - Military Cards

CardSprite* CardFactory::randomMilitaryTierOneCard()
{
    int rnd = arc4random()%4;
    if(rnd == 0){
        return econOne();
    }else if(rnd == 1){
        return improveNeutralEcon();
    }else if(rnd == 2){
        return econOne();
    }else if(rnd == 3){
        return populationIncrease();
    }else if(rnd == 4){
        return drawTwo();
    }
    return econOne();
}


#pragma mark tier 1

#pragma mark - Economy Cards

CardSprite* CardFactory::randomIndustryTierOneCard()
{
    int rnd = arc4random()%4;
    if(rnd == 0){
        return econOne();
    }else if(rnd == 1){
        return improveNeutralEcon();
    }else if(rnd == 2){
        return econOne();
    }else if(rnd == 3){
        return populationIncrease();
    }else if(rnd == 4){
        return drawTwo();
    }
    return econOne();
}

#pragma mark tier one
CardSprite* CardFactory::econOne()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 6;
    card->detailsLabel->setString("Gain 10 money");
    card->cardNameLabel->setString("matured investment");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    MoneyOffsetStatus *status = new MoneyOffsetStatus();
    status->initWithMoneyOffset(10);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}
CardSprite* CardFactory::improveNeutralEcon()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->costToPlay = 0;
    card->productionToPlay = 2;
    card->detailsLabel->setString("increase income of neutral solar system by 1");
    card->cardNameLabel->setString("terraform");
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = false;
    cardTargets->targetNeutralSystems = true;
    
    
    IncomeOffsetStatus *status = new IncomeOffsetStatus();
    status->initWithIncomeOffset(1);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}



CardSprite* CardFactory::populationIncrease()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("increase population of solar system by 0.1");
    card->cardNameLabel->setString("forced copulations");
    card->productionToPlay = 5;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    
    PopulationOffsetStatus *status = new PopulationOffsetStatus();
    status->initWithPopulationOffset(0, 1);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::drawTwo()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    card->detailsLabel->setString("Draw 2 cards");
    card->cardNameLabel->setString("Divination");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    CardDrawStatus *status = new CardDrawStatus();
    status->initWithCardDraw(2);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}


#pragma mark - expansion

CardSprite* CardFactory::randomExpansionTierOneCard()
{
    int rnd = arc4random()%4;
    if(rnd == 0){
        return militaryResearch();
    }else if(rnd == 1){
        return expansionResearch();
    }else if(rnd == 2){
        return econResearch();
    }else if(rnd == 3){
        return scienceResearch();
    }
    return econOne();
}


#pragma mark tier one

#pragma mark - science

CardSprite* CardFactory::randomScienceTierOneCard()
{
    int rnd = arc4random()%4;
    if(rnd == 0){
        return militaryResearch();
    }else if(rnd == 1){
        return expansionResearch();
    }else if(rnd == 2){
        return econResearch();
    }else if(rnd == 3){
        return scienceResearch();
    }
    return econOne();
}


#pragma mark tier 1

CardSprite* CardFactory::econResearch()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    card->detailsLabel->setString("gain 20 industry research");
    card->cardNameLabel->setString("industry theory I");
    
    ResearchOffsetStatus *status = new ResearchOffsetStatus();
    status->initWithResearchOffset(20, IndustryTech);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}


CardSprite* CardFactory::militaryResearch()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    card->detailsLabel->setString("gain 20 military research");
    card->cardNameLabel->setString("military theory I");
    
    ResearchOffsetStatus *status = new ResearchOffsetStatus();
    status->initWithResearchOffset(20, MilitaryTech);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::expansionResearch()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    card->detailsLabel->setString("gain 20 expansion research");
    card->cardNameLabel->setString("expansion theory I");
    
    ResearchOffsetStatus *status = new ResearchOffsetStatus();
    status->initWithResearchOffset(20, ExpansionTech);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::scienceResearch()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    card->detailsLabel->setString("gain 20 science research");
    card->cardNameLabel->setString("science theory I");
    
    ResearchOffsetStatus *status = new ResearchOffsetStatus();
    status->initWithResearchOffset(20, ScienceTech);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}



