//
//  Bullet.cpp
//  project
//
//  Created by peiyang  on 15/10/30.
//
//

#include <stdio.h>
#include "Bullet.h"

Bullet::Bullet() : m_kind(0)
{
    m_targetLocation = ccp(0, 0);
}

Bullet::~Bullet()
{
    
}

int Bullet::getKind()
{
    return m_kind;
}

void Bullet::setKind(int kind)
{
    this->m_kind = kind;
    return ;
}

CCPoint Bullet::getTargetLocation()
{
    return m_targetLocation;
}

void Bullet::setTargetLocation(CCPoint temp)
{
    m_targetLocation.x = temp.x;
    m_targetLocation.y = temp.y;
    return ;
}

CCSprite* Bullet::create(int kind)
{
    CCSprite *bullet = NULL;
    switch (kind) {
        case 1:
            bullet = CCSprite::create("bullet_02.png");
            break;
        case 2:
            bullet = CCSprite::createWithSpriteFrameName("runeA_2.png");
            break;
        case 3:
            bullet = CCSprite::createWithSpriteFrameName("runeA_4.png");
            break;
        default:
            break;
    }
    if ( !bullet )
    {
        return NULL;
    }
    return bullet;
}

