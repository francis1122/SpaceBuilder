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
    static ResourceCardSprite *waste();
    
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
    static CardSprite* randomIndustryTierTwoCard();
    
    //tier one
    static CardSprite* econOne();
    static CardSprite* contractors();

    static CardSprite* populationIncrease();
    static CardSprite* drawTwo();
    static CardSprite* productionImprovementBuilding();
    static CardSprite* productionResourceCardCreation();
    
    //tier two
    static CardSprite* productionResourceCardTwoCreation();
    
    //
    //expansion
    //
    static CardSprite* randomExpansionTierOneCard();
    
    static CardSprite* randomExpansionTierTwoCard();
    
    //tier one
    static CardSprite* foodResourceCardCreation();
    static CardSprite* populationImprovementBuilding();
    
    //tier two
    
    static CardSprite* foodResourceCardTwoCreation();
    
    //
    //science cards
    //
    static CardSprite* randomScienceTierOneCard();
    static CardSprite* randomScienceTierTwoCard();
    
    //tier one
    static CardSprite* econResearch();
    static CardSprite* militaryResearch();
    static CardSprite* expansionResearch();
    static CardSprite* scienceResearch();
    static CardSprite* researchBuilding();
    static CardSprite* techResourceCardCreation();
    
    //tier two
    static CardSprite* techResourceCardTwoCreation();
    
};

#endif /* defined(__RogueDeck__CardFactory__) */

