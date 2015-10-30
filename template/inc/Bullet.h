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

USING_NS_CC;

class Bullet : public CCSprite
{
public:
    Bullet();
    
    ~Bullet();
    
    int getKind();
    
    void setKind(int kind);
    
    CCPoint getTargetLocation();
    
    static CCSprite* create(int kind);
    
    void setTargetLocation(CCPoint temp);
private:
    int m_kind;
    
    CCPoint m_targetLocation;
};

#endif /* Bullet_h */
