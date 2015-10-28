//
//  ShootLayer.h
//  project
//
//  Created by peiyang  on 15/10/28.
//
//

#ifndef __SHOOTLAYER_H__
#define __SHOOTLAYER_H__

#include <cocos2d.h>
#define RANDOM(a,b) (rand()%((b)-(a)) + (a))

USING_NS_CC;

class ShootLayer : public CCLayer
{
public:
    //ShootLayer() : m_pPlayer(NULL), m_difficulty(1), score(0), m_bulletNum(0), m_pEasyBulletArr(NULL),m_pCommonBulletArr(NULL),m_pDiffcultBulletArr(NULL)  {}
    
    ShootLayer() : m_pPlayer(NULL), m_difficulty(1), score(0), m_bulletNum(0) {
        m_targetLocation.x = 0;
        m_targetLocation.y = 0;
    }
    virtual ~ShootLayer() {}
    
    virtual bool init();
    
    static CCScene* scene();
    
    void onEnter();
    
    void onExit();
    
    CREATE_FUNC(ShootLayer);
    
public:
    //初始化函数
    void setBackground();
    void createBullet(int difficulte);
    void createPlayer();
    void LoadGame();
    
    //schedule函数
    void calcScore();
    void update(float dt);
    void addBulletNum();
    
    //callback函数
    void removeBullet(CCNode *pSender);
    
    //触屏事件
    bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    void ccTouchMoved(CCTouch* touch,CCEvent* event);
    void ccTouchEnded(CCTouch* touch,CCEvent* event);
    
private:
    CCSprite *m_pPlayer;
    CCPoint m_targetLocation;
    int m_difficulty;
    int m_bulletNum;
    int score;
    
//    CCArray *m_pEasyBulletArr;
//    CCArray *m_pCommonBulletArr;
//    CCArray *m_pDiffcultBulletArr;
};


#endif /* ShootLayer_h */
