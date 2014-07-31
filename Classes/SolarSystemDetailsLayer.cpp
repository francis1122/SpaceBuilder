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
#include "UIState.h"
#include "BuildingObject.h"

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
    CCLayerColor *bg = CCLayerColor::create(ccc4(0, 0, 0,255));
    //     bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
    
    population = CCLabelTTF::create("10 population", Main_Font, 48);
    solarSystemName = CCLabelTTF::create("Solar System Name", Main_Font, 88);
    resourceGenerationLabel = CCLabelTTF::create("resource generation", Main_Font, 48);
    
    population->setPosition(ccp(790,  visibleSize.height - 60));
    solarSystemName->setPosition(ccp(320, visibleSize.height - 50));
    resourceGenerationLabel->setPosition(ccp(200, visibleSize.height - 150));
    
    
    this->addChild(population, 3);
    this->addChild(solarSystemName, 40);
    this->addChild(resourceGenerationLabel, 41);
    
    
    cardSpriteArray = new CCArray();
    cardSpriteArray->init();
    
    
    ///top bar stuff
    CCSprite *backSprite =CCSprite::createWithSpriteFrameName("Button");
    backSprite->setColor(ccYELLOW);
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(backSprite,
                                          CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                          this,
                                          menu_selector(SolarSystemDetailsLayer::backButtonPress));
	backButton->setPosition(ccp(50, visibleSize.height - 50));
    backButton->setScale(.7);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(backButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1002);
    
    CCLabelTTF *backButtonLabel = CCLabelTTF::create("back", Main_Font, 48);
    backButtonLabel->setPosition(ccp(85, visibleSize.height - 70));
    this->addChild(backButtonLabel, 1003);
    
    
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


CCSprite *SolarSystemDetailsLayer::getSpriteFromSprite(CCSprite *citySprite, float citySpriteWidth, float citySpriteHeight)
{
    CCPoint prevPosition = citySprite->getPosition();
    
    //Set position in order to make it fit inside CCRenderTexture (You can change this later)
    citySprite->setPosition(ccp(citySpriteWidth/2, citySpriteHeight/2));
    
    CCRenderTexture *render = CCRenderTexture::create(citySpriteWidth, citySpriteHeight);
    render->beginWithClear(0, 0, 0, 0);
    citySprite->visit();
    render->end();
    
    citySprite->setPosition(prevPosition);
    
    CCTexture2D *tex = render->getSprite()->getTexture();
    CCSprite *newCitySprite = CCSprite::createWithTexture(tex);
    newCitySprite->setFlipY(true);  //Texture might be upside down
    return newCitySprite;
}

void SolarSystemDetailsLayer::updateInterface(SolarSystemObject *solarSystem)
{
    
    CCString *populationString = CCString::createWithFormat("pop %i - %i\n%i" , solarSystem->population, solarSystem->populationLimit, solarSystem->populationFraction);
    population->setString(populationString->getCString());

    solarSystemName->setString(solarSystem->solarSystemName->getCString());
    
    
    if(solarSystem->owner){
        //RESOURCE GENERATION
        int foodTier = solarSystem->getSystemsResourceTier(FoodResource);
        int moneyTier = solarSystem->getSystemsResourceTier(MoneyResource);
        int productionTier = solarSystem->getSystemsResourceTier(ProductionResource);
        int scienceTier = solarSystem->getSystemsResourceTier(TechResource);
        resourceGenerationLabel->setString(CCString::createWithFormat("%i %i %i %i", foodTier, moneyTier * solarSystem->population, productionTier * solarSystem->population, scienceTier * solarSystem->population)->getCString() );
        
    }else{
        //RESOURCE GENERATION
        int foodTier = solarSystem->getSystemsResourceTier(FoodResource);
        int moneyTier = solarSystem->getSystemsResourceTier(MoneyResource);
        int productionTier = solarSystem->getSystemsResourceTier(ProductionResource);
        int scienceTier = solarSystem->getSystemsResourceTier(TechResource);
        resourceGenerationLabel->setString(CCString::createWithFormat("%i %i %i %i", foodTier, moneyTier, productionTier, scienceTier)->getCString() );

    }
    //buildings
    for(int i = 0; i < solarSystem->buildingSlots ; i++){
        CCSprite *buildingSprite;
        if(i < solarSystem->buildingsArray->count()){
            BuildingObject *building = (BuildingObject*)solarSystem->buildingsArray->objectAtIndex(i);
            buildingSprite = CCSprite::createWithSpriteFrameName(building->buildingSpriteName->getCString());
        }else{
            buildingSprite = CCSprite::createWithSpriteFrameName("Button_Pressed");
        }
        buildingSprite->setPosition(ccp(700 + 70 * i, 300));
        this->addChild(buildingSprite, 100);
    }
    
    
    //clear out old cards
    for(int i = 0; i < cardSpriteArray->count(); i++){
        CCSprite *card = (CCSprite*)cardSpriteArray->objectAtIndex(i);
        this->removeChild(card);
    }
    cardSpriteArray->removeAllObjects();
    //create cards
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    for(int i = 0; i < solarSystem->cardArray->count(); i++){
        CCSprite *card = (CCSprite*)solarSystem->cardArray->objectAtIndex(i);
//       save scale scale
        float savedScale = card->getScale();
        bool isVisible = card->isVisible();
        card->setScale(1);
        card->setVisible(true);
        CCSprite *cardCopy = this->getSpriteFromSprite(card, card->getContentSize().width, card->getContentSize().height);
        card->setScale(savedScale);
        card->setVisible(isVisible);
        cardCopy->setScale(.20);
        CCPoint position;
        if( i < 4){
            cardCopy->setPosition(ccp(130 + i * 115 , 385 ));
        }else{
            cardCopy->setPosition(ccp(130 + (i-3) * 115, 230));
        }

        this->addChild(cardCopy, 4);
        cardSpriteArray->addObject(cardCopy);
    }
    
}

void SolarSystemDetailsLayer::backButtonPress(CCObject *pSender)
{
    CCLog("leftButtonPressed");
    GM->gameLayer->getCurrentState()->transitionToNormalState();
}