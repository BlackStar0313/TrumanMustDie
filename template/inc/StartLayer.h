//
//  StartLayer.h
//  project
//
//  Created by peiyang  on 15/10/29.
//
//

#ifndef StartLayer_h
#define StartLayer_h

#include "cocos2d.h"


USING_NS_CC;

class StartLayer : public CCLayer
{
public:
    StartLayer();
    
    ~StartLayer();
    
    static CCScene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(StartLayer);
    
public:
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
};

#endif /* StartLayer_h */
