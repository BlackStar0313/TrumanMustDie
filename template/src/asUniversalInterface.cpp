//
//  asUniversalInterface.cpp
//  project
//
//  Created by peiyang  on 15/11/4.
//
//

#include <stdio.h>
#include "asUniversalInterface.h"

asUniversalInterface::asUniversalInterface()
{
    
}

asUniversalInterface::~asUniversalInterface()
{
    
}

float asUniversalInterface::calcAngle(CCPoint pointA, CCPoint pointB)
{
    if ( (pointA.x - pointB.x != 0) && (pointA.y - pointB.y != 0) )
    {
        float x = pointA.x - pointB.x, y = pointA.y - pointB.y;
        //CCLOG("atan %f", atan(x / y) * 180 / PI);
        float angle = atan(x / y) * 180 / PI - 90;
        return angle;
    }
}

CCPoint asUniversalInterface::randomPosition()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    int direction = RANDOM(0, 3);
    switch (direction) {
        case 0:
        {
            return ccp(-20, RANDOM(-20, int(visibleSize.height + 20)));
            break;
        }
        case 1:
        {
            return ccp(RANDOM(-20, int(visibleSize.width)), visibleSize.height + 20);
            break;
        }
        case 2:
        {
            return ccp(visibleSize.width + 20, RANDOM(0, int(visibleSize.height + 20)));
            break;
        }
        default:
        {
            CCLOG("ccp(0, 0)\n");
            return ccp(0, 0);
            break;
        }
    }
}

int asUniversalInterface::randType()
{
    int kind = RANDOM(1, 4);
    return kind;
}

CCPoint asUniversalInterface::calcDiff(CCPoint pointA, CCPoint pointB)
{
    CCPoint diff = ccp(0, 0);
    float x = pointA.x - pointB.x;
    float y = pointA.y - pointB.y;
    if (x != 0 && y != 0)
    {
        double angle;
        
        angle = atan(y / x);
        diff.x = cos(angle);
        diff.y = sin(angle);
        if ((x < 0 && y < 0) || (x < 0 && y > 0))
        {
            diff.x = -diff.x;
            diff.y = -diff.y;
        }
    }
    return diff;
}


