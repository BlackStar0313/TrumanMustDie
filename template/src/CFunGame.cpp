//
//  CFunGame.cpp
//  project
//
//  Created by liuzhiwei on 15/10/25.
//
//

#include "CFunGame.h"
#include "CTestScene.h"
#include "MainGameLayer.h"
#include "StartLayer.h"
#include "HelloWorldScene.h"

CFunGame* CFunGame::m_pThis = NULL;

CFunGame::CFunGame()
{

}

CFunGame::~CFunGame()
{

}

CFunGame* CFunGame::GetInstance()
{
    if (m_pThis == NULL) {
        m_pThis = new CFunGame();
    }
    return m_pThis;
}

void CFunGame::ReleaseInstance(void* pObj)
{
    CFunGame* pThis = (CFunGame* ) pObj;
    if(pThis) {
        (pThis)->~CFunGame();
        free(pThis);
    }
}


void CFunGame::Initialize()
{
    InitGameResource();
    
    EnterGame();
}

void CFunGame::InitGameResource()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("base.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("boom.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("use.plist");
}

void CFunGame::EnterGame()
{
//    test 
    CCScene *pScene = StartLayer::createScene();
    
    if (CCDirector::sharedDirector()->getRunningScene() == NULL) {
        CCDirector::sharedDirector()->runWithScene(pScene);
    } else {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void CFunGame::handlePause()
{
    //TODO:
}

void CFunGame::handleResume()
{
    //TODO:
}