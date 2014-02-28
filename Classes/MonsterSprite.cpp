//
//  MonsterSprite.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 11/20/13.
//
//

#include "MonsterSprite.h"
#include "GameManager.h"
#include "Player.h"
#include "Statuses.h"
#include "Constants.h"
#include "Utility.h"
#include "AnimationManager.h"
#include "AnimationObject.h"
#include "CCShake.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MonsterSprite::init()
{
    //////////////////////////////
    // 1. super init first
    
    if ( !CCSprite::initWithSpriteFrameName("monstercard2") )
    {
        return false;
    }
    BaseObject::initDefaultState();
    //    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    life = 4;
    maxLife = 4;
    attack = 2;
    location = 3;
    hasTaunt = false;
    hasRange = false;
    isBoss = false;
    summoningSickness = true;
    
    //details of card
    CCSize detailSize = CCSizeMake(325, 240);
    detailsLabel = CCLabelTTF::create("", Main_Font, 48, detailSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    detailsLabel->setColor(ccBLACK);
    detailsLabel->setPosition(ccp(240,235));
    this->addChild(detailsLabel);
    
    attackLabel = CCLabelTTF::create("2", LARGE_NUMBER_FONT, 128);
    lifeLabel =  CCLabelTTF::create("4", LARGE_NUMBER_FONT, 128);
    attackLabel->setColor(ccWHITE);
    lifeLabel->setColor(ccWHITE);
    
    attackLabel->setPosition(CCPointMake(85, 92));
    lifeLabel->setPosition(CCPointMake(379, 92));
    
    this->addChild(lifeLabel, 1);
    this->addChild(attackLabel, 1);
    
    activeStatusArray = new CCArray();
    activeStatusArray->init();
    killingBlowArray = new CCArray();
    killingBlowArray->init();
    afterDeathEffectArray = new CCArray();
    afterDeathEffectArray->init();
    this->setScale(DEFAULT_MONSTER_CARD_SCALE);
    
    glowSprite = CCSprite::createWithSpriteFrameName("cardGlow");
    glowSprite->setPosition(ccp(glowSprite->getContentSize().width/2 - 21,glowSprite->getContentSize().height/2 - 21));
    glowSprite->setVisible(false);
    glowSprite->setColor(ccGREEN);
    glowSprite->setScaleY(.7);
    this->addChild(glowSprite, -1);
    lifeRender = NULL;
    return true;
}

void MonsterSprite::enableInteractive(){
    glowSprite->setVisible(true);
    isInteractive = true;
}

void MonsterSprite::disableInteractive(){
    glowSprite->setVisible(false);
    isInteractive = false;
}

void MonsterSprite::updateInterface(){
    CCString *lifeString = CCString::createWithFormat("%i", life);
    lifeLabel->setString(lifeString->getCString());
    if(life < maxLife){
        lifeLabel->setColor(ccRED);
    }else{
        lifeLabel->setColor(ccWHITE);
    }
    
    CCString *attackString = CCString::createWithFormat("%i", attack);
    attackLabel->setString(attackString->getCString());
    if(lifeRender){
        lifeRender->removeFromParentAndCleanup(true);
        lifeRender = NULL;
    }
    
    if(attackRender){
        attackRender->removeFromParentAndCleanup(true);
        attackRender = NULL;
    }
    lifeRender = Utility::createTTFStroke(lifeLabel, 7, ccBLACK, 255);
    attackRender = Utility::createTTFStroke(attackLabel, 7, ccBLACK, 255);
    this->addChild(lifeRender);
    this->addChild(attackRender);
}


void MonsterSprite::onDeath(){
    CCObject *object;
    CCARRAY_FOREACH(afterDeathEffectArray, object){
        Status *status = (Status*)object;
        status->applyStatus();
    }
}

void MonsterSprite::turnUpdate(){
    if(!summoningSickness){
        //update status first
        for(int i = activeStatusArray->count() - 1; i >= 0 ;i--){
            Status *status = (Status*)activeStatusArray->objectAtIndex(i);
            status->updateStatus(this);
            if(status->checkEnd()){
                //should remove status
                status->applyEndStatus();
                activeStatusArray->removeObjectAtIndex(i);
            }
        }
        if(life > maxLife){
            life = maxLife;
        }
        if(life > 0){
            if(hasRange){
                //            GM->player->changeHealth(-attack);
                CCPoint monsterPos = ccp(180 + this->lane * 190, 520);
                CCMoveTo *action = CCMoveTo::create(.2, monsterPos);
                monsterPos = ccp(180 + this->lane * 190, 350);
                CCMoveTo *actionTwo = CCMoveTo::create(.1, monsterPos);
                monsterPos = ccp(180 + this->lane * 190, 400 + location * 30);
                CCMoveTo *actionThree = CCMoveTo::create(.05, monsterPos);
                
                CCSequence *seq = CCSequence::create(action, actionTwo, actionThree, NULL);
                AnimationObject *animationObject = new AnimationObject();
                animationObject->init(seq, this);
                if(!this->isZoomed){
                    animationObject->duration = .30;
                    AM->addAnimation(animationObject);
                }
                
                //screen shake
                //            CCDelayTime *delay = CCDelayTime::create(.3);
                CCShake *shakeAction = new CCShake();
                shakeAction->init(.3, ccp(10, 10), true, 0);
                //              CCSequence *shakeSeq = CCSequence::create(delay, shakeAction, NULL);
                //                GM->gameLayer->runAction(shakeSeq);
                animationObject = new AnimationObject();
                animationObject->initWithNode(shakeAction, GM->gameLayer);
                animationObject->duration = .05;
                AM->addAnimation(animationObject);
                
                //add damage
                //                            GM->player->changeHealth(-attack);
                CCCallFunc *obj = CCCallFunc::create(this, callfunc_selector(MonsterSprite::doDamage));
                AnimationObject *animationObject2 = new AnimationObject();
                animationObject->init(obj, this);
                animationObject->duration = .04;
                AM->addAnimation(animationObject2);
                
                
            }else{
                if(location > 0){
                    //move monster
                    location--;
                }else{
                    //attack human
                    //do attack animation
                    
                    CCPoint monsterPos = ccp(180 + this->lane * 190, 520);
                    CCMoveTo *action = CCMoveTo::create(.2, monsterPos);
                    monsterPos = ccp(180 + this->lane * 190, 350);
                    CCMoveTo *actionTwo = CCMoveTo::create(.1, monsterPos);
                    monsterPos = ccp(180 + this->lane * 190, 400);
                    CCMoveTo *actionThree = CCMoveTo::create(.05, monsterPos);
                    
                    CCSequence *seq = CCSequence::create(action, actionTwo, actionThree, NULL);
                    AnimationObject *animationObject = new AnimationObject();
                    animationObject->init(seq, this);
                    if(!this->isZoomed){
                        animationObject->duration = .28;
                        AM->addAnimation(animationObject);
                    }
                    
                    //screen shake
                    //                CCDelayTime *delay = CCDelayTime::create(.3);
                    
                    //                CCSequence *shakeSeq = CCSequence::create(delay, shakeAction, NULL);
                    //                GM->gameLayer->runAction(shakeSeq);
                    CCShake *shakeAction = new CCShake();
                    shakeAction->init(.3, ccp(10, 10), true, 0);
                    AnimationObject *animationObjectShake = new AnimationObject();
                    animationObjectShake->initWithNode(shakeAction, GM->gameLayer);
                    animationObjectShake->setDebugString(CCString::create("Shake Screen Animation"));
                    animationObjectShake->duration = .01;
                    AM->addAnimation(animationObjectShake);
                    
                    //add damage
                    //                GM->player->changeHealth(-attack);
                    CCCallFunc *obj = CCCallFunc::create(this, callfunc_selector(MonsterSprite::doDamage));
                    AnimationObject *animationObject2 = new AnimationObject();
                    animationObject2->initWithNode(obj, this);
                    animationObject2->duration = .01;
                    AM->addAnimation(animationObject2);
                }
            }
        }
    }
    
    if(life <= 0){
        isDead = true;
    }
    summoningSickness = false;
    
    //update monster labels
    updateInterface();
}

void MonsterSprite::setupMonsterImage(CCString* monserSpriteName)
{
    CCSprite *image = CCSprite::createWithSpriteFrameName(monserSpriteName->getCString());
    image->setPosition(ccp(235,473));
    this->addChild(image);
}

void MonsterSprite::changeMonsterAttack(int attackOffset)
{
    attack += attackOffset;
    if(attack < 1){
        attack = 1;
    }
}

void MonsterSprite::changeMonsterHealth(int healthOffset){
    if(healthOffset < 0){
        AM->createDamageIcon(healthOffset, this->getPosition());
    }
    life += healthOffset;
}

void MonsterSprite::doDamage()
{
    GM->player->changeHealth(-attack, ccp(this->getPosition().x, 290));
}

