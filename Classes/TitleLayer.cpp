//
//  TitleLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/17/13.
//
//

#include "TitleLayer.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "Constants.h"

USING_NS_CC;

CCScene* TitleLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleLayer *layer = TitleLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("StartButton_Normal"),
                                                            CCSprite::createWithSpriteFrameName("StartButton_Pressed"),
                                                            this,
                                                            menu_selector(TitleLayer::startGame));
    
	pCloseItem->setPosition(ccp(visibleSize.width/2,
                                150));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
//    CCLabelTTF* pLabel = CCLabelTTF::create("Rogue Deck", Main_Font, 24);
     CCSprite* title = CCSprite::createWithSpriteFrameName("Title");
    // position the label on the center of the screen
    title->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - title->getContentSize().height + 60));
    
    // add the label as a child to this layer
    this->addChild(title, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("MenuBG");
    pSprite->setPosition(ccp(pSprite->getContentSize().width/2,
                           pSprite->getContentSize().height/2));
    
    // position the sprite on the center of the screen
//  pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void TitleLayer::startGame(CCObject* pSender)
{

    //load game scene
    // create a scene. it's an autorelease object
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameLayer::scene();
    
    // run
    pDirector->replaceScene(pScene);
    GM->startNewGame();

}
