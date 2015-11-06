//
//  CPlane.cpp
//  project
//
//  Created by peiyang  on 15/11/3.
//
//

#include <stdio.h>
#include "CPlane.h"

CPlane::CPlane()
{
    
}

CPlane::~CPlane()
{
    
}

CPlane* CPlane::create()
{
    CPlane* pPlane = new CPlane();
    if (pPlane && pPlane->init())
    {
        pPlane->autorelease();
        return pPlane;
    }
    CC_SAFE_DELETE(pPlane);
    return NULL;
}

CPlane* CPlane::create(const char *fileName)
{
    CPlane* pPlane = new CPlane();
    if (pPlane && pPlane->initWithFile(fileName))
    {
        pPlane->autorelease();
        return pPlane;
    }
    CC_SAFE_DELETE(pPlane);
    return NULL;
}

bool CPlane::init()
{
    if ( !CCSprite::init() )
    {
        return false;
    }
    return true;
}

bool CPlane::initWithFile(const char *fileName)
{
    if ( !CCSprite::initWithFile(fileName) )
    {
        return false;
    }
    return true;
}

void CPlane::Move(float time, CCPoint position)
{
    CCActionInterval *move = CCMoveTo::create(time, position);
    this->runAction(move);
}

void CPlane::MoveToPosition(CCPoint position)
{
    CCPoint diff = asUniversalInterface::calcDiff(position, this->getPosition());
    this->setPosition(this->getPosition() + diff * 5);
}
