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
    
    this->setTouchEnabled(true);

    //setBackground();
    
    // bullet straight move to player.
//    StraightMove();
    
    //bullet rotate move to player
//    RotateMove();
    
    
    return true;
    
}

void MainGameLayer::setBackground()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *background = CCSprite::createWithSpriteFrameName("bg.png");
    
    background->setPosition(ccp(origin.x + background->getContentSize().width/2,
                                origin.y + visibleSize.height/2));
    this->addChild(background,0);

}

// bullet straight move to player.
void MainGameLayer::StraightMove()
{
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (p_player)
    {
        removeChild(p_player);
        p_player = NULL;
    }
    
    if (p_bullet)
    {
        removeChild(p_bullet);
        p_bullet = NULL;
    }
    
    p_player = CCSprite::create("Player.png");
    //CCSprite *player = CCSprite::createWithSpriteFrameName("bg.png");
    p_player->setPosition(ccp(10 + p_player->getContentSize().width, origin.y + visibleSize.height / 2 + p_player->getContentSize().height / 2));
    this->addChild(p_player, 1);
    
    p_bullet = CCSprite::create("bullet_02.png");
    //p_bullet->setTag(1);
    p_bullet->setPosition(ccp(origin.x + visibleSize.width - p_player->getContentSize().width / 2, origin.y + visibleSize.height / 2 + p_player->getContentSize().height / 2));
    
    CCActionInterval *moveto = CCMoveTo::create(2, p_player->getPosition());
    
    CCFiniteTimeAction *straigetMove = CCSequence::create(moveto,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
    
    p_bullet->runAction(straigetMove);
    
    this->addChild(p_bullet,1);

    this->getChildByTag(1);
}

//bullet rotate move to player
void MainGameLayer::RotateMove()
{
    
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    if (p_player)
    {
        removeChild(p_player);
        p_player = NULL;
    }
    if (p_bullet)
    {
        removeChild(p_bullet);
        p_bullet = NULL;
    }
    
    p_player = CCSprite::create("Player.png");
    
    
    p_player->setPosition(ccp(10 + p_player->getContentSize().width, origin.y + visibleSize.height / 3 + p_player->getContentSize().height / 2));
    
    
    
    this->addChild(p_player,1);
    
    p_bullet = CCSprite::create("Projectile.png");
    
    p_bullet->setPosition(ccp(origin.x + visibleSize.width - p_player->getContentSize().width / 2, origin.y + visibleSize.height / 2 + p_player->getContentSize().height / 2));
    
    CCActionInterval *move = CCMoveTo::create(2, p_player->getPosition());
    
    CCRepeatForever *rotate = CCRepeatForever::create(CCRotateBy::create(1.0f, 360));
    
    CCSequence *rotateMove = CCSequence::create(move,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
    
    p_bullet->runAction(rotateMove);
    
    p_bullet->runAction(rotate);
    
    this->addChild(p_bullet,1);
    
    

}

void MainGameLayer::callBack(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
}

void MainGameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent *pEvent)
{
    //this->removeFromParentAndCleanup(true);
    CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
    if (!touch) return;
    CCLOG("touch point (%f, %f)",touch->getLocation().x,touch->getLocation().y);
    switch (num) {
        case 1:
            StraightMove();
            break;
        case 2:
            RotateMove();
            break;
        default:
            break;
    }
    if ((num++) == MAXACTION)
    {
        num = 1;
    }
    
}




