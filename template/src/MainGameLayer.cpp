//
//  MainGameLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/26.
//
//

#include <stdio.h>
#include "MainGameLayer.h"

//#define ABS(a) (a) > 0 ? a : -a

USING_NS_CC;

CCScene* MainGameLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    if ( !scene ) {
        return NULL;
    }
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
//    setBackground();
//    
//    bullet straight move to player.
//    StraightMove();
//    
//    bullet rotate move to player
//    RotateMove();
    return true;
    
}

void MainGameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent *pEvent)
{
    //this->removeFromParentAndCleanup(true);
    bool flag = true;
    CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
    if (!touch) return;
    CCLOG("touch point (%f, %f)",touch->getLocation().x,touch->getLocation().y);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    switch (m_num) {
        case 1:
            StraightMove();
            break;
        case 2:
            RotateMove();
            break;
        case 3:
            BezierMove();
            break;
        case 4:
            speedMove();
            break;
        case 5:
            speedMove2();
            break;
        case 6:
        {
            removeChildByTag(1);
            if (!m_pPlayer || !m_pBullet)
            {
                LoadPlayer();
            }

            CCSprite *closeImage = CCSprite::createWithSpriteFrameName("choose_hero.png");
            closeImage->setTag(1);
            closeImage->setPosition(ccp(origin.x + visibleSize.width - closeImage->getContentSize().width/2 ,
                                        origin.y + closeImage->getContentSize().height/2));
            this->addChild(closeImage);
            flag = followMove(touch, closeImage);
            
        }
            break;
        case 7:
            removeChildByTag(1);
            downMove();
            break;
        case 8:
            randomBullet();
            break;
        default:
            break;
    }
    if (flag)
    {
        if (((m_num++) == MAXACTION))
        {
            m_num = 1;
        }
    }
    
    
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

void MainGameLayer::LoadPlayer()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    if (m_pPlayer)
    {
        removeChild(m_pPlayer);
        m_pPlayer = NULL;
    }
    if (m_pBullet)
    {
        removeChild(m_pBullet);
        m_pBullet = NULL;
    }
    
    m_pPlayer = CCSprite::create("Player.png");
    //CCSprite *player = CCSprite::createWithSpriteFrameName("bg.png");
    m_pPlayer->setPosition(ccp(50 + m_pPlayer->getContentSize().width, origin.y + visibleSize.height / 2 + m_pPlayer->getContentSize().height / 2));
    this->addChild(m_pPlayer, 1);
    
    m_pBullet = CCSprite::create("Projectile.png");
    m_pBullet->setPosition(ccp(origin.x + visibleSize.width - m_pPlayer->getContentSize().width / 2, origin.y + visibleSize.height / 2 + m_pPlayer->getContentSize().height / 2));
    this->addChild(m_pBullet,1);
}

// bullet straight move to player.
void MainGameLayer::StraightMove()
{
    CCLOG("Enter StraightMove");
    unschedule(schedule_selector(MainGameLayer::isKill));
    LoadPlayer();
    removeChildByTag(3);
    CCActionInterval *moveto = CCMoveTo::create(2, m_pPlayer->getPosition());
    CCFiniteTimeAction *straigetMove = CCSequence::create(moveto,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
    m_pBullet->runAction(straigetMove);
}

//bullet rotate move to player
void MainGameLayer::RotateMove()
{
    CCLOG("Enter RotateMove");
    LoadPlayer();
    
    CCActionInterval *move = CCMoveTo::create(2, m_pPlayer->getPosition());
    CCSequence *rotateMove = CCSequence::create(move,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
//    CCAction *action = CCSpawn::create(rotateMove,CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
//    m_pBullet->runAction(action);
    m_pBullet->runAction(rotateMove);
    m_pBullet->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
    
}

void MainGameLayer::BezierMove()
{
    CCLOG("Enter BezierMove");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    LoadPlayer();
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(visibleSize.width - 300, m_pPlayer->getPositionY() + 400);
    bezier.controlPoint_2 = ccp(m_pPlayer->getPositionX() + 300, m_pPlayer->getPositionY() - 400);
    bezier.endPosition = m_pPlayer->getPosition();
    CCActionInterval* bezierForward = CCBezierTo::create(2, bezier);
    CCFiniteTimeAction *BezierMove = CCSequence::create(bezierForward,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
//    CCAction *action = CCSpawn::create(BezierMove,CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
//    m_pBullet->runAction(action);
    m_pBullet->runAction(BezierMove);
    m_pBullet->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
    
}

void MainGameLayer::speedMove()
{
    CCLOG("Enter speedMove");
    LoadPlayer();
    
    CCActionInterval *move = CCMoveTo::create(2,m_pPlayer->getPosition());
    CCActionInterval *move_ease_out = CCEaseIn::create((CCActionInterval*)(move->copy()->autorelease()), 4.0f);
    CCFiniteTimeAction *speedMove = CCSequence::create(move_ease_out,CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
//    CCAction *action = CCSpawn::create(speedMove,CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
//    m_pBullet->runAction(action);
    m_pBullet->runAction(speedMove);
    m_pBullet->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
}

void MainGameLayer::speedMove2()
{
    CCLOG("Enter speedMove2");
    LoadPlayer();
    
    CCActionInterval *move = CCMoveTo::create(2, m_pPlayer->getPosition());
    CCActionInterval *move_esae_in = CCEaseOut::create(move, 3.0f);
    CCFiniteTimeAction *speedMove2 = CCSequence::create(move_esae_in, CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::callBack)),NULL);
//    CCAction *action = CCSpawn::create(speedMove2,CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
//    m_pBullet->runAction(action);
    m_pBullet->runAction(speedMove2);
    m_pBullet->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
}


bool MainGameLayer::followMove(CCTouch* touch, CCSprite *closeImage)
{
    CCLOG("Enter followMove");
    m_pCurrent = m_pPlayer->getPosition();
    m_pPlayerTarget = touch->getLocation();
    m_pBulletTarget = m_pPlayer->getPosition();
    if ((touch->getLocation().x < (closeImage->getPositionX() - closeImage->getContentSize().width / 2)) || (touch->getLocation().y > closeImage->getPositionY() * 2))
    {
        m_pBullet->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
        schedule(schedule_selector(MainGameLayer::update));
        scheduleOnce(schedule_selector(MainGameLayer::updateCustom), 2.0f);
//        CCActionInterval *playerMove = CCMoveTo::create(2, touch->getLocation());
//        CCActionInterval *bulletMove = CCMoveTo::create(2, m_pPlayer->getPosition());
//        m_pPlayer->runAction(playerMove);
//        m_pBullet->runAction(bulletMove);
        return false;
    }
    else
    {
        return true;
    }
    
}

void MainGameLayer::downMove()
{
    CCLOG("Enter downMove");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    if (m_pPlayer)
    {
        m_pPlayer->stopAllActions();
        removeChild(m_pPlayer);
        m_pPlayer = NULL;
    }
    if (m_pBullet)
    {
        m_pBullet->stopAllActions();
        removeChild(m_pBullet);
        m_pBullet = NULL;
    }
    
    //m_pPlayer = CCSprite::create("Player.png");
    //CCSprite *player = CCSprite::createWithSpriteFrameName("bg.png");
    //m_pPlayer->setPosition(ccp(50 + m_pPlayer->getContentSize().width, origin.y + visibleSize.height / 2 + m_pPlayer->getContentSize().height / 2));
    //this->addChild(m_pPlayer, 1);
    
    m_pBullet = CCSprite::create("bullet_02.png");
    m_pBullet->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - m_pBullet->getContentSize().height / 2));
    CCActionInterval *down = CCMoveTo::create(2, ccp(m_pBullet->getPositionX(), 150));
    CCSequence *downMove = CCSequence::create(down,CCCallFuncN::create(this,callfuncN_selector(MainGameLayer::boom)),NULL);
    m_pBullet->runAction(downMove);
    this->addChild(m_pBullet,1);
    
}

void MainGameLayer::randomBullet()
{
    CCLOG("Enter randomBullet");
    this->removeChildByTag(2);
    float positionX;
    srand( (unsigned)time(NULL) );
    positionX = RANDOM(0,1100);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    if (m_pPlayer)
    {
        removeChild(m_pPlayer);
        m_pPlayer = NULL;
    }
    if (m_pBullet)
    {
        removeChild(m_pBullet);
        m_pBullet = NULL;
    }
    m_pBullet = CCSprite::create("bullet_02.png");
    m_pBullet->setPosition(ccp(positionX, origin.y + visibleSize.height - m_pBullet->getContentSize().height / 2));
    this->addChild(m_pBullet);
    
    m_pPlayer = CCSprite::create("Player.png");
    m_pPlayer->setPosition(ccp(0, origin.y + m_pPlayer->getContentSize().height / 2));
    this->addChild(m_pPlayer, 1);
    
    CCSprite *shine = CCSprite::createWithSpriteFrameName("C.png");
    shine->setPosition(ccp(positionX, origin.y + m_pPlayer->getContentSize().height / 2 + 10));
    shine->setTag(3);
    this->addChild(shine, 1);
    
    schedule(schedule_selector(MainGameLayer::isKill));
}

void MainGameLayer::callBack(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
    pSender = NULL;
    m_pBullet = NULL;
    CCActionInterval *blink = CCBlink::create(1, 5);
    m_pPlayer->runAction(blink);
}

void MainGameLayer::boom(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
    CCSprite *boomSprite = CCSprite::createWithSpriteFrameName("btn_hint.png");
    boomSprite->setPosition(m_pBullet->getPosition());
    CCActionInterval *blink = CCBlink::create(1, 3);
    boomSprite->runAction(blink);
    boomSprite->setTag(2);
    this->addChild(boomSprite);
}

void MainGameLayer::isKill(CCNode *pSender)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if (m_pPlayer->getPositionX() >= m_pBullet->getPositionX() - m_pBullet->getContentSize().width / 2)
    {
        CCLOG("Over");
        unschedule(schedule_selector(MainGameLayer::isKill));
        CCActionInterval *blink = CCBlink::create(1, 2);
        m_pPlayer->runAction(blink);
        removeChild(m_pPlayer);
        m_pPlayer->stopAllActions();
        m_pPlayer = NULL;

    }
    else
    {
        if (m_pPlayer->getPositionX() >= visibleSize.width)
        {
            m_pPlayer->setPositionX(0);
        }
        m_pPlayer->setPositionX(m_pPlayer->getPositionX() + 1);
    }

}

void MainGameLayer::update(float dt)
{
    
    if (m_pPlayer && m_pBullet && m_pPlayer->getPositionX() != m_pBullet->getPositionX() && m_pPlayer->getPositionY() != m_pBullet->getPositionY())
    {
        CCPoint diffP = m_pPlayerTarget - m_pCurrent;
//        diffP.x = diffP.x / ABS(diffP.x) * 0.01;
//        diffP.y = diffP.y / ABS(diffP.y) * 0.01;
        diffP = diffP * dt * 0.5;
        CCPoint newposP = m_pPlayer->getPosition() + diffP;
        m_pPlayer->setPosition(newposP);
        
        m_pBulletTarget = m_pPlayer->getPosition();
        CCPoint diffB = m_pBulletTarget - m_pBullet->getPosition();
//        diffB.x = diffB.x / ABS(diffB.x) * 0.01;
//        diffB.y = diffB.y / ABS(diffB.y) * 0.01;
        diffB = diffB * dt * 0.5;
        CCPoint newposB = m_pBullet->getPosition() + diffB;
        m_pBullet->setPosition(newposB);
    }
    else if (m_pPlayer->getPositionX() == m_pBullet->getPositionX() && m_pPlayer->getPositionY() == m_pBullet->getPositionY())
    {
        unschedule(schedule_selector(MainGameLayer::update));
    }
}

void MainGameLayer::updateCustom()
{
    unschedule(schedule_selector(MainGameLayer::update));
    CCActionInterval *movePlayer = CCMoveTo::create(2, m_pPlayerTarget);
    CCActionInterval *moveBullet = CCMoveTo::create(2, m_pBulletTarget);
    m_pPlayer->runAction(movePlayer);
    m_pBullet->runAction(moveBullet);
}


