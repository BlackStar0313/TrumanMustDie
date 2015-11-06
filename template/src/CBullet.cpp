//
//  Bullet.cpp
//  project
//
//  Created by peiyang  on 15/10/30.
//
//

#include <stdio.h>
#include "CBullet.h"


CBullet::CBullet() : m_direction(ccp(0,0))
{
}

CBullet::~CBullet()
{
    
}



bool CBullet::initWithFile(const char *filename)
{
    if (!CCSprite::initWithFile(filename))
    {
        return false;
    }
    return true;
}


CBullet* CBullet::create()
{
    CBullet *pBullet = new CBullet();
    if (pBullet && pBullet->init())
    {
        pBullet->autorelease();
        return pBullet;
    }
    CC_SAFE_DELETE(pBullet);
    return NULL;
}

CBullet* CBullet::create(const char *fileName)
{
    CBullet *pBullet = new CBullet();
    if (pBullet && pBullet->initWithFile(fileName))
    {
        pBullet->autorelease();
        return pBullet;
    }
    CC_SAFE_DELETE(pBullet);
    return NULL;
}

CBullet* CBullet::create(CBullet::m_type type)
{
    CBullet *pBullet = NULL;
    switch (type) {
        case Easy:
        {
            pBullet = CBullet::create("runeA_2.png");
            break;
        }
        case Middle:
        {
            pBullet = CBullet::create("runeA_4.png");
            break;
        }
        case Diffcult:
        {
            pBullet = CBullet::create("runeA_6.png");
            break;
        }
        default:
            break;
    }
    pBullet->setPosition(asUniversalInterface::randomPosition());
    if (pBullet)
    {
        return pBullet;
    }
    return NULL;
}


bool CBullet::init()
{
    return true;
}

void CBullet::setDirection(CCPoint point)
{
    m_direction.x = point.x;
    m_direction.y = point.y;
}

CCPoint CBullet::getDirection()
{
    return m_direction;
}

void CBullet::Rotate(float time, float angle)
{
    CCActionInterval *rotate = CCRotateTo::create(time, angle);
    this->runAction(rotate);
}

void CBullet::Boom()
{
    CCAnimation *animation = CCAnimation::create();
    
    for( int i=12; i<=24; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "%02d-1.png", i);
        animation->addSpriteFrameWithFileName(szName);
    }
    animation->setDelayPerUnit(1 / 60.0f);
    animation->setRestoreOriginalFrame(true);

    CCAnimate* boom = CCAnimate::create(animation);
    CCActionInterval *anction = CCSequence::create(boom, CCCallFunc::create(this, callfunc_selector(CBullet::removeMyself)), NULL);
    this->runAction(anction);
}

void CBullet::Move(float time, CCPoint position)
{
    CCActionInterval *move = CCMoveTo::create(time, position);
    this->runAction(move);
}

void CBullet::MoveToPosition(CCPoint positon)
{
    CCPoint diff = asUniversalInterface::calcDiff(positon, this->getPosition());
    this->setPosition(this->getPosition() + diff * 5);
}

//call back
void CBullet::removeMyself()
{
    this->removeFromParentAndCleanup(true);
}












