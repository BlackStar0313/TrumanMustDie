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
#include <time.h>
#define MAXACTION 8
#define RANDOM(a,b) (rand()%((b)-(a)) + (a))

USING_NS_CC;

class MainGameLayer : public cocos2d::CCLayer
{
public:
    MainGameLayer():num(1), m_pPlayer(NULL), m_pBullet(NULL) { }
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainGameLayer);
    
    
    
public:
    void setBackground();
    void LoadPlayer();
    void StraightMove();
    void RotateMove();
    void BezierMove();
    void speedMove();
    void speedMove2();
    bool followMove(CCTouch* pTouches, CCSprite *closeImage);
    void downMove();
    void randomBullet();
    
    void callBack(CCNode* pSender);
    void boom(CCNode* pSender);
    void isKill(CCNode* pSender);
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
    void updateCustom();
    void update(float dt);
private:
    int num;
    CCSprite *m_pPlayer;
    CCSprite *m_pBullet;
    CCPoint m_pCurrent;
    CCPoint m_pBulletTarget;
    CCPoint m_pPlayerTarget;
};



#endif /* MainGameLayer_h */


