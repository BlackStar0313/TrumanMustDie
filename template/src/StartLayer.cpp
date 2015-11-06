//
//  StartLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/29.
//
//

#include <stdio.h>
#include "StartLayer.h"
#include "ShootLayer.h"

StartLayer::StartLayer()
{
    
}

StartLayer::~StartLayer()
{
    
}

CCScene* StartLayer::createScene()
{
    CCScene *scene = CCScene::create();
    if ( !scene )
    {
        return NULL;
    }
    StartLayer *layer = StartLayer::create();
    scene->addChild(layer);
    return scene;
}


bool StartLayer::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }
    
    setTouchEnabled(true);
    setTouchMode(ccTouchesMode::kCCTouchesOneByOne);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF* playLabel = CCLabelTTF::create("Press Screen Start", "Arial", 50);
    playLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 2 / 3));
    CCActionInterval *fadeIn = CCFadeIn::create(1);
    CCActionInterval *fadeOut = CCFadeOut::create(1);
    CCActionInterval *action = CCRepeatForever::create(CCSequence::create(fadeIn, fadeOut, NULL));
    playLabel->runAction(action);
    this->addChild(playLabel, 1);
    
    return true;
}
bool StartLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void StartLayer::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    CCScene *pScene = ShootLayer::createScene();
    CCTransitionProgressRadialCW* pChangeScence = CCTransitionProgressRadialCW::create(0.2f, pScene);
    CCDirector::sharedDirector()->replaceScene(pChangeScence);
}