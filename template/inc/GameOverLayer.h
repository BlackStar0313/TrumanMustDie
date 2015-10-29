//
//  GameOverLayer.h
//  project
//
//  Created by peiyang  on 15/10/29.
//
//

#ifndef GameOverLayer_h
#define GameOverLayer_h

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public CCLayer
{
public:
    
    GameOverLayer();
    ~GameOverLayer();
    virtual bool init();
    static CCScene* createScene();
    CREATE_FUNC(GameOverLayer);
    
public:
    void restartBtnClick(CCObject *pSender);
};

#endif /* GameOverLayer_h */
