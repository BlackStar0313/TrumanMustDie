//
//  GameOverLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/29.
//
//

#include <stdio.h>
#include "GameOverLayer.h"
#include "ShootLayer.h"

GameOverLayer::GameOverLayer()
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}
bool GameOverLayer::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF* playLabel = CCLabelTTF::create("Game Over", "Arial", 56);
    playLabel->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
    this->addChild(playLabel, 1);
    
//    CCMenuItemImage *restartItem = CCMenuItemImage::create("btn_back.png", "btn_back.png", this,menu_selector(GameOverLayer::restartClick));
//    
//    restartItem->setPosition(ccp(playLabel->getPositionX(), playLabel->getPositionY() - 60));
//    CCMenu* pMenu = CCMenu::create(restartItem, NULL);
//    pMenu->setPosition(CCPointZero);
//    this->addChild(pMenu, 1);
//    
//    CCLabelTTF *pLabel = CCLabelTTF::create("restart", "Arial", 35);
//    pLabel->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
//    this->addChild(pLabel, 1);
    
    //重新开始按钮
    CCMenuItemImage *restartItem = CCMenuItemImage::create("B1.png", "B1S.png", this, menu_selector(GameOverLayer::restartBtnClick));
    restartItem->setPosition(ccp(playLabel->getPositionX(), playLabel->getPositionY() - 100));
    CCMenu* pMenu = CCMenu::create(restartItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    CCLabelTTF *pLabel = CCLabelTTF::create("restart", "Arial", 30);
    pLabel->setPosition(ccp(restartItem->getPositionX(), restartItem->getPositionY() + 5));
    this->addChild(pLabel, 1);
    
    return true;
}
CCScene* GameOverLayer::createScene()
{
    CCScene *scene = CCScene::create();
    if ( !scene )
    {
        return NULL;
    }
    CCLayer *layer = GameOverLayer::create();
    scene->addChild(layer);
    return scene;
}

void GameOverLayer::restartBtnClick(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(ShootLayer::createScene());
}





