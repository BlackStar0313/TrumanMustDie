//
//  GamePauseLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/29.
//
//

#include <stdio.h>
#include "GamePauseLayer.h"

GamePauseLayer::GamePauseLayer()
{
    
}
GamePauseLayer::~GamePauseLayer()
{
    
}
bool GamePauseLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *playItem = CCMenuItemImage::create( "B1.png",
                                                          "B1S.png",
                                                          this,
                                                          menu_selector(GamePauseLayer::playBtnClick));
    playItem->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
    CCMenu* pMenu = CCMenu::create(playItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    CCLabelTTF *playLabel = CCLabelTTF::create("Play", "Arial", 30);
    playLabel->setPosition(ccp(playItem->getPositionX(), playItem->getPositionY() + 5));
    this->addChild(playLabel, 1);
    
    
    return true;
}

CCScene* GamePauseLayer::createScene()
{
    CCScene *scene = CCScene::create();
    
    if ( !scene )
    {
        return NULL;
    }
    
    CCLayer *layer = GamePauseLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

void GamePauseLayer::playBtnClick(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

