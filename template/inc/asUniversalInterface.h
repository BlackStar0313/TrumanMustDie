//
//  asUniversalInterface.h
//  project
//
//  Created by peiyang  on 15/11/4.
//
//

#ifndef asUniversalInterface_h
#define asUniversalInterface_h

#include "cocos2d.h"
#include <time.h>

#define RANDOM(a,b) (rand()%((b)-(a)) + (a))
#define PI 3.1415926
USING_NS_CC;

class asUniversalInterface
{
public:
    asUniversalInterface();
    ~asUniversalInterface();
    
    static CCPoint randomPosition();
    static int randType();
    static float calcAngle(CCPoint pointA, CCPoint pointB);
    static CCPoint calcDiff(CCPoint pointA, CCPoint pointB);

};

#endif /* asUniversalInterface_h */
