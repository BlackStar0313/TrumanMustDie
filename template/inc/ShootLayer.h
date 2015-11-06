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
#include <time.h>
#include <math.h>
#include "GameOverLayer.h"
#include "GamePauseLayer.h"
#include "CBullet.h"
#include "CPlane.h"
#include "CBulletManager.h"

using namespace std;
USING_NS_CC;

class ShootLayer : public CCLayer
{
public:
    ShootLayer();
    
    virtual ~ShootLayer();
    
    virtual bool init();
    
    static CCScene* createScene();
    
    CREATE_FUNC(ShootLayer);
    
public:
    //初始化函数
    void setBackground();
    void createBullet();
    void createPlayer();
    void LoadGame();
    
    //schedule函数
    void calcScoreAndBullet();
    void update(float dt);
    void updateEverySecond();
    
    //click事件
    void pauseBtnClick(CCObject *pSender);
    
    //触屏事件
    bool ccTouchBegan(CCTouch *touch,CCEvent *event);
    void ccTouchMoved(CCTouch *touch,CCEvent *event);
    void ccTouchEnded(CCTouch *touch,CCEvent *event);
    
private:
    CPlane *m_pPlayer;
    CCPoint m_targetLocation;
    CCLabelBMFont* m_pScore;
    int m_difficulty;
    int m_bulletNum;
    int m_score;
    int m_second;
};


#endif /* ShootLayer_h */
