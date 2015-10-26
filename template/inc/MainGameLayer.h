//
//  MainGameLayer.h
//  project
//
//  Created by peiyang  on 15/10/26.
//
//

#ifndef MainGameLayer_h
#define MainGameLayer_h

#include <cocos2d.h>
#define MAXACTION 2

USING_NS_CC;

class MainGameLayer : public cocos2d::CCLayer
{
public:
    MainGameLayer():num(1), p_player(NULL), p_bullet(NULL) { }
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainGameLayer);
    
    
    
public:
    void setBackground();
    void StraightMove();
    void RotateMove();
    void callBack(CCNode* _node);
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
private:
    int num;
    CCSprite *p_player;
    CCSprite *p_bullet;
};



#endif /* MainGameLayer_h */


