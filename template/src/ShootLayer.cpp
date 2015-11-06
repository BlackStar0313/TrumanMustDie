//
//  ShootLayer.cpp
//  project
//
//  Created by peiyang  on 15/10/28.
//
//

#include <stdio.h>
#include "ShootLayer.h"


ShootLayer::ShootLayer() :
m_pPlayer(NULL),
m_difficulty(1),
m_score(1),
m_bulletNum(0),
m_second(0) {
    //keep targetLocation equal m_pPlayer's location
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    m_targetLocation.x = origin.x + visibleSize.width / 2;
    m_targetLocation.y = origin.y + 100;
}

ShootLayer::~ShootLayer()
{
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
    
    setTouchEnabled(true);
    setTouchMode(ccTouchesMode::kCCTouchesOneByOne);
    
    setBackground();
    
    //随机种子
    srand( (unsigned)time(NULL) );
    
    LoadGame();
    
    return true;
}


//设置背景图片
void ShootLayer::setBackground()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite *background = CCSprite::createWithSpriteFrameName("bg.png");
    background->setPosition(ccp(origin.x + background->getContentSize().width/2,
                                origin.y + visibleSize.height/2));
    float winw = visibleSize.width; //获取屏幕宽度
    float winh = visibleSize.height;//获取屏幕高度
    
    float spx = background->getContentSize().width;
    float spy = background->getContentSize().height;
    
    background->setScaleX(winw / spx); //设置精灵宽度缩放比例
    background->setScaleY(winh / spy);
    this->addChild(background, -1);
}


void ShootLayer::LoadGame()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //分数显示
    m_pScore = CCLabelBMFont::create("0", "markerfelt24shadow.fnt");
    m_pScore->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
    this->addChild(m_pScore, 1);
    
    //暂停按钮
    CCMenuItemImage *pauseItem = CCMenuItemImage::create("B1.png", "B1S.png", this, menu_selector(ShootLayer::pauseBtnClick));
    pauseItem->setPosition(ccp(origin.x + visibleSize.width - pauseItem->getContentSize().width,
                               origin.y + visibleSize.height - pauseItem->getContentSize().height));
    CCMenu* pMenu = CCMenu::create(pauseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    //分数显示
    CCLabelTTF *pLabel = CCLabelTTF::create("pause", "Arial", 30);
    pLabel->setPosition(ccp(pauseItem->getPositionX(), pauseItem->getPositionY() + 5));
    this->addChild(pLabel, 1);
    
    //创建玩家
    createPlayer();
   
    createBullet();
    
    scheduleUpdate();
    
    //每秒更新
    schedule(schedule_selector(ShootLayer::updateEverySecond), 1.0f, kCCRepeatForever, 0.0f);
}

//create one player
void ShootLayer::createPlayer()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    m_pPlayer = CPlane::create("plane.png");
    m_pPlayer->cocos2d::CCNode::setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + 100));
    
    
    this->addChild(m_pPlayer, 1);
}

//create bullet according to difficulty
void ShootLayer::createBullet()
{
    CBullet* pBullet = CBulletManager::GetInstance()->CreateBullet();
    pBullet->Rotate(0.1, asUniversalInterface::calcAngle(m_pPlayer->getPosition(), pBullet->getPosition()));
    pBullet->setDirection(asUniversalInterface::calcDiff(m_pPlayer->getPosition(), pBullet->getPosition()) * 5);
//    CCLOG("position1(%f, %f)", pBullet->getPosition().x, pBullet->getPosition().y);
//    CCLOG("position2(%f, %f)", m_pPlayer->getPosition().x, m_pPlayer->getPosition().y);
//    CCLOG("position3(%f, %f)", pBullet->getDirection().x, pBullet->getDirection().y);
    this->addChild(pBullet, 1);
}

//schedule函数
void ShootLayer::update(float dt)
{
    m_pPlayer->MoveToPosition(m_targetLocation);
    CBulletManager::GetInstance()->AllBulletMove();

    if ((CBulletManager::GetInstance()->Collision(m_pPlayer)).size() > 0) {
        CBulletManager::GetInstance()->RemoveCollisionList();
        unscheduleUpdate();
        //this->stopAllActions();
        CCDirector::sharedDirector()->replaceScene(GameOverLayer::createScene());
    }
    if (CBulletManager::GetInstance()->checkFlyOut().size() > 0)
    {
        CBulletManager::GetInstance()->RemoveOutList();
    }
}

void ShootLayer::updateEverySecond()
{
    //calcScoreAndBullet();
    m_score++;
    CCString str;
    str.initWithFormat("%d",m_score);
    m_pScore->setString(str.getCString());
    
    m_bulletNum = RANDOM(1, m_second + 2);
    if (m_second % 2 == 0)
    {
        for(int i = 0; i < m_bulletNum; i++)
            createBullet();
    }
    m_second++;
}


//click事件
void ShootLayer::pauseBtnClick(CCObject *pSender)
{
    if (NULL == pSender) {
        return;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
    
    //遍历当前类的所有子节点信息，画入renderTexture中。
    //这里类似截图。
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();
    
    CCDirector::sharedDirector()->pushScene(GamePauseLayer::createScene(renderTexture));
}

//触屏事件
bool ShootLayer::ccTouchBegan(CCTouch* touch,CCEvent* event)
{
    //CCLOG("ccTouchBegan");
    m_targetLocation = touch->getLocation();
    return true;
}

void ShootLayer::ccTouchMoved(CCTouch* touch,CCEvent* event)
{
    //CCLOG("ccTouchMoved");
    m_targetLocation = touch->getLocation();
}

void ShootLayer::ccTouchEnded(CCTouch* touch,CCEvent* event)
{
    //CCLOG("ccTouchEnded");
    m_targetLocation = m_pPlayer->getPosition();
}

