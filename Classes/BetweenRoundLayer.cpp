//
//  BetweenRoundLayer.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/26/13.
//
//

#include "BetweenRoundLayer.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "Player.h"
#include "Constants.h"
#include "LevelTemplate.h"
//USING_NS_CC;
//USING_NS_CC_EXT

CCScene* BetweenRoundLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BetweenRoundLayer *layer = BetweenRoundLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool BetweenRoundLayer::init()
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
                                                          menu_selector(BetweenRoundLayer::startRound));
 */
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
    
    
    this->topNode = CCLayer::create();
    this->bottomNode = CCLayer::create();
    this->topNode->setPosition(ccp(0, visibleSize.height - TOP_BAR_HEIGHT));
    
    this->addChild(topNode, 1);
    this->addChild(bottomNode, 0);
    
    
    //topdescription
    CCSize titleSize = CCSizeMake(visibleSize.width - 500, 100);
    this->levelTitle = CCLabelTTF::create("",
                                               Main_Bold_Font,
                                               48,
                                               titleSize,
                                               kCCTextAlignmentCenter,
                                               kCCVerticalTextAlignmentCenter);
    this->levelTitle->setColor(ccBLACK);
    this->levelTitle->setPosition(ccp(visibleSize.width/2 - 80   , 140));
    topNode->addChild(levelTitle, 10);
    
    
        CCSize detailSize = CCSizeMake(visibleSize.width - 500, TOP_BAR_HEIGHT);
    this->levelDescription =CCLabelTTF::create("",
                                               Main_Font,
                                               36,
                                               detailSize,
                                               kCCTextAlignmentLeft,
                                               kCCVerticalTextAlignmentCenter);
    this->levelDescription->setColor(ccBLACK);
    this->levelDescription->setPosition(ccp(visibleSize.width/2 - 80   , 80));
    topNode->addChild(levelDescription, 10);
    
    startButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("StartButton_Normal"),
                                                            CCSprite::createWithSpriteFrameName("StartButton_Pressed"),
                                                            this,
                                                            menu_selector(BetweenRoundLayer::startRound));
    startButton->setEnabled(false);
	startButton->setPosition(ccp(visibleSize.width - 230,
                                80));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(startButton, NULL);
    pMenu->setPosition(CCPointZero);
    topNode->addChild(pMenu, 3);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    CCSprite* title = CCSprite::createWithSpriteFrameName("textbox");
    // position the label on the center of the screen
    title->setPosition(ccp(origin.x + visibleSize.width/2,
                           TOP_BAR_HEIGHT - 140));
    
    // add the label as a child to this layer
    topNode->addChild(title, 1);
    
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("map");
    pSprite->setPosition(ccp(pSprite->getContentSize().width/2,
                             pSprite->getContentSize().height/2));
    
    // add the sprite as a child to this layer
    bottomNode->addChild(pSprite, 0);
    int currentLevel = GM->currentLevel;
    
    float startNode = 200;
    float nodeOffset = 200;
    
    selectedSprite =  CCSprite::createWithSpriteFrameName("Button_Pressed");
    selectedSprite->setPosition(CCPointZero);
    selectedSprite->setVisible(false);
    bottomNode->addChild(selectedSprite, 10);
    
    //create the 'level' nodes to show the player's progress
    for(int i = 0; i < GM->possibleLevelArray->count(); i++){
        
        if(i < currentLevel){
            CCSprite *levelNode = CCSprite::createWithSpriteFrameName("Button");
            levelNode->setScale(.6);
            levelNode->setPosition(ccp(startNode + i * nodeOffset, 200));
            bottomNode->addChild(levelNode);
        }else if(i > currentLevel){
            CCSprite *levelNode = CCSprite::createWithSpriteFrameName("monsterIcon");
            levelNode->setScale(.6);
            levelNode->setPosition(ccp(startNode + i * nodeOffset, 200));
            bottomNode->addChild(levelNode);
        }else if(i == currentLevel){
            int levelNumber = GM->currentLevel;
            CCArray *levels = (CCArray*)GM->possibleLevelArray->objectAtIndex(levelNumber);
            CCArray *menuItems = new CCArray();
            menuItems->init();
            menuItems->autorelease();
            for(int j = 0; j < levels->count(); j++){
                CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("monsterIcon"),
                                                                        CCSprite::createWithSpriteFrameName("monsterIcon"),
                                                                        this,
                                                                        menu_selector(BetweenRoundLayer::levelSelected));
                pCloseItem->setPosition(ccp(startNode + i * nodeOffset, 80 + 100 * j));
                pCloseItem->setTag(j);
                pCloseItem->setScale(.6);
                menuItems->addObject(pCloseItem);
            }
            CCMenu* pMenu = CCMenu::createWithArray(menuItems);
            pMenu->setPosition(CCPointZero);
            bottomNode->addChild(pMenu, 1);
        }
    }
    return true;
}

void BetweenRoundLayer::levelSelected(CCObject* pSender)
{
    CCMenuItemSprite *pCloseItem = (CCMenuItemSprite*)pSender;
    selectedSprite->setVisible(true);
    selectedSprite->setPosition(pCloseItem->getPosition());
    startButton->setEnabled(true);
    
    int levelNumber = GM->currentLevel;
    CCArray *levels = (CCArray*)GM->possibleLevelArray->objectAtIndex(levelNumber);
    LevelTemplate *levelTemplate = (LevelTemplate*)levels->objectAtIndex(pCloseItem->getTag());
    if(levelTemplate){
        levelDescription->setString(levelTemplate->levelDescription->getCString());
        levelTitle->setString(levelTemplate->levelName->getCString());
        selectedLevel = levelTemplate;
    }
//    pSender->setSel
}

void BetweenRoundLayer::startRound(CCObject* pSender)
{
    //load game scene
    // create a scene. it's an autorelease object
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameLayer::scene();
    
    // run
    pDirector->replaceScene(pScene);

    
    if(selectedLevel != NULL){
        GM->startNewRound(selectedLevel);
    }
}

#pragma mark - touch code


CCArray* GameLayer::allTouchesFromSet(CCSet *touches)
{
    CCArray *arr = new CCArray();
    
    CCSetIterator it;
    
	for( it = touches->begin(); it != touches->end(); it++)
    {
        arr->addObject((CCTouch *)*it);
    }
    return arr;
}

bool BetweenRoundLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{

    // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
    CCPoint pointOne = touch->getLocationInView();
    
    // The touch points are always in "portrait" coordinates - convert to landscape
    pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
    //*2 adjusts for pixel something
    if(pointOne.y > TOP_BAR_HEIGHT * 2 ){
        return false;
    }
    
    previousTouch = pointOne;
    
    
    
    return true;
    /*    // This method is passed an NSSet of touches called (of course) "touches"
     // We need to convert it to an array first
     CCArray *allTouches = this->allTouchesFromSet(touches);
     CCTouch* fingerOne = (CCTouch *)allTouches->objectAtIndex(0);
     
     // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
     CCPoint pointOne = fingerOne->getLocationInView();
     
     // The touch points are always in "portrait" coordinates - convert to landscape
     pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
     
     // We store the starting point of the touch so we can determine whether the touch is a swipe or tap.
     */
}

void BetweenRoundLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
    CCPoint pointOne = touch->getLocationInView();
    
    // The touch points are always in "portrait" coordinates - convert to landscape
    pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
    
    //move bottom node
    CCPoint pos = this->bottomNode->getPosition();
    CCPoint dif = ccpSub(pointOne, previousTouch);
    this->bottomNode->setPosition(ccp(pos.x + dif.x, 0));
    //clamp
    if(this->bottomNode->getPosition().x >= 0){
        this->bottomNode->setPosition(ccp(0, 0));
    }
    if(this->bottomNode->getPosition().x <= -800){
        this->bottomNode->setPosition(ccp(-800, 0));
    }
    previousTouch = pointOne;


    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    /*    CCArray *allTouches = this->allTouchesFromSet(touches);
     
     // Only run the following code if there is more than one touch
     if (allTouches->count() > 1)
     {
     // We're going to track the first two touches (i.e. first two fingers)
     // Create "UITouch" objects representing each touch
     CCTouch* fingerOne = (CCTouch *)allTouches->objectAtIndex(0);
     
     // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
     CCPoint pointOne = fingerOne->getLocationInView();
     
     // The touch points are always in "portrait" coordinates - you will need to convert them if in landscape (which we are)
     pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
     }
     */
}

void BetweenRoundLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

}

void BetweenRoundLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event){

    
}

