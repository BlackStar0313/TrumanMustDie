//
//  ShootLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/28.
//
//

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "ShootLayer.h"
#include "GameOverLayer.h"
#include "GamePauseLayer.h"
#include "Bullet.h"
#define PI 3.1415926

USING_NS_CC;

ShootLayer::ShootLayer() : m_pPlayer(NULL), m_difficulty(1), m_score(1), m_bulletNum(0), m_second(0) {
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
    
    //随机种子
    srand( (unsigned)time(NULL) );
    
    //创建玩家
    createPlayer();
    
    m_bulletNum = m_difficulty * 3;
   
    createBullet();
    
    //玩家跟随鼠标移动
    schedule(schedule_selector(ShootLayer::playMove), 0.0f, kCCRepeatForever, 0.0f);
    
    scheduleUpdate();
    
    //every second update
    schedule(schedule_selector(ShootLayer::updateEverySecond), 1.0f, kCCRepeatForever, 1.0f);
    
}

//create one player
void ShootLayer::createPlayer()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    if ( !m_pPlayer )
    {
        m_pPlayer = CCSprite::create("plane.png");
        m_pPlayer->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + 100));
        this->addChild(m_pPlayer, 1);
    }
}

//create random position
CCPoint randChoosePosition()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    int direction = RANDOM(0, 3);
    switch (direction) {
        case 0:
        {
            return ccp(-10, RANDOM(-10, int(visibleSize.height + 10)));
            break;
        }
        case 1:
        {
            return ccp(RANDOM(-10, int(visibleSize.width)), visibleSize.height + 10);
            break;
        }
        case 2:
        {
            return ccp(visibleSize.width + 10, RANDOM(0, int(visibleSize.height + 10)));
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
void ShootLayer::createBullet()
{
    int kind = RANDOM(1, 4);
    CCSprite *bullet = NULL;
    switch (kind) {
        case 1:
        {
            bullet = CCSprite::create("bullet_02.png");
            
            CCPoint position = randChoosePosition();
            bullet->setPosition(position);
            float x = bullet->getPositionX() - m_pPlayer->getPositionX(), y = bullet->getPositionY() - m_pPlayer->getPositionY();
            //CCLOG("atan %f", atan(x / y) * 180 / PI);
            CCActionInterval *rotate = CCRotateTo::create(0.1, atan(x / y) * 180 / PI);
            bullet->runAction(rotate);
            
            CCActionInterval *move = CCMoveTo::create(3, m_pPlayer->getPosition());
            CCSequence *straightMove = CCSequence::create(rotate, move, CCCallFuncN::create(this,callfuncN_selector(ShootLayer::boom)), NULL);
            bullet->runAction(straightMove);
            break;
        }
        case 2:
        {
            bullet = CCSprite::createWithSpriteFrameName("runeA_2.png");
            
            CCPoint position = randChoosePosition();
            bullet->setPosition(position);
            float x = bullet->getPositionX() - m_pPlayer->getPositionX(), y = bullet->getPositionY() - m_pPlayer->getPositionY();
            //CCLOG("atan %f", atan(x / y) * 180 / PI);
            CCActionInterval *rotate = CCRotateTo::create(0.1, atan(x / y) * 180 / PI + 90);
            bullet->runAction(rotate);
            
            CCActionInterval *move = CCMoveTo::create(3, m_pPlayer->getPosition());
            CCSequence *straightMove = CCSequence::create(rotate, move, CCCallFuncN::create(this,callfuncN_selector(ShootLayer::boom)), NULL);
            bullet->runAction(straightMove);
            break;
        }
        case 3:
        {
            bullet = CCSprite::createWithSpriteFrameName("runeA_4.png");
            
            CCPoint position = randChoosePosition();
            bullet->setPosition(position);
            float x = bullet->getPositionX() - m_pPlayer->getPositionX(), y = bullet->getPositionY() - m_pPlayer->getPositionY();
            //CCLOG("atan %f", atan(x / y) * 180 / PI);
            CCActionInterval *rotate = CCRotateTo::create(0.1, atan(x / y) * 180 / PI + 90);
            bullet->runAction(rotate);
            
            CCActionInterval *move = CCMoveTo::create(3, m_pPlayer->getPosition());
            CCSequence *straightMove = CCSequence::create(rotate, move, CCCallFuncN::create(this,callfuncN_selector(ShootLayer::boom)), NULL);
            bullet->runAction(straightMove);
            break;
        }
        default:
            break;
    }
    this->addChild(bullet, 1);
    //CCRect *bulletRect = CCRect(bullet->getPositionX() - bullet->getContentSize().width / 2, bullet->getPositionY() - bullet->getContentSize().height / 2, bullet->getContentSize().width, bullet->getContentSize().height);
    m_pBulletArray.push_back(bullet);
}

//schedule函数

void ShootLayer::update(float dt)
{
    //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if (m_pPlayer)
    {
        for (auto it = m_pBulletArray.begin(); it != m_pBulletArray.end(); ++it)
        {
            if (((*it)->boundingBox()).intersectsRect(m_pPlayer->boundingBox()))
            {
                m_pPlayer->stopAllActions();
//                removeChild(m_pPlayer);
//                m_pPlayer = NULL;
//                (*it)->stopAllActions();
//                removeChild(*it);
//                (*it) = NULL;
                CCDirector::sharedDirector()->replaceScene(GameOverLayer::createScene());
                break;
            }
//            else if ((*it)->getPositionX() < 0 || (*it)->getPositionX() > visibleSize.width || (*it)->getPositionY() < 0 || (*it)->getPositionY() > visibleSize.height)
//                {
//                    (*it)->stopAllActions();
//                    removeChild((*it));
//                    m_pBulletArray.remove((*it));
//                    (*it) = NULL;
//                }
        }
    }
}

#if 0
void ShootLayer::calcScoreAndBullet()
{
    m_score++;
    CCString str;
    str.initWithFormat("%d",m_score);
    m_pScore->setString(str.getCString());
    m_bulletNum++;
    CCLOG("bullet num %d", m_bulletNum);
}
#endif


void ShootLayer::updateEverySecond()
{
    //calcScoreAndBullet();
    m_score++;
    CCString str;
    str.initWithFormat("%d",m_score);
    m_pScore->setString(str.getCString());
    m_bulletNum = RANDOM(1, m_second + 2) + m_bulletNum;
    
    if (m_second % 2 == 0)
    {
        for(int i = 0; i < m_bulletNum; i++)
            createBullet();
    }
//    if (m_second % 30 == 0)
//    {
//        CCLOG("m_difficulty %d", m_difficulty);
//        m_difficulty++;
//    }
    
    m_second++;
}

void ShootLayer::playMove()
{
    if (m_pPlayer && (m_targetLocation.x - m_pPlayer->getPositionX() != 0 && m_targetLocation.y- m_pPlayer->getPositionY() != 0))
    {
        CCPoint diff = m_targetLocation - m_pPlayer->getPosition();
        diff.x = diff.x * 1.111111111 / ABS(diff.x);
        diff.y = diff.y * 1.111111111 / ABS(diff.y);
        CCLOG("m_targetLocation (%f, %f)", diff.x, diff.y);
        m_pPlayer->setPosition(m_pPlayer->getPosition() + diff * 3);
    }
}

//callback函数

void ShootLayer::boom(CCNode *pSender)
{
    
    if (NULL == pSender) {
        return;
    }
    
    pSender->setVisible(false);
    CCAnimation* animation = CCAnimation::create();
    for( int i=12; i<=24; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "%02d-1.png", i);
        animation->addSpriteFrameWithFileName(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 14.0f);
    animation->setRestoreOriginalFrame(true);
    
    CCAnimate* action = CCAnimate::create(animation);
    
    pSender->runAction(CCSequence::create(action, CCCallFuncN::create(this,callfuncN_selector(ShootLayer::remove)), NULL));
    
    CCRect *rectBoom = new CCRect(pSender->getPositionX() - pSender->getContentSize().width / 2, pSender->getPositionY() - pSender->getContentSize().height / 2, 80, 80);
    m_RectArray.push_back(rectBoom);
}

void ShootLayer::remove(CCNode *pSender)
{
    if (NULL == pSender) {
        return;
    }
    m_pBulletArray.remove((CCSprite*)pSender);
    pSender->stopAllActions();
    removeChild(pSender);
    pSender = NULL;
}

//click事件
void ShootLayer::pauseBtnClick(CCObject *pSender)
{
    if (NULL == pSender) {
        return;
    }
    CCScene *pScene = GamePauseLayer::createScene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

//触屏事件
bool ShootLayer::ccTouchBegan(CCTouch* touch,CCEvent* event)
{
    CCLOG("ccTouchBegan");
    schedule(schedule_selector(ShootLayer::playMove), 0.0f, kCCRepeatForever, 0.0f);
    m_targetLocation = touch->getLocation();
    CCLOG("m_targetLocation (%f, %f)",m_targetLocation.x, m_targetLocation.y);
    return true;
}

void ShootLayer::ccTouchMoved(CCTouch* touch,CCEvent* event)
{
    //CCLOG("ccTouchMoved");
    m_targetLocation = touch->getLocation();
}

void ShootLayer::ccTouchEnded(CCTouch* touch,CCEvent* event)
{
    unschedule(schedule_selector(ShootLayer::playMove));
    //CCLOG("ccTouchEnded");
}

