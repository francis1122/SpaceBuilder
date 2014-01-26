//
//  PostRoundLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#include "PostRoundLayer.h"
#include "BetweenRoundLayer.h"
#include "Constants.h"


USING_NS_CC;

CCScene* PostRoundLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    PostRoundLayer *layer = PostRoundLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PostRoundLayer::init()
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
/*    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(PostRoundLayer::nextRound));
    */
    CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("StartButton_Normal"),
                                                            CCSprite::createWithSpriteFrameName("StartButton_Pressed"),
                                                            this,
                                                            menu_selector(PostRoundLayer::nextRound));
	pCloseItem->setPosition(ccp(visibleSize.width/2,
                                100));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("Victory");
    pSprite->setPosition(ccp(pSprite->getContentSize().width/2,
                             pSprite->getContentSize().height/2));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void PostRoundLayer::nextRound(CCObject* pSender)
{
    //load game scene
    // create a scene. it's an autorelease object
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = BetweenRoundLayer::scene();
    
    // run
    pDirector->replaceScene(pScene);
}


