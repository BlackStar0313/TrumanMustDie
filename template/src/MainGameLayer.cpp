//
//  MainGameLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/26.
//
//

#include <stdio.h>
#include "MainGameLayer.h"

USING_NS_CC;

CCScene* MainGameLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    MainGameLayer *layer = MainGameLayer::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool MainGameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // bullet straight move to player.
    CCSprite *player = CCSprite::create("Player.png");
    player->setPosition(ccp(10 + player->getContentSize().width, origin.y + visibleSize.height / 3 + player->getContentSize().height / 2));
    this->addChild(player);
    
    CCSprite *p_bullet = CCSprite::create("bullet_02.png");
    p_bullet->setPosition(ccp(origin.x + visibleSize.width - player->getContentSize().width / 2, origin.y + visibleSize.height / 3 + player->getContentSize().height / 2));
    
    CCActionInterval *moveto = CCMoveTo::create(2, player->getPosition());
    
    CCFiniteTimeAction *straigetMove = CCSequence::create(moveto,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack1)),NULL);
    
    p_bullet->runAction(straigetMove);
    
    this->addChild(p_bullet);
    
    //bullet rotate move to player
    
    CCSprite *player2 = CCSprite::create("Player.png");
    
    player2->setPosition(ccp(10 + player2->getContentSize().width, origin.y + visibleSize.height * 2 / 3 + player2->getContentSize().height / 2));
    
    this->addChild(player2);

    CCSprite *p_bullet2 = CCSprite::create("Projectile.png");
    
    p_bullet2->setPosition(ccp(origin.x + visibleSize.width - player2->getContentSize().width / 2, origin.y + visibleSize.height * 2 / 3 + player2->getContentSize().height / 2));
    
    CCActionInterval *move = CCMoveTo::create(2, player2->getPosition());
    
    CCRepeatForever *rotate = CCRepeatForever::create(CCRotateBy::create(1.0f, 360));
    
    CCSequence *rotateMove = CCSequence::create(move,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack1)),NULL);
    
    p_bullet2->runAction(rotateMove);
    
    p_bullet2->runAction(rotate);
    
    this->addChild(p_bullet2);
    
    return true;
    
}


void MainGameLayer::callBack1(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
}




