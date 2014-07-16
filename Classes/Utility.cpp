//
//  Utility.cpp
//  RogueDeck
//
//  Created by Hunter Francis on 1/18/14.
//
//

#include "Utility.h"


USING_NS_CC;

CCRenderTexture* Utility::createTTFStroke(CCSprite* label, int size, ccColor3B color, GLubyte opacity)
{
    CCRenderTexture* rt = CCRenderTexture::create(label->getTexture()->getContentSize().width + size * 2,
                                                  label->getTexture()->getContentSize().height+size * 2);
    
    
    
    CCPoint originalPos = label->getPosition();
    
    ccColor3B originalColor = label->getColor();
    
    GLubyte originalOpacity = label->getOpacity();
    
    bool originalVisibility = label->isVisible();
    
    label->setColor(color);
    
    label->setOpacity(opacity);
    
    label->setVisible(true);
    
    ccBlendFunc originalBlend = label->getBlendFunc();
    
    ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE};
    
    label->setBlendFunc(bf);
    
    CCPoint bottomLeft = ccp(
                             label->getTexture()->getContentSize().width * label->getAnchorPoint().x + size,
                             label->getTexture()->getContentSize().height * label->getAnchorPoint().y + size);
    
    //    CCPoint positionOffset= ccp(
    //                                - label->getTexture()->getContentSize().width / 2,
    //                                - label->getTexture()->getContentSize().height / 2);
    //
    
    //原來沒有判斷AnchorPoint的寫法
    //  CCPoint positionOffset= ccp(   - label->getTexture()->getContentSize().width / 2,
    //                                  - label->getTexture()->getContentSize().height / 2);
    //SetAnchorPoint會影響到positionOffset，所以要做判斷
    CCPoint positionOffset = CCPointZero;
    if(label->getAnchorPoint().x == 0.5f){
        positionOffset.x = 0;
    }else if(label->getAnchorPoint().x == 0.0f){
        positionOffset.x =- label->getTexture()->getContentSize().width / 2;
    }else{
        positionOffset.x = label->getTexture()->getContentSize().width/2;
    }
    if(label->getAnchorPoint().y == 0.5f){
        positionOffset.y = 0;
    }else if(label->getAnchorPoint().y == 0.0f){
        positionOffset.y =- label->getTexture()->getContentSize().height / 2;
    }else{
        positionOffset.y =  label->getTexture()->getContentSize().height/2;
    }
    
    CCPoint position = ccpSub(originalPos, positionOffset);
    
    rt->begin();
    
    for (int i=0; i<360; i+= 15) // you should optimize that for your needs
    {
        label->setPosition(
                           ccp(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*size, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*size)
                           );
        label->visit();
    }
    rt->end();
    
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    label->setVisible(originalVisibility);
    label->setOpacity(originalOpacity);
    
    rt->setPosition(position);
    
    return rt;
}


CCSprite *Utility::getSpriteFromSprite(CCSprite *citySprite, float citySpriteWidth, float citySpriteHeight)
{
    CCPoint prevPosition = citySprite->getPosition();
    
    //Set position in order to make it fit inside CCRenderTexture (You can change this later)
    citySprite->setPosition(ccp(citySpriteWidth/2, citySpriteHeight/2));
    citySprite->setPosition(ccp(0, 0));
    
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


