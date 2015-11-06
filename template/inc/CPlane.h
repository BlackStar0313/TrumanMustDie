//
//  CPlane.h
//  project
//
//  Created by peiyang  on 15/11/3.
//
//

#ifndef CPlane_h
#define CPlane_h
#include "cocos2d.h"
#include "asUniversalInterface.h"


USING_NS_CC;

class CPlane : public CCSprite
{
public:
    CPlane();
    ~CPlane();
    
    static CPlane* create();
    static CPlane* create(const char *);

    virtual bool init();
    
    virtual bool initWithFile(const char *fileName);
    
    void Move(float time, CCPoint position);
    
    void MoveToPosition(CCPoint positon);
};
#endif /* CPlane_h */

