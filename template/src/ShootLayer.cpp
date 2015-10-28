//
//  ShootLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/28.
//
//

#include <stdio.h>
#include <time.h>
#include "ShootLayer.h"



USING_NS_CC;

CCScene *ShootLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    if ( !scene ) return NULL;
    
    ShootLayer *layer = ShootLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool ShootLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    setBackground();
    
    LoadGame();
    
    return true;
}

void ShootLayer::onEnter()
{
    //注册触碰响应事件
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
    CCLayer::onEnter();//一定不要忘了调用父类的onEnter
}

void ShootLayer::onExit()
{
    //注销触屏响应事件
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();//一定不要忘了调用父类的onExit
}

void ShootLayer::setBackground()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite *background = CCSprite::createWithSpriteFrameName("bg.png");
    background->setPosition(ccp(origin.x + background->getContentSize().width/2,
                                origin.y + visibleSize.height/2));
    float winw = visibleSize.width; //获取屏幕宽度
    float winh = visibleSize.height;//获取屏幕高度
    
    float spx = background->getTextureRect().getMaxX();
    float spy = background->getTextureRect().getMaxY();
    
    background->setScaleX(winw / spx); //设置精灵宽度缩放比例
    background->setScaleY(winh / spy);
    this->addChild(background, 0);
}

void ShootLayer::LoadGame()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCString str;
    str.initWithFormat("%d",score);
    CCLabelTTF* pScore = CCLabelTTF::create(str.getCString(), "Arial", 50);
    pScore->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
    this->addChild(pScore, 1);
    
    createPlayer();
    
    m_bulletNum = m_difficulty * 3;
    
    createBullet(m_bulletNum);
    
    schedule(schedule_selector(ShootLayer::calcScore), 1.0f, kCCRepeatForever, 0.0f);
    
    schedule(schedule_selector(ShootLayer::addBulletNum), 60.0f, kCCRepeatForever, 0.0f);
}

//create one player
void ShootLayer::createPlayer()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    if ( !m_pPlayer )
    {
        CCSprite *m_pPlayer = CCSprite::create("Player.png");
        m_pPlayer->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + 100));
        this->addChild(m_pPlayer, 1);
    }
}

CCPoint randChoosePosition()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    srand( (unsigned)time(NULL) );
    int direction = RANDOM(0, 3);
    srand( (unsigned)time(NULL) );
    switch (direction) {
        case 0:
        {
            return ccp(30, RANDOM(30, int(visibleSize.height)));
            break;
        }
        case 1:
        {
            return ccp(RANDOM(30, int(visibleSize.width)), visibleSize.height);
            break;
        }
        case 2:
        {
            return ccp(visibleSize.width - 30, RANDOM(30, int(visibleSize.height)));
            break;
        }
        default:
        {
            CCLOG("ccp(0, 0)\n");
            return ccp(0, 0);
            break;
        }
    }
}

//create bullet according to difficulty
void ShootLayer::createBullet(int bulletNum)
{
    srand( (unsigned)time(NULL) );
    int easyBulletNum = 0;
    int commonBulletNum = 0;
    int difficultBulletNum = 0;
    srand( (unsigned)time(NULL) );
    if (m_difficulty <= 3)
    {
        easyBulletNum = RANDOM(0, bulletNum);
        commonBulletNum = bulletNum - easyBulletNum;
        difficultBulletNum = 0;
    }
    else if (m_difficulty <= 6)
    {
        difficultBulletNum = RANDOM(5, 10);
        easyBulletNum = RANDOM(5, bulletNum - difficultBulletNum);
        commonBulletNum = bulletNum - easyBulletNum - difficultBulletNum;
    }
    else
    {
        easyBulletNum = 0;
        commonBulletNum = RANDOM(0, bulletNum);
        difficultBulletNum = bulletNum - commonBulletNum - easyBulletNum;
    }
//    m_pEasyBulletArr = CCArray::create();
//    m_pCommonBulletArr = CCArray::create();
//    m_pDiffcultBulletArr = CCArray::create();
    for (int i = 0; i < easyBulletNum; i++)
    {
        CCSprite *easyBullet = CCSprite::create("bullet_02.png");
        easyBullet->setPosition(randChoosePosition());
        CCActionInterval *move = CCMoveTo::create(3, m_pPlayer->getPosition());
        CCSequence *straightMove = CCSequence::create(move, CCCallFuncN::create(this,callfuncN_selector(ShootLayer::removeBullet)), NULL);
        easyBullet->runAction(straightMove);
        this->addChild(easyBullet, 1);
    }
    
    for (int i = 0; i < commonBulletNum; i++)
    {
        CCSprite *commonBullet = CCSprite::createWithSpriteFrameName("runeA_2.png");
        commonBullet->setPosition(randChoosePosition());
        CCActionInterval *move = CCMoveTo::create(3, m_pPlayer->getPosition());
        CCActionInterval *move_esae_in = CCEaseOut::create(move, 3.0f);
        CCFiniteTimeAction *speedMove2 = CCSequence::create(move_esae_in, CCCallFuncN::create(this, callfuncN_selector(ShootLayer::removeBullet)),NULL);
        commonBullet->runAction(speedMove2);
        this->addChild(commonBullet, 1);
    }
    
    for (int i = 0; i < difficultBulletNum; i++)
    {
        CCSprite *difficultBullet = CCSprite::createWithSpriteFrameName("runeA_2.png");
        difficultBullet->setPosition(randChoosePosition());
        CCActionInterval *move = CCMoveTo::create(3, m_pPlayer->getPosition());
        CCActionInterval *move_esae_in = CCEaseOut::create(move, 3.0f);
        CCFiniteTimeAction *speedMove2 = CCSequence::create(move_esae_in, CCCallFuncN::create(this, callfuncN_selector(ShootLayer::removeBullet)),NULL);
        difficultBullet->runAction(speedMove2);
        this->addChild(difficultBullet, 1);
    }
}

//schedule函数

void ShootLayer::update(float dt)
{
    CCLOG("update");
}

void ShootLayer::calcScore()
{
    CCLOG("calcScore");
    score++;
}

void ShootLayer::addBulletNum()
{
    CCLOG("addDiffculty");
    m_difficulty++;
}


//callback函数

void ShootLayer::removeBullet(CCNode *pSender)
{
    // if bullet fly out screen, remove itself
    // if bullet fly on player, game over
    CCLOG("removeBullet");
}


//触屏事件
bool ShootLayer::ccTouchBegan(CCTouch* touch,CCEvent* event)
{
    CCLOG("ccTouchBegan");
    m_targetLocation = touch->getLocation();
    return true;
}
void ShootLayer::ccTouchMoved(CCTouch* touch,CCEvent* event)
{
    CCLOG("ccTouchMoved");
}
void ShootLayer::ccTouchEnded(CCTouch* touch,CCEvent* event)
{
    CCLOG("ccTouchEnded");
}

