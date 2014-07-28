//
//  ResearchLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 6/27/14.
//
//

#include "ResearchLayer.h"


#include "GameManager.h"
#include "UIState.h"
#include "GameLayer.h"
#include "Constants.h"
#include "SolarSystemObject.h"
#include "UIState.h"
#include "Utility.h"
#include "Player.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ResearchLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCLayerColor *bg = CCLayerColor::create(ccc4(50, 50, 50,255));
    //     bg->setPosition(ccp( bg->getContentSize().width/2, bg->getContentSize().height/2 + 310));
    this->addChild(bg);
    
    this->cardSpriteArray = new CCArray();
    cardSpriteArray->init();
    cardMenu = NULL;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //
    ///top bar stuff
    //
    CCSprite *backSprite =CCSprite::createWithSpriteFrameName("Button");
    backSprite->setColor(ccYELLOW);
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(backSprite,
                                                            CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                            this,
                                                            menu_selector(ResearchLayer::backButtonPress));
    backButton->setScale(.8);
    
    CCSprite *militarySprite =CCSprite::createWithSpriteFrameName("Button");
    militarySprite->setColor(ccYELLOW);
    CCMenuItemSprite *militaryButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tech_military"),
                                                                CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                                this,
                                                                menu_selector(ResearchLayer::militaryButtonPress));
    militaryButton->setScale(.3);
    
    CCSprite *industrySprite = CCSprite::createWithSpriteFrameName("Button");
    industrySprite->setColor(ccYELLOW);
    CCMenuItemSprite *industryButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tech_industry"),
                                                                CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                                this,
                                                                menu_selector(ResearchLayer::industryButtonPress));
    industryButton->setScale(.3);
    
    CCSprite *expansionSprite =CCSprite::createWithSpriteFrameName("Button");
    expansionSprite->setColor(ccYELLOW);
    CCMenuItemSprite *expansionButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tech_expansion"),
                                                                 CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                                 this,
                                                                 menu_selector(ResearchLayer::expansionButtonPress));
    expansionButton->setScale(.3);
    
    CCMenuItemSprite *scienceButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tech_science"),
                                                               CCSprite::createWithSpriteFrameName("Button_Pressed"),
                                                               this,
                                                               menu_selector(ResearchLayer::scienceButtonPress));
    scienceButton->setScale(.3);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(backButton, militaryButton, industryButton, expansionButton, scienceButton, NULL);
    
    pMenu->setPosition(ccp(75, 395));
    pMenu->alignItemsVerticallyWithPadding(0);
    this->addChild(pMenu, 1002);
    
    
    CCLabelTTF *backButtonLabel = CCLabelTTF::create("back", Main_Font, 48);
    backButtonLabel->setPosition(ccp(100, visibleSize.height - 70));
    this->addChild(backButtonLabel, 1003);
    
    titleLabel = CCLabelTTF::create("Military Tech", Main_Font, 52);
    titleLabel->setPosition(ccp(410, visibleSize.height - 50));
    
    this->addChild(titleLabel, 3);
    
    return true;
}


void ResearchLayer::updateInterface()
{
    //update title
    //currentTech
    CCArray *researchCardArray;
    int tillNext = GM->player->getPointsTillNextTier(currentTech);
    if(currentTech == MilitaryTech){
        CCString *researchString = CCString::createWithFormat("Military Tech %i\n %i till next level", GM->player->militaryTech, tillNext);
        titleLabel->setString(researchString->getCString());
        researchCardArray = GM->player->militaryTechCards;
    }else if(currentTech == IndustryTech){
        CCString *researchString = CCString::createWithFormat("Industry Tech %i\n %i till next level", GM->player->industryTech, tillNext);
        titleLabel->setString(researchString->getCString());
        researchCardArray = GM->player->industryTechCards;
    }else if(currentTech == ExpansionTech){
        CCString *researchString = CCString::createWithFormat("Expansion Tech %i\n %i till next level", GM->player->expansionTech, tillNext);
        titleLabel->setString(researchString->getCString());
        researchCardArray = GM->player->expansionTechCards;
    }else if(currentTech == ScienceTech){
        CCString *researchString = CCString::createWithFormat("Science Tech %i\n %i till next level", GM->player->scienceTech, tillNext);
        titleLabel->setString(researchString->getCString());
        researchCardArray = GM->player->scienceTechCards;
    }
    
    //    researchCards
    //clear out old cards
    
    if(cardMenu){
        cardMenu->removeAllChildren();
        this->removeChild(cardMenu);
    }
    cardMenu = NULL;
    cardSpriteArray->removeAllObjects();
    
    //create cards
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    for(int i = 0; i < 5; i++){
        CardSprite *card = NULL;
        //grab the correct card for the slot being created
        for(int j = 0; j < researchCardArray->count(); j++){
            CardSprite *cardA = (CardSprite*)researchCardArray->objectAtIndex(j);
            if(cardA->researchSlot == i){
                card = cardA;
                break;
            }
        }

        if(card){
                //        this->addChild(card);
                //        card->setPosition(CCPointZero);
                //        this->addChild(card);
                //        float scale = card->getScale();
                card->setScale(1);
                
                //        CCSprite *cardCopy = Utility::getSpriteFromSprite(card, card->getContentSize().width, card->getContentSize().height);
                //      card->setScale(scale);
                //        cardCopy->setScale(scale);
                CCPoint position;
                //        cardCopy->setScale(.4);
                
                CCMenuItemSprite *cardButton = CCMenuItemSprite::create(    card,
                                                                        CCSprite::createWithSpriteFrameName("spaceCards"),
                                                                        this,
                                                                        menu_selector(ResearchLayer::cardPressed));
                cardButton->setTag(i);
                cardButton->setScale(.35);
                cardButton->setPosition(CCPointZero);
                cardSpriteArray->addObject(cardButton);
                
                CCLabelTTF *money = CCLabelTTF::create("$50", Main_Font, 72);
                money->setPosition(ccp(225, -70));
                cardButton->addChild(money);
                if(i > 1){
                    money->setString("$200");
                }

            
        }else{
            
            CCMenuItemSprite *cardButton = CCMenuItemSprite::create( CCSprite::createWithSpriteFrameName("blankCard"),
                                                                    CCSprite::createWithSpriteFrameName("spaceCards"),
                                                                    this,
                                                                    menu_selector(ResearchLayer::cardPressed));
            cardButton->setTag(i);
            cardButton->setScale(.35);
            cardButton->setPosition(CCPointZero);
            cardSpriteArray->addObject(cardButton);
        }
        //        this->removeChild(card);
    }
    
    cardMenu = CCMenu::createWithArray(cardSpriteArray);
    //menu creation
    cardMenu->setPosition(ccp(610 , 380 ));
    cardMenu->setAnchorPoint(ccp(0.0, 0.5));
    cardMenu->alignItemsHorizontallyWithPadding(00);
    this->addChild(cardMenu, 1003);
}

void ResearchLayer::cardPressed(CCMenuItemSprite *pSender){
    CCArray *researchCardArray;
    if(currentTech == MilitaryTech){
        researchCardArray = GM->player->militaryTechCards;
    }else if(currentTech == IndustryTech){
        researchCardArray = GM->player->industryTechCards;
    }else if(currentTech == ExpansionTech){
        researchCardArray = GM->player->expansionTechCards;
    }else if(currentTech == ScienceTech){
        researchCardArray = GM->player->scienceTechCards;
    }
    
    int tag = pSender->getTag();
    if(tag < researchCardArray->count()){
        CardSprite *card = (CardSprite*)researchCardArray->objectAtIndex(tag);
        //check if player has enough money to buy card
        if(card->costToBuy <= GM->player->money){
            //purchase the cards if enough money is available
            GM->player->money -= card->costToBuy;
            card->setAnchorPoint(ccp(0.5, 0.5));
            GM->player->acquireCard(card);
            researchCardArray->removeObjectAtIndex(tag);
        }
    }
    updateInterface();
    GM->gameLayer->updateInterface();
}

void ResearchLayer::backButtonPress(CCObject *pSender)
{
    CCLog("leftButtonPressed");
    GM->gameLayer->getCurrentState()->transitionToNormalState();
    this->setVisible(false);
}

void ResearchLayer::militaryButtonPress(CCObject *pSender)
{
    CCLog("militaryButtonPress");
    currentTech = MilitaryTech;
    updateInterface();
}

void ResearchLayer::industryButtonPress(CCObject *pSender)
{
    CCLog("industryButtonPress");
    currentTech = IndustryTech;
    updateInterface();
}


void ResearchLayer::expansionButtonPress(CCObject *pSender)
{
    CCLog("expansionButtonPress");
    currentTech = ExpansionTech;
    updateInterface();
}


void ResearchLayer::scienceButtonPress(CCObject *pSender)
{
    CCLog("scienceButtonPress");
    currentTech = ScienceTech;
    updateInterface();
}


