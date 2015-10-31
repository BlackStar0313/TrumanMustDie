//
//  GamePauseLayer.h
//  project
//
//  Created by peiyang  on 15/10/29.
//
//

#ifndef GamePauseLayer_h
#define GamePauseLayer_h

#include "cocos2d.h"

USING_NS_CC;

class GamePauseLayer : public CCLayer
{
public:
    GamePauseLayer();
    ~GamePauseLayer();
    virtual bool init();
    static CCScene* createScene(CCRenderTexture *renderTexture);
    CREATE_FUNC(GamePauseLayer);
    
public:
    void playBtnClick(CCObject* pSender);
};

#endif /* GamePauseLayer_h */
