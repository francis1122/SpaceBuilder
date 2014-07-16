//
//  Player.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/21/13.
//
//

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
#include "CardFactory.h"
#include "ResourceCardSprite.h"

USING_NS_CC;

Player::Player()
{
    this->deckCards = new CCArray();
    this->playedCards = new CCArray();
    this->discardCards = new CCArray();
    this->handCards = new CCArray();
    this->libraryCards = new CCArray();
    this->solarSystemArray = new CCArray();
    this->militaryTechCards = new CCArray();;
    this->industryTechCards = new CCArray();;
    this->expansionTechCards = new CCArray();;
    this->scienceTechCards = new CCArray();;
    deckCards->init();
    playedCards->init();
    discardCards->init();
    handCards->init();
    libraryCards->init();
    solarSystemArray->init();
    
    militaryTechCards->init();
    industryTechCards->init();
    expansionTechCards->init();
    scienceTechCards->init();

}

void Player::setupPlayer()
{
    money = 40;
    production = 40;
    militaryTech = 0;
    industryTech = 0;
    expansionTech = 0;
    scienceTech = 0;

    currentPlayCard = NULL;
    //addCards To library
    
    //get home solar system
    //SolarSystemObject *homeSystem = (SolarSystemObject*)solarSystemArray->objectAtIndex(0);
    
    for(int i = 0; i < 1; i++){
        militaryTechCards->addObject(CardFactory::randomMilitaryTierOneCard());
        industryTechCards->addObject(CardFactory::randomIndustryTierOneCard());
        expansionTechCards->addObject(CardFactory::randomExpansionTierOneCard());
        scienceTechCards->addObject(CardFactory::randomScienceTierOneCard());
    }
    
    //attack cards
    for(int i = 0; i < 4; i++){
        CardSprite *card;
        if(i == 0){
            card = CardFactory::colonize();
            acquireCard(card);
        }else if(i == 1){
            card = CardFactory::econResearch();
            acquireCard(card);
        }else if(i < 3){
            card = CardFactory::populationIncrease();
            acquireCard(card);
        }else{
            card = CardFactory::econOne();
            acquireCard(card);
        }

        /*
         card->cardImageFile = "sword";
         card->initWithSpriteFrameName("YellowCard");
         card->isPassive = true;
         card->detailsLabel->setString("Building: generate 5 money each turn");
         //Make card ability
         PassiveTargets *cardTargets = new PassiveTargets();
         cardTargets->initWithCardSprite(card);
         
         MoneyOffsetStatus *status = new MoneyOffsetStatus();
         status->initWithMoneyOffset(5);
         cardTargets->statuses->addObject(status);
         
         card->passiveTargets = cardTargets;
         acquireCard(card);
         */
    }
    
    /*
     //soul cards
     for(int i = 0; i < 4; i++){
     CardSprite *card = new CardSprite();
     card->cardImageFile = "images";
     card->initWithSpriteFrameName("NeutralCard");
     //Make card ability
     CardTargets *cardTargets = new PlayAreaTargets();
     cardTargets->initWithCardSprite(card);
     GainSoulStatus *status = new GainSoulStatus();
     status->initWithSoulGain(2);
     cardTargets->statuses->addObject(status);
     
     card->cardTargets = cardTargets;
     card->setupSoulGainCard(2);
     libraryCards->addObject(card);
     deckCards->addObject(card);
     }
     */
}

#pragma mark - card manipulation

void Player::reset(){
    discardHand();
    discardCards->removeAllObjects();
    playedCards->removeAllObjects();
    handCards->removeAllObjects();
    libraryCards->removeAllObjects();
    
    libraryCards->addObjectsFromArray(deckCards);
    shuffle(libraryCards);
    money = 10;
}


void Player::updateCardInterfaces()
{
    CCObject *object;
    CCARRAY_FOREACH(deckCards, object){
        CardSprite *card = (CardSprite*)object;
        card->updateInterface();
    }
}


void Player::organizeHand(){
    CCObject *object;
    int handSize = handCards->count();
    int i = 0;
    CCLog("Hand Organize");
    float centralPoint = 550;
    float cardOffset = 110;
    float startPoint = centralPoint - (cardOffset/2)*handSize;
    AnimationObject *animationHolder = new AnimationObject();
    animationHolder->init();
    
    CCARRAY_FOREACH(handCards, object){
        CardSprite *card = (CardSprite*)object;
        card->setScale(DEFAULT_CARD_SCALE);
        //card->setPosition(CCPointMake(startPoint + i * 110, 75));
        AnimationObject *animation = new AnimationObject();
        CCMoveTo *move = CCMoveTo::create(.3, CCPointMake(startPoint + i * 110, 75));
        animation->init(move, card);
        if(!card->isZoomed){
            animationHolder->addAnimation(animation);
        }else{
            CCLog("nothing");
        }
        i++;
    }
    animationHolder->duration = .05;
    AM->addAnimation(animationHolder);
    //    organizePlayedCards();
}

void Player::organizePlayedCards(){
    CCObject *object;
    int handSize = playedCards->count();
    int i = 0;
    CCLog("PlayedCards Organize");
    float centralPoint = 700;
    float cardOffset = 110;
    float startPoint = centralPoint - (cardOffset/2)*handSize;
    AnimationObject *animationHolder = new AnimationObject();
    animationHolder->init();
    CCARRAY_FOREACH(playedCards, object){
        CardSprite *card = (CardSprite*)object;
        card->setScale(.15);
        AnimationObject *animation = new AnimationObject();
        CCMoveTo *move = CCMoveTo::create(.3, CCPointMake(startPoint + i * 70, 260));
        animation->init(move, card);
        if(!card->isZoomed){
            animationHolder->addAnimation(animation);
        }
        i++;
    }
    if(currentPlayCard != NULL){
        currentPlayCard->setScale(.3);
        currentPlayCard->setPosition(ccp(650, 250));
    }
    animationHolder->duration = .05;
    AM->addAnimation(animationHolder);
}

void Player::removeCard(CardSprite *card)
{
    card->removeFromParent();
    deckCards->removeObject(card);
    handCards->removeObject(card);
    libraryCards->removeObject(card);
    playedCards->removeObject(card);
    discardCards->removeObject(card);
    
    if(card->isPassive){
        card->passiveTargets->removeAllObjects();
    }
    card->owner = NULL;
}

void Player::acquireCardInSolarSystemSpot(CardSprite *card, SolarSystemObject* solarSystem, int index)
{
    CardSprite *cardBeingReplaced = (CardSprite*)solarSystem->cardArray->objectAtIndex(index);
    removeCard(cardBeingReplaced);
    card->owner = this;
    solarSystem->cardArray->replaceObjectAtIndex(index, card, true);
    if(card->isPassive){
        card->passiveTargets->checkAllObjects();
    }
    this->deckCards->addObject(card);
    this->discardCards->addObject(card);
}

void Player::changeResearch(int researchOffset, ResearchTypes type)
{
    if(type == MilitaryTech){
        militaryTech += researchOffset;
    }else if(type == IndustryTech){
        industryTech += researchOffset;
    }else if(type == ExpansionTech){
        expansionTech += researchOffset;
    }else if(type == ScienceTech){
        scienceTech += researchOffset;
    }
    GM->gameLayer->updateInterface();
}

bool Player::canUpgradeCard(CardSprite* upgradeCard, CardSprite* toCard)
{
    //TODO: figure out which cards can be upgraded based on tech level and card research type
    if(money >= toCard->costToBuy){
        return true;
    }
    return false;
}

void Player::upgradeCard(CardSprite* upgradeCard, CardSprite* toCard)
{
    //upgradeCard needs to be part of player deck
    //rotate home planet to new card
    toCard->homeSolarSystem = upgradeCard->homeSolarSystem;
    toCard->homeSolarSystem->cardArray->removeObject(upgradeCard);
    toCard->homeSolarSystem->cardArray->addObject(toCard);
    
    acquireCard(toCard);
    removeCard(upgradeCard);
    militaryTechCards->removeObject(toCard);
}

void Player::acquireCard(CardSprite *card)
{
    card->owner = this;
    if(card->isPassive){
        card->passiveTargets->checkAllObjects();
    }
    this->deckCards->addObject(card);
    this->discardCards->addObject(card);
}

void Player::addCardToHand()
{
    if(libraryCards->count() > 0){
        CCObject *object = libraryCards->lastObject();
        CardSprite *card = (CardSprite*)object;
        card->setVisible(true);
        card->updateInterface();
        card->setScale(DEFAULT_CARD_SCALE);
        AnimationObject *animation = new AnimationObject();
        CCCallFunc *obj = CCCallFunc::create(card, callfunc_selector(CardSprite::addCard));
        animation->initWithNode(obj, GM->gameLayer);
        animation->duration = .001;
        AM->addAnimation(animation);
        handCards->addObject(card);
        libraryCards->removeLastObject();
    }else{
        if(discardCards->count() > 0){
            reshuffleLibrary();
            addCardToHand();
        }else{
            // no cards to draw
            CCLog("No Cards To Draw");
        }
    }
}

bool Player::canPlayCard(CardSprite *card)
{
    
    if(money < card->costToPlay){
        return false;
    }
    if(production < card->productionToPlay){
        return false;
    }
     
    return true;
}

void Player::playCard(CardSprite *card){
    //execute card
    card->setScale(.15);
    card->setVisible(false);
    money -= card->costToPlay;
    production -= card->productionToPlay;
    currentPlayCard = card;
    handCards->removeObject(card);
    GM->gameLayer->updateInterface();
    GM->player->organizeHand();
    GM->player->organizePlayedCards();
}

void Player::finishedPlayingCard(){
    if(currentPlayCard != NULL){
        //check if card should either go to discard, or do anything else
        playedCards->addObject(currentPlayCard);
        currentPlayCard = NULL;
        GM->player->organizeHand();
        GM->player->organizePlayedCards();
    }
}

void Player::discardCard(CardSprite* card)
{
    discardCards->addObject(card);
    card->removeFromParent();
    handCards->removeObject(card);
}

void Player::discardPlayedCards()
{
    CCObject *object;
    CCARRAY_FOREACH(playedCards, object){
        
        CardSprite *card = (CardSprite*)object;
        card->removeFromParent();
        card->disableInteractive();
        discardCards->addObject(object);
    }
    playedCards->removeAllObjects();
}

void Player::discardHand()
{
    CCObject *object;
    AnimationObject *holderAnimation = new AnimationObject();
    holderAnimation->init();
    CCARRAY_FOREACH(handCards, object){
        AnimationObject *animation = new AnimationObject();
        CardSprite *card = (CardSprite*)object;
        card->disableInteractive();
        discardCards->addObject(object);
        CCMoveTo *move = CCMoveTo::create(.4, ccp(900, 10));
        CCCallFunc *obj = CCCallFunc::create(card, callfunc_selector(CardSprite::removeCard));
        CCSequence *seq = CCSequence::createWithTwoActions(move, obj);
        animation->init(seq, card);
        holderAnimation->addAnimation(animation);
    }
    holderAnimation->duration = .4;
    AM->addAnimation(holderAnimation);
    handCards->removeAllObjects();
}

void Player::drawHand()
{
    for(int i = 0; i < 5; i++){
        addCardToHand();
    }
}

void Player::reshuffleLibrary()
{
    //when deck runs out, add card's research points to pool
    tickResearchCycle();
    
    libraryCards->addObjectsFromArray(discardCards);
    shuffle(libraryCards);
    discardCards->removeAllObjects();
    GM->gameLayer->updateInterface();
}

void Player::shuffle(CCArray *array)
{
    int count = array->count();
    for (int i = 0; i < count; ++i) {
        // Select a random element between i and end of array to swap with.
        int nElements = count - i;
        int n = arc4random_uniform(nElements) + i;
        array->exchangeObjectAtIndex(i, n);
    }
}

void Player::loseSolarSystem(SolarSystemObject *solarSystem)
{
    solarSystem->owner = NULL;
    for(int i = 0; i < solarSystem->cardArray->count(); i++){
        CardSprite *card = (CardSprite*)solarSystem->cardArray->objectAtIndex(i);
        this->removeCard(card);
    }
}

void Player::acquireSolarSystem(SolarSystemObject *solarSystem)
{
    //clean up previous solar system owner
    if(solarSystem->owner){
        solarSystem->owner->loseSolarSystem(solarSystem);
    }
    //acquire
    solarSystem->owner = this;
    for(int i = 0; i < solarSystem->cardArray->count(); i++){
        CardSprite *card = (CardSprite*)solarSystem->cardArray->objectAtIndex(i);
        this->acquireCard(card);
    }
    updateCardInterfaces();
}



void Player::changeMoney(int moneyOffset)
{
    if(moneyOffset > 0){
//        AM->createSoulIcon(moneyOffset, ccp(545,260));
    }
    this->money += moneyOffset;
}

void Player::changeCommandPoints(int commandPointsOffset)
{
    Player::changeCommandPoints(commandPointsOffset, ccp(470, 300));
}

void Player::changeCommandPoints(int commandPointsOffset, CCPoint point)
{
    GM->gameLayer->updateInterface();
    GM->gameStateCheck();
}


#pragma mark - research stuff

void Player::tickResearchCycle(){
    //figure out how many cards to produce and what tier player tech is
    
    cycleResearch(IndustryTech);
    cycleResearch(MilitaryTech);
    cycleResearch(ExpansionTech);
    cycleResearch(ScienceTech);
}

void Player::cycleResearch(ResearchTypes tech)
{
    
    int tier = getTechTier(tech);
    
    //choose right array
    CCArray *techArray;
    CardSprite* (*tierOne)();
    if(tech == MilitaryTech){
        tierOne = CardFactory::randomMilitaryTierOneCard;
        techArray = militaryTechCards;
    }else if(tech == IndustryTech){
    tierOne = CardFactory::randomIndustryTierOneCard;
        techArray = industryTechCards;
    }else if(tech == ExpansionTech){
    tierOne = CardFactory::randomExpansionTierOneCard;
        techArray = expansionTechCards;
    }else if(tech == ScienceTech){
        tierOne = CardFactory::randomScienceTierOneCard;
        techArray = scienceTechCards;
    }
    
    //clear old cards
    techArray->removeAllObjects();
    
    if(tier == 1){
        techArray->addObject(tierOne());
    }else if(tier == 2){
        techArray->addObject(tierOne());
        techArray->addObject(tierOne());
    }else if(tier == 3){
        techArray->addObject(tierOne());
        techArray->addObject(tierOne());
        techArray->addObject(tierOne());
    }else if(tier == 4){
        techArray->addObject(tierOne());
        techArray->addObject(tierOne());
        techArray->addObject(tierOne());
    }
}

int Player::getTechTier(ResearchTypes tech)
{
    int techPoints = 0;
    if(tech == MilitaryTech){
        techPoints = militaryTech;
    }else if(tech == IndustryTech){
        techPoints = industryTech;
    }else if(tech == ExpansionTech){
        techPoints = expansionTech;
    }else if(tech == ScienceTech){
        techPoints = scienceTech;
    }
    
    int tier = 1;
    if(techPoints > 50){
        tier = 2;
    }
    if(techPoints > 150){
        tier = 3;
    }
    if(techPoints > 400){
        tier = 4;
    }
    return tier;
}


int Player::getPointsTillNextTier(ResearchTypes tech)
{
    int techPoints = 0;
    if(tech == MilitaryTech){
        techPoints = militaryTech;
    }else if(tech == IndustryTech){
        techPoints = industryTech;
    }else if(tech == ExpansionTech){
        techPoints = expansionTech;
    }else if(tech == ScienceTech){
        techPoints = scienceTech;
    }
    int pointsRequired = 0;

    if(techPoints < 50){
        pointsRequired = 50 - techPoints;
    }
    if(techPoints < 150){
        pointsRequired = 150 - techPoints;
    }
    if(techPoints < 400){
        pointsRequired = 400 - techPoints;
    }
    return pointsRequired;
}

#pragma mark - resource generation
void Player::resourceGeneration(ResourceCardSprite *resource)
{
    if(resource->resourceType == FoodResource){
        resource->homeSolarSystem->populationOffset(0,1);
        resource->updateInterface();
    }else if(resource->resourceType == ProductionResource){
        production += calculateProductionGeneartion();
    }else if(resource->resourceType == MoneyResource){
        money += calculateMoneyGeneration();
    }else if(resource->resourceType == TechResource){
        industryTech += calculateTechGeneration();
    }
}

int Player::calculateMoneyGeneration()
{
    int moneyToAdd = 0;
    //cycle through all cards in deck
    CCObject *object;
    CCARRAY_FOREACH(deckCards, object){
        //find resource cards
        CardSprite *card = (CardSprite*) object;
        if(card->cardType == Resource){
            ResourceCardSprite *resourceCard = (ResourceCardSprite*)card;
            // check if it's the correct resource
            if(resourceCard->resourceType == MoneyResource){
                //multiply resource cards tier by homeplanets
                moneyToAdd += (resourceCard->homeSolarSystem->population) * (resourceCard->tier);
            }
        }
    }
    return moneyToAdd;
}

int Player::calculateProductionGeneartion()
{
    int productionToAdd = 0;
    //cycle through all cards in deck
    CCObject *object;
    CCARRAY_FOREACH(deckCards, object){
        //find resource cards
        CardSprite *card = (CardSprite*) object;
        if(card->cardType == Resource){
            ResourceCardSprite *resourceCard = (ResourceCardSprite*)card;
            // check if it's the correct resource
            if(resourceCard->resourceType == ProductionResource){
                //multiply resource cards tier by homeplanets
                productionToAdd += (resourceCard->homeSolarSystem->population) * (resourceCard->tier);
            }
        }
    }
    return productionToAdd;
}

int Player::calculateTechGeneration()
{
    int techToAdd = 0;
    //cycle through all cards in deck
    CCObject *object;
    CCARRAY_FOREACH(deckCards, object){
        //find resource cards
        CardSprite *card = (CardSprite*) object;
        if(card->cardType == Resource){
            ResourceCardSprite *resourceCard = (ResourceCardSprite*)card;
            // check if it's the correct resource
            if(resourceCard->resourceType == TechResource){
                //multiply resource cards tier by homeplanets
                techToAdd += (resourceCard->homeSolarSystem->population) * (resourceCard->tier);
            }
        }
    }
    return techToAdd;
}





