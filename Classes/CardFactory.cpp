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
#include "Constants.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "CardSprite.h"
#include "Targets.h"
#include "SolarSystemObject.h"
#include "Constants.h"
#include "ResourceCardSprite.h"
#include "Ability.h"
#include "AbilityTargets.h"

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

ResourceCardSprite *CardFactory::waste()
{
    ResourceCardSprite *card = new ResourceCardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("Resource_waste");
    card->resourceType = WasteResource;
    card->cardType = Resource;
    card->cardNameLabel->setString("waste");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
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
    card->detailsLabel->setString("Ship: 1-1 colony");
    card->cardNameLabel->setString("Colony Ship");
    card->productionToPlay = 50;
    card->populationToPlay = 1;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    
    MoveShipStatus *status = new MoveShipStatus();
    status->init();
    
    SolarSystemAbilityTargets *abilityTargets = new SolarSystemAbilityTargets();
    //need to assign ship modedl later
    abilityTargets->init();
    abilityTargets->adjacentOnly = true;
    abilityTargets->needsFuel = true;
    abilityTargets->statuses->addObject(status);
    
    CCString *string = new CCString();
    string->initWithFormat("Command-hd");
    abilityTargets->normalCommandImage = string;
    string = new CCString();
    string->initWithFormat("Command_Pressed-hd");
    abilityTargets->selectedCommandImage = string;
    
    
    ColonizeStatus *statusColonize = new ColonizeStatus();
    statusColonize->init();

    
    PlayAbilityTargets *playAbilityTargets = new PlayAbilityTargets();
    //need to assign ship modedl later
    playAbilityTargets->init();
    playAbilityTargets->targetNeutralSystems = true;
    playAbilityTargets->statuses->addObject(statusColonize);
    
    string = new CCString();
    string->initWithFormat("Ability_Colonize");
    playAbilityTargets->normalCommandImage = string;
    string = new CCString();
    string->initWithFormat("Ability_Colonize_selected");
    playAbilityTargets->selectedCommandImage = string;
    
    
    CreateShipStatus *shipStatus = new CreateShipStatus();
    shipStatus->init();
    shipStatus->shipTitle = new CCString("Scout Ship");
    shipStatus->shipDescription = new CCString("2-2 ship");
    shipStatus->shipSpriteName = new CCString("tech_military");
    

    
    
    shipStatus->health = 1;
    shipStatus->attack = 0;
    shipStatus->abilities->addObject(abilityTargets);
    shipStatus->abilities->addObject(playAbilityTargets);
    
    
    cardTargets->statuses->addObject(shipStatus);
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
    
}

CardSprite* CardFactory::scoutShip()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("Ship: 0-2");
    card->cardNameLabel->setString("Scout Ship");
    card->productionToPlay = 20;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    
    MoveShipStatus *status = new MoveShipStatus();
    status->init();
    
    SolarSystemAbilityTargets *abilityTargets = new SolarSystemAbilityTargets();
    //need to assign ship modedl later
    abilityTargets->init();
    abilityTargets->adjacentOnly = true;
    abilityTargets->needsFuel = true;
    
    CCString *string = new CCString();
    string->initWithFormat("Command-hd");
    abilityTargets->normalCommandImage = string;
    string = new CCString();
    string->initWithFormat("Command_Pressed-hd");
    abilityTargets->selectedCommandImage = string;
    
    abilityTargets->statuses->addObject(status);
    
    
    CreateShipStatus *shipStatus = new CreateShipStatus();
    shipStatus->init();
    shipStatus->shipTitle = new CCString("Scout Ship");
    shipStatus->shipDescription = new CCString("2-2 ship");
    shipStatus->shipSpriteName = new CCString("tech_military");
    shipStatus->health = 2;
    shipStatus->attack = 2;
    shipStatus->abilities->addObject(abilityTargets);
    
    
    cardTargets->statuses->addObject(shipStatus);
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
        return econOne();
    }else if(rnd == 2){
        return populationIncrease();
    }else if(rnd == 3){
        return drawTwo();
    }
    return econOne();
}


#pragma mark tier 1

#pragma mark - Economy Cards

CardSprite* CardFactory::randomIndustryTierOneCard()
{
    int rnd = arc4random()%6;
    if(rnd == 0){
        return econOne();
    }else if(rnd == 1){
        return productionResourceCardCreation();
    }else if(rnd == 2){
        return populationIncrease();
    }else if(rnd == 3){
        return drawTwoDiscardTwo();
        return drawTwo();
    }else if(rnd == 4){
        return productionImprovementBuilding();
    }else if(rnd == 5){
        return contractors();
    }
    return econOne();
}

CardSprite* CardFactory::randomIndustryTierTwoCard()
{
    int rnd = arc4random()%2;
    if(rnd == 0){
        return drawTwoDiscardOne();
    }else if(rnd == 1){
        return productionResourceCardTwoCreation();
    }
    return econOne();
}

CardSprite* CardFactory::randomIndustryTierThreeCard()
{
    int rnd = arc4random()%2;
    if(rnd == 0){
        return drawTwo();
    }else if(rnd == 1){
        return productionResourceCardTwoCreation();
    }
    return econOne();
}

#pragma mark tier one
CardSprite* CardFactory::econOne()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 40;
    card->detailsLabel->setString("Gain 20 money");
    card->cardNameLabel->setString("matured investment");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    MoneyOffsetStatus *status = new MoneyOffsetStatus();
    status->initWithMoneyOffset(20);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::contractors()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    card->costToPlay = 40;
    card->detailsLabel->setString("Gain 20 production");
    card->cardNameLabel->setString("contractors");
    //Make card ability
    CardTargets *cardTargets = new PlayAreaTargets();
    cardTargets->initWithCardSprite(card);
    
    ProductionOffsetStatus *status = new ProductionOffsetStatus();
    status->initWithProductionOffset(20);
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
    card->detailsLabel->setString("increase population of solar system by 0.5");
    card->cardNameLabel->setString("forced copulations");
    card->productionToPlay = 25;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    PopulationOffsetStatus *status = new PopulationOffsetStatus();
    status->initWithPopulationOffset(0, 2);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::drawTwoDiscardTwo()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    card->detailsLabel->setString("Draw 2 cards, Discard 2");
    card->cardNameLabel->setString("Divination");
    //Make card ability
    CardTargets *cardTargets = new DrawDiscardTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetAmount = 2;
    
    CardDrawStatus *status = new CardDrawStatus();
    status->initWithCardDraw(2);
    cardTargets->initialStatuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}



CardSprite* CardFactory::productionImprovementBuilding()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("Building: generates 4 production each turn");
    card->cardNameLabel->setString("Factory I");
    card->productionToPlay = 25;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    ProductionOffsetStatus *status = new ProductionOffsetStatus();
    status->initWithProductionOffset(4);
    
    CreateBuildingStatus *buildingStatus = new CreateBuildingStatus();
    buildingStatus->init();
    buildingStatus->buildingTitle = new CCString("Factory I");
    buildingStatus->buildingDescription = new CCString("generates 5 production each turn");
    buildingStatus->buildingSpriteName = new CCString("planets_dead");
    buildingStatus->buildingStatuses->addObject(status);
    
    cardTargets->statuses->addObject(buildingStatus);
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::productionResourceCardCreation()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("give friendly system tier 1 production resource card");
    card->cardNameLabel->setString("Terraforming");
    card->productionToPlay = 20;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    CreateResourceCardStatus *status = new CreateResourceCardStatus();
    status->initWithResourceCard(ProductionResource, 1);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}


#pragma mark tier 2


CardSprite* CardFactory::drawTwoDiscardOne()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->productionToPlay = 0;
    card->detailsLabel->setString("Draw 2 cards, Discard 1");
    card->cardNameLabel->setString("Divination");
    //Make card ability
    CardTargets *cardTargets = new DrawDiscardTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetAmount = 1;
    
    CardDrawStatus *status = new CardDrawStatus();
    status->initWithCardDraw(2);
    cardTargets->initialStatuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::productionResourceCardTwoCreation()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("give friendly system tier 2 production resource card");
    card->cardNameLabel->setString("Terraforming");
    card->productionToPlay = 20;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    CreateResourceCardStatus *status = new CreateResourceCardStatus();
    status->initWithResourceCard(ProductionResource, 2);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

#pragma mark tier 3

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


#pragma mark - Expansion Cards

CardSprite* CardFactory::randomExpansionTierOneCard()
{
    int rnd = arc4random()%2;
    if(rnd == 0){
        return populationImprovementBuilding();
    }else if(rnd == 1){
        return foodResourceCardCreation();
    }
    return econOne();
}

CardSprite* CardFactory::randomExpansionTierTwoCard()
{
    int rnd = arc4random()%1;
    if(rnd == 0){
        return foodResourceCardTwoCreation();
    }
    return econOne();
}

#pragma mark tier one


CardSprite* CardFactory::foodResourceCardCreation()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("give friendly system tier 1 food resource card");
    card->cardNameLabel->setString("Terraforming");
    card->productionToPlay = 20;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    CreateResourceCardStatus *status = new CreateResourceCardStatus();
    status->initWithResourceCard(FoodResource, 1);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::populationImprovementBuilding()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("Building: increase population growth by 1");
    card->cardNameLabel->setString("Planned Cities");
    card->productionToPlay = 40;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;

    PopulationOffsetStatus *status = new PopulationOffsetStatus();
    status->initWithPopulationOffset(0, 1);
    
    CreateBuildingStatus *buildingStatus = new CreateBuildingStatus();
    buildingStatus->init();
    buildingStatus->buildingTitle = new CCString("Planned Cities");
    buildingStatus->buildingDescription = new CCString("increase population growth by 1");
    buildingStatus->buildingSpriteName = new CCString("planets_lava");
    buildingStatus->buildingStatuses->addObject(status);
    
    cardTargets->statuses->addObject(buildingStatus);
    card->cardTargets = cardTargets;
    card->updateInterface();
    
    return card;
}

#pragma mark tier 2

CardSprite* CardFactory::foodResourceCardTwoCreation()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->costToBuy = 100;
    card->detailsLabel->setString("give friendly system tier 2 food resource card");
    card->cardNameLabel->setString("Terraforming");
    card->productionToPlay = 50;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    CreateResourceCardStatus *status = new CreateResourceCardStatus();
    status->initWithResourceCard(FoodResource, 2);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

#pragma mark - science

CardSprite* CardFactory::randomScienceTierOneCard()
{
    int rnd = arc4random()%6;
    if(rnd == 0){
        return militaryResearch();
    }else if(rnd == 1){
        return expansionResearch();
    }else if(rnd == 2){
        return econResearch();
    }else if(rnd == 3){
        return scienceResearch();
    }else if(rnd == 4){
        return researchBuilding();
    }else if(rnd == 5){
        return techResourceCardCreation();
    }
    return econOne();
}

CardSprite* CardFactory::randomScienceTierTwoCard()
{
    int rnd = arc4random()%1;
    if(rnd == 0){
        return techResourceCardTwoCreation();
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

CardSprite* CardFactory::researchBuilding()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("Building: increase all techs by 5 each turn");
    card->cardNameLabel->setString("Research Lab");
    card->productionToPlay = 30;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    ResearchOffsetStatus *statusMilitary = new ResearchOffsetStatus();
    statusMilitary->initWithResearchOffset(5, MilitaryTech);
    ResearchOffsetStatus *statusIndustry = new ResearchOffsetStatus();
    statusIndustry->initWithResearchOffset(5, IndustryTech);
    ResearchOffsetStatus *statusExpansion = new ResearchOffsetStatus();
    statusExpansion->initWithResearchOffset(5, ExpansionTech);
    ResearchOffsetStatus *statusScience = new ResearchOffsetStatus();
    statusScience->initWithResearchOffset(5, ScienceTech);
    
    CreateBuildingStatus *buildingStatus = new CreateBuildingStatus();
    buildingStatus->init();
    buildingStatus->buildingTitle = new CCString("Research Lab");
    buildingStatus->buildingDescription = new CCString("increase all techs by 5 each turn");
    buildingStatus->buildingSpriteName = new CCString("planets_arid");
    buildingStatus->buildingStatuses->addObject(statusMilitary);
    buildingStatus->buildingStatuses->addObject(statusIndustry);
    buildingStatus->buildingStatuses->addObject(statusExpansion);
    buildingStatus->buildingStatuses->addObject(statusScience);
    
    cardTargets->statuses->addObject(buildingStatus);
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

CardSprite* CardFactory::techResourceCardCreation()
{
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->detailsLabel->setString("give friendly system tier 1 tech resource card");
    card->cardNameLabel->setString("Terraforming");
    card->productionToPlay = 20;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    CreateResourceCardStatus *status = new CreateResourceCardStatus();
    status->initWithResourceCard(TechResource, 1);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}

#pragma mark tier 2

CardSprite* CardFactory::techResourceCardTwoCreation(){
    CardSprite *card = new CardSprite();
    card->cardImageFile = "sword";
    card->initWithSpriteFrameName("spaceCards");
    card->costToBuy = 100;
    card->detailsLabel->setString("give friendly system tier 2 tech resource card");
    card->cardNameLabel->setString("Terraforming");
    card->productionToPlay = 50;
    //Make card ability
    SolarSystemTargets *cardTargets = new SolarSystemTargets();
    cardTargets->initWithCardSprite(card);
    cardTargets->targetFriendlySystems = true;
    
    CreateResourceCardStatus *status = new CreateResourceCardStatus();
    status->initWithResourceCard(TechResource , 2);
    cardTargets->statuses->addObject(status);
    
    card->cardTargets = cardTargets;
    card->updateInterface();
    return card;
}




