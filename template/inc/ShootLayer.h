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
#include <List>
#define RANDOM(a,b) (rand()%((b)-(a)) + (a))
#define ABS(a) ((a) > 0 ? (a) : (-a))

using namespace std;
USING_NS_CC;

class ShootLayer : public CCLayer
{
public:
    ShootLayer();
    
    virtual ~ShootLayer();
    
    virtual bool init();
    
    static CCScene* createScene();
    
    void onEnter();
    
    void onExit();
    
    CREATE_FUNC(ShootLayer);
    
public:
    //初始化函数
    void setBackground();
    void createBullet();
    void createPlayer();
    void LoadGame();
    //CCAnimation* createAnimation(NGSTR pListName, int32 start, int32 end, NGSTR imgFormat, float delayPerUnit);
    
    //schedule函数
    void calcScoreAndBullet();
    void update(float dt);
    void updateEverySecond();
    void playMove();
    
    //callback函数
    void boom(CCNode *pSender);
    void remove(CCNode *pSender);
    
    //click事件
    void pauseBtnClick(CCObject *pSender);
    
    //触屏事件
    bool ccTouchBegan(CCTouch *touch,CCEvent *event);
    void ccTouchMoved(CCTouch *touch,CCEvent *event);
    void ccTouchEnded(CCTouch *touch,CCEvent *event);
    
private:
    CCSprite *m_pPlayer;
    CCPoint m_targetLocation;
    CCLabelTTF* m_pScore;
    int m_difficulty;
    int m_bulletNum;
    int m_score;
    int m_second;
    
    list<CCSprite*> m_pBulletArray;
    list<CCRect*> m_RectArray;
    //CCArray *m_pBulletArray;
    //CCArray *m_pRectArray;
//    CCArray *m_pEasyBulletArr;
//    CCArray *m_pCommonBulletArr;
//    CCArray *m_pDiffcultBulletArr;
    
};


#endif /* ShootLayer_h */
