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
#include "GameOverLayer.h"
#include "GamePauseLayer.h"

USING_NS_CC;

ShootLayer::ShootLayer() : m_pPlayer(NULL), m_difficulty(1), m_score(0), m_bulletNum(0) {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    m_targetLocation.x = origin.x + visibleSize.width / 2;
    m_targetLocation.y = origin.y + 100;
}

ShootLayer::~ShootLayer()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCScene *ShootLayer::createScene()
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
    
    //分数显示
    m_pScore = CCLabelTTF::create("0", "Arial", 50);
    m_pScore->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
    this->addChild(m_pScore, 1);
    
    //暂停按钮
    CCMenuItemImage *pauseItem = CCMenuItemImage::create("B1.png", "B1S.png", this, menu_selector(ShootLayer::pauseBtnClick));
    pauseItem->setPosition(ccp(origin.x + visibleSize.width - pauseItem->getContentSize().width, origin.y + visibleSize.height - pauseItem->getContentSize().height));
    CCMenu* pMenu = CCMenu::create(pauseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    CCLabelTTF *pLabel = CCLabelTTF::create("pause", "Arial", 30);
    pLabel->setPosition(ccp(pauseItem->getPositionX(), pauseItem->getPositionY() + 5));
    this->addChild(pLabel, 1);
    
    
    
    //创建玩家
    createPlayer();
    
    m_bulletNum = m_difficulty * 3;
   
    createBullet(m_bulletNum);
    
    //玩家跟随鼠标移动
    //scheduleUpdate();
    
    //every second add score and bullet nums
    schedule(schedule_selector(ShootLayer::calcScoreAndBullet), 1.0f, kCCRepeatForever, 1.0f);
    
    //every two second create new bullets
    schedule(schedule_selector(ShootLayer::addNewBullet), 2.0f, kCCRepeatForever, 0.0f);
}

//create one player
void ShootLayer::createPlayer()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    if ( !m_pPlayer )
    {
        m_pPlayer = CCSprite::create("Player.png");
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
    
    if (m_difficulty <= 3)
    {
        easyBulletNum = RANDOM(0, bulletNum);
        commonBulletNum = bulletNum - easyBulletNum;
        difficultBulletNum = 0;
    }
    else if (m_difficulty <= 6)
    {
        difficultBulletNum = RANDOM(5, 10);
        if (bulletNum - difficultBulletNum != 5) {
            easyBulletNum = RANDOM(5, bulletNum - difficultBulletNum);
            commonBulletNum = bulletNum - easyBulletNum - difficultBulletNum;
        }
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
        CCActionInterval *move_esae_in = CCEaseIn::create(move, 3.0f);
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
//    CCLOG("update");
//    if bump game over
//    if (true)
//    {
//    }
    if (m_pPlayer)
    {
        CCPoint diff = m_targetLocation - m_pPlayer->getPosition();
        diff.x = diff.x / ABS(diff.x);
        diff.y = diff.y / ABS(diff.y);
        CCLOG("m_targetLocation (%f, %f)", diff.x, diff.y);
        m_pPlayer->setPosition(m_pPlayer->getPosition() + diff * 3);
        
    }
    
}

void ShootLayer::calcScoreAndBullet()
{
    //CCLOG("calcScore");
    m_score++;
    CCString str;
    str.initWithFormat("%d",m_score);
    m_pScore->setString(str.getCString());
    m_bulletNum++;
}

void ShootLayer::addNewBullet()
{
    CCLOG("addDiffculty");
    createBullet(m_bulletNum);
    m_difficulty++;
}

//callback函数

void ShootLayer::removeBullet(CCNode *pSender)
{
    CCLOG("removeBullet");
    pSender = (CCSprite*)pSender;
    
    //检测碰撞，即矩形区域是否相交
    // if bullet fly on player, game over
    if (m_pPlayer) {
        if ((pSender->boundingBox()).intersectsRect(m_pPlayer->boundingBox()))
        {
            m_pPlayer->stopAllActions();
            removeChild(m_pPlayer);
            m_pPlayer = NULL;
            pSender->stopAllActions();
            removeChild(pSender);
            pSender = NULL;
            CCDirector::sharedDirector()->replaceScene(GameOverLayer::createScene());
        }
    }
    
    // if bullet fly out screen, remove itself
    
}

//click事件
void ShootLayer::pauseBtnClick(CCObject *pSender)
{
    CCScene *pScene = GamePauseLayer::createScene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

//触屏事件

bool ShootLayer::ccTouchBegan(CCTouch* touch,CCEvent* event)
{
    CCLOG("ccTouchBegan");
    m_targetLocation = touch->getLocation();
    CCLOG("m_targetLocation (%f, %f)",m_targetLocation.x, m_targetLocation.y);
    return true;
}

void ShootLayer::ccTouchMoved(CCTouch* touch,CCEvent* event)
{
    //CCLOG("ccTouchMoved");
}

void ShootLayer::ccTouchEnded(CCTouch* touch,CCEvent* event)
{
    //CCLOG("ccTouchEnded");
}

