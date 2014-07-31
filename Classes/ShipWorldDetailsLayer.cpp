//
//  ShipWorldDetailsLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 7/28/14.
//
//

#include "ShipWorldDetailsLayer.h"
#include "GameManager.h"
#include "CardSprite.h"
#include "Constants.h"
#include "SolarSystemObject.h"
#include "ShipModel.h"
#include "Ability.h"
#include "AbilityTargets.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ShipWorldDetailsLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("PlayerHolder");
    pSprite->setColor(ccYELLOW);
    //    pSprite->initWithSpriteFrameName("background");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 300));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    //labels
    shipNameLabel = CCLabelTTF::create("", Main_Font, 48);
    locationLabel = CCLabelTTF::create("", Main_Font, 24);
    lifeLabel = CCLabelTTF::create("", Main_Font, 32);
    attackLabel = CCLabelTTF::create("", Main_Font, 32);
    
    shipNameLabel->setPosition(ccp(150, 100));
    locationLabel->setPosition(ccp(400, 100));
    lifeLabel->setPosition(ccp(280, 40));
    attackLabel->setPosition(ccp(100, 40));
    /*    discardCountLabel->setPosition(ccp(80, 35));
     moneyLabel->setPosition(ccp(visibleSize.width - 160, 90));
     commandPointsLabel->setPosition(ccp(visibleSize.width - 160, 30));
     */
    
    
    this->addChild(shipNameLabel, 100);
    this->addChild(locationLabel, 100);
    this->addChild(lifeLabel, 100);
    this->addChild(attackLabel, 100);
    return true;
}



void ShipWorldDetailsLayer::updateInterface(ShipModel *shipModel){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    
//    CCString *shipNameString = CCString::createWithFormat("%s", );
    shipNameLabel->setString(shipModel->name->getCString());
    locationLabel->setString(shipModel->location->nameLabel->getString());
    attackLabel->setString(CCString::createWithFormat("attack: %i", shipModel->attack)->getCString());
    lifeLabel->setString(CCString::createWithFormat("hull: %i", shipModel->health)->getCString());
    
    this->removeChild(abilityMenu);
    abilityMenu = CCMenu::create();
    abilityMenu->setPosition(ccp(visibleSize.width - 300, 100));
    for(int i = 0; i < shipModel->abilitiesArray->count(); i++){
//        activateAbility
        
        Ability *ability = (Ability*)shipModel->abilitiesArray->objectAtIndex(i);
        CCMenuItemSprite *button = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(ability->targets->normalCommandImage->getCString()),
                                                            CCSprite::createWithSpriteFrameName(ability->targets->selectedCommandImage->getCString()),
                                                            ability,
                                                            menu_selector(Ability::activateAbility));
        button->setScale(.75);
        button->setTag(i);
        if(ability->checkIfActivatable()){
            button->setEnabled(true);
        }else{
            button->setEnabled(false);
        }
        abilityMenu->addChild(button);
    }
    
    // create menu, it's an autorelease object
    abilityMenu->alignItemsHorizontally();
    this->addChild(abilityMenu, 102);
    
    
    /*    CCString *discardCountString =CCString::createWithFormat("%i", GM->player->discardCards->count());
     discardCountLabel->setString(discardCountString->getCString());
     CCString *moneyString =CCString::createWithFormat("money:%i", GM->player->money);
     moneyLabel->setString(moneyString->getCString());
     CCString *commandPointsString =CCString::createWithFormat("production:%i", GM->player->production);
     commandPointsLabel->setString(commandPointsString->getCString());
     
     */
}

void ShipWorldDetailsLayer::abilityButtonPressed(CCObject *pSender)
{
    
}
