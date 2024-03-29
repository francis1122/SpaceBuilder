//
//  EmpireCardLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/15/14.
//
//

#include "EmpireCardLayer.h"

#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"
#include "Constants.h"
#include "SolarSystemObject.h"
#include "UIState.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool EmpireCardLayer::init()
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

    
    cardSpriteArray = new CCArray();
    cardSpriteArray->init();
    
    
    ///top bar stuff
    CCSprite *backSprite =CCSprite::createWithSpriteFrameName("Button");
    backSprite->setColor(ccYELLOW);
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(backSprite,
                                                            CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                            this,
                                                            menu_selector(EmpireCardLayer::backButtonPress));
	backButton->setPosition(ccp(50, visibleSize.height - 50));
    backButton->setScale(.7);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(backButton, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1002);
    
    CCLabelTTF *backButtonLabel = CCLabelTTF::create("back", Main_Font, 48);
    backButtonLabel->setPosition(ccp(100, visibleSize.height - 100));
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


CCSprite *EmpireCardLayer::getSpriteFromSprite(CCSprite *citySprite, float citySpriteWidth, float citySpriteHeight)
{
    CCPoint prevPosition = citySprite->getPosition();
    
    //Set position in order to make it fit inside CCRenderTexture (You can change this later)
    citySprite->setPosition(ccp(citySpriteWidth/2, citySpriteHeight/2));
    
    CCRenderTexture *render = CCRenderTexture::create(citySpriteWidth, citySpriteWidth);
    render->beginWithClear(0, 0, 0, 0);
    citySprite->visit();
    render->end();
    
    citySprite->setPosition(prevPosition);
    
    CCTexture2D *tex = render->getSprite()->getTexture();
    CCSprite *newCitySprite = CCSprite::createWithTexture(tex);
    newCitySprite->setFlipY(true);  //Texture might be upside down
    return newCitySprite;
}

void EmpireCardLayer::updateInterface(SolarSystemObject *solarSystem)
{
    /*
    CCString *populationString = CCString::createWithFormat(" %i - %i population %i" , solarSystem->population, solarSystem->populationLimit, solarSystem->populationFraction);
    population->setString(populationString->getCString());
    CCString *incomeString = CCString::createWithFormat("%i income", solarSystem->incomeGeneration);
    income->setString(incomeString->getCString());
    CCString *cardLimitString = CCString::createWithFormat("%i cardLimit", solarSystem->cardSlots);
    cardLimit->setString(cardLimitString->getCString());
    solarSystemName->setString(solarSystem->solarSystemName->getCString());
    
    //clear out old cards
    for(int i = 0; i < cardSpriteArray->count(); i++){
        CCSprite *card = (CCSprite*)cardSpriteArray->objectAtIndex(i);
        this->removeChild(card);
    }
    cardSpriteArray->removeAllObjects();
    //create cards
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    for(int i = 0; i < solarSystem->cardArray->count(); i++){
        CCSprite *card = (CCSprite*)solarSystem->cardArray->objectAtIndex(i);
        CCSprite *cardCopy = this->getSpriteFromSprite(card, card->getContentSize().width, card->getContentSize().height);
        cardCopy->setPosition(ccp(200, 450 - i * 100));
        this->addChild(cardCopy, 4);
        cardSpriteArray->addObject(cardCopy);
    }
    */
}

void EmpireCardLayer::backButtonPress(CCObject *pSender)
{
    CCLog("leftButtonPressed");
    //GM->gameLayer->getCurrentState()->transitionToNormalState();
    GM->gameLayer->empireCardLayer->setVisible(false);
}