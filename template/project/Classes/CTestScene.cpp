//
//  CTestScene.cpp
//  project
//
//  Created by liuzhiwei on 15/10/25.
//
//

#include "CTestScene.h"
USING_NS_CC;

CCScene* CTestScene::createScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CTestScene *layer = CTestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool CTestScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//    
//    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("runeD_5.png");
//    //pSprite->setPosition(ccp(visibleSize.width / 2 , visibleSize.height / 2));
//    
//    pSprite->setPosition(ccp(200, 200));
//    this->addChild(pSprite);
//    
//    CCActionInterval *moveLeft = CCMoveTo::create(2, ccp(170,200));
//    CCActionInterval *moveRight = CCMoveTo::create(2, ccp(230,200));
//    //CCSequence* pSeq = CCSequence::create(CCMoveBy::create(4.0f, ccp(500, 200)), CCCallFuncN::create(pSprite, callfuncN_selector(CTestScene::callBack)) , NULL);
//    //pSprite->runAction(pSeq);
//    //CCSequence *seq = CCSpawn::create(moveLeft, moveRight, NULL);
//    //pSprite->runAction(seq);
//    
//    pSprite->runAction(moveLeft);
//    pSprite->runAction(moveRight);
    
    CCSprite* m_p = CCSprite::create("plane.png");
    //CC_SAFE_RETAIN(p);
    m_p->setPosition(ccp(200, 200));
    this->addChild(m_p);
    
    map<int,map<int, int> > my_Map;
    
//    CC_SAFE_RETAIN(p);
    
    return true;
}

void CTestScene::update(float dt)
{
    //this->addChild(m_p);
}

void CTestScene::callBack(cocos2d::CCNode *_node)
{
    _node->removeFromParent();
}