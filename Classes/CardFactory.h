//
//  CardFactory.h
//  RogueDeck
//
//  Created by Hunter Francis on 6/27/14.
//
//

#ifndef __RogueDeck__CardFactory__
#define __RogueDeck__CardFactory__

class CardSprite;
class ResourceCardSprite;
class CardFactory
{
    
public:
    CardFactory();

    
    
    
    //card creation fuctions
    
    //resource cards
    static ResourceCardSprite *food();
    static ResourceCardSprite *production();
    static ResourceCardSprite *money();
    static ResourceCardSprite *tech();
    
    //neutral cards
    //tier one
    static CardSprite* colonize();
    
    
    //
    //military cards
    //
    
    static CardSprite* randomMilitaryTierOneCard();
    
    //tier one
    
    //
    //econ cards
    //
    static CardSprite* randomIndustryTierOneCard();
    //tier one
    static CardSprite* econOne();
    static CardSprite* improveNeutralEcon();

    static CardSprite* populationIncrease();
    static CardSprite* drawTwo();
    
    //
    //expansion
    //
    static CardSprite* randomExpansionTierOneCard();
    
    //tier one
    
    //
    //science cards
    //
    static CardSprite* randomScienceTierOneCard();
    
    //tier one
    static CardSprite* econResearch();
    static CardSprite* militaryResearch();
    static CardSprite* expansionResearch();
    static CardSprite* scienceResearch();
    
};

#endif /* defined(__RogueDeck__CardFactory__) */

