//
//  MonsterTemplate.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/9/14.
//
//

#include "MonsterTemplate.h"



bool MonsterTemplate::init(float powerLevel){
    monsterPower = powerLevel;
    this->powerLevel = powerLevel;
    augmentationDescription = NULL;
    rewardDescription = NULL;
    
    return true;
}

MonsterSprite* MonsterTemplate::createMonster(){
    CCLog("MonsterTemplate::createdMonster");
    
    createdMonster = new MonsterSprite();
    createdMonster->init();
    
    //chance of additional cost
    
    
    //chance of augmentation
    addAugmentationStatus();
    
    //add main status
    this->addMainStats();
    
    addRewards();
    
    
    //add text to card
    this->addDescriptionText();
    
    return createdMonster;
}

void MonsterTemplate::addAugmentationStatus()
{
    
}


void MonsterTemplate::addMainStats()
{
    
}


void MonsterTemplate::addRewards()
{
    
    
}


void MonsterTemplate::addDescriptionText()
{
    const char* augDesc = "";
    if(augmentationDescription) augDesc = augmentationDescription->getCString();
    const char* reward = "";
    if(rewardDescription) reward= rewardDescription->getCString();
    CCString *detailsString =CCString::createWithFormat("%s%s", augDesc, reward);
    createdMonster->detailsLabel->setString(detailsString->getCString());
}


