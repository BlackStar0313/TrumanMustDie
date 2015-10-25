//
//  CTestScene.cpp
//  project
//
//  Created by liuzhiwei on 15/10/25.
//
//

#include "CTestScene.h"
USING_NS_CC;

CCScene* CTestScene::scene()
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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("choose_hero.png");
    pSprite->setPosition(ccp(visibleSize.width / 2 , visibleSize.height / 2));
    this->addChild(pSprite);
    
    CCSequence* pSeq = CCSequence::create(CCMoveBy::create(4.0f, ccp(500, 200)), CCCallFuncN::create(pSprite, callfuncN_selector(CTestScene::callBack)) , NULL);
    pSprite->runAction(pSeq);
    
    return true;
}

void CTestScene::callBack(cocos2d::CCNode *_node)
{
    _node->removeFromParent();
}