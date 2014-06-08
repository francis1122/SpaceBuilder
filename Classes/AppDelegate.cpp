#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "TitleLayer.h"
#include "PostRoundLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    float scrWidth = CCEGLView::sharedOpenGLView()->getFrameSize().width;
    float scrHeight= CCEGLView::sharedOpenGLView()->getFrameSize().height;
    
    
    CCSize designSize = CCSizeMake(scrWidth, scrHeight);

    std::vector<std::string> res;
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    if(scrWidth == 480 || scrHeight == 480){
        res.push_back("sd");
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(1.0f);
    }else if(scrWidth == 640 || scrHeight == 640){
        res.push_back("ipadhd");
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(1.0f);//why does cocos2d resize the sprites and make them really small with content scaling 2??? is it a bug in cocos2d-x?
    
    }else if(scrWidth == 1024 || scrHeight == 1024){ //ipad mini and old ipads
        res.push_back("hd");
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(2.0f);//why does cocos2d resize the sprites and make them really small with content scaling 2??? is it a bug in cocos2d-x?
    
    }else if(scrWidth == 2048 || scrHeight == 2048){ //ipad retina and mac platform
        res.push_back("ipadhd");
        designSize = CCSizeMake(1024, 768);
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(2.0f);
    }
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(res);
    frameCache->addSpriteFramesWithFile("RogueCardsDoc_RougeCards.plist");
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = TitleLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
