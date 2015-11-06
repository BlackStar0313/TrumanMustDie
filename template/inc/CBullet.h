//
//  Bullet.h
//  project
//
//  Created by peiyang  on 15/10/30.
//
//

#ifndef Bullet_h
#define Bullet_h

#include "cocos2d.h"
#include <stdio.h>
#include <math.h>
#include "string"
#include "asUniversalInterface.h"
#define PI 3.1415926
#define RANDOM(a,b) (rand()%((b)-(a)) + (a))

using namespace std;
USING_NS_CC;

class CBullet : public CCSprite
{
public:
    CBullet();
    
    virtual ~CBullet();
    
    enum m_type
    {
        empty = 0,
        Easy,
        Middle,
        Diffcult,
    };

    static CBullet* create();
    
    static CBullet* create(const char *filename);
    
    static CBullet* create(CBullet::m_type type);
    
    virtual bool initWithFile(const char *filename);
    
    virtual bool init();
    
    void Rotate(float time, float angle);
    
    void Boom();
    
    void Move(float time, CCPoint position);
    
    void MoveToPosition(CCPoint positon);
    
    void setDirection(CCPoint point);
    
    CCPoint getDirection();
    
    void removeMyself();
    
    
private:
    CCPoint m_direction;
};

#endif /* Bullet_h */
